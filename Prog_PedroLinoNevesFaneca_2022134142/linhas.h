// Feito por: Pedro Lino Neves Faneca nº2022134142
#ifndef TRABALHO_P_LINHAS_H
#define TRABALHO_P_LINHAS_H
// Estrutura de dados para guardar as paragens
typedef struct dados stop, *pstop;
struct dados {
    char nome[100];
    char codigo[5];
};

pstop addP(pstop p, int *total);

void listaP(pstop p, int total);

void gerar_codigo(char *codigo);

pstop buscarParagem(pstop p, int totalP, char *codigo);

// Estrutura de dados para guardar as linhas
typedef struct dadosLinhas linha, *plinha;
struct dadosLinhas {
    char nome[100];
    int total_paragens;
    pstop paragem;
    pstop prox;
};

pstop eliminaP(pstop tab, int *total, char *id, plinha tabL);

plinha addL(plinha p, int *totalL, pstop tab, int *totalP);

void listaL(plinha p);

void linhasP(plinha p, char *nomeParagem);

plinha atualizaL(plinha p, char *nomeLinha);

void calcularPercurso(plinha p, char *partida, char *chegada);

void salvarParagens(pstop p, int total);

pstop carregarParagens(int *total);

void salvarLinhas(plinha p);

plinha carregarLinhas();

void limparBufferEntrada();

void freeLinha(plinha p);

plinha lerLinhaDeFicheiro(char *nomeFicheiro, pstop p, int *totalP);

void limparArquivoBinario(const char *nomeFicheiro);

plinha adicionarLinhaLida(plinha p, int *totalL, pstop paragens, int *totalP);

#endif //TRABALHO_P_LINHAS_H
