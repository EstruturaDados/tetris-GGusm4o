#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// -------------------------------------------------------------------------------------------------
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
// -------------------------------------------------------------------------------------------------    
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
// -------------------------------------------------------------------------------------------------
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
// -------------------------------------------------------------------------------------------------

/* ── Constantes ─────────────────────────────────────────── */
#define MAX_FILA  5   /* capacidade máxima da fila circular  */
#define MAX_PILHA 3   /* capacidade máxima da pilha de reserva */

/* ── Contador global de IDs ──────────────────────────────── */
int countID = 0;

// ── Estrutura de uma peça ─────────────────────────────────
typedef struct {
    char tipo;  // I, O, T, L
    int id;
} Peca;

// ── Estrutura da Fila Circular ────────────────────────────
typedef struct {
    Peca itens[MAX_FILA];
    int inicio, fim, total;
} Fila;

// ── Estrutura da Pilha Linear ─────────────────────────────
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

/* ============================================================
 *  FUNÇÕES AUXILIARES
 * ============================================================ */

/* Gera uma nova peça com tipo aleatório e id sequencial */

Peca gerarPeca(void) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id   = countID++;
    return p;
}

/* ============================================================
 *  OPERAÇÕES DA FILA CIRCULAR
 * ============================================================ */

/* Inicializa a fila zerando índices e contador */
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

/* Retorna 1 se a fila estiver cheia, 0 caso contrário */
int filaCheia(Fila *f) {
    return f->total == MAX_FILA;
}

/* Retorna 1 se a fila estiver vazia, 0 caso contrário */
int filaVazia(Fila *f) {
    return f->total == 0;
}

/*
 * Insere uma peça no final da fila (enqueue).
 * Usa o operador módulo para manter a circularidade do array.
 */
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("  [!] Fila cheia. Não é possível inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA; /* avança circularmente */
    f->total++;
}

/*
 * Remove e retorna a peça da frente da fila (dequeue).
 * Retorna uma peça com id = -1 se a fila estiver vazia.
 */
Peca dequeue(Fila *f) {
    Peca vazia = {' ', -1};
    if (filaVazia(f)) {
        printf("  [!] Fila vazia. Não há peça para jogar.\n");
        return vazia;
    }
    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA; /* avança circularmente */
    f->total--;
    return removida;
}

/* ============================================================
 *  EXIBIÇÃO DO ESTADO ATUAL
 * ============================================================ */

/* Exibe todas as peças da fila na ordem de saída */
void mostrarFila(Fila *f) {
    printf("  Fila de pecas: ");
    if (filaVazia(f)) {
        printf("[vazia]");
    } else {
        for (int i = 0, idx = f->inicio; i < f->total; i++) {
            printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
            idx = (idx + 1) % MAX_FILA; /* percorre circularmente */
        }
    }
    printf("\n");
}

/* ============================================================
 *  OPERAÇÕES DA PILHA LINEAR
 * ============================================================ */

/* Inicializa a pilha com topo = -1 (convenção de pilha vazia) */
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

/* Retorna 1 se a pilha estiver cheia, 0 caso contrário */
int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

/* Retorna 1 se a pilha estiver vazia, 0 caso contrário */
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

/*
 * Empilha uma peça no topo da pilha (push).
 * O índice topo é incrementado antes da inserção.
 */
void push(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("  [!] Pilha cheia. Não é possível reservar.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = peca;
}

/*
 * Remove e retorna a peça do topo da pilha (pop).
 * Retorna uma peça com id = -1 se a pilha estiver vazia.
 */
Peca pop(Pilha *p) {
    Peca vazia = {' ', -1};
    if (pilhaVazia(p)) {
        printf("  [!] Pilha vazia. Não há peça reservada.\n");
        return vazia;
    }
    Peca removida = p->itens[p->topo];
    p->topo--;
    return removida;
}

/* ============================================================
 *  EXIBIÇÃO DO ESTADO ATUAL
 * ============================================================ */

/* Exibe as peças da pilha do topo até a base */
void mostrarPilha(Pilha *p) {
    printf("  Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia(p)) {
        printf("[vazia]");
    } else {
        /* percorre do topo até a base */
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
        }
    }
    printf("\n");
}


/* ============================================================
 *  FUNÇÕES GERAIS DO JOGO
 * ============================================================ */

/* Imprime o estado completo: fila e pilha */
void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n  ╔══════════════════════════════════════════╗\n");
    printf("  ║              ESTADO ATUAL                ║\n");
    printf("  ╚══════════════════════════════════════════╝\n");
    mostrarFila(f);
    mostrarPilha(p);
    printf("\n");
}

/* Exibe o menu de ações disponíveis */
void mostrarMenu(void) {
    printf("  ┌──────────────────────────────────────────────────────┐\n");
    printf("  │  OPCOES                                              │\n");
    printf("  │  1 - Jogar Peça da frente da fila                    │\n");
    printf("  │  2 - Enviar peça da fila para a reserva (pilha)      │\n");
    printf("  │  3 - Usar Peça da Reserva (pilha)                    │\n");
    printf("  │  4 - Trocar Peça da Frente com Topo da Pilha         │\n");
    printf("  │  5 - Trocar 3 Primeiros da Fila com os 3 da Pilha    │\n");
    printf("  │  0 - Sair                                            │\n");
    printf("  └──────────────────────────────────────────────────────┘\n");
    printf("  Opcao: ");             
}

/* ============================================================
 *  AÇÕES DO JOGO
 * ============================================================ */

/*
 * Ação 1: Jogar peça.
 * Remove a peça da frente da fila e insere automaticamente
 * uma nova peça gerada no final, mantendo a fila sempre cheia.
 */
void jogarPeca(Fila *f) {
    Peca jogada = dequeue(f);
    if (jogada.id == -1) {
        printf("  [!] Fila vazia. Nao e possivel jogar uma peca.\n");
        return; /* fila estava vazia */
    }

    printf("  >> Peca jogada: [%c %d]\n", jogada.tipo, jogada.id);

    /* Gera nova peça automaticamente para repor a fila */
    if (!filaCheia(f)) {
        Peca nova = gerarPeca();
        enqueue(f, nova);
        printf("  >> Nova peca gerada: [%c %d]\n", nova.tipo, nova.id);
    }
}

/*
 * Ação 2: Reservar peça.
 * Move a peça da frente da fila para o topo da pilha.
 * Após a remoção, uma nova peça é gerada para repor a fila.
 */
void reservarPeca(Fila *f, Pilha *p) {
    if (pilhaCheia(p)) {
        printf("  [!] Pilha de reserva cheia. Libere espaco primeiro.\n");
        return;
    }
    Peca reservada = dequeue(f);
    if (reservada.id == -1) return;

    push(p, reservada);
    printf("  >> Peca reservada: [%c %d]\n", reservada.tipo, reservada.id);

    /* Repõe a fila com nova peça gerada automaticamente */
    if (!filaCheia(f)) {
        Peca nova = gerarPeca();
        enqueue(f, nova);
        printf("  >> Nova peca gerada: [%c %d]\n", nova.tipo, nova.id);
    }
}

/*
 * Ação 3: Usar peça reservada.
 * Remove a peça do topo da pilha, simulando seu uso no jogo.
 * Essa peça não retorna à fila.
 */
void usarPecaReservada(Pilha *p) {
    Peca usada = pop(p);
    if (usada.id == -1) {
        printf("  [!] Pilha vazia. Nao e possivel usar uma peca.\n");
        return;
    }

    printf("  >> Peca usada da reserva: [%c %d]\n", usada.tipo, usada.id);
}

/*
 * Ação 4: Trocar frente da fila com topo da pilha.
 * Os dois elementos trocam de posição entre as estruturas.
 * Requer que ambas tenham pelo menos 1 elemento.
 */
void trocarFrenteTopo(Fila *f, Pilha *p) {
    if (filaVazia(f)) {
        printf("  [!] Fila vazia. Troca impossivel.\n");
        return;
    }
    if (pilhaVazia(p)) {
        printf("  [!] Pilha vazia. Troca impossivel.\n");
        return;
    }

    /* Remove os dois elementos envolvidos */
    Peca daFila = dequeue(f);
    Peca daPilha= pop(p);

    /* Reinsere em posições invertidas:
       - o que estava na pilha vai para a frente da fila
       - o que estava na fila vai para o topo da pilha      */

    /*
     * Para colocar daPilha na FRENTE da fila circular,
     * recuamos o índice inicio e inserimos diretamente.
     * Isso preserva a ordem dos demais elementos.
     */
    f->inicio = (f->inicio - 1 + MAX_FILA) % MAX_FILA;
    f->itens[f->inicio] = daPilha;
    f->total++;

    /* O que estava na frente da fila vai para o topo da pilha */
    push(p, daFila);

    printf("  >> Troca realizada:\n");
    printf("     Frente da fila agora: [%c %d]\n", daPilha.tipo, daPilha.id);
    printf("     Topo da pilha agora:  [%c %d]\n", daFila.tipo,  daFila.id);
}

/*
 * Ação 5: Trocar os 3 primeiros da fila com as 3 da pilha.
 * Requer que a fila tenha >= 3 peças e a pilha tenha exatamente 3.
 * Os três primeiros da fila vão para a pilha (na ordem invertida,
 * mantendo a lógica LIFO), e os três da pilha ficam na frente da fila.
 */
void trocarMultiplo(Fila *f, Pilha *p) {
    /* Valida pré-condições */
    if (f->total < 3) {
        printf("  [!] A fila precisa ter ao menos 3 pecas.\n");
        return;
    }
    if (p->topo != MAX_PILHA - 1) { /* pilha precisa estar cheia (3 peças) */
        printf("  [!] A pilha precisa ter exatamente 3 pecas para a troca em bloco.\n");
        return;
    }

    /* Armazena os 3 da frente da fila */
    Peca daFila[3];
    for (int i = 0; i < 3; i++) {
        daFila[i] = dequeue(f);
    }

    /* Armazena os 3 da pilha (topo ao fundo) */
    Peca daPilha[3];
    for (int i = 0; i < 3; i++) {
        daPilha[i] = pop(p);
    }
    /*
     * daPilha[0] = era o topo (Last In)
     * daPilha[2] = era a base (First In)
     * Para recolocar na frente da fila mantendo a ordem original da pilha
     * (topo vai para a frente), inserimos de trás para frente.
     */

    /* Reinsere peças da pilha na frente da fila (ordem: topo primeiro) */
    for (int i = 2; i >= 0; i--) {
        f->inicio = (f->inicio - 1 + MAX_FILA) % MAX_FILA;
        f->itens[f->inicio] = daPilha[i];
        f->total++;
    }

    /* Envia as 3 peças que eram da fila para a pilha */
    /* Para que o primeiro da fila seja o topo, empilhamos de trás para frente */
    for (int i = 2; i >= 0; i--) {
        push(p, daFila[i]);
    }

    printf("  >> Troca em bloco realizada!\n");
    printf("     Os 3 primeiros da fila agora sao: "
           "[%c %d] [%c %d] [%c %d]\n",
           daPilha[0].tipo, daPilha[0].id,
           daPilha[1].tipo, daPilha[1].id,
           daPilha[2].tipo, daPilha[2].id);
    printf("     A pilha agora contem (topo->base): "
           "[%c %d] [%c %d] [%c %d]\n",
           daFila[0].tipo, daFila[0].id,
           daFila[1].tipo, daFila[1].id,
           daFila[2].tipo, daFila[2].id);
}

/* ============================================================
 *  INICIALIZAÇÃO DO JOGO
 * ============================================================ */

/*
 * Preenche a fila com MAX_FILA peças geradas automaticamente.
 * Chamado uma única vez no início da partida.
 */
void inicializarJogo(Fila *f, Pilha *p) {
    inicializarFila(f);
    inicializarPilha(p);

    printf("\n  Inicializando o jogo...\n");
    for (int i = 0; i < MAX_FILA; i++) {
        Peca nova = gerarPeca();
        enqueue(f, nova);
    }
    printf("  Fila inicial criada com %d pecas.\n", MAX_FILA);
}

int main(void) {
    srand(time(NULL));

    Fila  fila;
    Pilha pilha;

    /* Cabeçalho */
    printf("\n");
    printf("  ╔══════════════════════════════════════════╗\n");
    printf("  ║                                          ║\n");
    printf("  ║        TETRIS STACK - NIVEL MESTRE       ║\n");
    printf("  ║                                          ║\n");
    printf("  ╚══════════════════════════════════════════╝\n");

    int opcao;

    inicializarJogo(&fila, &pilha);

    do {
        mostrarEstado(&fila, &pilha);
        mostrarMenu();
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
        case 1:
            jogarPeca(&fila);
            break;

        case 2:
            reservarPeca(&fila, &pilha);
            break;

        case 3:
            usarPecaReservada(&pilha);
            break;

        case 4:
            trocarFrenteTopo(&fila, &pilha);
            break;

        case 5:
            trocarMultiplo(&fila, &pilha);
            break;

        case 0:
            printf("\nEncerrar...\n");
            break;


        default:
        printf("\nOpção invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

