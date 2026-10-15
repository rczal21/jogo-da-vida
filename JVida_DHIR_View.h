// JVida_DHIR_View.h
// 13/10/2026
// Daniel Luis de Amorim Mariano Santos, Henrique Campos Rodrigues, Isabella de Souza Fleury, Rafaella Castro Zandona Alves de Lima 

#ifndef JVida_DHIR_VIEW_H
#define JVida_DHIR_VIEW_H

void mostrarMapa();
int pedirDim();
void mostrarMenu();
int lerOpcao();
void pedirCoordenadas(int *l, int *c);
int perguntarExcluir();
void mostrarCoordInvalida();
void mostrarDespedida();
void mostrarOpcaoInvalida();
void mostrarEstadoMortos(int estado);
void mostrarSalvoOk();
void mostrarCarregadoOk();
void mostrarFimGeracoes();
void mostrarErroArquivo();
void mostrarContagem(int vivas, int mortas);

#endif
