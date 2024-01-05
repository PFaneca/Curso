#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <ncurses.h>
#include "JogoUI.h"
#include <pthread.h>

#define ENABLE_LOGS 0






void mostraLabirinto(char mapa[NLIN][NCOL], WINDOW *janela)
{
    int linhas = NLIN;
    int colunas = NCOL;
    wclear(janela);
    // IMPRIME MUNDO
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            char avatar = mapa[i][j];

            if (avatar == 'B')
            {
                
                mvwaddch(janela, i, j, ' '); // mvwaddch para adicionar um caractere à janela
            }
            else
            {
                mvwaddch(janela, i, j, avatar); // mvwaddch para adicionar um caractere à janela
            }
        }
    }

    refresh();
    wrefresh(janela);
}


// para mutex_mapa
pthread_mutex_t mutex_mapa = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex_posicao_A = PTHREAD_MUTEX_INITIALIZER;
void enviarMensagemParaMotor(AtualizacaoJogadorA novaPosicao)
{
  
    int fd_envio = open(SERVER_JOGO_FIFO, O_WRONLY);
    /*if (fd_envio == -1)
    {
        perror("Erro ao abrir FIFO para escrita");
        exit(EXIT_FAILURE);
    }*/

    // Tente escrever no FIFO
    int sizew = write(fd_envio, &novaPosicao, sizeof(novaPosicao));

    if (sizew == -1)
    {
        perror("Erro ao escrever no FIFO");
        close(fd_envio);
        exit(EXIT_FAILURE);
    }

    close(fd_envio);
}
// Função para a thread que trata o teclado
void *trataTecladoThread(void *data)
{
    DADOST *pdadost = (struct DADOST *)data;
    // WINDOW *janela = (WINDOW *)arg;
    WINDOW *janelaLabirinto = pdadost->janelaLabirinto;
    WINDOW *janelaComandos = pdadost->janelaComandos;
    //Jogador jogador = pdadost->nomeJogador;
    while (1)
    {
        keypad(janelaLabirinto, TRUE);

        int tecla = wgetch(janelaLabirinto);
        char cmd[100];
        pthread_mutex_lock(&mutex_posicao_A);

        switch (tecla)
        {
        case KEY_UP:
            tecla = UP;
            break;
        case KEY_DOWN:
            tecla = DOWN;
            break;
        case KEY_LEFT:
            tecla = LEFT;
            break;
        case KEY_RIGHT:
            tecla = RIGHT;
            break;
        case ' ':
            echo(); // habilita a maneira como o utilizador visualiza o que escreve
            wclear(janelaComandos);
            wprintw(janelaComandos, "\n Comando> "); // utilizada para imprimir.
            //werase(janelaComandos);                  // Limpar a janelaBaixo
            wgetstr(janelaComandos, cmd);            // para receber do teclado uma string na "janelaBaixo" para a variavel comando

            verifica_comando(cmd);

            noecho(); // voltar a desabilitar o que o utilizador escreve
            wrefresh(janelaComandos);
            break;
        default:
            break;
             //tecla = wgetch(janelaTopo); 
        }

        AtualizacaoJogadorA novaPosicao;
        novaPosicao.direcao = tecla;
        novaPosicao.id = getpid();

        

        enviarMensagemParaMotor(novaPosicao);

        pthread_mutex_unlock(&mutex_posicao_A);

    }

    return NULL;
}

void verifica_comando(char *input)
{
    if (strlen(input) == 0)
        return;

    char straux[50];
    strcpy(straux, input);

    char delim[] = " \n"; // Modificado para incluir espaço como delimitador
    char *ptr = strtok(straux, delim);
    int cmd_len = (sizeof comandoss / sizeof(struct comando));
    for (int i = 0; i < cmd_len; ++i)
    {
        if (strcmp(comandoss[i].nome, ptr) == 0)
        {
            comandoss[i].func(input);
            return;
        }
    }
    printf("Comando desconhecido: %s\n", input);
}

void comandos_cmd(char *x)
{
    printf("Lista de comandos permitidos\n");
    for (int i = 0; i < (sizeof comandoss / sizeof(struct comando)); i++)
    {
        printf("%s -%s\n", comandoss[i].nome, comandoss[i].descricao);
    }
}

void mostrar_jogadores_cmd(Jogador jogador)
{   

    
}


//Retorna true se enviou mensagem com sucesso
/*bool enviarMensagemPrivada(char* utilizador, char* utilizadorDestino, char* mensagem) {
    char pipeName[100];
    sprintf(pipeName, MAILBOX_FIFO, utilizadorDestino);

    //Tenta conectar-se ao pipe do outro utilizador
    int fd = open(SERVER_JOGO_FIFO, O_RDWR);
    if(fd == -1) return false;

    MensagemPrivada mensagemPrivada;
    strcpy(mensagemPrivada.user_destino, utilizadorDestino);
    strcpy(mensagemPrivada.user_origem, utilizador);

    write(fd, &mensagemPrivada, sizeof(MensagemPrivada));
    close(fd);

    return true;
}  */

void enviar_msg_cmd(char *input)
{
    char delim[] = " \n";
    char *ptr = strtok(input, delim);

    if (ptr == NULL)
    {
        printf("Utilize o seguinte formato para o comando: msg <nome_utilizador> <mensagem>\n");
        return;
    }

    char *nomeUtilizador = strtok(NULL, delim);

    if (nomeUtilizador == NULL)
    {
        printf("Nome de utilizador ausente. Utilize o seguinte formato para o comando: msg <nome_utilizador> <mensagem>\n");
        return;
    }

    char *mensagem = strtok(NULL, ""); // Usamos NULL para continuar a partir da última posição

    if (mensagem == NULL)
    {
        printf("Mensagem ausente. Utilize o seguinte formato para o comando: msg <nome_utilizador> <mensagem>\n");
        return;
    }

    // Agora temos nome do utilizador em 'nomeUsuario' e a mensagem em 'mensagem'

    // Aqui você pode adicionar lógica para enviar a mensagem ao utilizador específico
    
    /*if(enviarMensagemPrivada(nomeOrigem, nomeUtilizador, mensagem)){
        printf("[SUCESSO] mensagem para '%s': '%s'\n", nomeUtilizador, mensagem);
    } else {
        printf("[ERRO] mensagem para '%s': '%s'\n", nomeUtilizador, mensagem);
    }*/
}

void sair_cmd()
{
    printf("Sair do jogo...\n");
    unlink(CLIENT_FIFO);
    exit(1);
}


/*void recebeMensagens(void *dados)
{
    DADOST *pdados = (DADOST *)dados; // cast
    MensagemPrivada msg;

    // Lê a mensagem do FIFO
    int fd_recebe = open(MAILBOX_FIFO, O_RDWR);
    if (fd_recebe == -1)
    {
        perror("Erro a abrir FIFO para leitura");
        exit(EXIT_FAILURE);
    }

    do
    {
        int size = read(fd_recebe, &msg, sizeof(msg));
        if (size == -1)
        {
            perror("Erro ao ler dados do pipe");
            exit(EXIT_FAILURE);
        }

        // Mostra a mensagem
        if (size > 0)
        {
            wclear(pdados->janelaComandos);
            wprintw(pdados->janelaComandos, "\nNova Mensagem de %s: %s", msg.user_origem, msg.mensagem);
        }

    } while (1);
    // Fecha o FIFO após a conclusão do loop
    close(fd_recebe);

    // Finaliza a thread
    pthread_exit(NULL);
}*/

void recebeMapa(void *dados)
{
    DADOST *pdados = (DADOST *)dados; // cast
    dataMsg msg;

    // Lê a mensagem do FIFO
    int fd_recebe = open(SERVER_FIFO, O_RDWR);
    if (fd_recebe == -1)
    {
        perror("Erro a abrir FIFO para leitura");
        exit(EXIT_FAILURE);
    }

    do
    {
        int size = read(fd_recebe, &msg.mapa, sizeof(msg.mapa));
        if (size == -1)
        {
            perror("Erro ao ler dados do pipe");
            exit(EXIT_FAILURE);
        }

        // Mostra o mapa
        if (size > 0)
        {
            mostraLabirinto(msg.mapa, pdados->janelaLabirinto);
            /* mvprintw(10, 12, "M");
            mvprintw(1, 10, " ----------  %c -----------   ", msg.mapa[10][11]);
            // TODO: meter dados dinâmicos
            mvprintw(NLIN + 5, 1, "Nivel: 1\tJogadores:Pedro,Martim\t Paredes:2\tBloqueios:1 "); */
        }

    } while (1);
    // Fecha o FIFO após a conclusão do loop
    close(fd_recebe);

    // Finaliza a thread
    pthread_exit(NULL);
}

void login(char *nome)
{

    dataMsg msgrecebida, msgenviar;
    msgenviar.idMsg = 1;
    strcpy(msgenviar.nome, nome);
    msgenviar.pid = getpid();
    int fd_envio = open(SERVER_FIFO, O_WRONLY);

    if (fd_envio == -1)
    {
        perror("Erro ao abrir FIFO para escrita");
        exit(EXIT_FAILURE);
    }

    // Tente escrever no FIFO
    int sizew = write(fd_envio, &msgenviar, sizeof(msgenviar));

    if (sizew == -1)
    {
        perror("Erro ao escrever no FIFO");
        close(fd_envio);
        exit(EXIT_FAILURE);
    }

    close(fd_envio);

    int fd_resposta = open(CLIENT_FIFO_FINAL, O_RDONLY);

    if (fd_resposta == -1)
    {
        perror("Erro ao abrir FIFO de resposta para leitura");
        exit(EXIT_FAILURE);
    }

    int sizeR = read(fd_resposta, &msgrecebida, sizeof(msgrecebida));

    if (sizeR == -1)
    {
        perror("Erro ao ler do FIFO de resposta");
        close(fd_resposta);
        exit(EXIT_FAILURE);
    }

    close(fd_resposta);

    printf("%s", msgrecebida.aviso);
}

/*void criarCaixaDeCorreio(char* nome) {
    char pipeName[100];
    sprintf(pipeName, MAILBOX_FIFO, nome);
    if (mkfifo(pipeName, 0666) == -1)
    {
        perror("Erro ao criar fifa para caixa de correio");
    }
}*/

int main(int argc, char *argv[])
{

    setbuf(stdout, NULL);
    sprintf(CLIENT_FIFO_FINAL, CLIENT_FIFO, getpid());
    if (mkfifo(CLIENT_FIFO_FINAL, 0666) == -1)
    {
        perror("Erro a abrir fifo ou fifo já existe");
    }
    //cria o fifo do SERVER_JOGO_FIFO
    if (mkfifo(SERVER_JOGO_FIFO, 0666) == -1)
    {
        perror("Erro a abrir fifo ou fifo já existe");
    }
    if (argc != 2)
    {
        printf("Erro do numero de argumentos\n");
        return -1;
    }
    DADOST dadost;
    char *nome = argv[1];
    
    login(nome);
    //criarCaixaDeCorreio(nome);

    initscr();
    cbreak();
    raw();
    noecho();
    attrset(A_DIM);

    pthread_t idThreadMapa;
    pthread_create(&idThreadMapa, NULL, (void *)&recebeMapa, (void *)&dadost);

    //pthread_t idThreadMensagens;
    //pthread_create(&idThreadMensagens, NULL, (void *)&recebeMensagens, (void *)&dadost);

    /* WINDOW *janelaBaixo = newwin(15, 82, 26, 1);
    WINDOW *janelaTopo = newwin(NLIN + 1, NCOL + 2, 3, 1);
    WINDOW *janelaMeio = newwin(1, 82, 25, 1); */

    WINDOW *janelaLabirinto = newwin(NLIN, NCOL, 0, 2);
    WINDOW *janelaComandos = newwin(2, 20, NLIN + 2, 2);

    dadost.janelaLabirinto = janelaLabirinto;
    dadost.janelaComandos = janelaComandos;
    //strcpy(dadost.nomeJogador, nome);

    pthread_t idTeclado;
    pthread_create(&idTeclado, NULL, (void *)&trataTecladoThread, (void *)&dadost);

    pthread_join(idTeclado, NULL); // Espera pela thread do teclado
    endwin();

    pthread_join(idThreadMapa, NULL);
    //pthread_join(idThreadMensagens, NULL);

    unlink(CLIENT_FIFO);
    //unlink(MAILBOX_FIFO);

    return 0;
}