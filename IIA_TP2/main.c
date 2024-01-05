#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"
#include "funcao.h"

#define DEFAULT_RUNS 30
#define PROB_RECOMBINACAO 0.3
#define PROB_MUTACAO 0.001
#define NUM_GERACOES 2500
#define POPSIZE 100

int main(int argc, char *argv[]) {
    char    nome_fich[100];
    int     vert, num_iter, k, runs, custo, best_custo=5000,arestas,i,opcao;
    int     *grafo, *sol, *best;
    float   mbf = 0.0;
    pchrom      pop = NULL, parents = NULL;
    int x;
    chrom melhor_ronda_atual, melhor_ronda_final;
    int geracao_atual, inv;
    int solucoes_invalidas;

    // Defina os valores da estrutura manualmente
    int popsize = 100;            // Exemplo: tamanho da população 100
    int numGeracoes = 2500;       // Exemplo: 2500 gerações
    float probRecombinacao = 0.3; // Exemplo: probabilidade de recombinação 0.3
    float probMutacao = 0.01;     // Exemplo: probabilidade de mutação 0.01


    if(argc == 3)
    {
        runs = atoi(argv[2]);
        strcpy(nome_fich, argv[1]);
    }
    else
    if(argc == 2)
    {
        runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    }
    else
    {
        runs = DEFAULT_RUNS;
        printf("Nome do Ficheiro: ");
        gets(nome_fich);
    }
    if(runs <= 0)
        return 0;



    // Menu
    printf("1- Trepa Colinas\n");
    printf("2- Algoritmo Evolutivo\n");
    printf("3- Algoritmo Hibrido\n");

    printf("Escolha: ");
    scanf("%d",&opcao);
    init_rand(); // Preenche matriz de adjacencias
    grafo = init_dados(nome_fich, &k,&vert,&arestas);


    sol = malloc(sizeof(int)*vert);
    best = malloc(sizeof(int)*vert);
    if(sol == NULL || best == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    if(opcao==1){


        for( i=0; i<runs; i++)
        {
            // Gerar solucao inicial
            gera_sol_inicial(sol, vert,k);
            puts("\n");
            printf("\nSolucao Inicial %d:", i);
            escreve_sol(sol, vert);

            // Recrestilizacao Simulada
            custo = trepa_colinas(sol,grafo,vert,10000);

            // Escreve resultados da repeticao k
            printf("\nRepeticao %d:", i);
            escreve_sol(sol, vert);
            printf("Custo final: %2d\n", custo);
            mbf += custo;
            if(i==0 || best_custo > custo)
            {
                best_custo = custo;
                substitui(best, sol, vert);
            }
        }
        // Escreve eresultados globais
        printf("\n\nMBF: %f\n", mbf/i);
        printf("\nMelhor solucao encontrada");
        escreve_sol(best, vert);
        printf("Custo final: %2d\n", best_custo);

    }

    else if(opcao==2){

        // Algoritmo Evolutivo


        for (x = 0; x < runs; x++) {
            printf("\nRepeticao %d\n", x + 1);
            printf("--------------------");

            // Geração da população inicial
            pop = init_pop(vert, k);
            // Avalia a população inicial
            evaluate(pop, grafo, vert, k, popsize);
            // Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
            melhor_ronda_atual = pop[0];

            // Encontra-se a melhor solução dentro de toda a população
            melhor_ronda_atual = get_best(pop, popsize, melhor_ronda_atual);

            // Reserva espaço para os pais da população seguinte
            parents = malloc(sizeof(chrom)*popsize);
            // Caso não consiga fazer a alocação, envia aviso e termina o programa
            if (parents==NULL)
            {
                printf("Erro na alocacao de memoria\n");
                exit(1);
            }
            geracao_atual = 1;
            // Ciclo de optimização
            while (geracao_atual <= numGeracoes)
            {
                // Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
                tournament(pop, popsize, parents);
                // Torneio com mais elementos
                //tournament_geral(pop, POPSIZE, parents);
                // Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
                genetic_operators(parents, popsize, pop, vert);
                // Avalia a nova população (a dos filhos)
                evaluate(pop, grafo, vert, k, popsize);
                // Actualiza a melhor solução encontrada
                melhor_ronda_atual = get_best(pop, popsize, melhor_ronda_atual);
                geracao_atual++;
            }
            // Contagem das soluções inválidas
            for (inv=0, i=0; i<popsize; i++)
                if (pop[i].valido == 0)
                    inv++;
            // Escreve resultados da repetição que terminou
            //printf("\nRepeticao %d:", x);
            write_best(melhor_ronda_atual, vert);

            printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/popsize);
            mbf += melhor_ronda_atual.fitness;
            if (x==0 || melhor_ronda_atual.fitness < melhor_ronda_final.fitness)
                melhor_ronda_final = melhor_ronda_atual;


            // Liberta a memória usada
            free(parents);
            free(pop);
        }

        printf("\n\nMBF: %f\n", mbf / runs);
        printf("\nMelhor solucao encontrada");
        write_best(melhor_ronda_final, vert);
    }

    else if(opcao==3){

        for (int i = 0; i < runs; i++)
        {
            printf("Repeticao %d:\n", i+1);

            // Gera populacao inicial
            pop = init_pop(vert, k);

            // Avalia populacao inicial
            evaluate(pop, grafo, vert, k, popsize);

            // Hibrido i)
            for(int m=0;m<popsize;m++){
               pop[m].fitness= trepa_colinas(pop[i].p,grafo,vert,10000);
            }


           melhor_ronda_atual= pop[0];
           melhor_ronda_atual = get_best(pop, popsize, melhor_ronda_atual);

            parents = malloc(sizeof(chrom)*popsize);
            if (parents == NULL)
            {
                printf("Erro na alocacao de memoria\n");
                exit(1);
            }

            geracao_atual = 1;
            // Clico de otimizacao
            while (geracao_atual <=numGeracoes)
            {
                // Encontrar os progenitores
                // Torneio binario
                //tournament(pop, popsize, parents);
                // Torneio com mais elementos
                tournament_geral(pop, POPSIZE, parents);

                // Operadores genericos
                genetic_operators(parents, popsize, pop, vert);

                // Avalia nova populacao
                evaluate(pop, grafo, vert, k, popsize);




                // Atualiza nova solucao
               melhor_ronda_atual = get_best(pop, popsize, melhor_ronda_atual);
               geracao_atual++;
            }



            // Contagem de solucoes invalidas
            inv = 0;
            for (int i = 0; i < popsize; i++)
            {
                if (pop[i].valido == 0)
                {
                    inv++;
                }
            }

            //HIBRIDO2-MELHORAR POP FINAL
            //for(int m=0;m<popsize;m++){
            //   pop[m].fitness= trepa_colinas(pop[i].p,grafo,vert,10000);
            //}
            //melhor_ronda_atual= get_best(pop,popsize,melhor_ronda_atual);

            // Escreve resultados
            write_best(melhor_ronda_atual, vert);
            printf("\nPercentagem Invalidos %f\n", 100*(float)inv/popsize);
            mbf += melhor_ronda_atual.fitness;
            if (i == 0 || melhor_ronda_atual.fitness < melhor_ronda_final.fitness)
            {
                melhor_ronda_final = melhor_ronda_atual;
            }

            free(parents);
            free(pop);
        }

        // Resultados finais
        printf("\n\nMBF: %f\n", mbf/runs);
        printf("\nMelhor solucao encontrada");
        write_best(melhor_ronda_final, vert);



    }


    else{
        printf("Opcao invalida\n");
        free(grafo);
        free(sol);
        free(best);
        exit(1);
    }

    free(grafo);
    free(sol);
    free(best);
    return 0;
}