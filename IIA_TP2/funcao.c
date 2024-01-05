//
// Created by ASUS on 26/11/2023.
//
#include "funcao.h"
#include "algoritmo.h"
#include "utils.h"
#include "stdlib.h"

// Calcula a qualidade de uma solu��o
// Recebe:  A solu��o, a, a matriz de adjac�ncias, mat, e o n�mero de v�rtices, vert
// Devolve: O custo que � o n�mero de liga��es que existem na solu��o
int calcula_fit(int a[], int *mat, int vert) {
    int total = 0;



    // Array de conexões
    int con[vert];
    for (int i = 0; i < vert; i++) {
        con[i] = 0;
    }

    // Loop por toda a matriz para verificar se é válida
    for (int i = 0; i < vert; i++) {
        // Verifica se a linha pertence à solução
        if (a[i] == 1) {
            for (int j = 0; j < vert; j++) {
                // Verifica se há uma conexão entre os vértices i e j
                if (a[j] == 1 && *(mat+i*vert+j) != 0) {
                    con[i] = 1;
                    con[j] = 1;
                    // Adiciona o custo
                    total += *(mat+i*vert+j);
                }
            }
        }
    }

    // Verifica se a solução é válida
    for (int i = 0; i < vert; i++) {
        if (con[i] == 0 && a[i] == 1) {
            // Solução inválida
           return 5000;
        }
    }

    // Retorna o custo total
    return total/2;
}

int calcula_fit2(int a[], int *mat, int vert, int k, int *v) {
    int total = 0, lig = 0;

    for (int i = 0; i < vert; i++)
    {
        if (a[i] == 1)
        {
            lig++;
        }
    }

    // Numero de vertices do subconjunto diferente de K
    if (lig != k)
    {
        *v = 0;
        return 5000;
    }

    // Array de conexoes
    int con[vert];
    for (int i = 0; i < vert; i++)
    {
        con[i] = 0;
    }

    // Loop por toda a matriz para verificar se é valida
    for (int i = 0; i < vert; i++)
    {
        // Verifica se a linha pertence a solucao
        if (a[i] == 1)
        {
            for (int j = 0; j < vert; j++)
            {
                if(a[j] == 1 && *(mat+i*vert+j) != 0)
                {
                    con[i] = 1;
                    con[j] = 1;

                    // Adiciona o custo
                    total += *(mat+i*vert+j);
                }
            }
        }
    }

    for (int i = 0; i < vert; i++)
    {
        if (con[i] == 0 && a[i] == 1)
        {
            // Solucao invalida - Não existem as ligacões necessárias
            *v = 0;
            return 5000;
        }
    }

    *v = 1;
    return total / 2;
}

void evaluate(pchrom pop, int* mat, int vert, int k, int popsize) {
    int i;

    for (i = 0; i < popsize; i++) {
        // Penalizacao cega
        //pop[i].fitness = calcula_fit2(pop[i].p, mat, vert, k, &pop[i].valido);
        // Penalizacao nao cega
        //pop[i].fitness = calcula_fit_penalizado(pop[i].p, mat, vert, k, &pop[i].valido);
        // Reparacao1
        //pop[i].fitness = calcula_fit_reparado1(pop[i].p, mat, vert, k, &pop[i].valido);
        // Reparacao2
        pop[i].fitness = calcula_fit_reparado2(pop[i].p, mat, vert, k, &pop[i].valido);
        // Atualizar a validade conforme necessário (dependendo de como a função calcula_fit manipula a validade)

    }
}

int calcula_fit_penalizado(int a[], int *mat, int vert, int k, int *v) {
    int total = 0, lig = 0;

    for (int i = 0; i < vert; i++)
    {
        if (a[i] == 1)
        {
            lig++;
        }
    }

    // Penalizar 500 + 100 por cada vertice a mais ou a menos
    if (lig != k)
    {
        *v = 0;
        return 500 + abs(((k-lig)*100));
    }

    // Array de conexoes
    int con[vert];
    for (int i = 0; i < vert; i++)
    {
        con[i] = 0;
    }

    // Loop por toda a matriz para verificar se é valida
    for (int i = 0; i < vert; i++)
    {
        // Verifica se a linha pertence a solucao
        if (a[i] == 1)
        {
            for (int j = 0; j < vert; j++)
            {
                if(a[j] == 1 && *(mat+i*vert+j) != 0)
                {
                    con[i] = 1;
                    con[j] = 1;

                    // Adiciona o custo
                    total += *(mat+i*vert+j);
                }
            }
        }
    }

    for (int i = 0; i < vert; i++)
    {
        if (con[i] == 0 && a[i] == 1)
        {
            // Penalizar 500 se não existirem as ligacoes necessarias
            *v = 0;
            return total + 500;
        }
    }

    *v = 1;
    return total / 2;
}

int calcula_fit_reparado1(int a[], int *mat, int vert, int k, int *v) {
    int total = 0, lig = 0;
    int prep;

    for (int i = 0; i < vert; i++)
    {
        if (a[i] == 1)
        {
            lig++;
        }
    }

    // Reparacao 1 -> Ajusta o tamanho do subconjunto para ficar igual a K
    if (lig > k)
    {
        do {
            do {
                prep = random_l_h(0, vert-1);
            }while(a[prep] != 1);

            a[prep] = 0;
            lig--;
        }while(lig != k);
    }
    if (lig < k)
    {
        do {
            do {
                prep = random_l_h(0, vert-1);
            }while(a[prep] != 0);

            a[prep] = 1;
            lig++;
        }while(lig != k);
    }

    // Array de conexoes
    int con[vert];
    for (int i = 0; i < vert; i++)
    {
        con[i] = 0;
    }

    // Loop por toda a matriz para verificar se é valida
    for (int i = 0; i < vert; i++)
    {
        // Verifica se a linha pertence a solucao
        if (a[i] == 1)
        {
            for (int j = 0; j < vert; j++)
            {
                if(a[j] == 1 && *(mat+i*vert+j) != 0)
                {
                    con[i] = 1;
                    con[j] = 1;

                    // Adiciona o custo
                    total += *(mat+i*vert+j);
                }
            }
        }
    }

    for (int i = 0; i < vert; i++)
    {
        if (con[i] == 0 && a[i] == 1)
        {
            // Solucao invalida
            *v = 0;
            return 5000;
        }
    }

    *v = 1;
    return total / 2;
}


int calcula_fit_reparado2(int a[], int *mat, int vert, int k, int *v) {
    int total = 0, lig = 0;
    int prep, ncon = 0;

    for (int i = 0; i < vert; i++)
    {
        if (a[i] == 1)
        {
            lig++;
        }
    }

    // Reparacao 1
    if (lig > k)
    {
        do {
            do {
                prep = random_l_h(0, vert-1);
            }while(a[prep] != 1);

            a[prep] = 0;
            lig--;
        }while(lig != k);
    }
    if (lig < k)
    {
        do {
            do {
                prep = random_l_h(0, vert-1);
            }while(a[prep] != 0);

            a[prep] = 1;
            lig++;
        }while(lig != k);
    }

    // Array de conexoes
    int con[vert];
    for (int i = 0; i < vert; i++)
    {
        con[i] = 0;
    }

    for (int i = 0; i < vert; i++)
    {
        if (a[i] == 1)
        {
            for (int j = 0; j < vert; j++)
            {
                if(a[j] == 1 && *(mat+i*vert+j) != 0)
                {
                    con[i] = 1;
                    con[j] = 1;
                }
            }
        }
    }

    // Verifica se o num de conexoes criadas é menor que k (Assim sera impossivel)
    for (int i = 0; i < vert; i++)
    {
        if (con[i] == 1)
        {
            ncon++;
        }
    }
    if (ncon < k)
    {
        *v = 0;
        return 5000;
    }

    // Reparacao nova -> Faz substituição dos vertices sem ligacao por vertices que tenham alguma ligacao com o conjunto mas não fazem parte dele
    for (int i = 0; i < vert; i++)
    {
        if (con[i] == 0 && a[i] == 1)
        {
            // Solucao invalida
            do {
                prep = random_l_h(0, vert-1);
            }while(con[prep] == 1 && a[prep] == 0);

            a[i] = 0;
            a[prep] = 1;
        }
    }

    // Loop por toda a matriz para verificar se é valida
    for (int i = 0; i < vert; i++)
    {
        // Verifica se a linha pertence a solucao
        if (a[i] == 1)
        {
            for (int j = 0; j < vert; j++)
            {
                if(a[j] == 1 && *(mat+i*vert+j) != 0)
                {
                    // Adiciona o custo
                    total += *(mat+i*vert+j);
                }
            }
        }
    }

    *v = 1;
    return total / 2;
}

