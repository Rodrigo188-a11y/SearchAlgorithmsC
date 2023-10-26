#ifndef DICIONARIO_H_INCLUDED
#define DICIONARIO_H_INCLUDED
#include "cabecalho.h"

typedef struct _palavra {
    char *word;
    struct _palavra *next;
}DIC_PALAVRAS; // ESTRUTURA QUE GUARDA CADA PALAVRA DO DICIONARIO

DIC_PALAVRAS **cria_dicionario_hash_table(char nome_ficheiro[], int n_palavras, char *word); // CRIA HASH TABLE PARA GUARDAR DICIONARIO
DIC_PALAVRAS **cria_dicionario_hash_table_cadeia(char nome_ficheiro[], int n_palavras, char *l1, char *l2);
DIC_PALAVRAS **cria_dicionario_hash_table_sem_k(char nome_ficheiro[], int n_palavras, char *word); // CRIA HASH TABLE PARA GUARDAR DICIONARIO
DIC_PALAVRAS **cria_dicionario_hash_table_cadeia_sem_k(char nome_ficheiro[], int n_palavras, char *l1, char *l2);
int numero_palavras(char nome_ficheiro[], char *word); // CONTA O NUMERO DE PALAVRAS DO FICHEIRO
int numero_palavras_cadeia(char nome_ficheiro[], char *l1, char *l2);
int numero_palavras_sem_k(char nome_ficheiro[], char *word); // CONTA O NUMERO DE PALAVRAS DO FICHEIRO
int numero_palavras_cadeia_sem_k(char nome_ficheiro[], char *l1, char *l2);
int disperse(char palavra[], int n_palavras); // CRIA E DEVOLVE O INDICE DA TABELA ONDE VAI FICAR A PALAVRA
void mostra_dicionario(DIC_PALAVRAS **head, int n_palavras); // MOSTRA A HASH TABLE
void liberta_dicionario( DIC_PALAVRAS **head, int num_palavras); // LIBERTA A HASH TABLE


#endif // DICIONARIO_H_INCLUDED
