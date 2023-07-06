// Feito por: Pedro Lino Neves Faneca nº2022134142
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linhas.h"

void gerar_codigo(char *codigo) {
    // Gera um código aleatório de 4 caracteres
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 4; i++) {
        int index = rand() % strlen(charset);
        codigo[i] = charset[index];
    }
    // Termina a string
    codigo[4] = '\0';
}

pstop addP(pstop p, int *total) {
    pstop aux;
    int i, contador;
    char codigo_local[5];
    char nome_paragem[100];
    // Realoca memória para a paragem
    aux = realloc(p, sizeof(stop) * (*total + 1));
    // Verifica se a memória foi alocada
    if (aux == NULL) {
        return p;
    }
    p = aux;
    printf("Nome da nova paragem: ");
    scanf(" %[^\n]", nome_paragem); // Leitura do nome com espaços em branco


    // Verificar se o nome ou código da paragem já existe
    for (i = 0; i < (*total); i++) {
        if (strcmp(p[i].nome, nome_paragem) == 0) {
            printf("Nome de paragem ja existente. Paragem nao adicionada.\n");
            return p;
        }
        if (strcmp(p[i].codigo, codigo_local) == 0) {
            printf("Codigo de paragem ja existente. Paragem nao adicionada.\n");
            return p;
        }
    }
    // Adiciona nome e id à paragem
    strcpy(p[*total].nome, nome_paragem);
    gerar_codigo(codigo_local);
    strcpy(p[*total].codigo, codigo_local);
    (*total)++;
    return p;
}


void listaP(pstop p, int total) {
    // Listar todas as paragens
    for (int i = 0; i < total; i++) {
        printf("\nParagem[%d]: %s %s", i, p[i].nome, p[i].codigo);

    }
}

pstop eliminaP(pstop tab, int *total, char *id, plinha tabL) {
    int i, contador = 0, total_paragens;
    for (i = 0; i < (*total); i++) {
        if (strcmp(tab[i].codigo, id) == 0) {
            // Verifica se a paragem está em alguma linha
            int paragemEncontrada = 0;
            plinha auxL = tabL;
            while (auxL != NULL) {
                // Verifica se a paragem está na linha atual
                pstop auxP = auxL->paragem;
                int j;
                total_paragens = auxL->total_paragens;
                for (j = 0; j < total_paragens; j++) {
                    if (strcmp(auxP[j].codigo, id) == 0) {
                        paragemEncontrada = 1;
                        break;
                    }
                }
                // Se a paragem foi encontrada, sai do ciclo
                if (paragemEncontrada == 1) {
                    break;
                }
                auxL = auxL->prox;
            }
            // Se a paragem não foi encontrada em nenhuma linha, elimina a paragem
            if (paragemEncontrada == 0) {
                tab[i] = tab[*total - 1];
                (*total)--;
                contador++;
            }
        }
    }
    if (contador == 0) {
        printf("\nParagem nao encontrada ou associada a uma linha.\n");
    }
    return tab;
}


plinha addL(plinha p, int *totalL, pstop paragens, int *totalP) {
    plinha aux, novo;
    int i, contador, total_paragens;
    char nome_local[50], nome_paragem[50];
    // Realoca memória para a linha
    novo = malloc(sizeof(linha));
    // Verifica se a memória foi alocada
    if (novo == NULL) {
        printf("Erro ao alocar memória para nova linha\n");
        return p;
    }
    // Adiciona nome à linha
    printf("\nNome da nova linha: ");
    scanf("%s", nome_local);
    // Verifica se o nome da linha já existe
    aux = p;
    while (aux != NULL) {
        if (strcmp(nome_local, aux->nome) == 0) {
            printf("Nome da linha ja existe. Digite um nome diferente.\n");
            free(novo);
            return p;
        }

        aux = aux->prox;
    }
    // Adiciona nome à linha e total de paragens que tem associado
    strcpy(novo->nome, nome_local);
    printf("Total de paragens: ");
    scanf("%d", &novo->total_paragens);
    total_paragens = novo->total_paragens;

    // Aloca memória para as paragens da linha
    novo->paragem = malloc(sizeof(stop) * total_paragens);
    for (i = 0; i < total_paragens; i++) {
        // Verifica se o nome da paragem existe
        do {
            contador = 0;
            printf("Nome da Paragem[%d]: ", i);
            scanf("%s", nome_paragem);
            for (int j = 0; j < (*totalP); j++) {
                if (strcmp(nome_paragem, paragens[j].nome) == 0) {
                    contador++;
                    break;
                }
            }
            if (contador == 0) {
                printf("Paragem invalida. Digite um nome de paragem existente.\n");
            }
        } while (contador == 0);
        // Verifica se o nome da paragem já existe na linha
        for (int j = 0; j < i; j++) {
            if (strcmp(novo->paragem[j].nome, nome_paragem) == 0) {
                printf("A paragem '%s' ja existe na linha. Digite um nome de paragem diferente.\n", nome_paragem);
                i--; // Decrementa o índice para refazer a leitura da paragem
                break;
            }
        }
        strcpy(novo->paragem[i].nome, nome_paragem);

    }
    // Adiciona a linha à lista de linhas
    novo->prox = NULL;
    if (p == NULL) {
        p = novo;
    } else {
        aux = p;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    // Incrementa o total de linhas
    (*totalL)++;
    printf("Linha '%s' adicionada com sucesso.\n", novo->nome);
    return p;
}

void listaL(plinha p) {
    plinha aux;
    int y = 0, total_paragens;
    char nomeLinha[100];
    aux = p;
    printf("\n--------------------------\n");
    while (aux != NULL) {
        // Lista todas as linhas
        printf("Linha[%d]:", y++);
        strcpy(nomeLinha, aux->nome);
        printf("\nNome da linha: %s", nomeLinha);
        printf("\nTotal de paragens: %d", aux->total_paragens);
        total_paragens = aux->total_paragens;
        for (int i = 0; i < total_paragens; i++) {
            printf("\nParagem[%d]: %s", i, aux->paragem[i].nome);

        }
        printf("\n--------------------------\n");
        aux = aux->prox;
    }
}

void linhasP(plinha p, char *nomeParagem) {
    plinha aux = p;
    int total_paragens;
    char linhasParagem[100];
    strcpy(linhasParagem, "");
    while (aux != NULL) {
        total_paragens = aux->total_paragens;
        // Verifica se a paragem existe na linha
        for (int i = 0; i < total_paragens; i++) {
            if (strcmp(aux->paragem[i].nome, nomeParagem) == 0) {
                // Adiciona o nome da linha à string
                strcat(linhasParagem, aux->nome);
                strcat(linhasParagem, ", ");
                break; // Evita adicionar o mesmo nome de linha várias vezes
            }
        }
        aux = aux->prox;
    }
    if (strlen(linhasParagem) > 0) {
        // Remove a última vírgula e espaço
        linhasParagem[strlen(linhasParagem) - 2] = '\0';

        printf("\nAs linhas %s passam pela paragem %s.\n", linhasParagem, nomeParagem);
    } else {
        printf("Nenhuma linha passa pela paragem %s\n", nomeParagem);
    }
}

plinha atualizaL(plinha p, char *nomeLinha) {
    plinha aux;
    int i, total_paragens;
    char nome_local[50], nomeParagem[50];
    aux = p;
    while (aux != NULL) {
        if (strcmp(aux->nome, nomeLinha) == 0) {
            int opcao;
            // Menu de opções para melhorar a experiência do utilizador
            printf("1. Adicionar paragem\n");
            printf("2. Eliminar paragem\n");
            printf("Escolha a opcao: ");
            scanf("%d", &opcao);
            switch (opcao) {
                case 1: {
                    // Adicionar paragens
                    int novasParagens;

                    printf("Numero de paragens a adicionar: ");
                    scanf("%d", &novasParagens);
                    // Aloca mais memória para as paragens da linha
                    aux->paragem = realloc(aux->paragem, sizeof(stop) * (aux->total_paragens + novasParagens));
                    // Lê o nome das novas paragens
                    for (i = 0; i < novasParagens; i++) {
                        printf("Nome da Paragem[%d]: ", aux->total_paragens + i);
                        scanf("%s", aux->paragem[aux->total_paragens + i].nome);
                    }
                    // Atualiza o total de paragens da linha
                    aux->total_paragens += novasParagens;

                    printf("Paragens adicionadas com sucesso!\n");
                    break;
                }
                case 2: {
                    // Elimina paragens
                    int paragensEliminadas;

                    printf("Numero de paragens a eliminar: ");
                    scanf("%d", &paragensEliminadas);
                    for (int z = 0; z < paragensEliminadas; z++) {
                        printf("Nome da paragem a eliminar: ");
                        scanf("%s", nomeParagem);
                        // Procura o índice da paragem
                        int indiceParagem = -1;
                        total_paragens = aux->total_paragens;
                        for (i = 0; i < total_paragens; i++) {
                            if (strcmp(aux->paragem[i].nome, nomeParagem) == 0) {
                                // Guarda o índice da paragem
                                indiceParagem = i;
                                break;
                            }
                        }
                        // Se a paragem foi encontrada, remove-a
                        if (indiceParagem != -1) {
                            for (int y = indiceParagem; y < total_paragens - 1; y++) {
                                strcpy(aux->paragem[y].nome, aux->paragem[y + 1].nome);
                            }
                            // Aloca menos memória para as paragens da linha
                            aux->paragem = realloc(aux->paragem, sizeof(stop) * (aux->total_paragens - 1));
                            aux->total_paragens--;

                            printf("Paragem eliminada com sucesso!\n");
                        } else {
                            printf("Paragem nao encontrada!\n");
                        }
                    }
                    break;
                }
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
            return p;
        }
        aux = aux->prox;
    }
    printf("Linha nao encontrada!\n");
    return p;
}

void calcularPercurso(plinha p, char *partida, char *chegada) {
    printf("Percursos entre as paragens %s e %s:\n", partida, chegada);
    plinha aux, aux2, aux3;
    aux = p;
    int total_paragens, cont = 0;

    // Percursos sem mudança de linha
    while (aux != NULL) {
        total_paragens = aux->total_paragens;
        for (int i = 0; i < total_paragens; i++) {
            if (strcmp(aux->paragem[i].nome, partida) == 0) {
                // Verifica se a paragem de chegada existe na linha
                for (int j = i + 1; j < total_paragens; j++) {
                    // Se a paragem de chegada existe na linha, imprime o percurso
                    if (strcmp(aux->paragem[j].nome, chegada) == 0) {
                        printf("Linha %s: ", aux->nome);
                        cont++;
                        for (int k = i; k <= j; k++) {
                            // Se for a última paragem, não imprime a seta
                            if (k == j) {
                                printf("%s\n", aux->paragem[k].nome);
                                break;
                            }
                            // Imprime a paragem do percurso com a seta para a próxima paragem
                            printf("%s -> ", aux->paragem[k].nome);
                        }
                    }
                }
            }
        }
        aux = aux->prox;
    }

    // Percursos com mudança de linha
    char paragem_local[100];
    aux2 = p;
    while (aux2 != NULL) {
        total_paragens = aux2->total_paragens;
        for (int i = 0; i < total_paragens; i++) {
            // Verifica se a paragem de partida existe na linha
            if (strcmp(aux2->paragem[i].nome, partida) == 0) {
                // Copia o nome da paragem imediatamente a seguir para uma paragem local
                strcpy(paragem_local, aux2->paragem[i + 1].nome);
                aux3 = p;
                while (aux3 != NULL) {
                    if (aux3 != aux2) {
                        // Verifica se a paragem  local  existe em outra linha
                        total_paragens = aux3->total_paragens;
                        for (int j = 0; j < total_paragens; j++) {
                            if (strcmp(aux3->paragem[j].nome, paragem_local) == 0) {
                                for (int k = j + 1; k < total_paragens; k++) {
                                    // Verifica se a paragem de chegada existe na linha
                                    if (strcmp(aux3->paragem[k].nome, chegada) == 0) {
                                        // Imprime o nome da linha de onde parte o percurso
                                        printf("Linha %s: ", aux2->nome);
                                        cont++;
                                        for (int l = i; l < aux2->total_paragens; l++) {
                                            if (strcmp(aux2->paragem[l].nome, paragem_local) == 0) {
                                                // Não imprime a seta para a paragem local
                                                printf("%s -> ", aux2->paragem[l].nome);
                                                break;
                                            }
                                            // Imprime o percurso até à paragem local
                                            printf("%s -> ", aux2->paragem[l].nome);
                                        }
                                        // Imprime o nome da linha para que se mudou no percurso
                                        printf("Linha %s: ", aux3->nome);
                                        for (int l = j; l <= k; l++) {
                                            if (l == k) {
                                                // Imprime a paragem de chegada sem a seta
                                                printf("%s\n", aux3->paragem[l].nome);
                                                break;
                                            }
                                            // Imprime o percurso da paragem local até à paragem de chegada
                                            printf("%s -> ", aux3->paragem[l].nome);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    aux3 = aux3->prox;
                }
            }
        }
        aux2 = aux2->prox;
    }

    if (cont == 0) {
        printf("Nao existe percurso direto entre as paragens %s e %s\n", partida, chegada);
    }
}

// Função para armazenar as paragens num ficheiro binário
void salvarParagens(pstop p, int total) {
    // Abre o ficheiro para escrita
    FILE *f = fopen("paragensbin.bin", "wb");
    // Verifica se o ficheiro foi aberto
    if (f == NULL) {
        printf("Erro ao abrir o arquivo de paragens.\n");
        return;
    }
    // Escreve o total de paragens e as paragens no arquivo
    fwrite(&total, sizeof(int), 1, f);
    fwrite(p, sizeof(struct dados), total, f);
    // Fecha o ficheiro
    fclose(f);
    printf("Paragens salvas com sucesso.\n");
}

// Função para carregar as paragens de um ficheiro binário
pstop carregarParagens(int *total) {
    // Abre o ficheiro para leitura
    FILE *f = fopen("paragensbin.bin", "rb");
    // Verifica se o ficheiro foi aberto
    if (f == NULL) {
        printf("Arquivo de paragens nao encontrado.\n");
        *total = 0;
        return NULL;
    }
    // Lê o total de paragens
    fread(total, sizeof(int), 1, f);
    // Aloca memória para as paragens
    pstop p = (pstop) malloc(*total * sizeof(struct dados));
    // Verifica se a memória foi alocada
    if (p == NULL) {
        printf("Erro ao alocar memoria.\n");
        fclose(f);
        *total = 0;
        return NULL;
    }
    // Lê as paragens do ficheiro
    fread(p, sizeof(struct dados), *total, f);
    // Fecha o ficheiro
    fclose(f);
    return p;
}

// Função para salvar as linhas num arquivo binário
void salvarLinhas(plinha p) {
    // Abre o ficheiro para escrita
    FILE *f = fopen("linhas.bin", "wb");
    // Verifica se o ficheiro foi aberto
    if (f == NULL) {
        printf("Erro ao abrir o arquivo de linhas.\n");
        return;
    }

    int totalLinhas = 0;
    plinha aux = p;

    // Conta o total de linhas
    while (aux != NULL) {
        totalLinhas++;
        aux = aux->prox;
    }
    // Escreve o total de linhas no arquivo
    fwrite(&totalLinhas, sizeof(int), 1, f);
    // Volta para o início da lista
    aux = p;
    // Escreve as linhas no ficheiro
    while (aux != NULL) {
        // Salva os dados da linha
        fwrite(aux, sizeof(struct dadosLinhas), 1, f);

        // Salva as paragens da linha
        fwrite(aux->paragem, sizeof(stop), aux->total_paragens, f);

        aux = aux->prox;
    }
    // Fecha o ficheiro
    fclose(f);
    printf("Linhas salvas com sucesso.\n");
}


// Função para carregar as linhas num arquivo binário
plinha carregarLinhas() {
    // Abre o ficheiro para leitura
    FILE *f = fopen("linhas.bin", "rb");
    // Verifica se o ficheiro foi aberto
    if (f == NULL) {
        printf("Arquivo de linhas não encontrado.\n");
        return NULL;
    }
    // Lê o total de linhas
    int totalLinhas = 0;
    fread(&totalLinhas, sizeof(int), 1, f);
    // Declara a lista de linhas
    plinha p = NULL;
    plinha temp = NULL;
    // Declara  a variável para armazenar temporariamente os dados de cada linha lida do ficheiro
    struct dadosLinhas linha;
    // Lê as linhas do arquivo
    for (int i = 0; i < totalLinhas; i++) {
        // Lê os dados da linha
        fread(&linha, sizeof(struct dadosLinhas), 1, f);
        // Aloca memória para a linha
        plinha novoElemento = (plinha) malloc(sizeof(struct dadosLinhas));
        // Copia os dados da linha para a memória alocada
        memcpy(novoElemento, &linha, sizeof(struct dadosLinhas));
        novoElemento->prox = NULL;
        // Aloca memória para o array de paragens da linha
        novoElemento->paragem = (pstop) malloc(sizeof(stop) * novoElemento->total_paragens);

        // Lê as paragens da linha a partir do ficheiro
        fread(novoElemento->paragem, sizeof(stop), novoElemento->total_paragens, f);
        // Adiciona a linha na lista
        if (p == NULL) {
            p = novoElemento;
            temp = p;
        } else {
            temp->prox = novoElemento;
            temp = temp->prox;
        }
    }
    // Fecha o ficheiro
    fclose(f);
    printf("Linhas carregadas com sucesso.\n");
    return p;
}

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Função para libertar a memória alocada para uma lista de linhas
void freeLinha(plinha p) {
    plinha temp;
    while (p != NULL) {
        temp = p;
        p = p->prox;
        // Liberta a memória alocada para o array de paragens da linha
        free(temp->paragem);
        // Liberta a memória alocada para a linha
        free(temp);
    }
}

// Função para liberar a memória alocada para a tabela de paragens ou de linhas dos ficheiros binários(usei para testar)
void limparFicheiroBinario(const char *nomeFicheiro) {
    // Abre o ficheiro para escrita
    FILE *f = fopen(nomeFicheiro, "wb");
    // Verifica se o ficheiro foi aberto
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    // Fecha o arquivo vazio
    fclose(f);
    printf("Arquivo limpo com sucesso.\n");
}

// Função para encontrar uma paragem na tabela de paragens
pstop buscarParagem(pstop p, int totalP, char *codigo) {
    for (int i = 0; i < totalP; i++) {
        // Verifica se o código da paragem é igual ao código procurado
        if (strcmp(p[i].codigo, codigo) == 0) {
            // Retorna o endereço da paragem
            return &p[i];
        }
    }
    return NULL; // Paragem não encontrada
}

plinha lerLinhaDeFicheiro(char *nomeFicheiro, pstop p, int *totalP) {
    // Abre o ficheiro para leitura
    FILE *f = fopen(nomeFicheiro, "r");
    // Verifica se o ficheiro foi aberto
    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeFicheiro);
        return NULL;
    }
    // Ignora a primeira linha do arquivo
    plinha novaLinha = (plinha) malloc(sizeof(linha));
    // Verifica se a memória foi alocada
    if (novaLinha == NULL) {
        printf("Erro ao alocar memória para a nova linha.\n");
        fclose(f);
        return NULL;
    }
    // Lê o nome da linha
    char nomeLinha[100];
    // Verifica se o nome da linha foi lido
    if (fgets(nomeLinha, sizeof(nomeLinha), f) == NULL) {
        printf("Erro ao ler o nome da linha no arquivo.\n");
        fclose(f);
        free(novaLinha);
        return NULL;
    }
    // Remove o caractere de nova linha
    nomeLinha[strcspn(nomeLinha, "\n")] = '\0';
    // Inicializa a nova linha
    strcpy(novaLinha->nome, nomeLinha);
    novaLinha->total_paragens = 0;
    novaLinha->paragem = NULL;
    novaLinha->prox = NULL;
    // Lê as paragens da linha
    char codigoParagem[5];
    // Verifica se o código da paragem foi lido
    while (fgets(codigoParagem, sizeof(codigoParagem), f)) {
        codigoParagem[strcspn(codigoParagem, "\n")] = '\0'; // Remove o caractere de nova linha
        // Busca a paragem na tabela de paragens
        pstop paragem = buscarParagem(p, *totalP, codigoParagem);
        if (paragem != NULL) {
            // Incrementa o total de paragens da linha
            novaLinha->total_paragens++;

            // Realoca o array de paragens com o novo tamanho
            novaLinha->paragem = (pstop) realloc(novaLinha->paragem, novaLinha->total_paragens * sizeof(stop));
            if (novaLinha->paragem == NULL) {
                printf("Erro ao realocar memória para as paragens da linha.\n");
                fclose(f);
                // Libera a memória alocada para a linha
                freeLinha(novaLinha);
                return NULL;
            }

            // Copia a paragem encontrada para o array
            pstop novaParagem = &(novaLinha->paragem[novaLinha->total_paragens - 1]);
            strcpy(novaParagem->codigo, codigoParagem);
            strcpy(novaParagem->nome, paragem->nome);
        }
    }
    // Fecha o ficheiro
    fclose(f);
    return novaLinha;
}

plinha adicionarLinhaLida(plinha p, int *totalL, pstop paragens, int *totalP) {
    // Lê a nova linha do ficheiro
    plinha novaLinha = lerLinhaDeFicheiro("linhas.txt", paragens, totalP);
    // Verifica se a linha foi lida
    if (novaLinha != NULL) {
        // Verifica se a linha já existe na lista
        plinha aux = p;
        while (aux != NULL) {
            // Verifica se o nome da linha é igual ao nome da linha da lista
            if (strcmp(novaLinha->nome, aux->nome) == 0) {
                printf("A linha '%s' já existe na lista.\n", novaLinha->nome);
                // Liberta a memória alocada para a nova linha
                freeLinha(novaLinha);
                // Retorna a lista original sem modificação
                return p;
            }
            aux = aux->prox;
        }
        // Adiciona a nova linha à lista
        if (p == NULL) {
            p = novaLinha;
        } else {
            aux = p;
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = novaLinha;
        }
        (*totalL)++;
        printf("Linha '%s' adicionada com sucesso.\n", novaLinha->nome);
    }
    return p;
}





































