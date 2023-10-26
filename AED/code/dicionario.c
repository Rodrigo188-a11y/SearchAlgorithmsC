#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"
#define PESO 237

// CRIA E DEVOLVE A HASH TABLE COM O DICIONARIO
DIC_PALAVRAS **cria_dicionario_hash_table_sem_k(char nome_ficheiro[], int n_palavras, char *word){

    DIC_PALAVRAS **tabela=NULL, *x = NULL, *novo;
    FILE *f_dic;
    char palavra[30];
    int i = -1, t =0;

    // ALOCA UMA TABELA COM O COMPRIMENTO DO NUMERO DE PALAVRAS
    tabela = (DIC_PALAVRAS**)calloc(n_palavras,sizeof(DIC_PALAVRAS*));
    // INICIALIZA A LISTA DE PALAVRAS DE CADA INDICE DA TABELA
    for(i=0; i<n_palavras; i++)
        tabela[i] = NULL;

    f_dic = fopen(nome_ficheiro,"r");
    i=-1;
    // CORRE O FICHEIRO DICIONARIO PARA INTRODUZIR AS PALAVRAS NA HASH
    while(fscanf(f_dic,"%s",palavra) == 1)
    {
        if((strncmp(palavra,word,strlen(word))== 0)&&(strlen(palavra)>2))
        {
            t++;
            // CRIA E DEVOLVE O INDICE ONDE VAI FICAR A PALAVRA
            i++;
            // X E UM AUXILIAR PARA CORRER A LISTA DO INDICE [I]
            x = tabela[i];
            if(tabela[i] != NULL)
            {
                // SE O INDICE [I] DA TABELA JA TIVER PALAVRAS ...
                for(x=tabela[i]; x != NULL; x = x->next)
                {
                    // SE JA EXISTIR A PALAVRA NA HASH NAO SE INTRODUZ
                    if(strcmp(x->word, palavra)== 0)
                        break;
                    // SE NAO EXISTIR CRIA-SE UMA NOVA ESTRUTURA E INTRODUZ-SE NA LISTA DE INDICE [I]
                    if(x->next == NULL)
                    {
                        // ALOCA SE ESPACO PARA A ESTRUTURA
                        novo = (DIC_PALAVRAS*)calloc(1,sizeof(DIC_PALAVRAS));
                        // ALOCA SE ESPAÇO PARA A PALAVRA DA ESTRUTURA E METE SE LA A PALAVRA
                        novo->word = (char*)calloc((strlen(palavra)+1),sizeof(char));
                        strcpy(novo->word,palavra);
                        novo->next = NULL;
                        // INTRODUZ-SE NO FIM DA LISTA
                        novo->next = x->next;
                        x->next = novo;
                        break;
                    }
                }
            }
            else if(tabela[i] == NULL){
                // SE A TABELA ESTIVER VAZIA ALOCA SE ESPACO PARA A ESTRUTURA E INTRODUZ SE NO INICIO DA LISTA
                novo = (DIC_PALAVRAS*)calloc(1,sizeof(DIC_PALAVRAS));
                novo->word = (char*)calloc((strlen(palavra)+1),sizeof(char));
                strcpy(novo->word,palavra);
                novo->next = NULL;
                tabela[i] = novo;
            }
        }
    }
    fclose(f_dic);

    return tabela;
}

// CRIA E DEVOLVE A HASH TABLE COM O DICIONARIO
DIC_PALAVRAS **cria_dicionario_hash_table_cadeia_sem_k(char nome_ficheiro[], int n_palavras, char *l1, char *l2){

    DIC_PALAVRAS **tabela=NULL, *x = NULL, *novo;
    FILE *f_dic;
    char palavra[30];
    int i;

    // ALOCA UMA TABELA COM O COMPRIMENTO DO NUMERO DE PALAVRAS
    tabela = (DIC_PALAVRAS**)calloc(n_palavras,sizeof(DIC_PALAVRAS*));
    // INICIALIZA A LISTA DE PALAVRAS DE CADA INDICE DA TABELA
    for(i=0; i<n_palavras; i++)
        tabela[i] = NULL;

    f_dic = fopen(nome_ficheiro,"r");
    i=-1;
    // CORRE O FICHEIRO DICIONARIO PARA INTRODUZIR AS PALAVRAS NA HASH
    while(fscanf(f_dic,"%s",palavra) == 1)
    {
        if(((palavra[0] == l1[0])|| (palavra[0] == l2[0]))&&(strlen(palavra)>2))
        {
            // CRIA E DEVOLVE O INDICE ONDE VAI FICAR A PALAVRA
            i++;
            // X E UM AUXILIAR PARA CORRER A LISTA DO INDICE [I]
            x = tabela[i];
            if(tabela[i] != NULL)
            {
                // SE O INDICE [I] DA TABELA JA TIVER PALAVRAS ...
                for(x=tabela[i]; x != NULL; x = x->next)
                {
                    // SE JA EXISTIR A PALAVRA NA HASH NAO SE INTRODUZ
                    if(strcmp(x->word, palavra)== 0)
                        break;
                    // SE NAO EXISTIR CRIA-SE UMA NOVA ESTRUTURA E INTRODUZ-SE NA LISTA DE INDICE [I]
                    if(x->next == NULL)
                    {
                        // ALOCA SE ESPACO PARA A ESTRUTURA
                        novo = (DIC_PALAVRAS*)calloc(1,sizeof(DIC_PALAVRAS));
                        // ALOCA SE ESPAÇO PARA A PALAVRA DA ESTRUTURA E METE SE LA A PALAVRA
                        novo->word = (char*)calloc((strlen(palavra)+1),sizeof(char));
                        strcpy(novo->word,palavra);
                        novo->next = NULL;
                        // INTRODUZ-SE NO FIM DA LISTA
                        printf("%s\n",novo->word);
                        novo->next = x->next;
                        x->next = novo;
                        break;
                    }
                }
            }
            else if(tabela[i] == NULL){
                // SE A TABELA ESTIVER VAZIA ALOCA SE ESPACO PARA A ESTRUTURA E INTRODUZ SE NO INICIO DA LISTA
                novo = (DIC_PALAVRAS*)calloc(1,sizeof(DIC_PALAVRAS));
                novo->word = (char*)calloc((strlen(palavra)+1),sizeof(char));
                strcpy(novo->word,palavra);
                novo->next = NULL;

                tabela[i] = novo;
            }
        }
    }
    fclose(f_dic);

    return tabela;
}



// CRIA E DEVOLVE A HASH TABLE COM O DICIONARIO
DIC_PALAVRAS **cria_dicionario_hash_table(char nome_ficheiro[], int n_palavras, char *word){

    DIC_PALAVRAS **tabela=NULL, *x = NULL, *novo;
    FILE *f_dic;
    char palavra[30];
    int i;

    // ALOCA UMA TABELA COM O COMPRIMENTO DO NUMERO DE PALAVRAS
    tabela = (DIC_PALAVRAS**)calloc(n_palavras,sizeof(DIC_PALAVRAS*));
    // INICIALIZA A LISTA DE PALAVRAS DE CADA INDICE DA TABELA
    for(i=0; i<n_palavras; i++)
        tabela[i] = NULL;

    f_dic = fopen(nome_ficheiro,"r");
    i=-1;
    // CORRE O FICHEIRO DICIONARIO PARA INTRODUZIR AS PALAVRAS NA HASH
    while(fscanf(f_dic,"%s",palavra) == 1)
    {
        if(strlen(palavra) == cabecalho.k)
        {
            if((strncmp(palavra,word,strlen(word))== 0)&&(strlen(palavra)>2))
            {
                // CRIA E DEVOLVE O INDICE ONDE VAI FICAR A PALAVRA
                i++;
                // X E UM AUXILIAR PARA CORRER A LISTA DO INDICE [I]
                x = tabela[i];
                if(tabela[i] != NULL)
                {
                    // SE O INDICE [I] DA TABELA JA TIVER PALAVRAS ...
                    for(x=tabela[i]; x != NULL; x = x->next)
                    {
                        // SE JA EXISTIR A PALAVRA NA HASH NAO SE INTRODUZ
                        if(strcmp(x->word, palavra)== 0)
                            break;
                        // SE NAO EXISTIR CRIA-SE UMA NOVA ESTRUTURA E INTRODUZ-SE NA LISTA DE INDICE [I]
                        if(x->next == NULL)
                        {
                            // ALOCA SE ESPACO PARA A ESTRUTURA
                            novo = (DIC_PALAVRAS*)calloc(1,sizeof(DIC_PALAVRAS));
                            // ALOCA SE ESPAÇO PARA A PALAVRA DA ESTRUTURA E METE SE LA A PALAVRA
                            novo->word = (char*)calloc((strlen(palavra)+1),sizeof(char));
                            strcpy(novo->word,palavra);
                            novo->next = NULL;
                            // INTRODUZ-SE NO FIM DA LISTA
                            novo->next = x->next;
                            x->next = novo;

                            break;
                        }
                    }
                }
                else if(tabela[i] == NULL){
                // SE A TABELA ESTIVER VAZIA ALOCA SE ESPACO PARA A ESTRUTURA E INTRODUZ SE NO INICIO DA LISTA
                novo = (DIC_PALAVRAS*)calloc(1,sizeof(DIC_PALAVRAS));
                novo->word = (char*)calloc((strlen(palavra)+1),sizeof(char));
                strcpy(novo->word,palavra);
                novo->next = NULL;
                tabela[i] = novo;
                }
            }
        }
    }
    fclose(f_dic);

    return tabela;
}

// CRIA E DEVOLVE A HASH TABLE COM O DICIONARIO
DIC_PALAVRAS **cria_dicionario_hash_table_cadeia(char nome_ficheiro[], int n_palavras, char *l1, char *l2){

    DIC_PALAVRAS **tabela=NULL, *x = NULL, *novo;
    FILE *f_dic;
    char palavra[30];
    int i;

    // ALOCA UMA TABELA COM O COMPRIMENTO DO NUMERO DE PALAVRAS
    tabela = (DIC_PALAVRAS**)calloc(n_palavras,sizeof(DIC_PALAVRAS*));
    // INICIALIZA A LISTA DE PALAVRAS DE CADA INDICE DA TABELA
    for(i=0; i<n_palavras; i++)
        tabela[i] = NULL;

    f_dic = fopen(nome_ficheiro,"r");
    i=-1;
    // CORRE O FICHEIRO DICIONARIO PARA INTRODUZIR AS PALAVRAS NA HASH
    while(fscanf(f_dic,"%s",palavra) == 1)
    {
        if(strlen(palavra) == cabecalho.k)
        {
            if((palavra[0] == l1[0])|| (palavra[0] == l2[0]))
            {
                // CRIA E DEVOLVE O INDICE ONDE VAI FICAR A PALAVRA
                i++;
                // X E UM AUXILIAR PARA CORRER A LISTA DO INDICE [I]
                x = tabela[i];
                if(tabela[i] != NULL)
                {
                    // SE O INDICE [I] DA TABELA JA TIVER PALAVRAS ...
                    for(x=tabela[i]; x != NULL; x = x->next)
                    {
                        // SE JA EXISTIR A PALAVRA NA HASH NAO SE INTRODUZ
                        if(strcmp(x->word, palavra)== 0)
                            break;
                        // SE NAO EXISTIR CRIA-SE UMA NOVA ESTRUTURA E INTRODUZ-SE NA LISTA DE INDICE [I]
                        if(x->next == NULL)
                        {
                            // ALOCA SE ESPACO PARA A ESTRUTURA
                            novo = (DIC_PALAVRAS*)calloc(1,sizeof(DIC_PALAVRAS));
                            // ALOCA SE ESPAÇO PARA A PALAVRA DA ESTRUTURA E METE SE LA A PALAVRA
                            novo->word = (char*)calloc((strlen(palavra)+1),sizeof(char));
                            strcpy(novo->word,palavra);
                            novo->next = NULL;
                            // INTRODUZ-SE NO FIM DA LISTA
                            novo->next = x->next;
                            x->next = novo;
                            break;
                        }
                    }
                }
                else if(tabela[i] == NULL){
                // SE A TABELA ESTIVER VAZIA ALOCA SE ESPACO PARA A ESTRUTURA E INTRODUZ SE NO INICIO DA LISTA
                novo = (DIC_PALAVRAS*)calloc(1,sizeof(DIC_PALAVRAS));
                novo->word = (char*)calloc((strlen(palavra)+1),sizeof(char));
                strcpy(novo->word,palavra);
                novo->next = NULL;

                tabela[i] = novo;
                }
            }
        }
    }
    fclose(f_dic);

    return tabela;
}


// CONTA O NUMERO DE PALAVRAS, PARA SE SABER O TAMANHO DA TABELA
int numero_palavras(char nome_ficheiro[], char *word){

    int n_palavras = 0;
    FILE *f_dict;
    char palavra[30];

    f_dict = fopen(nome_ficheiro,"r");
    // CORRE O FICHEIRO DICIONARIO E CONTA O NUMERO DE PALAVRAS
    while(fscanf(f_dict,"%s",palavra) == 1)
    {
        if(strlen(palavra)==cabecalho.k)
        {
            palavra[strlen(word)] = '\0';
            if(strcmp(palavra,word)== 0)
                n_palavras++;
        }
    }

    fclose(f_dict);
    return n_palavras;
}

int numero_palavras_sem_k(char nome_ficheiro[], char *word){

    int n_palavras = 0;
    FILE *f_dict;
    char palavra[30];

    f_dict = fopen(nome_ficheiro,"r");
    // CORRE O FICHEIRO DICIONARIO E CONTA O NUMERO DE PALAVRAS
    while(fscanf(f_dict,"%s",palavra) == 1)
    {
        if(strlen(palavra)>2)
        {
            palavra[strlen(word)] = '\0';
            if(strcmp(palavra,word)== 0)
                n_palavras++;
        }
    }

    fclose(f_dict);
    return n_palavras;
}


int numero_palavras_cadeia(char nome_ficheiro[], char *l1, char *l2){

    int n_palavras = 0;
    FILE *f_dict;
    char palavra[30];

    f_dict = fopen(nome_ficheiro,"r");
    // CORRE O FICHEIRO DICIONARIO E CONTA O NUMERO DE PALAVRAS
    while(fscanf(f_dict,"%s",palavra) == 1)
    {
        if(strlen(palavra)==cabecalho.k)
        {
            if((palavra[0]==l1[0])||(palavra[0] == l2[0]))
                n_palavras++;
        }
    }

    fclose(f_dict);
    return n_palavras;
}

int numero_palavras_cadeia_sem_k(char nome_ficheiro[], char *l1, char *l2){

    int n_palavras = 0;
    FILE *f_dict;
    char palavra[30];

    f_dict = fopen(nome_ficheiro,"r");
    // CORRE O FICHEIRO DICIONARIO E CONTA O NUMERO DE PALAVRAS
    while(fscanf(f_dict,"%s",palavra) == 1)
    {
        if(((palavra[0]==l1[0])||(palavra[0] == l2[0]))&&(strlen(palavra)>2))
            n_palavras++;
    }

    fclose(f_dict);
    return n_palavras;
}

// CRIA E DEVOLVE O INDICE DA TABELA ONDE SE VAI INTRODUZIR A PALAVRA
int disperse(char palavra[], int n_palavras){

    int n = 0,h = 0,pp = 0,i;

    n = strlen(palavra);
    for(i=0; i<((unsigned int)n); i++)
    {
        pp = ((unsigned int)palavra[i])%512;
        h = (pp *PESO + h)% n_palavras;
    }
    return h;
}

void mostra_dicionario(DIC_PALAVRAS **head, int n_palavras){

    int i;
    DIC_PALAVRAS *aux;
    for(i = 0; i < n_palavras; i++)
    {
        aux = head[i];
        while(aux != NULL)
        {
            printf("tabela = %s ",aux->word );
            aux=aux->next;
        }
    }
}

// LIBERTA A HASH TABLE
void liberta_dicionario( DIC_PALAVRAS **head, int num_palavras){

    DIC_PALAVRAS *auxA, *auxD;
    int i;
    // CORRE A TABELA TODA
    for(i = 0; i < num_palavras; i++)
    {
        // CORRE A LISTA TODA DE CADA INDICE DA TABELA
        for(;head[i]!= NULL; head[i] = auxD)
        {
            auxD = head[i]->next;
            auxA = head[i];
            free(auxA->word);
            free(auxA);
        }
    }
    free(head);
}
