//
// Created by ASUS on 26/11/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include "math.h"
#define PR 0.3
#define PM 0.001
#define TSIZE 2

void gera_vizinho(int a[], int b[], int n)
{
    int i, p1, p2;

    for(i=0; i<n; i++)
        b[i]=a[i];
    // Encontra posicao com valor 0
    do
        p1=random_l_h(0, n-1);
    while(b[p1] != 0);
    // Encontra posicao com valor 0
    do
        p2=random_l_h(0, n-1);
    while(b[p2] != 1);

    // Troca
    b[p1] = 1;
    b[p2] = 0;
}



void gera_vizinho2(int a[], int b[], int n)
{
    int i, p1, p2,p3,p4;

    for(i=0; i<n; i++)
        b[i]=a[i];
    // Encontra posicao com valor 0
    do
        p1=random_l_h(0, n-1);
    while(b[p1] != 0);
    // Encontra posicao com valor 0
    do
        p2=random_l_h(0, n-1);
    while(b[p2] != 1);

    //ACRESCENTO PARA 2 VIZINHANCA-> MAIS 2 TROCAS
    do
        p3= random_l_h(0,n-1);
    while(b[p3]!= 0 || p3 == p1);

    do
        p4= random_l_h(0,n-1);
    while(b[p4] != 1 ||  p4==p2);
    // Troca
    b[p1] = 1;
    b[p2] = 0;
    b[p3] = 1;
    b[p4] = 0;
}


int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;

    nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for(i=0; i<num_iter; i++)
    {
        // Gera vizinho
        gera_vizinho(sol, nova_sol, vert);
        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, mat, vert);
        // Aceita vizinho se o custo diminuir (problema de minimizacao)
        if(custo_viz < custo) //CUSTO IGUAL-> 2 tabela
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }

    }
    free(nova_sol);
    return custo;
}


void tournament(pchrom pop, int popsize, pchrom parents)
{
    int i, x1, x2;

    // Realiza popsize torneios
    for(i=0; i<popsize;i++)
    {
        x1 = random_l_h(0, popsize-1);
        do
            x2 = random_l_h(0, popsize-1);
        while(x1==x2);
        if(pop[x1].fitness < pop[x2].fitness)		// Problema de minimizacao
            parents[i]=pop[x1];
        else
            parents[i]=pop[x2];
    }
}

void tournament_geral(pchrom pop, int popsize, pchrom parents) {
    int sair, best, *pos;

    pos = malloc(sizeof(int)*TSIZE);

    for (int i = 0; i < popsize; i++)
    {
        for (int j = 0; j < TSIZE; j++)
        {
            do {
                pos[j] = random_l_h(0, popsize-1);

                // Verifica se não repete uma solucao
                sair = 0;
                for (int k = 0; k < j; k++)
                {
                    if (pos[k] == pos[j])
                    {
                        sair = 1;
                    }
                }
            }while (sair);

            if (j == 0 || pop[pos[j]].fitness < pop[pos[best]].fitness)   //minimizacao
            {
                best = j;
            }
        }
        parents[i] = pop[pos[best]];
    }
    free(pos);
}

void genetic_operators(pchrom parents, int popsize, pchrom offspring, int vert)
{
    // Recombinação com um ponto de corte
    crossover(parents, popsize, offspring, vert);
    // 2 pontos de corte
    //recombinacao_dois_pontos_corte(parents, offspring, popsize, vert);
    // Uniforme
    //recombinacao_uniforme(parents, offspring, popsize, vert);
    // Mutação binária
    //mutation(offspring, popsize, vert);
    // Por troca
    //mutacao_por_troca(offspring, popsize, vert);
}

void crossover(pchrom parents, int popsize, pchrom offspring, int vert)
{
    int i, j, point;
    float pr = PR;

    for (i=0; i<popsize; i+=2)
    {
        if (rand_01() < PR)
        {
            point = random_l_h(0, vert-1);
            for (j=0; j<point; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }
            for (j=point; j<vert; j++)
            {
                offspring[i].p[j]= parents[i+1].p[j];
                offspring[i+1].p[j] = parents[i].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }
    }
}

void recombinacao_dois_pontos_corte(pchrom parents, pchrom offspring, int popsize, int vert) {
    int p1, p2;

    for (int i = 0; i < popsize; i += 2)
    {
        if (rand_01() < PR)
        {
            p1 = random_l_h(0, vert-1);
            p2 = random_l_h(0, vert-1);

            for (int j = 0; j < p1; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }

            for (int j = p1; j < p2; j++)
            {
                offspring[i].p[j] = parents[i+1].p[j];
                offspring[i+1].p[j] = parents[i].p[j];
            }

            for (int j = p2; j < vert; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }
    }
}

void recombinacao_uniforme(pchrom parents, pchrom offspring, int popsize, int vert) {

    for (int i = 0; i < popsize; i += 2)
    {
        if (rand_01() < PR)
        {
            for (int j = 0; j < vert; j++)
            {
                if (flip() == 1)
                {
                    offspring[i].p[j] = parents[i].p[j];
                    offspring[i+1].p[j] = parents[i+1].p[j];
                }
                else
                {
                    offspring[i].p[j] = parents[i+1].p[j];
                    offspring[i+1].p[j] = parents[i].p[j];
                }
            }
        }
        else {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }
    }
}

void mutacao(pchrom offspring, int popsize, int vert)
{
    int i, j;

    for (i=0; i<popsize; i++)
        for (j=0; j<vert; j++)
            if (rand_01() < PM)
                offspring[i].p[j] = !(offspring[i].p[j]);
}

void mutacao_por_troca(pchrom offspring, int popsize, int vert) {
    int p1, p2, aux;

    for (int i = 0; i < popsize; i++)
    {
        if (rand_01() < PM)
        {
            do {
                p1 = random_l_h(0, vert-1);
            }while (offspring[i].p[p1] == 1);

            do {
                p2 = random_l_h(0, vert-1);
            }while (offspring[i].p[p2] == 0);

            aux = offspring[i].p[p1];
            offspring[i].p[p1] = offspring[i].p[p2];
            offspring[i].p[p2] = aux;
        }
    }
}


