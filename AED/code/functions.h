#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "cabecalho.h"
#include "auxiliar_opcoes.h"
#include "dicionario.h"

void opcoes(int **marestas, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]); // ESCOLHE QUAL DAS OPCOES E QUE SE VAI FAZER

void opcaoA1(int **marestas, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]);
void opcaoA2(int **marestas, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]);
char *devolve_palavra_resposta_ao_problema_A(DIC_PALAVRAS **head_dicionario, PALAVRAS *head_lista_palavras, int num_palavras, int *teste);

void opcaoD1(int **marestas, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]);
void opcaoD2(int **marestas, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]);

void opcaoE1(int **marestas, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]);
void opcaoE2(int **marestas, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]);

void opcaoF1(int **marestas, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]);
void opcaoF2(int **marestas, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]);
char *devolve_palavra_resposta_ao_problema_F(int valor_atual, DIC_PALAVRAS **head_dicionario, PALAVRAS *head_lista_palavras, int num_palavras, int *teste);

char *devolve_palavra_resposta_ao_problema_D(DIC_PALAVRAS **head_dicionario, PALAVRAS *head_lista_palavras, int num_palavras, int *teste);
#endif
