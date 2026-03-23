#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define MAX 5

// ----- Estrutura da peça -----
typedef struct {
    char tipo;  // I, O, T, L
    int id;
} Peca;

// ----- Estrutura da fila circular -----
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// ----- Variável global para ID único -----
int countID = 0;

// ----- Gerar peça automaticamente -----
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

// ----- inicializar fila -----
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// ----- Verificações -----
int filaCheia(Fila *f){
    return f->total == MAX;
}

int filaVazia(Fila *f){
    return f->total == 0;
}

// ----- Enqueue -----
void inserirPeca(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila CHEIA. Não é possivel inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

// ----- Dequeue -----
void removerPeca(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Fila VAZIA. Não é possivel remover.\n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
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
        int idx = (f->inicio + i) % MAX;
        printf("[%c, %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }

    printf("\n");
}

// ----- Preencher fila inicial -----
void preencherInicial(Fila *f) {
    for (int i = 0; i < MAX; i++) {
        // Altere aqui para o nome correto que você definiu na função
        inserirPeca(f, gerarPeca(countID++)); 
    }
}

int main(void) {

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

    srand(time(NULL));
    Fila filaPeca;
    Peca PecaAux;
    int opcao;

    inicializarFila(&filaPeca);
    preencherInicial(&filaPeca);

    do {
        mostrarFila(&filaPeca);
        
        printf("\n1 - Jogar Peça (dequeue)");
        printf("\n2 - Inserir Nova Peça (enqueue)");
        printf("\n0 - Sair");
        printf("\nEscolha um opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            removerPeca(&filaPeca, &PecaAux);
            break;

        case 2:
            inserirPeca(&filaPeca, PecaAux);
            break;

        case 0:
            printf("Encerrar...\n");
            break;


        default:
        printf("Opção invalida!\n");
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

