//
// Created by ASUS on 26/11/2023.
//

#ifndef IIA_TP2_ALGORITMO_H
#define IIA_TP2_ALGORITMO_H
#define MAX_OBJ 1000		// Numero maximo de objectos


int trepa_colinas(int sol[], int *mat, int vert, int num_iter);

// Individuo (solu��o)
typedef struct individual chrom, *pchrom;

struct individual
{
    // Solu��o (objetos que est�o dentro da mochila)
    int     p[MAX_OBJ];
    // Valor da qualidade da solu��o
    int  fitness;
    // 1 se for uma solu��o v�lida e 0 se n�o for
    int     valido;
};

void tournament(pchrom pop, int popsize, pchrom parents);

void genetic_operators(pchrom parents, int popsize, pchrom offspring, int vert);

void crossover(pchrom parents, int popsize, pchrom offspring, int vert);

void mutacao(pchrom offspring, int popsize, int vert);
void mutacao_por_troca(pchrom offspring, int popsize, int vert);
void recombinacao_dois_pontos_corte(pchrom parents, pchrom offspring, int popsize, int vert);
void recombinacao_uniforme(pchrom parents, pchrom offspring, int popsize, int vert);
void tournament_geral(pchrom pop, int popsize, pchrom parents);
int trepa_colinas_hibrido(pchrom pop, int popsize, int *mat, int vert, int k,int num_iter);
#endif //IIA_TP2_ALGORITMO_H
