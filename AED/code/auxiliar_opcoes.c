#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliar_opcoes.h"


// CRIA E INTRODUZ NOVOS SEGEMENTOS DE PALAVRAS NA LISTA DE PALAVRAS
PALAVRAS *cria_lista_palavras(PALAVRAS *head, char *aux_palav){

    PALAVRAS *new_palavra, *aux;

    // SE A LISTA AINDA NAO TIVER NADA ...
    if(head == NULL)
    {
        // ALOCA ESPACO PARA 1 ESTRUTURA DO TIPO PALAVRA
        if((new_palavra = (PALAVRAS*)calloc(1,sizeof(PALAVRAS))) == NULL)
            exit(0);
        // ALOCA ESPACO PA AS LETRAS QUE VAO SER INTRODUZIDAS
        if((new_palavra->ch = (char*)calloc((strlen(aux_palav)+1),sizeof(char))) == NULL)
            exit(0);
        // COPIA O QUE ESTA NO AUXILIAR DE PALAVRA E INTRODUZ NA PALAVRA DA ESTRUTURA
        new_palavra->ch[strlen(aux_palav)] = '\0';
        strcpy(new_palavra->ch,aux_palav);
        new_palavra->next = NULL;
        // INTRODUZ A ESTRUTURA NO TOPO DA LISTA
        head = new_palavra;
    }
    else{
        // SE A LISTA NAO ESTIVER VAZIA CORRE SE A LISTA TODA E...
        for(aux = head; aux != NULL; aux = aux->next)
        {
            // PARA CADA PALAVRA JA EXISTENTE ALOCA SE ESPACO PARA O QUE ESTA LA E PARA O QUE SE PRETENDE INTRODUZIR
            if((aux->ch = (char*)realloc(aux->ch,sizeof(char)*(strlen(aux_palav)+strlen(aux->ch)+1))) == NULL)
                exit(0);
            // JUNTA SE A NOVA PARTE DA PALAVRA A PALAVRA JA EXISTENTE
            aux->ch[strlen(aux_palav)+ strlen(aux->ch)] = '\0';
            strcat(aux->ch,aux_palav);
        }
    }
    return head;
}

// CRIA E INTRODUZ NOVOS SEGEMENTOS DE PALAVRAS NA LISTA DE PALAVRAS
PALAVRAS *cria_lista_palavras_cadeia_palavras(PALAVRAS *head, char *aux_palav1, char *aux_palav2){

    PALAVRAS *new_palavra1, *new_palavra2,*aux;

     // SE A LISTA AINDA NAO TIVER NADA ...
    if(head == NULL)
    {
        // COMO E UMA CADEIA DE LETRAS VAI SE CRIAR DUAS NOVAS ESTRUTURAS PARA INTRODUZIR NA LISTA
        if((new_palavra1 = (PALAVRAS*)calloc(1,sizeof(PALAVRAS))) == NULL)
            exit(0);

        if((new_palavra1->ch = (char*)calloc((strlen(aux_palav1)+1),sizeof(char))) == NULL)
            exit(0);
        // COPIA SE O QUE ESTA NO PRIMEIRO SEGMENTO PARA A PRIMEIRA PALAVRA
        new_palavra1->ch[strlen(aux_palav1)] = '\0';
        strcpy(new_palavra1->ch,aux_palav1);
        new_palavra1->next = NULL;

        if((new_palavra2 = (PALAVRAS*)calloc(1,sizeof(PALAVRAS))) == NULL)
            exit(0);

        if((new_palavra2->ch = (char*)calloc((strlen(aux_palav2)+1),sizeof(char))) == NULL)
            exit(0);
        // COPIA SE O QUE ESTA NO SEGUNDO SEGMENTO PARA A SEGUNDA PALAVRA
        new_palavra2->ch[strlen(aux_palav2)] = '\0';
        strcpy(new_palavra2->ch,aux_palav2);
        new_palavra2->next = NULL;

        // INTRODUZ SE A PRIMEIRA ESTRUTURA NO TOPO DA LISTA
        head = new_palavra1;
        // INTRODUZ SE A SEGUNDA ESTRUTURA NO TOPO DA LISTA
        new_palavra2->next = head;
        head = new_palavra2;
    }
    else{
         // SE A LISTA NAO ESTIVER VAZIA CORRE SE A LISTA TODA E...
        for(aux = head; aux != NULL; aux = aux->next)
        {
            // ALOCA SE ESPACO PARA UMA NOVA ESTRUTURA
            if((new_palavra1 = (PALAVRAS*)calloc(1,sizeof(PALAVRAS))) == NULL)
                exit(0);
            // ALOCA SE ESPACO PARA COPIAR A PALAVRA JA EXISTENTE NESTA POSICAO DA LISTA E ADICIONAR O SEGMENTO 1
            if((new_palavra1->ch = (char*)calloc((strlen(aux_palav1)+strlen(aux->ch)+1),sizeof(char))) == NULL)
                exit(0);
            // COPIA SE A PALAVRA JA EXISTENTE NESTA POSICAO DA LISTA E JUNTA SE O SEGMENTO 1
            new_palavra1->ch[strlen(aux_palav1)+strlen(aux->ch)] = '\0';
            strcpy(new_palavra1->ch,aux->ch);
            strcat(new_palavra1->ch,aux_palav1);
            // AUMENTA SE O ESPACO PARA A PALAVRA DA POSICAO ATUAL ONDE SE VAI JUNTAR O SEGMENTO 2
            if((aux->ch = (char*)realloc(aux->ch,sizeof(char)*(strlen(aux_palav2)+strlen(aux->ch)+1))) == NULL)
                exit(0);
            // COPIA SE O SEGMENTO 2 PARA A PALAVRA QUE JA EXISTE NESTA POSICAO
            aux->ch[strlen(aux_palav2)+ strlen(aux->ch)] = '\0';
            strcat(aux->ch,aux_palav2);

            // INTRODUZ SE A NOVA ESTRUTURA NO INICIO DA LISTA E SEGUE SE PARA A POSICAO SEGUINTE DA POSICAO ATUAL
            new_palavra1->next = head;
            head = new_palavra1;
        }
    }
    return head;
}

int cria_segmento_palavra(char **l1, char **l2, char **word, char *novas_letras){

    int j=0;
    int aux1=0, aux2=0, aux3=0;
    char hyphen = '-', slash = '/';
    char *presu, *aux4;
    int lenl2=0;

    aux4 = NULL;
    presu = NULL;

    aux4 = strchr(novas_letras, slash);

    if(aux4 != NULL)
    {
        lenl2 = strlen(aux4);
        (*l2) = (char*)malloc((lenl2+1)*sizeof(char));
        (*l2)[lenl2] = '\0';
        strcpy((*l2), aux4);
    }
    if((*l2) == NULL)
    {
        (*l1) = (char*)malloc((strlen(novas_letras)+1)*sizeof(char));
        (*l1)[strlen(novas_letras)] = '\0';
        strcpy((*l1), novas_letras);
    }
    else
    {
        aux1 = strlen((*l2));
        aux2 = strlen(novas_letras);
        aux3 = aux2-aux1;

        (*l1) = (char*)malloc((aux3+1)*sizeof(char));
        (*l1)[aux3] = '\0';
        strncpy((*l1), novas_letras, aux3);

        for(j=0; j<aux1-1; j++)
        {
            (*l2)[j] = (*l2)[j+1];
        }
        (*l2)[aux1-1] = '\0';

        return 1; // 1 QUER DIZER CADEIA DE LETRAS
    }

    presu = strchr((*l1), hyphen);

    if(presu != NULL)
    {
        if((strlen(presu) == 1))
        {
             (*word) = (char*)malloc(strlen((*l1))*sizeof(char));
             (*word)[strlen((*l1))-1] = '\0';

            strncpy((*word), (*l1), strlen((*l1))-1);
            if((*l1) != NULL)
                free((*l1));

            return 2; // 2 QUER DIZER PREFIXO
        }
        else if(strlen(presu) != 1)
        {
            for(j=0; j<((int)strlen((*l1))-1); j++)
            {
                presu[j] = presu[j+1];
            }

            presu[(int)strlen((*l1))-1] = '\0';

            (*word) = (char*)malloc((strlen((*l1))+1)*sizeof(char));
            (*word)[strlen((*l1))] = '\0';

            strcpy((*word), presu);

            if((*l1) != NULL)
                free((*l1));

            return 3; // 3 QUER DIZER SUFIXO
        }
    }
    else{
        (*word) = (char*)malloc((strlen((*l1))+1)*sizeof(char));
        (*word)[strlen((*l1))] = '\0';
        strcpy( (*word), (*l1));

        if((*l1) != NULL)
            free((*l1));
        if((*l2) != NULL)
            free((*l2));

        return 4; // 4 QUER DIZER LETRAS NORMAIS
    }
    return 0;
}

// LIBERTA A LISTA DE PALAVRAS CRIADA APARTIR DO DFS
void liberta_lista_palavras(PALAVRAS *head){

    PALAVRAS *aux;

    aux = head;
    while(head != NULL)
    {
        aux = head;
        head = head->next;
        free(aux->ch);
        free(aux);
    }
}

int deepsearch(int **matriz, int vert_atual, int *vert_vistos, int vert_anterior){

    int j;

    if(vert_anterior != -1)
    {
        for(j = vert_anterior+1;j<cabecalho.V;j++)
        {
            if((matriz[vert_atual][j] == -1)&&(vert_vistos[j]!=1))
                return j;
        }
    }
    else if(vert_anterior == -1){
        for(j = 0;j<cabecalho.V;j++)
        {
            if((matriz[vert_atual][j] == -1)&&(vert_vistos[j]!=1))
                return j;
        }
    }
    return -1;
}

int *cria_caminho_final(int *caminho_atual, int tamanho_caminho){

    int i;
    int *novo;

    novo = (int*)calloc((tamanho_caminho),sizeof(int));
    for(i = 0; i< tamanho_caminho;i++)
        novo[i] = caminho_atual[i];

    return novo;
}

PALAVRAS *realloca_tamanho_palavras_lista(PALAVRAS *head, int tamanho){

    PALAVRAS *aux1, *aux2, *new_palavra,*new_head = NULL;
    int sub = 0,teste = 0;

    if((tamanho !=1))
    {
        for(aux1 = head; aux1 != NULL; aux1 = aux1->next)
        {
            sub = 0;
            sub = (int)strlen(aux1->ch) - tamanho;
            aux1->ch[sub] = '\0';
        }
        return head;
    }
    else
    {
        for(aux1 = head; aux1 != NULL; aux1 = aux1->next)
        {
            sub = 0;
            sub = (int)strlen(aux1->ch) - tamanho;
            aux1->ch[sub] = '\0';
        }
        // ALOCA ESPACO PARA 1 ESTRUTURA DO TIPO PALAVRA
        if((new_palavra = (PALAVRAS*)calloc(1,sizeof(PALAVRAS))) == NULL)
            exit(0);
        // ALOCA ESPACO PA AS LETRAS QUE VAO SER INTRODUZIDAS
        if((new_palavra->ch = (char*)calloc((strlen(head->ch)+1),sizeof(char))) == NULL)
            exit(0);
        // COPIA O QUE ESTA NO AUXILIAR DE PALAVRA E INTRODUZ NA PALAVRA DA ESTRUTURA
        new_palavra->ch[strlen(head->ch)] = '\0';
        strcpy(new_palavra->ch,head->ch);
        new_palavra->next = NULL;
        // INTRODUZ A ESTRUTURA NO TOPO DA LISTA
        new_head = new_palavra;
        for(aux1 = head; aux1 != NULL; aux1 = aux1->next)
        {
            teste  = 0;
            for(aux2 = new_head;aux2 != NULL; aux2 = aux2->next)
            {
                if(strcmp(aux1->ch,aux2->ch) == 0)
                {
                    teste = 1;
                    break;
                }
            }
            if(teste == 0)
            {
                // ALOCA ESPACO PARA 1 ESTRUTURA DO TIPO PALAVRA
                if((new_palavra = (PALAVRAS*)calloc(1,sizeof(PALAVRAS))) == NULL)
                    exit(0);
                // ALOCA ESPACO PA AS LETRAS QUE VAO SER INTRODUZIDAS
                if((new_palavra->ch = (char*)calloc((strlen(aux1->ch)+1),sizeof(char))) == NULL)
                    exit(0);
                // COPIA O QUE ESTA NO AUXILIAR DE PALAVRA E INTRODUZ NA PALAVRA DA ESTRUTURA
                new_palavra->ch[strlen(aux1->ch)] = '\0';
                strcpy(new_palavra->ch,aux1->ch);
                new_palavra->next = NULL;
                // INTRODUZ A ESTRUTURA NO TOPO DA LISTA
                new_palavra->next = new_head;
                new_head = new_palavra;
            }
        }
        liberta_lista_palavras(head);
        return new_head;
    }
    return 0;
}

char *cria_palavra_final(char *palavra_nova){

    char *cria;

    cria = (char*)calloc((strlen(palavra_nova)+1),sizeof(char));
    cria[strlen(palavra_nova)]='\0';
    strcpy(cria,palavra_nova);

    return cria;
}

