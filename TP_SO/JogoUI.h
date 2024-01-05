//define o tamanha do mapa
#define NCOL 41
#define NLIN 16
//named pipes
#define SERVER_FIFO "SERVIDOR"
#define SERVER_JOGO_FIFO "SERVIDOR_JOGO_FIFO"
#define CLIENT_FIFO "CLIENTE%d"
//#define MAILBOX_FIFO "MAILBOX_%s"
// Constantes para as direções de movimento
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define UP_LEFT 4
#define UP_RIGHT 5
#define DOWN_LEFT 6
#define DOWN_RIGHT 7


char CLIENT_FIFO_FINAL[100];
int listaClientes[100]; // melhorar
char mapa[NLIN][NCOL];

typedef struct
{
    WINDOW *janelaLabirinto;
    WINDOW *janelaComandos;
    int trinco;

} DADOST;
// Estrutura para armazenar informações sobre a atualização do jogador 'A'
typedef struct
{
    int direcao; // 1: cima, 2: direita, 3: baixo, 4: esquerda (ou qualquer esquema que você preferir)
    int id;
} AtualizacaoJogadorA;

typedef struct {
    char nome[50];
    pid_t pid;
    //int estado;
    int idMsg;
    char mapa[NLIN][NCOL];
    char tecla[2];
    char aviso[100];
}Jogador;

typedef struct{ 
    pid_t pid;
    char mapa[NLIN][NCOL];
    int idMsg;
    char nome[50];
   //char aviso[100];
   char letra[2];
   char aviso[100];
}dataMsg;

typedef struct{
    char user_origem[50];
    char user_destino[50];
    char mensagem[100];
}MensagemPrivada;




struct comando{
    char *nome;
    char * descricao;
    void(*func)(char *);
   
};


void verifica_comando(char*);
void mostrar_jogadores_cmd();
void comandos_cmd( char *);
void enviar_msg_cmd();
void sair_cmd();


static const struct comando comandoss[]={
    {"ajuda","Mostra a lista de comandos permitidos",&comandos_cmd},
    {"players","Lista de todos os jogadores ativos no sistema",&mostrar_jogadores_cmd},
    {"msg","Enviar mensagem a um utilizador especifico", &enviar_msg_cmd},
    {"exit","Sair",&sair_cmd},

};