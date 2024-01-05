//
// Created by ASUS on 26/11/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include <string.h>
#include "algoritmo.h"


// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias
int* init_dados(char *nome, int *k,int *vertices,int *arestas)
{
    FILE *f;
    int *p, *q;
    int i, j,v1,v2,c;


    f=fopen(nome, "r");
    if(!f)
    {
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }

    // Numero K
    fscanf(f, "k %d", k);
    // Numero de arestas e vertices
    fscanf(f, "\np edge %d %d", vertices, arestas);


    // Alocacao dinamica da matriz
    p = malloc(sizeof(int)*(*vertices)*(*vertices));
    if(!p)
    {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
    q=p;
    // Preenchimento da matriz
    // Inicializa a matriz de adjacência com zeros
    for (i = 0; i < *vertices; i++)
        for (j = 0; j < *vertices; j++)
            p[i*(*vertices)+j] = 0;

    //Coloca as informacoes das arestas e os seus respetivos custos no array
    while (fscanf(f,"\ne %d %d %d",&v1,&v2,&c)==3){
        p[(v1-1)*(*vertices)+(v2-1)] = c;
        p[(v2-1)*(*vertices)+(v1-1)] = c;
    }

    fclose(f);
    return p;
}
int flip(){
    if ((rand() % 100) < 50)
        return 0;
    else
        return 1;
}

void gera_sol_inicial(int *sol, int v,int k)
{
    int i, x;

    for(i=0; i<v; i++)
        sol[i]=0;
    for(i=0; i<k  ; i++)
    {
        do
            x = random_l_h(0, v-1);
        while(sol[x] != 0);
        sol[x]=1;
    }
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices


// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
    int i;

    printf("\nVertices da Solucao:");
    for(i = 0; i < vert; i++) {
        if (sol[i] == 1) {
            printf("%d  ", i + 1);
        }
    }
    printf("\n");
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
    srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
    return min + rand() % (max-min+1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01()
{
    return ((float)rand())/RAND_MAX;
}


pchrom init_pop(int vert, int k)
{
    int     i, j;
    int popsize = 100;
    pchrom  indiv;

    indiv = malloc(sizeof(chrom)*popsize);
    if (indiv==NULL)
    {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
    for (i=0; i<popsize; i++)
    {
        gera_sol_inicial(indiv[i].p, vert, k);
    }
    return indiv;
}


chrom get_best(pchrom pop, int popsize, chrom best)
{
    int i;

    for (i=0; i<popsize; i++)
    {
        if (best.fitness > pop[i].fitness)
            best=pop[i];
    }
    return best;
}

void write_best(chrom x, int vert)
{
    int i;

    printf("\n Custo final: %d\n", x.fitness);
    for (i=0; i<vert; i++)
        printf("%d", x.p[i]);
    putchar('\n');
}





