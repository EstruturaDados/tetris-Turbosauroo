#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5  // Tamanho máximo da fila

typedef struct {
    char peca;
    int id;
} Struct_peca;

typedef struct {
    Struct_peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// Inicializa os valores da fila
void inicializar_fila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int fila_cheia(Fila *f) {
    return f->total == MAX;
}

int fila_vazia(Fila *f) {
    return f->total == 0;
}

// Gera uma nova peça com um ID único
Struct_peca gerar_peca(int id) {
    char letras[4] = {'I', 'O', 'T', 'L'};
    int tamanho_array = sizeof(letras) / sizeof(letras[0]);
    int indice_aleatorio = rand() % tamanho_array;

    Struct_peca nova;
    nova.peca = letras[indice_aleatorio];
    nova.id = id;

    return nova;
}

void inserir(Fila *f, Struct_peca p) {
    if (fila_cheia(f)) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(Fila *f, Struct_peca *p) {
    if (fila_vazia(f)) {
        printf("Fila vazia. Não é possível remover.\n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void mostrarFila(Fila *f) {
    if (fila_vazia(f)) {
        printf("Fila: [vazia]\n");
        return;
    }

    printf("Fila: ");

    int contador = 0;
    int idx = f->inicio;

    while (contador < f->total) {
        Struct_peca p = f->itens[idx];
        printf("[Peca: %c, ID: %d] ", p.peca, p.id);
        idx = (idx + 1) % MAX;
        contador++;
    }

    printf("\n");
}

int main() {
    int opcao = -1;
    int proximo_id = 0;  // ? ID único para cada peça

    Fila f;
    Struct_peca removida;

    srand(time(NULL));  // ? Semente do rand inicializada uma vez só

    inicializar_fila(&f);

    while (opcao != 0) {
        mostrarFila(&f);
        printf("1 - Jogar peça\n2 - Inserir nova peça\n0 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!fila_vazia(&f)) {
                    remover(&f, &removida);
                    printf("Peça jogada: [Peca: %c, ID: %d]\n", removida.peca, removida.id);  // ? Feedback
                } else {
                    printf("Não há peças para jogar.\n");
                }
                break;
            case 2: {
                Struct_peca nova = gerar_peca(proximo_id++);  // ? ID único garantido
                inserir(&f, nova);
                break;
            }
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção errada!\n");
        }
    }

    return 0;
}

