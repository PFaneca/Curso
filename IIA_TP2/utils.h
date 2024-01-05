//
// Created by ASUS on 26/11/2023.
//

#ifndef IIA_TP2_UTILS_H
#define IIA_TP2_UTILS_H
#include "algoritmo.h"
int* init_dados(char *nome, int *k, int *vert, int *ares);
void gera_sol_inicial(int *sol, int v,int k);
void escreve_sol(int *sol, int vert);
void substitui(int a[], int b[], int n);
void init_rand();
int random_l_h(int min, int max);
float rand_01();
int flip();


void write_best(chrom x, int vert);
pchrom init_pop(int vert, int k);
void print_pop(pchrom pop, struct info d);
chrom get_best(pchrom pop, int popsize, chrom best);

#endif //IIA_TP2_UTILS_H
