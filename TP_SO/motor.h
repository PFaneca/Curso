


#define MAXUTILIZADORES 5
#define PROCESSOSBOT 10
#define PEDRAS 50
#define NIVEIS 3
#define BLOQUEIOS 5


// define para o tamanho do mapa
#define NCOL 41
#define NLIN 16

// Labirintos
#define LABIRINTO_1 "mapa1.txt"
#define LABIRINTO_2 "mapa2.txt"

// Constantes para peças
#define ESPACO_EM_BRANCO ' '
#define PEDRA 'P'
#define ENTUPIMENTO 'M'
#define PAREDE '#'

// Constantes para as direções de movimento
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define UP_LEFT 4
#define UP_RIGHT 5
#define DOWN_LEFT 6
#define DOWN_RIGHT 7

#define SERVER_FIFO "SERVIDOR"
#define SERVER_JOGO_FIFO "SERVIDOR_JOGO_FIFO"
#define CLIENT_FIFO "CLIENTE%d"

#define NIVEIS_EXISTENTES 2





typedef struct{ 
    pid_t pid;
    char mapa[NLIN][NCOL];
    int idMsg;
    char nome[50];
   //char aviso[100];
   char letra[2];
   char aviso[100];
}dataMsg;


typedef struct {
    char letra;
    char nome[50];
    pid_t pid;
    //int estado;
    int idMsg;
    char mapa[NLIN][NCOL];
    char tecla[2];
    char aviso[100];
    int ocupado; //Flag para indicar se a entrada está ocupada
}Jogador;




struct comando{
    char *nome;
    char * descricao;
    void(*func)(char *);
    int argumentos;
 
};


//  LISTAS LIGADAS
static struct utilizador * lista_utilizadores = 0;







//  FUNÇÕES DE COMANDOS
void verifica_comando(char *);
void teste_bot(char *);
void comandos_cmd(char *);
void encerra_jogo_cmd();
void mostrar_utilizadores_cmd();
void mostrar_bots_cmd();
void insere_bloqueio_cmd();
void remover_utilizador_cmd(char *);
void remover_bloqueio_cmd();
void comeca_jogo_cmd();




//Lista DE COMANDOS
static const struct comando comandoss[]={

    {"ajuda","Mostra a lista de comandos permitidos", &comandos_cmd},
    {"users","Lista os jogadores atualmente a usar a plataforma", &mostrar_utilizadores_cmd},
    {"kick", "Bane um jogador atualmente registado",  &remover_utilizador_cmd},
    {"bots","Lista os bots atualmente ativos",  &mostrar_bots_cmd},
    {"bmov","Insere bloqueio movel",  &insere_bloqueio_cmd},
    {"rbm","Elimina bloqueio movel", &remover_bloqueio_cmd},
    {"begin","Inicia jogo manualmente", &comeca_jogo_cmd},
    {"end","Encerra jogo",  &encerra_jogo_cmd},
    {"test_bot","Teste bot",&teste_bot},
    

};



