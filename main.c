#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

/*
 * Struct Item
 * Representa um item do inventario (mochila).
 * - nome: nome do item
 * - tipo: categoria do item (arma, municao, cura, ferramenta, etc)
 * - quantidade: quantidade coletada
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/*
 * Funcao: listarItens
 * Mostra todos os itens cadastrados ate o momento.
 * itens -> vetor de Item
 * total -> quantidade atual de itens
 */
void listarItens(Item itens[], int total) {
    printf("\n=== ITENS NA MOCHILA (%d/%d) ===\n", total, MAX_ITENS);

    if (total == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, itens[i].nome, itens[i].tipo, itens[i].quantidade);
    }
}

/*
 * Funcao auxiliar: buscarIndicePorNome
 * Busca sequencial para achar o indice do item pelo nome.
 * Retorna o indice se encontrar, senao retorna -1.
 */
int buscarIndicePorNome(Item itens[], int total, const char *nome) {
    for (int i = 0; i < total; i++) {
        if (strcmp(itens[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * Funcao: inserirItem
 * Cadastra um novo item no inventario se ainda houver espaco.
 * itens -> vetor de Item
 * total -> ponteiro para quantidade atual (sera atualizada)
 */
void inserirItem(Item itens[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\n=== INSERIR ITEM ===\n");

    // Le nome permitindo espacos (ate 29 chars)
    printf("Digite o nome do item: ");
    scanf(" %29[^\n]", novo.nome);

    // Le tipo (palavra unica)
    printf("Digite o tipo do item (arma, municao, cura, etc): ");
    scanf(" %19s", novo.tipo);

    // Le quantidade
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    if (novo.quantidade <= 0) {
        printf("Quantidade invalida. Ajustando para 1.\n");
        novo.quantidade = 1;
    }

    // Insere no final da lista
    itens[*total] = novo;
    (*total)++;

    printf("Item inserido com sucesso!\n");
}

/*
 * Funcao: removerItem
 * Remove um item pelo nome, reorganizando o vetor (lista sequencial).
 * itens -> vetor de Item
 * total -> ponteiro para quantidade atual (sera atualizada)
 */
void removerItem(Item itens[], int *total) {
    if (*total == 0) {
        printf("\nMochila vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[30];

    printf("\n=== REMOVER ITEM ===\n");
    printf("Digite o nome do item a remover: ");
    scanf(" %29[^\n]", nomeBusca);

    int idx = buscarIndicePorNome(itens, *total, nomeBusca);

    if (idx == -1) {
        printf("Item '%s' nao encontrado.\n", nomeBusca);
        return;
    }

    // Desloca os itens para "tampar o buraco"
    for (int i = idx; i < *total - 1; i++) {
        itens[i] = itens[i + 1];
    }

    (*total)--;

    printf("Item removido com sucesso!\n");
}

/*
 * Funcao: buscarItem
 * Busca sequencial por nome e exibe os dados do item encontrado.
 * itens -> vetor de Item
 * total -> quantidade atual de itens
 */
void buscarItem(Item itens[], int total) {
    if (total == 0) {
        printf("\nMochila vazia. Nada para buscar.\n");
        return;
    }

    char nomeBusca[30];

    printf("\n=== BUSCAR ITEM ===\n");
    printf("Digite o nome do item a buscar: ");
    scanf(" %29[^\n]", nomeBusca);

    int idx = buscarIndicePorNome(itens, total, nomeBusca);

    if (idx == -1) {
        printf("Item '%s' nao encontrado.\n", nomeBusca);
        return;
    }

    printf("\nItem encontrado!\n");
    printf("Nome: %s\n", itens[idx].nome);
    printf("Tipo: %s\n", itens[idx].tipo);
    printf("Quantidade: %d\n", itens[idx].quantidade);
}

int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    printf("=== SISTEMA DE INVENTARIO (MOCHILA) ===\n");

    do {
        printf("\nMenu:\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens); // listar apos operacao
                break;

            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens); // listar apos operacao
                break;

            case 3:
                listarItens(mochila, totalItens);
                break;

            case 4:
                buscarItem(mochila, totalItens);
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
