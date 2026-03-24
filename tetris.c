#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define MAX_FILA 5
#define MAX_PILHA 3

// ----- Estrutura da peça -----
typedef struct {
    char tipo;  // I, O, T, L
    int id;
} Peca;

// ----- Estrutura da fila circular -----
typedef struct {
    Peca itens[MAX_FILA];
    int inicio, fim, total;
} Fila;

typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;


// ----- Variável global para ID único -----
int countID = 0;

// ----- Gerar peça automaticamente -----
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = countID++;
    return p;
}
// ----- Funções da fila -----
// ----- inicializar fila -----
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
    for (int i = 0; i < MAX_FILA; i++) {
        f->itens[f->fim] = gerarPeca();
        f->fim = (f->fim + 1) % MAX_FILA;
        f->total++;
    }
}

// ----- Verificações -----
int filaCheia(Fila *f){
    return f->total == MAX_FILA;
}

int filaVazia(Fila *f){
    return f->total == 0;
}

// ----- Enqueue -----
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila CHEIA. Não é possivel inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

// ----- Dequeue -----
void dequeue(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Fila VAZIA. Não é possivel remover.\n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
}

// ----- Exibir fila -----
void mostrarFila(Fila *f) {
    printf("\nFila de peças: ");

    if (filaVazia(f)){
        printf("[Vazia]");
        return;
    }

    int i, idx = f->inicio;

    for (int i = 0, idx = f->inicio; i < f->total; i++) {
        int idx = (f->inicio + i) % MAX_FILA;
        printf("[%c, %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }

    printf("\n");
}

// ----- Preencher fila inicial -----
void preencherInicial(Fila *f) {
    for (int i = 0; i < MAX_FILA; i++) {
        // Altere aqui para o nome correto que você definiu na função
        enqueue(f, gerarPeca());
    }
}

// ----- Funções da Pilha -----
// ----- inicializar pilha -----
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// ----- Verificações -----
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
};

void push(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Erro: pilha cheia. Não é possível inserir.\n");
        return;
    }

    p->topo++; // Avança o topo
    p->itens[p->topo] = nova; // Insere o novo elemento
}

void pop(Pilha *p, Peca *removida) {
    if (pilhaVazia(p)) {
        printf("Erro: Pilha vazia. Não é possívelremover.\n");
        return;
    }

    *removida = p->itens[p->topo]; // Copia o valor do topo
    p->topo--; // Decrementa o topo
}

void mostrarPilha(Pilha *p) {
    printf("Pilha (topo -> base):\n");

    for (int i = p->topo; i >= 0; i--) {
        printf("[%c,%d] ", p->itens[i].tipo, p->itens[i].id);
    }
    printf("\n");
}

int main(void) {
    srand(time(NULL));

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

    Fila filaPeca;
    Peca pecaAux;
    Pilha pilhaReserva;
    int opcao;

    inicializarFila(&filaPeca);
    inicializarPilha(&pilhaReserva);

    do {
        mostrarFila(&filaPeca);
        mostrarPilha(&pilhaReserva);

        printf("\n1 - Jogar Peça");
        printf("\n2 - Reservar Peça");
        printf("\n3 - Usar Peça da Reserva");
        printf("\n0 - Sair");
        printf("\nEscolha um opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            if (!filaVazia(&filaPeca)) {
                dequeue(&filaPeca, &pecaAux);
                printf("\n>>> Jogou: [%c %d]\n", pecaAux.tipo, pecaAux.id);
                enqueue(&filaPeca, gerarPeca());
            }
            break;

        case 2:
            if (pilhaCheia(&pilhaReserva)) {
                printf("\nErro: Pilha de reserva cheia!\n");
            } else if (!filaVazia(&filaPeca)) {
                dequeue(&filaPeca, &pecaAux);
                push(&pilhaReserva, pecaAux);
                printf("\n>>> [%c %d] movida para a reserva.\n", pecaAux.tipo, pecaAux.id);
                enqueue(&filaPeca, gerarPeca());
            }
            break;

        case 3:
            if (!pilhaVazia(&pilhaReserva)) {
                pop(&pilhaReserva, &pecaAux);
                printf("\n>>> Usou da reserva: [%c %d]\n", pecaAux.tipo, pecaAux.id);
            } else {
                printf("\nErro: Reserva vazia!\n");
            }
            break;

        case 0:
            printf("\nEncerrar...\n");
            break;


        default:
        printf("\nOpção invalida!\n");
        }
    } while (opcao != 0);

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).

    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}

