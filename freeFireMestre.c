#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==========================
// Estrutura principal
// ==========================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
    int quantidade;
} Componente;

// ==========================
// Funções utilitárias
// ==========================
void mostrarComponentes(Componente componentes[], int qtd) {
    printf("\n--- Componentes ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d | Quantidade: %d\n",
               i + 1,
               componentes[i].nome,
               componentes[i].tipo,
               componentes[i].prioridade,
               componentes[i].quantidade);
    }
    printf("-------------------\n\n");
}

// ==========================
// Função de cadastro
// ==========================
void cadastrarComponente(Componente componentes[], int *qtd) {
    if (*qtd >= 20) {
        printf("Mochila cheia! (máx. 20 componentes)\n");
        return;
    }

    Componente novo;
    printf("Digite o nome do componente: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Digite o tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Digite a prioridade (1 a 10): ");
    scanf("%d", &novo.prioridade);

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpar buffer

    componentes[*qtd] = novo;
    (*qtd)++;

    printf("\nComponente adicionado!\n");
    mostrarComponentes(componentes, *qtd);
}

// ==========================
// Função para descartar componente
// ==========================
int descartarComponentePorNome(Componente componentes[], int *qtd, char nome[], int *comparacoes) {
    if (*qtd == 0) return 0;

    int idx = -1;
    for (int i = 0; i < *qtd; i++) {
        (*comparacoes)++;
        if (strcmp(componentes[i].nome, nome) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) return 0;

    for (int j = idx; j < *qtd - 1; j++) {
        componentes[j] = componentes[j + 1];
    }
    (*qtd)--;

    return 1;
}

// ==========================
// Algoritmos de ordenação
// ==========================
void bubbleSortNome(Componente componentes[], int qtd, int *comparacoes) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
}

void insertionSortTipo(Componente componentes[], int qtd, int *comparacoes) {
    for (int i = 1; i < qtd; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        while (j >= 0 && strcmp(componentes[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            componentes[j + 1] = componentes[j];
            j--;
        }
        if (j >= 0) (*comparacoes)++;
        componentes[j + 1] = chave;
    }
}

void selectionSortPrioridade(Componente componentes[], int qtd, int *comparacoes) {
    for (int i = 0; i < qtd - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < qtd; j++) {
            (*comparacoes)++;
            if (componentes[j].prioridade < componentes[minIndex].prioridade) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Componente temp = componentes[i];
            componentes[i] = componentes[minIndex];
            componentes[minIndex] = temp;
        }
    }
}

// ==========================
// Busca binária por nome
// ==========================
int buscaBinariaPorNome(Componente componentes[], int qtd, char nome[], int *comparacoes) {
    int inicio = 0, fim = qtd - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(componentes[meio].nome, nome);

        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

// ==========================
// Medição de tempo
// ==========================
double medirTempo(void (*algoritmo)(Componente[], int, int*), Componente componentes[], int qtd, int *comparacoes) {
    clock_t inicio = clock();
    algoritmo(componentes, qtd, comparacoes);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// ==========================
// Função principal
// ==========================
int main() {
    Componente componentes[20];
    int qtd = 0;
    int opcao;

    do {
        printf("\n===== MÓDULO FINAL: TORRE DE FUGA =====\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Ordenar por nome (Bubble Sort)\n");
        printf("3 - Ordenar por tipo (Insertion Sort)\n");
        printf("4 - Ordenar por prioridade (Selection Sort)\n");
        printf("5 - Buscar componente-chave (Busca Binária - por nome)\n");
        printf("6 - Mostrar todos componentes\n");
        printf("7 - Descartar componente por nome\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                cadastrarComponente(componentes, &qtd);
                break;

            case 2: {
                int comparacoes = 0;
                double tempo = medirTempo(bubbleSortNome, componentes, qtd, &comparacoes);
                printf("\nOrdenado por nome (Bubble Sort).\n");
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(componentes, qtd);
                break;
            }

            case 3: {
                int comparacoes = 0;
                double tempo = medirTempo(insertionSortTipo, componentes, qtd, &comparacoes);
                printf("\nOrdenado por tipo (Insertion Sort).\n");
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(componentes, qtd);
                break;
            }

            case 4: {
                int comparacoes = 0;
                double tempo = medirTempo(selectionSortPrioridade, componentes, qtd, &comparacoes);
                printf("\nOrdenado por prioridade (Selection Sort).\n");
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(componentes, qtd);
                break;
            }

            case 5: {
                if (qtd == 0) {
                    printf("Nenhum componente cadastrado!\n");
                    break;
                }
                char nomeBusca[30];
                printf("Nome do componente-chave: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;

                int comparacoes = 0;
                int pos = buscaBinariaPorNome(componentes, qtd, nomeBusca, &comparacoes);
                if (pos != -1) {
                    printf("\nComponente encontrado:\n");
                    printf("Nome: %s | Tipo: %s | Prioridade: %d | Quantidade: %d\n",
                           componentes[pos].nome,
                           componentes[pos].tipo,
                           componentes[pos].prioridade,
                           componentes[pos].quantidade);
                } else {
                    printf("\nComponente '%s' não encontrado.\n", nomeBusca);
                }
                printf("Comparações (busca binária): %d\n", comparacoes);
                break;
            }

            case 6:
                mostrarComponentes(componentes, qtd);
                break;

            case 7: {
                if (qtd == 0) {
                    printf("Nenhum componente para descartar.\n");
                    break;
                }
                char alvo[30];
                printf("Nome do componente a descartar: ");
                fgets(alvo, 30, stdin);
                alvo[strcspn(alvo, "\n")] = 0;

                int comparacoesDesc = 0;
                int removido = descartarComponentePorNome(componentes, &qtd, alvo, &comparacoesDesc);
                if (removido) {
                    printf("\nComponente '%s' descartado com sucesso.\n", alvo);
                } else {
                    printf("\nComponente '%s' não encontrado.\n", alvo);
                }
                printf("Comparações (descartar): %d\n", comparacoesDesc);
                mostrarComponentes(componentes, qtd);
                break;
            }

            case 0:
                printf("\nSaindo da torre... boa sorte na fuga!\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
