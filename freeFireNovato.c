#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ----------------------------
// Estrutura que representa um item do inventário
// ----------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ----------------------------
// Funções do sistema
// ----------------------------
void inserirItem(Item mochila[], int *contador);
void removerItem(Item mochila[], int *contador);
void listarItens(Item mochila[], int contador);
void buscarItem(Item mochila[], int contador);

// ----------------------------
// Função principal
// ----------------------------
int main() {
    Item mochila[MAX_ITENS];
    int contador = 0;
    int opcao;

    do {
        printf("\n=== SISTEMA DE INVENTÁRIO ===\n");
        printf("1 - Inserir novo item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem(mochila, &contador);
                break;
            case 2:
                removerItem(mochila, &contador);
                break;
            case 3:
                listarItens(mochila, contador);
                break;
            case 4:
                buscarItem(mochila, contador);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// ----------------------------
// Função: Inserir novo item na mochila
// ----------------------------
void inserirItem(Item mochila[], int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("Digite o nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; // Remove '\n'

    printf("Digite o tipo do item (arma, munição, cura, etc): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar();

    mochila[*contador] = novoItem;
    (*contador)++;

    printf("Item adicionado com sucesso!\n");
    listarItens(mochila, *contador);
}

// ----------------------------
// Função: Remover item pelo nome
// ----------------------------
void removerItem(Item mochila[], int *contador) {
    if (*contador == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = 0;

    int i, encontrado = 0;
    for (i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            for (int j = i; j < *contador - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*contador)--;
            printf("Item '%s' removido com sucesso!\n", nomeRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado!\n");
    }

    listarItens(mochila, *contador);
}

// ----------------------------
// Função: Listar todos os itens da mochila
// ----------------------------
void listarItens(Item mochila[], int contador) {
    if (contador == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    printf("\n--- ITENS NA MOCHILA ---\n");
    for (int i = 0; i < contador; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("-------------------------\n");
}

// ----------------------------
// Função: Buscar item pelo nome (busca linear)
// ----------------------------
void buscarItem(Item mochila[], int contador) {
    if (contador == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (int i = 0; i < contador; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("Item '%s' não encontrado.\n", nomeBusca);
}
