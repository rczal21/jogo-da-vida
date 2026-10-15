// JVida_DHIR_Model.cpp
// 13/10/2026
/*Daniel Luis de Amorim Mariano Santos
Henrique Campos Rodrigues
Isabella de Souza Fleury
Rafaella Castro Zandona Alves de Lima */

#include <stdio.h>
#include "JVida_DHIR_Model.h"

#define ARQUIVO "geracoes.txt"

char Matriz[60][60];
int dim;
int mostrarMortos;

static int proxGeracao = 0; //quantas geracoes ja foram carregadas

static char Aux[60][60]; //matriz auxiliar para a proxima geracao

int dimValida(int d) {
    if (d >= 10 && d <= 60) {
        return 1;
    }
    return 0;
}

void limparMapa() {
    int l, c;
    for (l = 0; l < dim; l++) {
        for (c = 0; c < dim; c++) {
            Matriz[l][c] = '.';
        }
    }
}

int coordValida(int l, int c) {
    if (l >= 0 && l <= dim - 1 && c >= 0 && c <= dim - 1) {
        return 1;
    }
    return 0;
}

int celulaViva(int l, int c) {
    if (Matriz[l][c] == 'O') {
        return 1;
    }
    return 0;
}

void incluirCelula(int l, int c) {
    Matriz[l][c] = 'O';
}

void excluirCelula(int l, int c) {
    Matriz[l][c] = '.';
}

void marcarVizinhasMortas() {
    int l, c, i, j;
    for (l = 0; l < dim; l++) {
        for (c = 0; c < dim; c++) {
            if (celulaViva(l, c)) {
                for (i = l - 1; i <= l + 1; i++) {
                    for (j = c - 1; j <= c + 1; j++) {
                        if (coordValida(i, j) && Matriz[i][j] == '.') {
                            Matriz[i][j] = '+'; //marcar as vizinhas mortas com + 
                        }
                    }
                }
            }
        }
    }
}

void desmarcarVizinhasMortas() {
	int i, j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
        	if (Matriz[i][j] == '+'){
            Matriz[i][j] = '.';
        	}
        }
    }
}

// retorna 1 se salvou, 0 se deu erro
int salvarGeracao() {
    FILE *f;
    int l, c, qtd = 0;

    f = fopen(ARQUIVO, "a"); // "a" = acrescenta no fim
    if (f == NULL) {
        return 0;
    }

    for (l = 0; l < dim; l++) {
        for (c = 0; c < dim; c++) {
            if (celulaViva(l, c)) {
                qtd++;
            }
        }
    }

    fprintf(f, "%d %d\n", dim, qtd); // cabecalho: dimensao e quantidade
    for (l = 0; l < dim; l++) {
        for (c = 0; c < dim; c++) {
            if (celulaViva(l, c)) {
                fprintf(f, "%d %d\n", l, c);
            }
        }
    }

    fclose(f);
    return 1;
}

// retorna 1 se carregou, 0 se acabaram as geracoes, -1 se nao achou o arquivo
int carregarGeracao() {
    FILE *f;
    int g, i, d, qtd, l, c;

    f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        return -1;
    }

    // pula as geracoes que ja foram carregadas
    for (g = 0; g < proxGeracao; g++) {
        if (fscanf(f, "%d %d", &d, &qtd) != 2) {
            fclose(f);
            proxGeracao = 0; //volta ao comeco na proxima vez
            return 0;
        }
        for (i = 0; i < qtd; i++) {
            fscanf(f, "%d %d", &l, &c);
        }
    }

    // le a geracao da vez
    if (fscanf(f, "%d %d", &d, &qtd) != 2 || !dimValida(d)) {
        fclose(f);
        proxGeracao = 0;
        return 0;
    }

    dim = d;
    limparMapa();
    for (i = 0; i < qtd; i++) {
        if (fscanf(f, "%d %d", &l, &c) == 2 && coordValida(l, c)) {
            incluirCelula(l, c);
        }
    }

    fclose(f);
    proxGeracao++;
    return 1;
}

//conta os vizinhos vivos de uma casa (no maximo 8)
int contarVizinhosVivos(int l, int c) {
    int i, j, n = 0;
    for (i = l - 1; i <= l + 1; i++) {
        for (j = c - 1; j <= c + 1; j++) {
            if (!(i == l && j == c) && coordValida(i, j) && celulaViva(i, j)) {
                n++;
            }
        }
    }
    return n;
}

//quantidade de celulas vivas
int contarVivas() {
    int l, c, n = 0;
    for (l = 0; l < dim; l++) {
        for (c = 0; c < dim; c++) {
            if (celulaViva(l, c)) {
                n++;
            }
        }
    }
    return n;
}

//quantidade de vizinhas-mortas (casa nao viva com pelo menos 1 vizinho vivo)
int contarVizinhasMortas() {
    int l, c, n = 0;
    for (l = 0; l < dim; l++) {
        for (c = 0; c < dim; c++) {
            if (!celulaViva(l, c) && contarVizinhosVivos(l, c) > 0) {
                n++;
            }
        }
    }
    return n;
}

//gera a proxima geracao usando a matriz auxiliar
void proximaGeracao() {
    int l, c, viz;

    for (l = 0; l < dim; l++) {
        for (c = 0; c < dim; c++) {
            viz = contarVizinhosVivos(l, c);
            if (celulaViva(l, c)) {
                if (viz == 2 || viz == 3) {
                    Aux[l][c] = 'O';   //sobrevive
                } else {
                    Aux[l][c] = '.';   //morre de solidao ou falta de comida
                }
            } else {
                if (viz == 3) {
                    Aux[l][c] = 'O';   //nasce
                } else {
                    Aux[l][c] = '.';
                }
            }
        }
    }

    for (l = 0; l < dim; l++) {        ///copia a nova geracao de volta
        for (c = 0; c < dim; c++) {
            Matriz[l][c] = Aux[l][c];
        }
    }
}
