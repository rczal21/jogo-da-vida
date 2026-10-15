//JVida_DHIR_View.cpp
//13/10/2026
/*Daniel Luis de Amorim Mariano Santos
Henrique Campos Rodrigues
Isabella de Souza Fleury
Rafaella Castro Zandona Alves de Lima */

#include <stdio.h>
#include "JVida_DHIR_View.h"


/* descarta o que sobrou na linha de entrada */
static void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

/* le um inteiro; retorna 1 se leu, 0 se a entrada era invalida, -1 se acabou a entrada (EOF) */
static int lerInteiro(int *valor) {
    int r = scanf("%d", valor);
    if (r == 1) {
        limparBuffer();
        return 1;
    }
    if (r == EOF) {
        return -1;
    }
    limparBuffer();
    return 0;
}

void mostrarMapa() {
    int l, c;

    printf("\n    ");
    for (c = 0; c < dim; c++) {
        printf("%02d ", c); /* escreve o numero com 2 digitos */
    }
    printf("\n");

    for (l = 0; l < dim; l++) {
        printf("%02d  ", l);
        for (c = 0; c < dim; c++) {
            printf("%c  ", Matriz[l][c]);
        }
        printf("\n");
    }
}

int pedirDim() {
    int d = 0;
    int r;
    do {
        printf("Digite a dimensao do mapa (de 10 a 60): ");
        r = lerInteiro(&d);
        if (r == -1) {
            return 10; /* entrada encerrada: usa o minimo para nao travar */
        }
        if (r == 0 || !dimValida(d)) {
            printf("Valor invalido!\n");
            d = 0;
        }
    } while (!dimValida(d));
    return d;
}

void mostrarMenu() {
    printf("\n  J O G O   D A   V I D A\n");
    printf("===========================\n");
    printf("1 - Apresentar o Mapa\n");
    printf("2 - Limpar mapa\n");
    printf("3 - Incluir/excluir celulas vivas\n");
    printf("4 - Mostrar/Esconder os mortos-vizinhos\n");
    printf("5 - Salvar geracao no arquivo\n");
    printf("6 - Carregar proxima geracao do arquivo\n");
    printf("7 - Avancar uma geracao\n");
    printf("0 - Sair\n");
    printf("Opcao selecionada: ");
}

int lerOpcao() {
    int op;
    int r = lerInteiro(&op);
    if (r == -1) {
        return 0; /* entrada encerrada: sai do programa */
    }
    if (r == 0) {
        return -1; /* cai no "Opcao invalida!" */
    }
    return op;
}

void pedirCoordenadas(int *l, int *c) { /* * indica ponteiro, onde guarda o "endereco" da variavel. */
    printf("Linha: ");
    if (lerInteiro(l) != 1) {
        *l = -1; /* coordenada invalida */
    }
    printf("Coluna: ");
    if (lerInteiro(c) != 1) {
        *c = -1; /* coordenada invalida */
    }
}

int perguntarExcluir() {
    char e = 'n';
    printf("Ja existe uma celula viva aqui. Excluir? (s/n): ");
    scanf(" %c", &e);
    limparBuffer();
    if (e == 's' || e == 'S') {
        return 1;
    }
    return 0;
}

void mostrarCoordInvalida() {
    printf("Coordenada invalida!\n"); /* case 3 */
}

void mostrarDespedida() {
    printf("Ate logo!\n"); /* case 0 */
}

void mostrarOpcaoInvalida() {
    printf("Opcao invalida!\n"); /* default */
}

void mostrarEstadoMortos(int estado) {
    if (estado == 1) {
        printf("Vizinhas-mortas: MOSTRANDO\n");
    } else {
        printf("Vizinhas-mortas: ESCONDIDAS\n");
    }
}

void mostrarSalvoOk() {
    printf("Geracao salva com sucesso!\n");
}

void mostrarCarregadoOk() {
    printf("Geracao carregada! Use a opcao 1 para ver o mapa.\n");
}

void mostrarFimGeracoes() {
    printf("Nao ha mais geracoes no arquivo. Na proxima vez volta para a primeira.\n");
}

void mostrarErroArquivo() {
    printf("Nenhuma geracao salva ainda (arquivo nao encontrado)!\n");
}

void mostrarContagem(int vivas, int mortas) {
    printf("\nCelulas vivas: %d\n", vivas);
    printf("Vizinhas-mortas: %d\n", mortas);
}
