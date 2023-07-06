;------------------------------------------------------------------------
;	Base para TRABALHO PRATICO - TECNOLOGIAS e ARQUITECTURAS de COMPUTADORES
;   
;	ANO LECTIVO 2022/2023
;--------------------------------------------------------------
; Demostra  o da navega  o do cursor do Ecran 
;
;		arrow keys to move 
;		press ESC to exit
;
;--------------------------------------------------------------

.8086
.model small
.stack 2048

dseg	segment para public 'data'


				; TEXTO BEM VINDO

	Bem_Vindo	db "Bem-vindo ao Jogo Ultimate-Tic-Tac-Toe!",13,10
				db "Prima qualquer tecla para continuar...!    ",13,10,'$'
				

	

		;Ficheiros
        Erro_Open       db      'Erro ao tentar abrir o ficheiro$'
        Erro_Ler_Msg    db      'Erro ao tentar ler do ficheiro$'
        Erro_Close      db      'Erro ao tentar fechar o ficheiro$'
        Fich         	db      'jogo.TXT',0
        HandleFich      dw      0
        car_fich        db      ?


		;Main

		Car				db	32	; Guarda um caracter do Ecran 
		Cor				db	7	; Guarda os atributos de cor do caracter
		POSy			        db	3	; a linha pode ir de [1 .. 25]
		POSx			        db	3	; POSx pode ir [1..80]
		
		introduzir_nome1            db      'Nome do Jogador 1: ','$'
		introduzir_nome2            db 	    'Nome do Jogador 2: ','$'
	  	Nome_Jogador1	            db		20 dup ('_'), '$'   ; Guarda o nome do jogador1
		Nome_Jogador2	            db		20 dup ('_'), '$'   ; Guarda o nome do jogador2
		
		jogador1_simbolo db '?'        ; Símbolo do jogador 1
		jogador2_simbolo db '?'        ; Símbolo do jogador 2
		
		jogador1msg     db       'Jogador 1 comeca o jogo!','$'
		jogador2msg     db	 'Jogador 2 comeca o jogo!','$'
		


		ultimo_num_aleat dw 0

		 board db 0, 0, 0, 0, 0, 0, 0, 0, 0 ; Representação do tabuleiro
    	player db 'X' ; Jogador atual ('X' ou 'O')

dseg	ends

cseg	segment para public 'code'
assume		cs:cseg, ds:dseg

;game started
start:

	; call set_game_pointer



;########################################################################
goto_xy	macro		POSx,POSy
		mov		ah,02h
		mov		bh,0		; numero da p gina
		mov		dl,POSx
		mov		dh,POSy
		int		10h
endm


;ROTINA PARA APAGAR ECRAN

apaga_ecran	proc
			mov		ax,0B800h
			mov		es,ax
			xor		bx,bx
			mov		cx,25*80
		
apaga:		mov		byte ptr es:[bx],' '
			mov		byte ptr es:[bx+1],7
			inc		bx
			inc 	bx
			loop	apaga
			ret
apaga_ecran	endp


;########################################################################
; IMP_FICH

IMP_FICH	PROC

		;abre ficheiro
        mov     ah,3dh
        mov     al,0
        lea     dx,Fich
        int     21h
        jc      erro_abrir
        mov     HandleFich,ax
        jmp     ler_ciclo

erro_abrir:
        mov     ah,09h
        lea     dx,Erro_Open
        int     21h
        jmp     sai_f

ler_ciclo:
        mov     ah,3fh
        mov     bx,HandleFich
        mov     cx,1
        lea     dx,car_fich
        int     21h
		jc		erro_ler
		cmp		ax,0		;EOF?
		je		fecha_ficheiro
        mov     ah,02h
		mov		dl,car_fich
		int		21h
		jmp		ler_ciclo

erro_ler:
        mov     ah,09h
        lea     dx,Erro_Ler_Msg
        int     21h

fecha_ficheiro:
        mov     ah,3eh
        mov     bx,HandleFich
        int     21h
        jnc     sai_f

        mov     ah,09h
        lea     dx,Erro_Close
        Int     21h
sai_f:	
		RET
		
IMP_FICH	endp		


;########################################################################
; LE UMA TECLA	

LE_TECLA	PROC
		
		mov		ah,08h
		int		21h
		mov		ah,0
		cmp		al,0
		jne		SAI_TECLA
		mov		ah, 08h
		int		21h
		mov		ah,1
SAI_TECLA:	RET
LE_TECLA	endp



;########################################################################
;NOME
Nome PROC
			
		; Exibir mensagem para o Jogador 1
    		lea dx,introduzir_nome1
		mov ah, 09
    		int 21h

    		; Ler o nome do Jogador 1
    		mov ah, 0Ah
    		lea dx,  nome_jogador1
		int 21h
			
		;Quebra de linha
		mov dl, 13 ; caractere de retorno de carro
		mov ah, 02h
		int 21h
		mov dl, 10 ; caractere de alimentação de linha
		int 21h
			
			
		; Exibir mensagem para o Jogador 2
    		lea dx,introduzir_nome2
		mov ah, 09
    		int 21h

    		; Ler o nome do Jogador 2
    		mov ah, 0Ah
    		lea dx, nome_jogador2
		int 21h

			

		; Gerar um número aleatório entre 0 e 1 para determinar qual jogador receberá 'X' ou 'O'
    		mov ah, 2Ch     ; Função de gerar número aleatório do DOS
    		int 21h         ; Gerar número aleatório
    		and dx, 0001h   ; Obter o bit menos significativo para determinar o jogador inicial

    		; Associar os símbolos aos jogadores com base no número aleatório
    		cmp dx, 0      ; Se o número aleatório for 0
    		je jogador1_recebe_x
    		mov byte ptr jogador1_simbolo, 'O'
    		mov byte ptr jogador2_simbolo, 'X'
			jogador_atual_simbolo db '?'        ; Símbolo do jogador atual
            jogador_atual db '?'                ; Identificador do jogador atual
			jogador_atual_msg db 20 DUP('$')	; Mensagem do jogador atual
   		jmp continuar

jogador1_recebe_x:
    		mov byte ptr jogador1_simbolo, 'X'
    		mov byte ptr jogador2_simbolo, 'O'

continuar:
    ; Exibir mensagem informando qual jogador começa o jogo
		;Quebra de linha
		mov dl, 13 ; caractere de retorno de carro
		mov ah, 02h
		int 21h
		mov dl, 10 ; caractere de alimentação de linha
		int 21h

	
    cmp dx, 0
    je jogador1_comeca
    lea dx, jogador2msg
    jmp exibir_mensagem

jogador1_comeca:
    lea dx, jogador1msg

exibir_mensagem:
    mov ah, 09h
    int 21h

			
    ret
NOME endp
;########################################################################
;VERIFICA SE O JOGADOR GANHOU O TABULEIRO PRINCIPAL OU NAO
VERIFICA_GANHOU PROC
    push ax
    push bx
    push cx
    push dx
    push si
    push di

    ; Define as coordenadas iniciais do tabuleiro principal
    mov si, 7    ; Linha inicial
    mov di, 56   ; Coluna inicial

    ; Verifica as possíveis combinações de vitória
    mov ax, si                 ; Move o valor de SI para AX
    add ax, si                 ; Adiciona SI ao valor de AX
    add ax, ax                 ; Multiplica AX por 4 para obter o deslocamento em bytes
    add ax, ax                 ; Multiplica AX por 4 novamente (total de 16 bytes por linha)
    add ax, di                 ; Adiciona DI ao valor de AX

    mov bx, ax                 ; Move o valor de AX para BX para ser usado como índice de memória

    mov ax, es                 ; Move o valor do segmento de dados (ES) para AX
    mov ds, ax                 ; Carrega o valor de AX novamente em DS para acessar a memória correta

    movsb                      ; Lê um byte da memória em [BX] e armazena em AL


    ; Obtém o jogador da célula superior esquerda
    mov dx, 0                 ; Flag indicando se o jogador ganhou (0 = não ganhou, 1 = ganhou)

    ; Verifica as linhas
    mov bx, si
    add bx, bx                 ; Multiplica BX por 2 para obter o deslocamento em bytes
    add bx, bx                 ; Multiplica BX por 2 novamente (total de 4 bytes por célula)
    add bx, di
    cmp al, byte ptr [bx]
    jne proxima_combinacao

    add bx, 16                 ; Adiciona 16 para avançar para a próxima célula na mesma linha
    cmp al, byte ptr [bx]
    jne proxima_combinacao

    add bx, 16                 ; Adiciona 16 novamente para avançar para a próxima célula na mesma linha
    cmp al, byte ptr [bx]
    je jogador_ganhou

    ; Verifica as colunas
    mov bx, si
    add bx, bx                 ; Multiplica BX por 2 para obter o deslocamento em bytes
    add bx, bx                 ; Multiplica BX por 2 novamente (total de 4 bytes por célula)
    add bx, di
    add bx, 2                  ; Avança para a próxima coluna
    cmp al, byte ptr [bx]
    jne proxima_combinacao

    add bx, 4                  ; Avança mais 4 bytes para a próxima célula na mesma coluna
    cmp al, byte ptr [bx]
    jne proxima_combinacao

    add bx, 4                  ; Avança mais 4 bytes para a próxima célula na mesma coluna
    cmp al, byte ptr [bx]
    je jogador_ganhou

    ; Verifica as diagonais
    mov bx, si
    add bx, bx                 ; Multiplica BX por 2 para obter o deslocamento em bytes
    add bx, bx                 ; Multiplica BX por 2 novamente (total de 4 bytes por célula)
    add bx, di
    cmp al, byte ptr [bx]
    jne proxima_combinacao

    add bx, 18                 ; Avança 18 bytes para a próxima célula na diagonal
    cmp al, byte ptr [bx]
    jne proxima_combinacao

    add bx, 18                 ; Avança mais 18 bytes para a próxima célula na diagonal
    cmp al, byte ptr [bx]
    je jogador_ganhou

    mov bx, si
    add bx, bx                 ; Multiplica BX por 2 para obter o deslocamento em bytes
    add bx, bx                 ; Multiplica BX por 2 novamente (total de 4 bytes por célula)
    add bx, di
    add bx, 32                 ; Avança 32 bytes para a próxima célula na diagonal inversa
    cmp al, byte ptr [bx]
    jne proxima_combinacao

    sub bx, 30                 ; Subtrai 30 bytes para voltar à célula anterior na diagonal inversa
    cmp al, byte ptr [bx]
    jne proxima_combinacao

    sub bx, 30                 ; Subtrai mais 30 bytes para voltar à célula inicial na diagonal inversa
    cmp al, byte ptr [bx]
    je jogador_ganhou

    ; Jogador não ganhou
    jmp fim_verificacao

jogador_ganhou:
    ; Jogador ganhou
    mov dx, 1

    ; Armazena o símbolo do jogador que ganhou
    cmp al, 'X'
    je jogador1_ganhou
    mov [jogador2_simbolo], al
    jmp fim_verificacao

jogador1_ganhou:
    mov [jogador1_simbolo], al

proxima_combinacao:
    ; Aqui, o valor de DX indica se o jogador ganhou (0 = não ganhou, 1 = ganhou)

fim_verificacao:
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax

    ret
VERIFICA_GANHOU ENDP


;########################################################################
;EXIBE MENSAGEM DE VITORIA
; Declaração das variáveis
jogador1_simbolo db ?
jogador2_simbolo db ?

VERIFICA_GANHOU
cmp dx, 1   ; Verifica se o jogador ganhou (valor de DX igual a 1)
jne nao_ganhou

; Jogador 1 ganhou
mov ah, 09h
mov dx, offset mensagem_jogador1
int 21h
jmp fim_mensagem

nao_ganhou:
; Jogador 2 ganhou
mov ah, 09h
mov dx, offset mensagem_jogador2
int 21h

fim_mensagem:
...

; Mensagens de felicitação aos jogadores
mensagem_jogador1 db "Parabéns Jogador 1! Ganhou o jogo!", 0
mensagem_jogador2 db "Parabéns Jogador 2! Ganhou o jogo!", 0
;########################################################################
;TABELA DE MINI TABULEIROS BLOQUEADOS
TAB_BLOQUEADO db 9 dup(0)  ; Tabela para armazenar o estado de bloqueio dos mini-tabuleiros

; Inicializa a tabela TAB_BLOQUEADO
mov si, offset TAB_BLOQUEADO
mov cx, 9  ; Número total de mini-tabuleiros
mov al, DESBLOQUEADO  ; Valor inicial de desbloqueio dos mini-tabuleiros

inicializa_tab_bloqueado:
    mov [si], al  ; Armazena o valor de desbloqueio na tabela
    inc si  ; Avança para o próximo elemento da tabela
    loop inicializa_tab_bloqueado

DESBLOQUEADO equ 0  ; Valor para indicar que o mini-tabuleiro está desbloqueado
BLOQUEADO equ 1    ; Valor para indicar que o mini-tabuleiro está bloqueado

JOGA proc
    ; Verifica se o mini-tabuleiro já foi bloqueado
    mov bx, offset TAB_BLOQUEADO
    add bx, dx
    mov al, [bx]  ; Carrega o valor do mini-tabuleiro em AL
    cmp al, BLOQUEADO
    je fim_joga
	; Verifica se o mini-tabuleiro já foi ganho
    push dx  ; Salva o valor de dx para uso posterior
    call VERIFICA_MINI_GANHOU
    pop dx   ; Restaura o valor original de dx
	cmp dx, VERIFICA_MINI_GANHOU
	je bloqueia_mini_tabuleiro
fim_joga:
    ret

bloqueia_mini_tabuleiro:
    ; Marca o mini-tabuleiro como bloqueado na tabela correspondente
    mov bx, offset TAB_BLOQUEADO
    add bx, dx
    mov byte ptr [bx], BLOQUEADO
	jmp fim_joga
JOGA endp



;########################################################################
;VERIFICA 	SE O JOGADOR GANOU UM MINI TABULEIRO

VERIFICA_MINI_GANHOU PROC
    ; Verifica se o jogador ganhou na horizontal
    mov ax, 0B800h  ; Endereço de memória de vídeo para o modo de texto colorido do DOS/VGA
    mov es, ax      ; Configura o segmento de destino para o segmento de memória de vídeo
    mov bx, 0       ; Posição inicial do cursor no mini tabuleiro (primeiro caractere)
    mov cx, 3       ; Número de caracteres por linha no mini tabuleiro
    mov dx, 0       ; Inicializa dx como 0 (nenhum mini tabuleiro ganho)

    ; Compara os caracteres na mesma linha do mini tabuleiro
    mov al, es:[bx]       ; Caractere na posição atual
    mov dl, es:[bx+2]     ; Caractere na posição atual
    cmp al, es:[bx+160]  ; Compara o caractere na próxima linha
    jne nao_ganhou        ; Se não for igual, pula para a etiqueta "nao_ganhou"
    cmp dl, es:[bx+162]  ; Compara o caractere na próxima linha
    jne nao_ganhou        ; Se não for igual, pula para a etiqueta "nao_ganhou"

    ; Se todas as comparações forem iguais, o jogador ganhou na horizontal
    mov dx, 1       ; Define dx como 1 (indica que o jogador ganhou no mini tabuleiro 1)
    jmp atualiza_tabuleiro

nao_ganhou:
    ; Verifica se o jogador ganhou na vertical
    mov bx, 160     ; Posição inicial do cursor na próxima linha (primeiro caractere)
    mov al, es:[bx]       ; Caractere na posição atual
    mov dl, es:[bx+2]     ; Caractere na posição atual
    cmp al, es:[bx+160]  ; Compara o caractere na próxima linha
    jne nao_ganhou2       ; Se não for igual, pula para a etiqueta "nao_ganhou2"
    cmp dl, es:[bx+162]  ; Compara o caractere na próxima linha
    jne nao_ganhou2       ; Se não for igual, pula para a etiqueta "nao_ganhou2"

    ; Se todas as comparações forem iguais, o jogador ganhou na vertical
    mov dx, 2       ; Define dx como 2 (indica que o jogador ganhou no mini tabuleiro 2)
    jmp atualiza_tabuleiro

nao_ganhou2:
    ; Verifica se o jogador ganhou na diagonal
    mov bx, 320     ; Posição inicial do cursor na próxima linha (primeiro caractere)
    mov al, es:[bx]       ; Caractere na posição atual
    mov dl, es:[bx+2]     ; Caractere na posição atual
    cmp al, es:[bx+160]  ; Compara o caractere na próxima linha
    jne nao_ganhou3       ; Se não for igual, pula para a etiqueta "nao_ganhou3"
    cmp dl, es:[bx+162]  ; Compara o caractere na próxima linha
    jne nao_ganhou3       ; Se não for igual, pula para a etiqueta "nao_ganhou3"

    ; Se todas as comparações forem iguais, o jogador ganhou na diagonal
    mov dx, 3       ; Define dx como 3 (indica que o jogador ganhou no mini tabuleiro 3)
    jmp atualiza_tabuleiro

nao_ganhou3:
    ; Se nenhuma das verificações anteriores foi bem-sucedida, nenhum mini tabuleiro foi ganho
    mov dx, 0       ; Define dx como 0 (indica que nenhum mini tabuleiro foi ganho)

atualiza_tabuleiro:
    ; Calcula o deslocamento para o início do tabuleiro geral
    mov bx, 56    ; Coluna inicial do tabuleiro geral
    sub bx, 1     ; Ajusta o deslocamento para a posição correta
    shl bx, 1     ; Multiplica o deslocamento por 2 para considerar os caracteres e atributos

    ; Calcula o deslocamento para a linha correta do tabuleiro geral
    mov cx, 7     ; Linha inicial do tabuleiro geral
    sub cx, 3     ; Ajusta o deslocamento para a posição correta
    mov dx, 160   ; Valor imediato a ser multiplicado
    mul cx        ; Multiplica o deslocamento pela largura da linha (160 caracteres)

    ; Adiciona os deslocamentos para obter o endereço de destino do tabuleiro geral
    add bx, dx    ; Endereço da coluna do tabuleiro geral

    ; Preenche o espaço correspondente no tabuleiro geral com o caractere correspondente ao mini-tabuleiro ganho
    mov al, dl    ; Move o valor do mini-tabuleiro para AL
    mov es:[bx], al   ; Preenche o caractere do mini-tabuleiro no tabuleiro geral

    ; Define a cor de fundo do caractere
    mov ah, 09h   ; Função 09h da interrupção 10h do DOS (exibe caractere com atributos)
    mov bh, 00h   ; Página de exibição
    mov bl, 1Fh   ; Cor de fundo (por exemplo, azul)
    mov cx, 1     ; Número de repetições (1 caractere)

    int 10h       ; Chama a interrupção de vídeo do DOS para exibir o caractere com a cor de fundo

    ret            ; Retorna do procedimento VERIFICA_MINI_GANHOU
VERIFICA_MINI_GANHOU endp

;########################################################################
;SE O JOGADOR GANHOU UM MINI TABULEIRO ACRESCENTA O SIMBOLO DELE NO TABULEIRO GERAL

;########################################################################
;SE O JOGADOR GANHAR UM MINI TABULEIRO; ESSE MINI TABULEIRO FICA FECHADO SEM PODER SER JOGADO OU NAVEGADO
;FECHA_MINI_TABULEIRO PROC
		;call VERIFICA_MINI_GANHOU
		
		;ret
; ACRESCE O SIMBOLO DO JOGADOR NO TABULEIRO GERAL QUANDO O JOGADOR GANHA UM MINI TABULEIRO

		
;########################################################################
MENSAGEM PROC 
    ; Exibir mensagem com o resultado final (nomes e associação dos símbolos)
    
    ; Exibir nome do jogador 1
    lea dx, nome_jogador1
    mov ah, 09h
    int 21h
    ; Exibir nome do jogador 2
    lea dx, nome_jogador2
    mov ah, 09h
    int 21h
    RET
MENSAGEM endp
;########################################################################
; Avatar
AVATAR	PROC
			mov		ax,0B800h
			mov		es,ax





CICLO:		
			
			goto_xy	POSx,POSy		; Vai para nova possi  o
			mov 	ah, 08h
			mov		bh,0			; numero da p gina
			int		10h		
			mov		Car, al			; Guarda o Caracter que est  na posi  o do Cursor
			mov		Cor, ah			; Guarda a cor que est  na posi  o do Cursor
		
			goto_xy	78,0			; Mostra o caractr que estava na posi  o do AVATAR
			mov		ah, 02h			; IMPRIME caracter da posi  o no canto
			mov		dl, Car	
			int		21H			
	
			goto_xy	POSx,POSy	; Vai para posicao do cursor
		
LER_SETA:	call 	LE_TECLA
			cmp		ah, 1
			je		ESTEND
			CMP 	AL, 27		; ESCAPE = 27
			JE		FIM
			CMP 	AL, 13		; ENTER = 13
			JNE		LER_SETA

			goto_xy	POSx,POSy 	; verifica se pode escrever o caracter no ecran
			mov		CL, Car
			cmp		CL, 32		; So  escreve se for espaco em branco
			JNE 	LER_SETA
			mov		ah, 02h	; coloca o caracter lido no ecra
            ;faz colocar X ou O consoante o simbolo do jogador
			; Verificar qual jogador está atualmente a jogar
			;cmp jogador_atual, '1'
            ;jne JOGADOR2
            ;cmp jogador1_simbolo, 'O'
            ;jne JOGADOR1_X
            ;mov dl, 'O'
            ;int 21h
			;goto_xy	POSx,POSy
			;jmp		LER_SETA
			; Verificar qual jogador está atualmente a jogar
            cmp jogador_atual, '1'
            jne JOGADOR2
            cmp jogador1_simbolo, 'O'
            je JOGADOR1_O
            mov dl, 'X'
            jmp ESCREVER_SIMBOLO

JOGADOR1_O:
            mov dl, 'O'
            mov jogador_atual, '2'  ; Alterna para o jogador 2
            jmp ESCREVER_SIMBOLO

JOGADOR2:
            cmp jogador2_simbolo, 'O'
            je JOGADOR2_O
            mov dl, 'X'
            jmp ESCREVER_SIMBOLO

JOGADOR2_O:
            mov dl, 'O'
			mov jogador_atual, '1'  ; Alterna para o jogador 1
            jmp ESCREVER_SIMBOLO

ESCREVER_SIMBOLO:
            mov [jogador_atual_simbolo], dl   ; Armazena o símbolo do jogador atual
            mov ah, 02h
            int 21h

            
            jmp LER_SETA   



		
ESTEND:		cmp 	al,48h
			jne		BAIXO
			dec		POSy		;cima
			jmp		CICLO

BAIXO:		cmp		al,50h
			jne		ESQUERDA
			inc 	POSy		;Baixo
			jmp		CICLO

ESQUERDA:
			cmp		al,4Bh
			jne		DIREITA
			dec		POSx		;Esquerda
			jmp		CICLO

DIREITA:
			cmp		al,4Dh
			jne		LER_SETA 
			inc		POSx		;Direita
			jmp		CICLO

fim:				
			RET
AVATAR		endp
;########################################################################
Main  proc
		mov			ax, dseg
		mov			ds,ax
		
		mov			ax,0B800h
		mov			es,ax
		
		call		apaga_ecran
		
		goto_xy		0,0
		call		IMP_FICH
		
		goto_xy		0,20  ;NOME
		call		NOME
		
		call 		AVATAR
		goto_xy		0,22
		
		mov			ah,4CH
		INT			21H
		

	

	
Main	endp
Cseg	ends
end	Main


		
