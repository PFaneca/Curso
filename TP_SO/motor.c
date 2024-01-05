#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include "motor.h"
#include <ncurses.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/select.h>

#define ENABLE_LOGS 0




char CLIENT_FIFO_FINAL[100];
char mapa[NLIN][NCOL];
// para comecar o jogo
bool jogoComecou = false;
// Nova variável para indicar encerramento do jogo
bool encerrarJogo = false; 
// Variável para indicar o nivel inicial do jogo
int nivel = 1;

typedef struct
{
    WINDOW *xpto;
    int trinco;

} DADOST;

typedef struct
{
    int x;
    int y;
} Posicao;

typedef struct
{
    int x;
    int y;
    int duracaoBloqueio;
} Bloqueio;
typedef struct
{
    int direcao;
    int id;
} AtualizacaoJogadorA;


Jogador listaClientes[MAXUTILIZADORES] = {0};
Posicao posicaoVencedora;


//Obtém letra correspondente ao índice 
char gerarLetra(int index)
{
    // TODO: refactor
    // Assuming the input index is a non-negative integer
    if (index >= 0 && index < 26)
    {
        // ASCII value of 'A' is 65, so adding the index to it gives the desired character
        return 'A' + index;
    }
    else
    {
        // Handle the case when the index is out of range
        return '?'; // You can choose a different character to represent an error, or handle it differently
    }
}


// Coloca o jogador na posição inicial
void colocarJogadorNaPosicaoInicial(Jogador jogador)
{
    for (int i = 0; i < NLIN; i++)
    {
        for (int j = 1; j < NCOL; j++)
        {
            if (mapa[NLIN - 1][j] == ESPACO_EM_BRANCO)
            {
                mapa[NLIN - 1][j] = jogador.letra;
                return;
            }
        }
    }
}

pthread_mutex_t mutex_listaClientes = PTHREAD_MUTEX_INITIALIZER;
// Adiciona um novo cliente à lista de clientes
int verificaCliente(char *nome, int pid)
{
    pthread_mutex_lock(&mutex_listaClientes);

    for (int i = 0; i < MAXUTILIZADORES; i++)
    {
        if (listaClientes[i].ocupado && strcmp(nome, listaClientes[i].nome) == 0)
        {

            pthread_mutex_unlock(&mutex_listaClientes);
            return 1; // Nome já existe
        }
    }

    for (int i = 0; i < MAXUTILIZADORES; i++)
    {
        if (!listaClientes[i].ocupado)
        {
            // Cria jogador
            listaClientes[i].letra = gerarLetra(i);
            listaClientes[i].ocupado = 1;
            listaClientes[i].pid = pid;
            strcpy(listaClientes[i].nome, nome);

            // Coloca no mapa
            colocarJogadorNaPosicaoInicial(listaClientes[i]);

            pthread_mutex_unlock(&mutex_listaClientes);
            return 0; // Cliente adicionado com sucesso
        }
    }

    pthread_mutex_unlock(&mutex_listaClientes);
    return -1;
}
void *login(void *dados)
{
    dataMsg *pdados = (dataMsg *)dados;
    fd_set read_fds;
    struct timeval tv;
    dataMsg msgrecebida, msgenviar;
    char mensagemrecebida[100];
    pid_t ultimoCliente = 0;
    int nJogadores = 0;

    msgrecebida.idMsg = 1;

    char *inscricao_str = getenv("INSCRICAO");
    char *nplayers_str = getenv("NPLAYERS");

    // Verifica se as variáveis de ambiente INSCRICAO e NPLAYERS existem
    if (inscricao_str == NULL || nplayers_str == NULL)
    {
        printf("Erro: Variáveis de ambiente não encontradas.\n");
        exit(EXIT_FAILURE);
    }

    // Converte as strings para números inteiros
    int tempoInscricao = atoi(inscricao_str);
    int minimo_jogadores = atoi(nplayers_str);

    int fd_receber_jog = open(SERVER_FIFO, O_RDONLY);
    if (fd_receber_jog == -1)
    {
        perror("Erro a abrir FIFO para leitura");
        exit(EXIT_FAILURE);
    }

    tv.tv_sec = tempoInscricao;
    tv.tv_usec = 0;

    while (tempoInscricao > 0 && nJogadores < MAXUTILIZADORES && !jogoComecou)
    {
        FD_ZERO(&read_fds);
        FD_SET(fd_receber_jog, &read_fds);

        // Aguarda até que haja dados para ler no FIFO ou até que o tempo de inscrição expire
        int retval = select(fd_receber_jog + 1, &read_fds, NULL, NULL, &tv);

        if (retval == -1)
        {
            perror("Erro na chamada select");
            exit(EXIT_FAILURE);
        }
        else if (retval > 0 && FD_ISSET(fd_receber_jog, &read_fds))
        {
            int sizeR = read(fd_receber_jog, &msgrecebida, sizeof(msgrecebida));
            if (sizeR > 0 && msgrecebida.pid != ultimoCliente)
            {

                ultimoCliente = msgrecebida.pid;
                printf("\nUtilizador %s entrou no jogo\n", msgrecebida.nome);
                int v = verificaCliente(msgrecebida.nome, msgrecebida.pid);

                char CLIENT_FIFO_FINAL[20];
                sprintf(CLIENT_FIFO_FINAL, CLIENT_FIFO, msgrecebida.pid);
                int fd_resposta = open(CLIENT_FIFO_FINAL, O_WRONLY | O_NONBLOCK);

                if (v == 1)
                {
                    strcpy(msgenviar.aviso, "Nome de Jogador já existe\n");
                }
                else if (v == 0)
                {
                    strcpy(msgenviar.aviso, "Adicionado com sucesso. Aguarde!\n");
                    nJogadores++;
                }
                else if (v == -1)
                {
                    strcpy(msgenviar.aviso, "Não existem mais vagas\n");
                }

                write(fd_resposta, &msgenviar, sizeof(msgenviar));
                close(fd_resposta);
            }
        }
        else
        {
            printf("Tempo de inscrição expirado ou nenhum jogador adicionado.\n");
            break;
        }
    }

    /*if (nJogadores >= minimo_jogadores)
    {
        printf("Temos um mínimo de jogadores. Iniciando o jogo...\n");
        // Inicie o jogo aqui...
    }
    else
    {
        printf("Número mínimo de jogadores não atingido. Encerrando o servidor...\n");
        // Encerre o servidor ou tome a ação apropriada se o número mínimo de jogadores não for atingido
    }*/

    close(fd_receber_jog);
    pthread_exit(NULL);
}

void termina(int s, siginfo_t *i, void *v)
{
    encerrarJogo = true;
    for (int i = 0; i < MAXUTILIZADORES; i++)
    {
        if (listaClientes[i].ocupado)
            kill(listaClientes[i].pid, SIGINT);
    }

    unlink(SERVER_FIFO);
    unlink(SERVER_JOGO_FIFO);
    printf("\nAdeus\n");
    exit(1);
}

void lerLabirinto(char *nome)
{
    FILE *arquivo = fopen(nome, "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Lê o labirinto do arquivo
    for (int i = 0; i < NLIN; i++)
    {
        int j = 0;
        int c;
        while ((c = fgetc(arquivo)) != EOF && c != '\n')
        {
            if (c == 'B')
            {
                mapa[i][j] = ESPACO_EM_BRANCO; // Substitui  'B' por espaços brancos
            }
            else
            {
                mapa[i][j] = c;
            }
            j++;
        }

        mapa[i][j] = '\0'; // Adiciona terminador de string
    }

    fclose(arquivo);
}

void mostraLabirinto()
{
    int linhas = NLIN;
    int colunas = NCOL;

    // IMPRIME MUNDO
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            char avatar = mapa[i][j];

            if (avatar == 'B')
            {
                printf("");
            }
            else
            {
                printf("%c", avatar);
            }
        }
        printf("\n");
    }
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
            if (strcmp(ptr, "test_bot") == 0)
            {
                comandoss[i].func(NULL);
                return;
            }
            else
            {
                comandoss[i].func(input);

                return;
            }
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
void enviaMapaParaJogoUi()
{
    dataMsg dataMapa;
    int fd = open(SERVER_FIFO, O_WRONLY | O_NONBLOCK);

    write(fd, mapa, sizeof(mapa));
    close(fd);
}

// Mutex para controlar o acesso ao mapa
pthread_mutex_t mapa_mutex = PTHREAD_MUTEX_INITIALIZER;
// Coordenadas do entupimento móvel
int entupimentoX, entupimentoY;
// Função para verificar se uma célula é bloqueada
int estaBloqueada(int x, int y)
{
    return (mapa[x][y] != ESPACO_EM_BRANCO);
}
int removerEntupimento = 0;
// Função para gerar entupimentos móveis
void *geraEntupimento(void *arg)
{
    srand(time(NULL));
    int *thread_id = (int *)arg;

    while (1)
    {
        if (removerEntupimento)
        {
            // Se a variável indicar para remover, sai do loop
            break;
        }
        pthread_mutex_lock(&mapa_mutex);

        // Remova o entupimento móvel da posição anterior
        mapa[entupimentoX][entupimentoY] = ESPACO_EM_BRANCO;

        // Gere uma direção de movimento aleatória
        int direction = rand() % 8;

        // Atualize as coordenadas com base na direção de movimento
        switch (direction)
        {
        case UP:
            entupimentoX = (entupimentoX - 1 + NLIN) % NLIN;
            break;
        case DOWN:
            entupimentoX = (entupimentoX + 1) % NLIN;
            break;
        case LEFT:
            entupimentoY = (entupimentoY - 1 + NCOL) % NCOL;
            break;
        case RIGHT:
            entupimentoY = (entupimentoY + 1) % NCOL;
            break;
        case UP_LEFT:
            entupimentoX = (entupimentoX - 1 + NLIN) % NLIN;
            entupimentoY = (entupimentoY - 1 + NCOL) % NCOL;
            break;
        case UP_RIGHT:
            entupimentoX = (entupimentoX - 1 + NLIN) % NLIN;
            entupimentoY = (entupimentoY + 1) % NCOL;
            break;
        case DOWN_LEFT:
            entupimentoX = (entupimentoX + 1) % NLIN;
            entupimentoY = (entupimentoY - 1 + NCOL) % NCOL;
            break;
        case DOWN_RIGHT:
            entupimentoX = (entupimentoX + 1) % NLIN;
            entupimentoY = (entupimentoY + 1) % NCOL;
            break;
        }
        // Verifica se a nova posição está bloqueada
        while (entupimentoY == 0 || estaBloqueada(entupimentoX, entupimentoY))
        {
            // Se estiver bloqueada, escolhe outra direção aleatória

            if (entupimentoY == 0)
            {
                direction = rand() % 7;
            }
            else
            {
                direction = rand() % 8;
            }
            // Atualiza as coordenadas com base na nova direção de movimento
            switch (direction)
            {
            case UP:
                entupimentoX = (entupimentoX - 1 + NLIN) % NLIN;
                break;
            case DOWN:
                entupimentoX = (entupimentoX + 1) % NLIN;
                break;
            case LEFT:
                entupimentoY = (entupimentoY - 1 + NCOL) % NCOL;
                break;
            case RIGHT:
                entupimentoY = (entupimentoY + 1) % NCOL;
                break;
            case UP_LEFT:
                entupimentoX = (entupimentoX - 1 + NLIN) % NLIN;
                entupimentoY = (entupimentoY - 1 + NCOL) % NCOL;
                break;
            case UP_RIGHT:
                entupimentoX = (entupimentoX - 1 + NLIN) % NLIN;
                entupimentoY = (entupimentoY + 1) % NCOL;
                break;
            case DOWN_LEFT:
                entupimentoX = (entupimentoX + 1) % NLIN;
                entupimentoY = (entupimentoY - 1 + NCOL) % NCOL;
                break;
            case DOWN_RIGHT:
                entupimentoX = (entupimentoX + 1) % NLIN;
                entupimentoY = (entupimentoY + 1) % NCOL;
                break;
            }
        }

        // Coloca 'M' na nova posição do entupimento móvel
        mapa[entupimentoX][entupimentoY] = ENTUPIMENTO;
        enviaMapaParaJogoUi();

        pthread_mutex_unlock(&mapa_mutex);

        // Aguarda um tempo antes de mover o entupimento móvel
        sleep(1); // 1 segundo
    }
    printf("Thread de entupimento %d encerrada.\n", *thread_id);

    return NULL;
}

Jogador obterJogador(int idJogador)
{
    int nrJogadores = sizeof(listaClientes) / sizeof(listaClientes[0]);
    for (int i = 0; i < nrJogadores; i++)
    {
        if (listaClientes[i].pid == idJogador)
        {
            return listaClientes[i];
        }
    }
    Jogador notFound = {-1};
    return notFound;
}
// Obter posição atual do jogador
Posicao obterPosicaoAtualDoJogador(Jogador jogador)
{
    Posicao posicaoAtual;

    // Obter posicao atual do jogador
    for (int i = 0; i < NLIN; i++)
    {
        for (int j = 0; j < NCOL; j++)
        {
            if (mapa[i][j] == jogador.letra)
            {
                posicaoAtual.x = i;
                posicaoAtual.y = j;
                break;
            }
        }
    }

    return posicaoAtual;
}

 //Recebe direcao em que jogador se quer mexer e devolve a posição pretendida
Posicao calcularPosicaoPretendida(Jogador jogador, int direcao)
{
    Posicao posicaoAtual = obterPosicaoAtualDoJogador(jogador);

    switch (direcao)
    {
    case UP:
        posicaoAtual.x = (posicaoAtual.x - 1 + NLIN) % NLIN;
        break;
    case DOWN:
        posicaoAtual.x = (posicaoAtual.x + 1 + NLIN) % NLIN;
        break;
    case LEFT:
        posicaoAtual.y = (posicaoAtual.y - 1 + NCOL) % NCOL;
        break;
    case RIGHT:
        posicaoAtual.y = (posicaoAtual.y + 1 + NCOL) % NCOL;
        break;
    default:
        break;
    }

    return posicaoAtual;
}

// Encontra a posição antiga e apaga e adiciona letra do jogador à nova
void atualizaMapa(Jogador jogador, Posicao posicao)
{
    pthread_mutex_lock(&mapa_mutex);
    for (int i = 0; i < NLIN; i++)
    {
        for (int j = 0; j < NCOL; j++)
        {
            // Encontrar posição antiga e apagar
            if (mapa[i][j] == jogador.letra)
            {
                mapa[i][j] = ESPACO_EM_BRANCO;
            }
        }
    }

    mapa[posicao.x][posicao.y] = jogador.letra;

    pthread_mutex_unlock(&mapa_mutex);
    enviaMapaParaJogoUi();
}

bool posicaoValida(Posicao posicao)
{
    // Só permitir movimentação se célula estiver vazia
    return mapa[posicao.x][posicao.y] == ESPACO_EM_BRANCO;
}
Posicao calculaPosicaoVencedora()
{
    Posicao posicao;
    // Percorre toda a primeira linha (coluna a coluna) até encontrar um espaço em branco (que é a saída)
    for (int i = 1; i < NCOL; i++)
    {
        if (mapa[0][i] == ESPACO_EM_BRANCO)
        {
            posicao.y = i;
            posicao.x = 0;
        }
    }

    return posicao;
}
bool jogadorGanhou(Jogador jogador)
{

    Posicao posicaoAtual = obterPosicaoAtualDoJogador(jogador);
    return posicaoAtual.x == posicaoVencedora.x && posicaoAtual.y == posicaoVencedora.y;
}

void addToLog(char logToAdd[])
{
    if (ENABLE_LOGS == 0)
        return;
    FILE *file = fopen("logs.txt", "aw");
    fprintf(file, "\n%s", logToAdd);
    fclose(file);
}
// Função para animar o jogador vencedor duarnte a troca de mapa
void animarJogadorVencedor(Jogador jogador, char novoSimbolo)
{
    for (int i = 0; i < NLIN; i++)
    {
        for (int j = 0; j < NCOL; j++)
        {
            if (mapa[i][j] == jogador.letra)
            {
                jogador.letra = novoSimbolo;
                mapa[i][j] = jogador.letra;
                return;
            }
        }
    }
}

void gerarAnimacaoDeVitoria(Jogador jogador) {
    animarJogadorVencedor(jogador, '@');
    enviaMapaParaJogoUi();
    sleep(1);
}
// Função para trocar o mapa do nivel 1 para o nivel 2
void trocarMapa(Jogador jogador)
{
    gerarAnimacaoDeVitoria(jogador);
    nivel++;
    lerLabirinto(LABIRINTO_2);
    colocarJogadorNaPosicaoInicial(jogador);
    posicaoVencedora = calculaPosicaoVencedora();
    enviaMapaParaJogoUi();
}

void receberMensagemDoJogo()
{
    AtualizacaoJogadorA info;
    //addToLog("ENTREI");

    // Abre a pipe com o nome SERVER_FIFO para leitura
    int fd = open(SERVER_JOGO_FIFO, O_RDWR);

    // Verifica se a abertura do arquivo foi bem-sucedida
    if (fd == -1)
    {
        perror("Erro ao abrir a pipe");
        exit(EXIT_FAILURE);
    }

    // Lê da FIFO
    int bytesRead = read(fd, &info, sizeof(AtualizacaoJogadorA));

    char log[100];
    sprintf(log, "Recebi: %d | %d", (info).direcao, info.id);
    addToLog(log);

    // Verifica se a quantidade correta de bytes foi lida
    if (bytesRead != sizeof(AtualizacaoJogadorA))
    {
        fprintf(stderr, "Erro: Não foi lido o número esperado de bytes.\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Obter jogador da lista de jogadores
    Jogador jogador = obterJogador((info).id);
    Posicao novaPosicao = calcularPosicaoPretendida(jogador, (info).direcao);

    if (posicaoValida(novaPosicao))
    {
        atualizaMapa(jogador, novaPosicao);
        if (jogadorGanhou(jogador))
        {

            if (nivel < NIVEIS_EXISTENTES)
            {
                printf("Jogador %s passou o nível! A mudar de mapa...\n", jogador.nome);
                trocarMapa(jogador);
            }
            else
            {
                printf("Jogador %s ganhou!!!\n", jogador.nome);
                termina(0, NULL, NULL);
                
            }
        }
    }


    // Fecha a FIFO após a leitura
    close(fd);
}

// Mutex para proteger o acesso à função enviaMapaParaJogoUi
pthread_mutex_t mutex_envia_mapa = PTHREAD_MUTEX_INITIALIZER;
void *threadEnviaMapaParaJogoUi(void *arg)
{
    while (1)
    {
        // Aguarda 1 segundo
        sleep(1); 
        pthread_mutex_lock(&mutex_envia_mapa);


        enviaMapaParaJogoUi();

        pthread_mutex_unlock(&mutex_envia_mapa);
    }

    return NULL;
}
// faz um mutext so para esta thread
pthread_mutex_t mutex_jogador = PTHREAD_MUTEX_INITIALIZER;
void *threadAtualizacaoMapa(void *arg)
{
    // Lógica da thread de atualização do mapa
    while (1)
    {
        pthread_mutex_lock(&mutex_jogador);
        // Crie uma estrutura para armazenar as informações
        // Aguarde uma mensagem do jogo
        receberMensagemDoJogo();

        pthread_mutex_unlock(&mutex_jogador);
    }

    return NULL;
}
void encerra_jogo_cmd()
{
    printf("Jogo encerrado\n");
    termina(0, NULL, NULL);
}

void remover_utilizador_cmd(char *input)
{
    char delim[] = " \n";
    char *token;
    char *seguinte = NULL;

    // Divide a string em tokens usando os delimitadores
    token = strtok(input, delim);

    while (token != NULL)
    {
        // Se encontrarmos o comando desejado, pegamos o próximo token como a palavra desejada
        token = strtok(NULL, delim);
        if (token != NULL)
        {
            seguinte = token;
            printf("Comando válido. Jogador a ser removido: %s\n", seguinte);
            for (int i = 0; i < MAXUTILIZADORES; i++)
            {
                if (listaClientes[i].ocupado)
                {
                    if (strcmp(listaClientes[i].nome, seguinte) == 0)
                    {
                        listaClientes[i].ocupado = 0;
                        kill(listaClientes[i].pid, SIGINT);
                        printf("Jogador removido com sucesso\n");
                        return;
                    }
                }
            }
            return;
        }
        else
        {
            printf("Comando invalido.Digite um nome!\n");
            return;
        }
    }
}

void mostrar_utilizadores_cmd()
{
    int cont = 0;
    for (int i = 0; i < MAXUTILIZADORES; i++)
    {
        if (listaClientes[i].ocupado)
        {
            printf("Nome do jogador %d: %s\n", i + 1, listaClientes[i].nome);
            cont++;
        }
    }
    if (cont == 0)
    {
        printf("Não existem jogadores registados\n");
    }
}

void mostrar_bots_cmd()
{
    printf("Comando valido\n");
}

void insere_bloqueio_cmd()
{
    printf("Comando valido\n");
}

// Mutex para sincronizar o acesso à variável global
pthread_mutex_t mutex_removerEntupimento = PTHREAD_MUTEX_INITIALIZER;
void remover_bloqueio_cmd()
{
    printf("Removendo entupimento.\n");
    pthread_mutex_lock(&mutex_removerEntupimento);
    removerEntupimento = 1;
    pthread_mutex_unlock(&mutex_removerEntupimento);
}

void handle_sigalrm(int s, siginfo_t *i, void *v)
{

    printf("\nAcabou o tempo- PERDERAM TODOS\n");
    termina(s, i, v);
    exit(1);
}


void *temporizador_handler(void *arg)
{

    Bloqueio *bloqueio = (Bloqueio *)arg;

    // Aguarda a duração do bloqueio
    sleep(bloqueio->duracaoBloqueio);

    // Remove 'P' do mapa após a duração
    pthread_mutex_lock(&mapa_mutex);
    mapa[bloqueio->x][bloqueio->y] = ESPACO_EM_BRANCO;
    enviaMapaParaJogoUi();
    pthread_mutex_unlock(&mapa_mutex);

    free(bloqueio);

    return NULL;
}

void teste_bot(char *input)
{
    int id;
    int fd[2];
    int erro = pipe(fd);
    char intervalo_str[10], duracao_str[10];
    union sigval val;

    char *token = strtok(input, " ");
    if (token == NULL)
    {
        printf("Formato incorreto. Formato: test_bot <intervalo> <duracao>\n");
        return;
    }

    int intervalo = atoi(token);

    token = strtok(NULL, " ");
    if (token == NULL)
    {
        printf("Faltam argumentos. Formato: test_bot <intervalo> <duracao>\n");
        return;
    }

    int duracao = atoi(token);

    id = fork();

    if (id == 0)
    {
        sprintf(intervalo_str, "%d", intervalo);
        sprintf(duracao_str, "%d", duracao);

        close(1);
        dup(fd[1]);
        close(fd[1]);
        close(fd[0]);

        execl("bot", "bot", intervalo_str, duracao_str, NULL);

        printf("Erro no execl\n");
        return;
    }
    else if (id > 0)
    {
        close(fd[1]);
        char mensagem[50];
        int i = 0;
        while (i < 10)
        {
            int size = read(fd[0], mensagem, sizeof(mensagem));
            if (size > 0)
            {
                mensagem[size] = '\0';
                printf("RECEBI: %s\n", mensagem);
                Bloqueio *bloqueio = (Bloqueio *)malloc(sizeof(Bloqueio));
                // Extrair coordenadas e duração dos bloqueios da mensagem
                sscanf(mensagem, "%d %d %d", &bloqueio->x, &bloqueio->y, &bloqueio->duracaoBloqueio);
                // Atualizar o mapa com 'P' nas coordenadas fornecidas
                pthread_mutex_lock(&mapa_mutex);
                mapa[bloqueio->x][bloqueio->y] = PEDRA;
                enviaMapaParaJogoUi();
                pthread_mutex_unlock(&mapa_mutex);

                // Crie uma thread para gerenciar a duração do bloqueio
                pthread_t thread_id;
                pthread_create(&thread_id, NULL, temporizador_handler, (void *)bloqueio);
                pthread_detach(thread_id);
            }
            i++;
        }

        sigqueue(id, SIGINT, val);
        wait(&id);
    }
}


void *RecebeMsg(void *dados)
{

    DADOST *pdados = (DADOST *)dados;
    fd_set read_fds;
    struct timeval tv;
    dataMsg msgrecebida, msgenviar;
    pid_t ultimoCliente = 0;
    int nJogadores = 0;
    char *inscricao_str = getenv("INSCRICAO");
    char *nplayers_str = getenv("NPLAYERS");


    int fd_receber_jog = open(SERVER_FIFO, O_RDONLY);

    if (fd_receber_jog == -1)
    {
        perror("Erro ao abrir FIFO para leitura");
        exit(EXIT_FAILURE);
    }

    while (pdados->trinco)
    {
        int sizeR = read(fd_receber_jog, &msgrecebida, sizeof(msgrecebida));

        if (sizeR > 0 && msgrecebida.idMsg == 1)
        {
            printf("\nO utilizador %s entrou no jogo\n", msgrecebida.nome);
            int v = verificaCliente(msgrecebida.nome, msgrecebida.pid);
            sprintf(CLIENT_FIFO_FINAL, CLIENT_FIFO, msgrecebida.pid);
            int fd_resposta = open(CLIENT_FIFO_FINAL, O_WRONLY);

            if (v == 1)
            {
                strcpy(msgenviar.aviso, "Nome de Jogador já existe\n");
            }
            else if (v == 0)
            {
                strcpy(msgenviar.aviso, "Adicionado com sucesso. Espera!\n");
                nJogadores++;
            }
            else if (v == -1)
            {
                strcpy(msgenviar.aviso, "Não existem mais vagas\n");
            }

            write(fd_resposta, &msgenviar, sizeof(msgenviar));
            close(fd_resposta);
        }
        close(fd_receber_jog);
        // if (nJogadores >= minimo_jogadores) {
        //     printf("Temos um minimo de jogadores comeca o jogo");
        // Comeca o jogo aqui...

        //     }

        if (msgrecebida.idMsg == 2)
        {
        }
        pthread_exit(NULL);
    }
}
void *verificaComandoThread(void *comando)
{
    // Converte o argumento para a string do comando
    char *cmd = (char *)comando;

    // Lógica para validar o comando
    verifica_comando(cmd);

    // Libera a memória alocada para a string do comando
    free(cmd);

    return NULL;
}
void *comeca_jogo_thread(void *arg)
{
    // A função aceita um argumento, mas você pode não precisar usá-lo neste caso
    (void)arg;
    Jogador jogador;
    // Cria threads para verificar comandos simultaneamente
    pthread_t thread1, thread2;

    // Aloca memória para as strings dos comandos
    char *comando1 = strdup("test_bot 10 15");
    char *comando2 = strdup("test_bot 6 15");
    // Cria as threads
    pthread_create(&thread1, NULL, verificaComandoThread, (void *)comando1);
    pthread_create(&thread2, NULL, verificaComandoThread, (void *)comando2);

    // Aguarda o término das threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_exit(NULL);
}

// Função intermediária que atua como manipulador de sinal
void temporizador_sinal_handler(int signo)
{
    // Não é necessário fazer nada aqui, pois vamos chamar handle_sigalrm diretamente
}
// Função que será chamada quando o temporizador expirar
void *temporizador_thread(void *arg)
{
    // Aguarda 100 segundos para acabar o jogo
    char * duracao_str = getenv("DURACAO");
    int duracao = atoi(duracao_str);
    sleep(duracao);
    printf("\nAcabou o tempo - PERDERAM TODOS\n");
    // Configuração do manipulador de sinal
    struct sigaction sa, st;
    union sigval s;
    sa.sa_sigaction = termina;
    sigaction(SIGALRM, &sa, NULL);

    st.sa_sigaction = handle_sigalrm;
    // Chame a função handle_sigalrm após 10 segundos
    raise(SIGALRM);
    // alarm(20);
    return NULL;
}

void comeca_jogo_cmd()
{
    jogoComecou = true;
    // Criaa uma thread para o temporizador
    pthread_t temporizador_thread_id;
    pthread_create(&temporizador_thread_id, NULL, temporizador_thread, NULL);

    // Cria uma thread para verificar comandos
    // pthread_t verifica_comando_thread_id;
    // pthread_create(&verifica_comando_thread_id, NULL, verificaComandoThread, NULL);
    pthread_t jogo_thread;
    pthread_create(&jogo_thread, NULL, comeca_jogo_thread, NULL);

    // Cria uma thread para atualização do mapa
    pthread_t idAtualizacaoMapa;
    pthread_create(&idAtualizacaoMapa, NULL, threadAtualizacaoMapa, NULL);
    // Cria uma thread para enviar o mapa para a interface do jogo
    pthread_t idEnviaMapaParaJogoUi;
    pthread_create(&idEnviaMapaParaJogoUi, NULL, threadEnviaMapaParaJogoUi, NULL);
    // Cria uma thread para gerar entupimentos móveis
    int thread_id1 = 1, thread_id2 = 2;

    pthread_t entupimento_thread1, entupimento_thread2;
    pthread_create(&entupimento_thread1, NULL, geraEntupimento, &thread_id1);
    pthread_detach(entupimento_thread1);
    // Aguarde a conclusão da thread
    // pthread_join(jogo_thread, NULL);
    pthread_join(idEnviaMapaParaJogoUi, NULL);
    pthread_join(temporizador_thread_id, NULL);
}

int main(int argc, char *argv[])
{
    if (mkfifo(SERVER_FIFO, 0666) == -1)
    {
        perror("Erro a abrir fifo ou fifo já existe");
        return -1;
    }
    if (mkfifo(SERVER_JOGO_FIFO, 0666) == -1)
    {
        perror("Erro a abrir fifo ou fifo já existe");
        return -1;
    }
    setbuf(stdout, NULL);
    struct sigaction sa, st;
    union sigval s;
    sa.sa_sigaction = termina;
    sigaction(SIGINT, &sa, NULL);

    st.sa_sigaction = handle_sigalrm;
    st.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &st, NULL);

    dataMsg msg;
    pthread_t pthread_motor, pthread_login;

    // Cria a thread para receber mensagens
    pthread_create(&pthread_motor, NULL, &RecebeMsg, &msg);
    dataMsg dados;
    // Cria a thread para lidar com o login
    pthread_create(&pthread_login, NULL, &login, (void *)&dados);

    lerLabirinto(LABIRINTO_1);
    posicaoVencedora = calculaPosicaoVencedora();

    char cmd[50];

    do
    {

        
        printf("\nComando > ");
        fgets(cmd, 50, stdin);
        DADOST ola;
        ola.trinco = 0;
        // Remove o caractere de nova linha
        cmd[strcspn(cmd, "\n")] = '\0';
        verifica_comando(cmd);

        if (strcmp(cmd, "end") == 0)
        {

            break;
        }

    } while (1);

    pthread_join(pthread_motor, NULL);
    pthread_join(pthread_login, NULL);

    unlink(SERVER_JOGO_FIFO);
    unlink(SERVER_FIFO);

    return 0;
}
