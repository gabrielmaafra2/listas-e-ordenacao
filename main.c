#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

/*  
 * Struct Item
 * Armazena nome, tipo e quantidade de um item da mochila.
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/*
 * Struct No
 * Representa um no da lista encadeada, contendo um Item e um ponteiro
 * para o proximo no da lista.
 */
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/* ========================
   CONTADORES DE COMPARACOES
   ======================== */

int comp_seq_vetor = 0;
int comp_bin_vetor = 0;
int comp_seq_lista = 0;

/* ============================
   FUNCOES PARA A MOCHILA COM VETOR
   ============================ */

/*
 * Inserir item no vetor
 */
void inserirItemVetor(Item vetor[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia.\n");
        return;
    }

    Item novo;
    printf("Nome do item: ");
    scanf(" %29[^\n]", novo.nome);

    printf("Tipo do item: ");
    scanf(" %19s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    vetor[*total] = novo;
    (*total)++;

    printf("Item inserido no vetor.\n");
}

/*
 * Remover item do vetor pelo nome
 */
void removerItemVetor(Item vetor[], int *total) {
    if (*total == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Nome do item a remover: ");
    scanf(" %29[^\n]", nomeBusca);

    int found = -1;
    for (int i = 0; i < *total; i++) {
        if (strcmp(vetor[i].nome, nomeBusca) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Item nao encontrado.\n");
        return;
    }

    for (int i = found; i < *total - 1; i++) {
        vetor[i] = vetor[i + 1];
    }

    (*total)--;

    printf("Item removido.\n");
}

/*
 * Listar itens do vetor
 */
void listarItensVetor(Item vetor[], int total) {
    printf("=== Mochila (Vetor) ===\n");
    if (total == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d) Nome: %s | Tipo: %s | Qtd: %d\n",
               i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}

/*
 * Buscar sequencial no vetor
 */
int buscarSequencialVetor(Item vetor[], int total, const char *nome) {
    comp_seq_vetor = 0;

    for (int i = 0; i < total; i++) {
        comp_seq_vetor++;
        if (strcmp(vetor[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

/*
 * Ordenar vetor por nome com Bubble Sort
 */
void ordenarVetor(Item vetor[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Item temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    printf("Vetor ordenado por nome.\n");
}

/*
 * Busca binaria no vetor (requer vetor ordenado)
 */
int buscarBinariaVetor(Item vetor[], int total, const char *nome) {
    int inicio = 0;
    int fim = total - 1;
    comp_bin_vetor = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comp_bin_vetor++;

        int cmp = strcmp(vetor[meio].nome, nome);

        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

/* ============================
   FUNCOES PARA LISTA ENCADEADA
   ============================ */

/*
 * Inserir item na lista
 */
void inserirItemLista(No **lista) {
    No *novo = (No*)malloc(sizeof(No));

    printf("Nome do item: ");
    scanf(" %29[^\n]", novo->dados.nome);

    printf("Tipo do item: ");
    scanf(" %19s", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *lista;
    *lista = novo;

    printf("Item inserido na lista.\n");
}

/*
 * Remover item da lista pelo nome
 */
void removerItemLista(No **lista) {
    if (*lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Nome do item: ");
    scanf(" %29[^\n]", nomeBusca);

    No *atual = *lista;
    No *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior == NULL)
                *lista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido.\n");
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item nao encontrado.\n");
}

/*
 * Listar itens da lista
 */
void listarItensLista(No *lista) {
    printf("=== Mochila (Lista Encadeada) ===\n");

    if (lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    No *aux = lista;
    while (aux != NULL) {
        printf("Nome: %s | Tipo: %s | Qtd: %d\n",
               aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
    }
}

/*
 * Busca sequencial na lista
 */
No* buscarSequencialLista(No *lista, const char *nome) {
    comp_seq_lista = 0;

    No *aux = lista;
    while (aux != NULL) {
        comp_seq_lista++;
        if (strcmp(aux->dados.nome, nome) == 0)
            return aux;

        aux = aux->proximo;
    }

    return NULL;
}

/*
 * Liberar lista
 */
void liberarLista(No **lista) {
    No *aux = *lista;
    while (aux != NULL) {
        No *tmp = aux;
        aux = aux->proximo;
        free(tmp);
    }
    *lista = NULL;
}

/* ============================
   MENU PRINCIPAL E EXECUCAO
   ============================ */

int main() {
    Item vetor[MAX_ITENS];
    int total = 0;

    No *lista = NULL;

    int opcao, sub;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Mochila com vetor\n");
        printf("2 - Mochila com lista encadeada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            do {
                printf("\n=== Mochila com Vetor ===\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Busca sequencial\n");
                printf("5 - Ordenar vetor\n");
                printf("6 - Busca binaria\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &sub);

                if (sub == 1) inserirItemVetor(vetor, &total);
                else if (sub == 2) removerItemVetor(vetor, &total);
                else if (sub == 3) listarItensVetor(vetor, total);
                else if (sub == 4) {
                    char nome[30];
                    printf("Nome a buscar: ");
                    scanf(" %29[^\n]", nome);
                    int pos = buscarSequencialVetor(vetor, total, nome);
                    printf("Comparacoes: %d\n", comp_seq_vetor);
                    if (pos >= 0)
                        printf("Item encontrado na posicao %d.\n", pos + 1);
                    else
                        printf("Nao encontrado.\n");
                }
                else if (sub == 5) ordenarVetor(vetor, total);
                else if (sub == 6) {
                    char nome[30];
                    printf("Nome a buscar: ");
                    scanf(" %29[^\n]", nome);
                    int pos = buscarBinariaVetor(vetor, total, nome);
                    printf("Comparacoes: %d\n", comp_bin_vetor);
                    if (pos >= 0)
                        printf("Item encontrado na posicao %d.\n", pos + 1);
                    else
                        printf("Nao encontrado.\n");
                }

            } while (sub != 0);
        }

        else if (opcao == 2) {
            do {
                printf("\n=== Mochila com Lista Encadeada ===\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Busca sequencial\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &sub);

                if (sub == 1) inserirItemLista(&lista);
                else if (sub == 2) removerItemLista(&lista);
                else if (sub == 3) listarItensLista(lista);
                else if (sub == 4) {
                    char nome[30];
                    printf("Nome a buscar: ");
                    scanf(" %29[^\n]", nome);
                    No *r = buscarSequencialLista(lista, nome);
                    printf("Comparacoes: %d\n", comp_seq_lista);
                    if (r != NULL)
                        printf("Item encontrado: %s (%s)\n",
                               r->dados.nome, r->dados.tipo);
                    else
                        printf("Nao encontrado.\n");
                }

            } while (sub != 0);
        }

    } while (opcao != 0);

    liberarLista(&lista);

    printf("Sistema finalizado.\n");
    return 0;
}
