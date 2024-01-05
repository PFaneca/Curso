//
// Created by ASUS on 26/11/2023.
//

#ifndef IIA_TP2_FUNCAO_H
#define IIA_TP2_FUNCAO_H
#include "algoritmo.h"
int calcula_fit(int a[], int *mat, int vert);
int calcula_fit_penalizado(int a[], int *mat, int vert, int k, int *v);
int calcula_fit_reparado1(int a[], int *mat, int vert, int k, int *v);
int calcula_fit_reparado2(int a[], int *mat, int vert, int k, int *v);
void evaluate(pchrom pop, int* mat, int vert, int k, int popsize);
int calcula_fit2(int a[], int *mat, int vert, int k, int *v);
int calcula_fit_hibrido(int a[], int *mat, int vert, int k, int *v);
#endif //IIA_TP2_FUNCAO_H
