#ifndef AUXILIAR_OPCOES_H_INCLUDED
#define AUXILIAR_OPCOES_H_INCLUDED
#include "cabecalho.h"

typedef struct _vetor_vertices {

    char *ch;
    int valor;
}VERTICES; // ESTRUTURA QUE GUARDA O VALOR DE CADA VERTICE

typedef struct _lista_palavras {

    char *ch;
    struct _lista_palavras *next;
}PALAVRAS; // ESTRUTURA QUE GUARDA UMA LISTA DE PALAVRAS

int cria_segmento_palavra(char **l1, char **l2, char **word, char *novas_letras); // CRIA SEGMETO PARA INTRODUZIR NAS PALAVRAS JA EXISTENTES
PALAVRAS *cria_lista_palavras_cadeia_palavras(PALAVRAS *head, char *aux_palav1, char *aux_palav2); // SE FOR UMA CADEIA DE PALAVRAS CRIA E INTRODUZ NA LISTA
PALAVRAS *cria_lista_palavras(PALAVRAS *head, char *aux_palav); // SE FOR UM CONJUNTO NORMAL DE LETRAS CRIA E INTRODUZ NA LISTA
void liberta_lista_palavras(PALAVRAS *head); // LIBERTA A LISTA DE PALAVRAS
int deepsearch(int **matriz, int vert_atual, int *vert_vistos, int vert_anterior); // DEVOLVE O PROXIMO VERTICE A SER VISITADO
int *cria_caminho_final(int *caminho_atual, int tamanho_caminho); // CRIA O CAMINHO DA PALAVRA FINAL
PALAVRAS *realloca_tamanho_palavras_lista(PALAVRAS *head, int tamanho); // QUANDO SE ANDA VERTICES PARA TRAS RETIRA SE AS LETRAS INTRODUZIDAS
char *cria_palavra_final(char *palavra_nova);

#endif // AUXILIAR_OPCOES_H_INCLUDED
