#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

/*
 * Struct Componente
 * Representa um componente usado na torre final de fuga.
 * - nome: nome do componente (string)
 * - tipo: categoria do componente (string)
 * - prioridade: numero de 1 a 10 que define sua importancia
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

/*
 * Variaveis globais para contar comparacoes
 */
int comp_bubble = 0;
int comp_insertion = 0;
int comp_selection = 0;
int comp_busca_bin = 0;

/*
 * Mostrar componentes na tela
 */
void mostrarComponentes(Componente v[], int n) {
    printf("\n=== COMPONENTES ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
            i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
    printf("=====================\n");
}

/*
 * Bubble Sort - ordenar por nome (string)
 */
void bubbleSortNome(Componente v[], int n) {
    comp_bubble = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comp_bubble++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

/*
 * Insertion Sort - ordenar por tipo (string)
 */
void insertionSortTipo(Componente v[], int n) {
    comp_insertion = 0;

    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comp_insertion++;
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = chave;
    }
}

/*
 * Selection Sort - ordenar por prioridade (int)
 */
void selectionSortPrioridade(Componente v[], int n) {
    comp_selection = 0;

    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            comp_selection++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }

        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
}

/*
 * Busca Binaria - apenas se estiver ordenado por nome
 */
int buscaBinariaPorNome(Componente v[], int n, char nomeBusca[]) {
    int inicio = 0, fim = n - 1;
    comp_busca_bin = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comp_busca_bin++;

        int cmp = strcmp(v[meio].nome, nomeBusca);

        if (cmp == 0)
            return meio;

        if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

/*
 * Funcao auxiliar para medir tempo de execucao
 */
double medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio = clock();
    algoritmo(v, n);
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

/*
 * Cadastro dos componentes
 */
int cadastrarComponentes(Componente v[]) {
    int n;

    printf("Quantos componentes deseja cadastrar (max 20)? ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_COMPONENTES) {
        printf("Numero invalido.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("\nComponente %d:\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", v[i].nome);

        printf("Tipo: ");
        scanf(" %19s", v[i].tipo);

        printf("Prioridade (1 a 10): ");
        scanf("%d", &v[i].prioridade);

        if (v[i].prioridade < 1 || v[i].prioridade > 10) {
            v[i].prioridade = 5;
        }
    }

    return n;
}

/*
 * MENU PRINCIPAL DO SISTEMA
 */
int main() {
    Componente v[MAX_COMPONENTES];
    int n = 0;
    int opcao;

    printf("=== SISTEMA DE ORDENACAO E BUSCA (DESAFIO FINAL) ===\n");

    n = cadastrarComponentes(v);

    if (n == 0) {
        printf("Nenhum componente cadastrado. Encerrando.\n");
        return 0;
    }

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Bubble Sort por nome\n");
        printf("2 - Insertion Sort por tipo\n");
        printf("3 - Selection Sort por prioridade\n");
        printf("4 - Busca binaria por nome (apenas apos Bubble Sort)\n");
        printf("5 - Mostrar componentes\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            double tempo = medirTempo(bubbleSortNome, v, n);
            printf("\nBubble Sort concluido.\n");
            printf("Comparacoes: %d\n", comp_bubble);
            printf("Tempo: %f segundos\n", tempo);
            mostrarComponentes(v, n);
        }

        else if (opcao == 2) {
            double tempo = medirTempo(insertionSortTipo, v, n);
            printf("\nInsertion Sort concluido.\n");
            printf("Comparacoes: %d\n", comp_insertion);
            printf("Tempo: %f segundos\n", tempo);
            mostrarComponentes(v, n);
        }

        else if (opcao == 3) {
            double tempo = medirTempo(selectionSortPrioridade, v, n);
            printf("\nSelection Sort concluido.\n");
            printf("Comparacoes: %d\n", comp_selection);
            printf("Tempo: %f segundos\n", tempo);
            mostrarComponentes(v, n);
        }

        else if (opcao == 4) {
            char chave[30];
            printf("Nome do componente-chave: ");
            scanf(" %29[^\n]", chave);

            int pos = buscaBinariaPorNome(v, n, chave);

            printf("Comparacoes: %d\n", comp_busca_bin);

            if (pos >= 0)
                printf("Componente encontrado: %s (%s) prioridade %d\n",
                    v[pos].nome, v[pos].tipo, v[pos].prioridade);
            else
                printf("Componente NAO encontrado.\n");
        }

        else if (opcao == 5) {
            mostrarComponentes(v, n);
        }

    } while (opcao != 0);

    printf("\nSistema finalizado.\n");
    return 0;
}
