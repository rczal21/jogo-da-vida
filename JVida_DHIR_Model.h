//JVida_DHIR_Model.h
//13/10/2026
/*Daniel Luis de Amorim Mariano Santos
Henrique Campos Rodrigues
Isabella de Souza Fleury
Rafaella Castro Zandona Alves de Lima */ 

#ifndef JVida_DHIR_MODEL_H
#define JVida_DHIR_MODEL_H

extern char Matriz[60][60];
extern int dim;
extern int mostrarMortos;

void limparMapa();
int dimValida(int d);

int coordValida(int l, int c);
int celulaViva(int l, int c);
void incluirCelula(int l, int c);
void excluirCelula(int l, int c);
void marcarVizinhasMortas();
void desmarcarVizinhasMortas();

int salvarGeracao();
int carregarGeracao();

int contarVizinhosVivos(int l, int c);
int contarVivas();
int contarVizinhasMortas();
void proximaGeracao();

#endif
