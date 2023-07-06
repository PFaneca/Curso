// Feito por: Pedro Lino Neves Faneca nº2022134142
#include <stdio.h>
#include <stdlib.h>
#include "linhas.h"


int main() {
    // Inicializa a lista de paragens
    pstop tab = NULL;
    int i, total = 0;
    // Inicializa a lista de linhas
    plinha tabL = NULL;
    int totalL = 0;
    // Ambas as funçoes abaixo servem para limpar os ficheiros binarios(usei para testes)
    //limparFicheiroBinario("paragensbin.bin");
    //limparFicheiroBinario("linhas.bin");
    // Carrega as paragens e as linhas do ficheiro binario
    tab = carregarParagens(&total);
    tabL = carregarLinhas();
    // Menu
    int opcao;
    do {

        printf("\n\n\n\n\n\n\n---- MENU ----\n");
        printf("1. Adicionar paragem\n");
        printf("2. Listar paragens\n");
        printf("3. Eliminar paragem\n");
        printf("4. Adicionar linha\n");
        printf("5. Listar linhas\n");
        printf("6. Linhas por paragem\n");
        printf("7. Atualizar linha\n");
        printf("8. Calcular percurso\n");
        printf("9. Ler arquivo para adicionar linha\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        // Lê a opção do utilizador
        scanf("%d", &opcao);
        limparBufferEntrada();
        // Verifica se a opção é válida
        if (opcao < 0 || opcao > 9) {
            printf("Opção invalida. Tente novamente.\n");
            continue; // Reinicia o loop
        }
        switch (opcao) {
            case 1:
                tab = addP(tab, &total);
                break;
            case 2:
                listaP(tab, total);
                break;
            case 3: {
                char id[5];
                printf("Digite o codigo da paragem a eliminar: ");
                scanf("%s", id);
                limparBufferEntrada();
                tab = eliminaP(tab, &total, id, tabL);
            }
                break;
            case 4:
                tabL = addL(tabL, &totalL, tab, &total);
                break;
            case 5:
                listaL(tabL);
                break;
            case 6: {
                char nomeParagem[100];
                printf("Digite o nome da paragem: ");
                scanf("%s", nomeParagem);
                limparBufferEntrada();
                linhasP(tabL, nomeParagem);
            }
                break;
            case 7: {
                char nomeLinha[100];
                printf("Digite o nome da linha: ");
                scanf("%s", nomeLinha);
                limparBufferEntrada();
                tabL = atualizaL(tabL, nomeLinha);
            }
                break;
            case 8: {
                char partida[100], chegada[100];
                printf("Digite a paragem de partida: ");
                scanf("%s", partida);
                limparBufferEntrada();
                printf("Digite a paragem de chegada: ");
                scanf("%s", chegada);
                limparBufferEntrada();
                calcularPercurso(tabL, partida, chegada);
            }
                break;
            case 9: {
                plinha novaLinha = lerLinhaDeFicheiro("linhas.txt", tabL, &total);
                if (novaLinha != NULL) {
                    // Adiciona a nova linha à lista de linhas
                    tabL = adicionarLinhaLida(tabL, &totalL, tab, &total);
                }
            }
                break;
            case 0:
                printf("A terminar...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
    // Guarda as paragens e as linhas no ficheiro binario
    salvarParagens(tab, total);
    salvarLinhas(tabL);
    // Liberta a memória alocada
    freeLinha(tabL);
    free(tab);
    return 0;
}
