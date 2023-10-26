#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void opcoes(int **marestas, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[])
{
    int lixo=0;

    if(strcmp(cabecalho.O, "A1")==0)
    {
        opcaoA1(marestas,vertices,fout,nome_ficheiro_dic);
    }
    else if(strcmp(cabecalho.O, "A2")==0)
    {
        opcaoA2(marestas,vertices,fout,nome_ficheiro_dic);
    }
    else if(strcmp(cabecalho.O, "D1")==0)
    {
        opcaoD1(marestas,vertices,fout,nome_ficheiro_dic);
    }
    else if(strcmp(cabecalho.O, "D2")==0)
    {
        opcaoD2(marestas,vertices,fout,nome_ficheiro_dic);
    }
    else if(strcmp(cabecalho.O, "E1")==0)
    {
        opcaoE1(marestas,vertices,fout,nome_ficheiro_dic);
    }
    else if(strcmp(cabecalho.O, "E2")==0)
    {
        opcaoE2(marestas,vertices,fout,nome_ficheiro_dic);
    }
    else if(strcmp(cabecalho.O, "F1")==0)
    {
        opcaoF1(marestas,vertices,fout,nome_ficheiro_dic);
    }
    else if(strcmp(cabecalho.O, "F2")==0)
    {
        opcaoF2(marestas,vertices,fout,nome_ficheiro_dic);
    }
    else
    {
        if(fprintf(fout, "%d %d %s %d %d -1\n\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial) > 0)
            lixo = lixo+1;
    }
}

void opcaoA1(int **matriz, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]){

    int t,vert_seguinte=0;
    int *caminho_vert=NULL, teste = 0, tamanho_caminho = 0, num_palavras = 0;
    int *vert_vistos=NULL, vert_anterior;
    DIC_PALAVRAS **head_dicionario = NULL;
    PALAVRAS *head_lista_palavras = NULL;
    char *word = NULL,*l1 =  NULL,*l2 = NULL;
    char *palavra_final = NULL;
    int  *caminho_char = NULL;
    int valor_final = 0, comp_palav=0;


    // ALOCA ESPAÇO PARA O VETOR QUE VERIFICA OS VERTICES JA VISTOS E PARA O VETOR QUE VE O NUMERO DE LETRAS INTRODUZIDAS EM CADA VERTICE
    vert_vistos = (int*)malloc(cabecalho.V*sizeof(int*));
    caminho_char = (int*)malloc(1*sizeof(int*));
    // INICIALIZA O VETOR COM 0 (TODOS OS VERTICES AINDA TEM NAO VISTO)
    for(t=0; t<cabecalho.V; t++)
        vert_vistos[t] = 0;
    // ESTE VETOR SERVE DE PILHA, SEMPRE QUE SE PASSA NUM VERTICE INTRODUZ SE QUANDO NAO A MAIS TIRA SE E VAI SE AO ANTERIOR
    caminho_vert = (int*)malloc(1*sizeof(int*));
    tamanho_caminho = 1;
    // O PRIMEIRO VERTICE E O DADO PELO ENUNCIADO E INICIALIZA SE O VETOR VISTOS COM 1
    caminho_vert[0] = (cabecalho.v_inicial-1);
    vert_vistos[(cabecalho.v_inicial-1)] = 1;
    vert_anterior = -1;
    valor_final = vertices[(cabecalho.v_inicial-1)].valor;
    // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
    teste = cria_segmento_palavra(&l1,&l2,&word,vertices[(cabecalho.v_inicial-1)].ch);
    // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
    if(word != NULL){
        head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
        // VE O NUMERO DE PALAVRAS DO DICIONARIO
        num_palavras = numero_palavras(nome_ficheiro_dic,word);
        // CRIA O DICIONARIO
        head_dicionario = cria_dicionario_hash_table(nome_ficheiro_dic,num_palavras,word);
        // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
        caminho_char[0] = strlen(word);
        comp_palav = comp_palav + strlen(word);
        free(word);
        word = NULL;
    }
    else{
        // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
        head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
        // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
        caminho_char[0] = 1;
        comp_palav = comp_palav + 1;

        num_palavras = numero_palavras_cadeia(nome_ficheiro_dic,l1,l2);
        // CRIA O DICIONARIO
        head_dicionario = cria_dicionario_hash_table_cadeia(nome_ficheiro_dic,num_palavras,l1,l2);

        free(l1);
        free(l2);
        l1 = NULL;
        l2 = NULL;
    }
    palavra_final = devolve_palavra_resposta_ao_problema_A(head_dicionario,head_lista_palavras,num_palavras,&teste);

    if((palavra_final == NULL)&&(teste !=3)&&(comp_palav <= cabecalho.k))
    {
        do{
            vert_seguinte = deepsearch(matriz,caminho_vert[(tamanho_caminho-1)], vert_vistos,vert_anterior);

            if(vert_seguinte != -1)
            {
                // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
                teste = cria_segmento_palavra(&l1,&l2,&word,vertices[vert_seguinte].ch);
                // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
                if(word != NULL)
                    comp_palav = comp_palav + strlen(word);
                else
                    comp_palav = comp_palav + 1;
                if((teste != 2)&&(comp_palav <= cabecalho.k))
                {
                    if(word != NULL){
                        head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
                        // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = strlen(word);
                        free(word);
                        word = NULL;
                    }
                    else{
                        // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
                        head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
                        // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = 1;
                        free(l1);
                        free(l2);
                        l1 = NULL;
                        l2 = NULL;
                    }
                    palavra_final = devolve_palavra_resposta_ao_problema_A(head_dicionario,head_lista_palavras,num_palavras,&teste);

                    vert_vistos[vert_seguinte] = 1;
                    vert_anterior = -1;
                    tamanho_caminho++;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                    valor_final = valor_final + vertices[vert_seguinte].valor;
                }
                else{
                    caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                    caminho_char[(tamanho_caminho)] = 0;
                    vert_vistos[vert_seguinte] = 1;
                    tamanho_caminho++;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                    teste = 2;
                    if(word != NULL)
                        comp_palav = comp_palav - strlen(word);
                    else
                        comp_palav = comp_palav - 1;
                }
            }
            if((vert_seguinte == -1) || (teste == 3)||(teste == 2))
            {
                if(teste == 2)
                {
                    if(word != NULL){
                        free(word);
                        word = NULL;
                    }
                    else{
                        free(l1);
                        free(l2);
                        l1 = NULL;
                        l2 = NULL;
                    }
                }
                vert_anterior = caminho_vert[(tamanho_caminho-1)];
                vert_vistos[caminho_vert[(tamanho_caminho-1)]] = 0;
                if(teste != 2){
                    head_lista_palavras = realloca_tamanho_palavras_lista(head_lista_palavras,caminho_char[(tamanho_caminho-1)]);
                    valor_final = valor_final - vertices[caminho_vert[(tamanho_caminho-1)]].valor;
                    comp_palav = comp_palav - caminho_char[(tamanho_caminho-1)];
                }
                tamanho_caminho--;
                caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho)));
            }
            if(palavra_final != NULL)
                break;
        }while(tamanho_caminho > 0);
    }
    if(palavra_final != NULL)
    {
        fprintf(fout, "%d %d %s %d %d 1\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
        fprintf(fout, "%s ",palavra_final);
        for(t = 0; t < tamanho_caminho; t++)
            fprintf(fout, "%d ",(caminho_vert[t]+1));
        fprintf(fout,"%d\n\n",valor_final);
        free(palavra_final);
    }
    else{
        fprintf(fout, "%d %d %s %d %d -1\n\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
    }

    liberta_dicionario(head_dicionario, num_palavras);
    liberta_lista_palavras(head_lista_palavras);
    if(caminho_char != NULL)
        free(caminho_char);
    if(caminho_vert != NULL)
        free(caminho_vert);
    if(vert_vistos != NULL)
        free(vert_vistos);
}

void opcaoA2(int **matriz, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]){

    int t,vert_seguinte=0;
    int *caminho_vert=NULL, teste = 0, tamanho_caminho = 0, num_palavras = 0,c = 0;
    int *vert_vistos=NULL, vert_anterior;
    DIC_PALAVRAS **head_dicionario = NULL;
    PALAVRAS *head_lista_palavras = NULL;
    char *word = NULL,*l1 =  NULL,*l2 = NULL;
    char *palavra_final = NULL;
    int  *caminho_char = NULL, valor_final = 0, comp_palav = 0;


    vert_vistos = (int*)malloc(cabecalho.V*sizeof(int*));


    for(c = 0; c <cabecalho.V;c++)
    {
        head_lista_palavras = NULL;
        head_dicionario = NULL;
        teste = 0;
        comp_palav = 0;
        num_palavras = 0;
        valor_final = vertices[c].valor;
        // ALOCA ESPAÇO PARA O VETOR QUE VERIFICA OS VERTICES JA VISTOS E PARA O VETOR QUE VE O NUMERO DE LETRAS INTRODUZIDAS EM CADA VERTICE
        caminho_char = (int*)malloc(1*sizeof(int*));
        // INICIALIZA O VETOR COM 0 (TODOS OS VERTICES AINDA TEM NAO VISTO)
        for(t=0; t<cabecalho.V; t++)
            vert_vistos[t] = 0;
        // ESTE VETOR SERVE DE PILHA, SEMPRE QUE SE PASSA NUM VERTICE INTRODUZ SE QUANDO NAO A MAIS TIRA SE E VAI SE AO ANTERIOR
        caminho_vert = (int*)malloc(1*sizeof(int*));
        tamanho_caminho = 1;
        // O PRIMEIRO VERTICE E O DADO PELO ENUNCIADO E INICIALIZA SE O VETOR VISTOS COM 1
        caminho_vert[0] = c;
        vert_vistos[c] = 1;
        vert_anterior = -1;
        // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
        teste = cria_segmento_palavra(&l1,&l2,&word,vertices[c].ch);
        // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA

        if(word != NULL){
            head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
            // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
            // VE O NUMERO DE PALAVRAS DO DICIONARIO
            num_palavras = numero_palavras(nome_ficheiro_dic,word);
            // CRIA O DICIONARIO
            head_dicionario = cria_dicionario_hash_table(nome_ficheiro_dic,num_palavras,word);
            caminho_char[0] = strlen(word);
            comp_palav = comp_palav + strlen(word);
            free(word);
            word = NULL;
        }
        else{
            // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
            head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
            // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
            num_palavras = numero_palavras_cadeia(nome_ficheiro_dic,l1,l2);
            // CRIA O DICIONARIO
            head_dicionario = cria_dicionario_hash_table_cadeia(nome_ficheiro_dic,num_palavras,l1,l2);

            comp_palav = comp_palav + 1;
            caminho_char[0] = 1;
            free(l1);
            free(l2);
            l1 = NULL;
            l2 = NULL;
        }
        palavra_final = devolve_palavra_resposta_ao_problema_A(head_dicionario,head_lista_palavras,num_palavras,&teste);

        if((palavra_final == NULL)&&(teste !=3)&&(comp_palav <= cabecalho.k))
        {
            do{
                teste = 0;
                vert_seguinte = deepsearch(matriz,caminho_vert[(tamanho_caminho-1)], vert_vistos,vert_anterior);

                if(vert_seguinte != -1)
                {
                    // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
                    teste = cria_segmento_palavra(&l1,&l2,&word,vertices[vert_seguinte].ch);
                    // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
                    if(word != NULL)
                          comp_palav = comp_palav + strlen(word);
                    else
                          comp_palav = comp_palav + 1;
                    if((teste != 2)&&(comp_palav <= cabecalho.k))
                    {
                        if(word != NULL){
                            head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
                            // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
                            caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                            caminho_char[(tamanho_caminho)] = strlen(word);
                            free(word);
                            word = NULL;
                        }
                        else{
                            // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
                            head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
                            // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
                            caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                            caminho_char[(tamanho_caminho)] = 1;
                            free(l1);
                            free(l2);
                            l1 = NULL;
                            l2 = NULL;
                        }
                        palavra_final = devolve_palavra_resposta_ao_problema_A(head_dicionario,head_lista_palavras,num_palavras,&teste);

                        vert_vistos[vert_seguinte] = 1;
                        vert_anterior = -1;
                        tamanho_caminho++;
                        caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                        caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                        valor_final = valor_final + vertices[vert_seguinte].valor;
                    }
                    else{
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = 0;
                        vert_vistos[vert_seguinte] = 1;
                        tamanho_caminho++;
                        caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                        caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                        teste = 2;
                        if(word != NULL)
                            comp_palav = comp_palav - strlen(word);
                        else
                            comp_palav = comp_palav - 1;
                    }
                }
                if((vert_seguinte == -1) || (teste == 3)||(teste == 2))
                {
                    if(teste == 2)
                    {
                        if(word != NULL){
                            free(word);
                            word = NULL;
                        }
                        else{
                            free(l1);
                            free(l2);
                            l1 = NULL;
                            l2 = NULL;
                        }
                    }
                    vert_anterior = caminho_vert[(tamanho_caminho-1)];
                    vert_vistos[caminho_vert[(tamanho_caminho-1)]] = 0;
                    if(teste != 2){
                        head_lista_palavras = realloca_tamanho_palavras_lista(head_lista_palavras,caminho_char[(tamanho_caminho-1)]);
                        valor_final = valor_final - vertices[caminho_vert[(tamanho_caminho-1)]].valor;
                        comp_palav = comp_palav - caminho_char[(tamanho_caminho-1)];
                    }
                    tamanho_caminho--;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho)));
                }
                if(palavra_final != NULL)
                    break;
            }while(tamanho_caminho > 0);
        }
        if(head_lista_palavras != NULL)
            liberta_lista_palavras(head_lista_palavras);
        if(head_dicionario != NULL)
            liberta_dicionario(head_dicionario, num_palavras);
        if(caminho_char != NULL)
            free(caminho_char);
        if((caminho_vert != NULL)&&(palavra_final == NULL))
            free(caminho_vert);
        if(palavra_final != NULL)
            break;
    }
    if(palavra_final != NULL)
    {
        fprintf(fout, "%d %d %s %d %d 1\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
        fprintf(fout, "%s ",palavra_final);
        for(t = 0; t < tamanho_caminho; t++)
            fprintf(fout, "%d ",(caminho_vert[t]+1));
        fprintf(fout,"%d\n\n",valor_final);
        free(palavra_final);
        free(caminho_vert);
    }
    else{
        fprintf(fout, "%d %d %s %d %d -1\n\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
    }
    if(vert_vistos != NULL)
        free(vert_vistos);
}

char *devolve_palavra_resposta_ao_problema_A(DIC_PALAVRAS **head_dicionario, PALAVRAS *head_lista_palavras, int num_palavras, int *teste){

    int i, teste1  = 0, teste2 = 0;
    char *palavra = NULL;
    DIC_PALAVRAS *aux_dicionario;
    PALAVRAS *aux_lista;

    for(i = 0; i < num_palavras; i++)
    {
        aux_dicionario = head_dicionario[i];
        while(aux_dicionario != NULL)
        {
            for(aux_lista = head_lista_palavras; aux_lista != NULL; aux_lista = aux_lista->next)
            {
                if(strncmp(aux_lista->ch,aux_dicionario->word,strlen(aux_lista->ch))==0)
                {
                    teste2 = 1;
                    if((strlen(aux_lista->ch) == cabecalho.k) && (strcmp(aux_lista->ch,aux_dicionario->word) == 0))
                    {
                        palavra = (char*)malloc((strlen(aux_dicionario->word)+1)*sizeof(char));
                        palavra[strlen(aux_dicionario->word)]='\0';
                        strcpy(palavra,aux_dicionario->word);
                        teste1 = 1;
                        break;
                    }
                }
            }
            if(teste1 == 1)
                break;
            aux_dicionario = aux_dicionario->next;
        }
        if(teste1 == 1)
            break;
    }
    if(teste2 == 1)
        (*teste) = (*teste);
    else
        (*teste) = 3;
    return palavra;
}

void opcaoD1(int **matriz, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]){

    int t,vert_seguinte=0;
    int *caminho_vert=NULL, teste = 0, tamanho_caminho = 0,tamanho_caminho_final = 0, num_palavras = 0;
    int *vert_vistos=NULL, vert_anterior;
    DIC_PALAVRAS **head_dicionario = NULL;
    PALAVRAS *head_lista_palavras = NULL;
    char *word = NULL,*l1 =  NULL,*l2 = NULL;
    char *palavra_final = NULL, *palavra_aux = NULL;
    int  *caminho_char = NULL, *caminho_final = NULL;
    int valor_atual = 0, valor_final = 0, tamanho_palavra=-1;;

    // ALOCA ESPAÇO PARA O VETOR QUE VERIFICA OS VERTICES JA VISTOS E PARA O VETOR QUE VE O NUMERO DE LETRAS INTRODUZIDAS EM CADA VERTICE
    vert_vistos = (int*)malloc(cabecalho.V*sizeof(int*));
    caminho_char = (int*)malloc(1*sizeof(int*));
    // INICIALIZA O VETOR COM 0 (TODOS OS VERTICES AINDA TEM NAO VISTO)
    for(t=0; t<cabecalho.V; t++)
        vert_vistos[t] = 0;
    // ESTE VETOR SERVE DE PILHA, SEMPRE QUE SE PASSA NUM VERTICE INTRODUZ SE QUANDO NAO A MAIS TIRA SE E VAI SE AO ANTERIOR
    caminho_vert = (int*)malloc(1*sizeof(int*));
    tamanho_caminho = 1;
    // O PRIMEIRO VERTICE E O DADO PELO ENUNCIADO E INICIALIZA SE O VETOR VISTOS COM 1
    caminho_vert[0] = (cabecalho.v_inicial-1);
    vert_vistos[(cabecalho.v_inicial-1)] = 1;
    vert_anterior = -1;
    valor_atual = vertices[(cabecalho.v_inicial-1)].valor;
    // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
    teste = cria_segmento_palavra(&l1,&l2,&word,vertices[(cabecalho.v_inicial-1)].ch);
    // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
    if(word != NULL){
        head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);

         // VE O NUMERO DE PALAVRAS DO DICIONARIO
        num_palavras = numero_palavras_sem_k(nome_ficheiro_dic,word);
        // CRIA O DICIONARIO
        head_dicionario = cria_dicionario_hash_table_sem_k(nome_ficheiro_dic,num_palavras,word);
        // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
        caminho_char[0] = strlen(word);
        free(word);
        word = NULL;
    }
    else{
        // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
        head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
        // VE O NUMERO DE PALAVRAS DO DICIONARIO
        num_palavras = numero_palavras_cadeia_sem_k(nome_ficheiro_dic,l1,l2);
        // CRIA O DICIONARIO
        head_dicionario = cria_dicionario_hash_table_cadeia_sem_k(nome_ficheiro_dic,num_palavras,l1,l2);
        // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
        caminho_char[0] = 1;
        free(l1);
        free(l2);
        l1 = NULL;
        l2 = NULL;
    }
    palavra_aux = devolve_palavra_resposta_ao_problema_D(head_dicionario,head_lista_palavras,num_palavras,&teste);

    if(palavra_aux != NULL)
    {
        palavra_final = cria_palavra_final(palavra_aux);
        caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
        tamanho_caminho_final = tamanho_caminho;
        free(palavra_aux);
        palavra_aux = NULL;
        valor_final = valor_atual;
        tamanho_palavra = strlen(palavra_final);
    }

    if(teste !=3)
    {
        do{
            vert_seguinte = deepsearch(matriz,caminho_vert[(tamanho_caminho-1)], vert_vistos,vert_anterior);

            if(vert_seguinte != -1)
            {
                // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
                teste = cria_segmento_palavra(&l1,&l2,&word,vertices[vert_seguinte].ch);
                // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
                if(teste != 2)
                {
                    if(word != NULL){
                        head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
                        // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = strlen(word);
                        free(word);
                        word = NULL;
                    }
                    else{
                        // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
                        head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
                        // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = 1;
                        free(l1);
                        free(l2);
                        l1 = NULL;
                        l2 = NULL;
                    }
                    vert_vistos[vert_seguinte] = 1;
                    vert_anterior = -1;
                    tamanho_caminho++;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                    valor_atual = valor_atual + vertices[vert_seguinte].valor;

                    palavra_aux = devolve_palavra_resposta_ao_problema_D(head_dicionario,head_lista_palavras,num_palavras,&teste);

                    if(palavra_aux != NULL)
                    {
                        if(palavra_final == NULL){
                            palavra_final = cria_palavra_final(palavra_aux);
                            caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                            tamanho_caminho_final = tamanho_caminho;
                            valor_final = valor_atual;
                            tamanho_palavra = strlen(palavra_final);
                        }
                        else{
                            if(strlen(palavra_aux) > strlen(palavra_final)){
                                free(palavra_final);
                                free(caminho_final);
                                palavra_final = NULL;
                                palavra_final = cria_palavra_final(palavra_aux);
                                caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                                tamanho_caminho_final = tamanho_caminho;
                                valor_final = valor_atual;
                                tamanho_palavra = strlen(palavra_final);
                            }
                        }
                        free(palavra_aux);
                        palavra_aux = NULL;
                    }
                }
                else{
                    caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                    caminho_char[(tamanho_caminho)] = 0;
                    vert_vistos[vert_seguinte] = 1;
                    tamanho_caminho++;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                }
            }
            if((vert_seguinte == -1) || (teste == 3)||(teste == 2))
            {
                if(teste == 2)
                {
                    if(word != NULL){
                        free(word);
                        word = NULL;
                    }
                    else{
                        free(l1);
                        free(l2);
                        l1 = NULL;
                        l2 = NULL;
                    }
                }
                vert_anterior = caminho_vert[(tamanho_caminho-1)];
                vert_vistos[caminho_vert[(tamanho_caminho-1)]] = 0;
                if(teste != 2){
                    head_lista_palavras = realloca_tamanho_palavras_lista(head_lista_palavras,caminho_char[(tamanho_caminho-1)]);
                    valor_atual = valor_atual - vertices[caminho_vert[(tamanho_caminho-1)]].valor;
                }
                tamanho_caminho--;
                caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho)));
            }
        }while(tamanho_caminho > 0);
    }
    if(palavra_final != NULL)
    {
        fprintf(fout, "%d %d %s %d %d 1\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
        fprintf(fout, "%s ",palavra_final);
        for(t = 0; t < tamanho_caminho_final; t++)
            fprintf(fout, "%d ",(caminho_final[t]+1));
        fprintf(fout,"%d\n\n",valor_final);
        free(palavra_final);
        free(caminho_final);
    }
    else{
        fprintf(fout, "%d %d %s %d %d -1\n\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
    }

    liberta_dicionario(head_dicionario, num_palavras);
    liberta_lista_palavras(head_lista_palavras);

    if(caminho_char != NULL)
        free(caminho_char);
    if(caminho_vert != NULL)
        free(caminho_vert);
    if(vert_vistos != NULL)
        free(vert_vistos);
}

void opcaoD2(int **matriz, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]){

    int t,vert_seguinte=0;
    int *caminho_vert=NULL, teste = 0, tamanho_caminho = 0, tamanho_caminho_final = 0, num_palavras = 0,c = 0;
    int *vert_vistos=NULL, vert_anterior;
    DIC_PALAVRAS **head_dicionario = NULL;
    PALAVRAS *head_lista_palavras = NULL;
    char *word = NULL,*l1 =  NULL,*l2 = NULL, *palavra_aux = NULL;
    char *palavra_final = NULL;
    int  *caminho_char = NULL, *caminho_final = NULL;
    int valor_final = 0, valor_atual = 0;

    vert_vistos = (int*)malloc(cabecalho.V*sizeof(int*));

    for(c = 0; c <cabecalho.V;c++)
    {
        head_lista_palavras = NULL;
        head_dicionario = NULL;
        teste = 0;
        valor_atual = vertices[c].valor;
        // ALOCA ESPAÇO PARA O VETOR QUE VERIFICA OS VERTICES JA VISTOS E PARA O VETOR QUE VE O NUMERO DE LETRAS INTRODUZIDAS EM CADA VERTICE
        caminho_char = (int*)malloc(1*sizeof(int*));
        // INICIALIZA O VETOR COM 0 (TODOS OS VERTICES AINDA TEM NAO VISTO)
        for(t=0; t<cabecalho.V; t++)
            vert_vistos[t] = 0;
        // ESTE VETOR SERVE DE PILHA, SEMPRE QUE SE PASSA NUM VERTICE INTRODUZ SE QUANDO NAO A MAIS TIRA SE E VAI SE AO ANTERIOR
        caminho_vert = (int*)malloc(1*sizeof(int*));
        tamanho_caminho = 1;
        // O PRIMEIRO VERTICE E O DADO PELO ENUNCIADO E INICIALIZA SE O VETOR VISTOS COM 1
        caminho_vert[0] = c;
        vert_vistos[c] = 1;
        vert_anterior = -1;
        // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
        teste = cria_segmento_palavra(&l1,&l2,&word,vertices[c].ch);
        // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
        if(word != NULL){
            head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
            // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
            // VE O NUMERO DE PALAVRAS DO DICIONARIO
            num_palavras = numero_palavras_sem_k(nome_ficheiro_dic,word);
            // CRIA O DICIONARIO
            head_dicionario = cria_dicionario_hash_table_sem_k(nome_ficheiro_dic,num_palavras,word);
            caminho_char[0] = strlen(word);
            free(word);
            word = NULL;
        }
        else{
            // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
            head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
            // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
            num_palavras = numero_palavras_cadeia_sem_k(nome_ficheiro_dic,l1,l2);
            // CRIA O DICIONARIO
            head_dicionario = cria_dicionario_hash_table_cadeia_sem_k(nome_ficheiro_dic,num_palavras,l1,l2);
            caminho_char[0] = 1;
            free(l1);
            free(l2);
            l1 = NULL;
            l2 = NULL;
        }
        palavra_aux = devolve_palavra_resposta_ao_problema_D(head_dicionario,head_lista_palavras,num_palavras,&teste);

        if(palavra_aux != NULL)
        {
            if(palavra_final == NULL){
                palavra_final = cria_palavra_final(palavra_aux);
                caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                tamanho_caminho_final = tamanho_caminho;
                valor_final = valor_atual;
            }
            else{
                if(strlen(palavra_aux) > strlen(palavra_final)){
                    free(palavra_final);
                    free(caminho_final);
                    palavra_final = NULL;
                    palavra_final = cria_palavra_final(palavra_aux);
                    caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                    tamanho_caminho_final = tamanho_caminho;
                    valor_final = valor_atual;
                }
            }
            free(palavra_aux);
            palavra_aux = NULL;
        }
        if(teste !=3)
        {
            do{
                teste = 0;
                vert_seguinte = deepsearch(matriz,caminho_vert[(tamanho_caminho-1)], vert_vistos,vert_anterior);

                if(vert_seguinte != -1)
                {
                    // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
                    teste = cria_segmento_palavra(&l1,&l2,&word,vertices[vert_seguinte].ch);
                    // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
                    if(teste != 2)
                    {
                        if(word != NULL){
                            head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
                            // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
                            caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                            caminho_char[(tamanho_caminho)] = strlen(word);
                            free(word);
                            word = NULL;
                        }
                        else{
                            // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
                            head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
                            // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
                            caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                            caminho_char[(tamanho_caminho)] = 1;
                            free(l1);
                            free(l2);
                            l1 = NULL;
                            l2 = NULL;
                        }
                        vert_vistos[vert_seguinte] = 1;
                        vert_anterior = -1;
                        tamanho_caminho++;
                        caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                        caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                        valor_atual = valor_atual + vertices[vert_seguinte].valor;

                        palavra_aux = devolve_palavra_resposta_ao_problema_D(head_dicionario,head_lista_palavras,num_palavras,&teste);
                        if(palavra_aux != NULL)
                        {
                            if(palavra_final == NULL){
                                palavra_final = cria_palavra_final(palavra_aux);
                                caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                                tamanho_caminho_final = tamanho_caminho;
                                valor_final = valor_atual;
                            }
                            else{
                                if(strlen(palavra_aux) > strlen(palavra_final)){
                                    free(palavra_final);
                                    free(caminho_final);
                                    palavra_final = NULL;
                                    palavra_final = cria_palavra_final(palavra_aux);
                                    caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                                    tamanho_caminho_final = tamanho_caminho;
                                    valor_final = valor_atual;
                                }
                            }
                            free(palavra_aux);
                            palavra_aux = NULL;
                        }
                    }
                    else{
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = 0;
                        vert_vistos[vert_seguinte] = 1;
                        tamanho_caminho++;
                        caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                        caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                    }
                }
                if((vert_seguinte == -1) || (teste == 3)||(teste == 2))
                {
                    if(teste == 2)
                    {
                        if(word != NULL){
                            free(word);
                            word = NULL;
                        }
                        else{
                            free(l1);
                            free(l2);
                            l1 = NULL;
                            l2 = NULL;
                        }
                    }
                    vert_anterior = caminho_vert[(tamanho_caminho-1)];
                    vert_vistos[caminho_vert[(tamanho_caminho-1)]] = 0;
                    if((teste != 2)){
                        head_lista_palavras = realloca_tamanho_palavras_lista(head_lista_palavras,caminho_char[(tamanho_caminho-1)]);
                        valor_atual = valor_atual - vertices[caminho_vert[(tamanho_caminho-1)]].valor;
                    }
                    tamanho_caminho--;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho)));
                }
            }while(tamanho_caminho > 0);
        }
        if(head_lista_palavras != NULL)
            liberta_lista_palavras(head_lista_palavras);
        if(head_dicionario != NULL)
            liberta_dicionario(head_dicionario, num_palavras);
        if(caminho_char != NULL)
            free(caminho_char);
        if(caminho_vert != NULL)
            free(caminho_vert);
    }

    if(palavra_final != NULL)
    {
        fprintf(fout, "%d %d %s %d %d 1\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
        fprintf(fout, "%s ",palavra_final);
        for(t = 0; t < tamanho_caminho_final; t++)
            fprintf(fout, "%d ",(caminho_final[t]+1));
        fprintf(fout,"%d\n\n",valor_final);
        free(caminho_final);
        free(palavra_final);
    }
    else{
        fprintf(fout, "%d %d %s %d %d -1\n\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
    }
    if(vert_vistos != NULL)
        free(vert_vistos);
}

char *devolve_palavra_resposta_ao_problema_D(DIC_PALAVRAS **head_dicionario, PALAVRAS *head_lista_palavras, int num_palavras, int *teste){

    int i, teste1  = 0, teste2 = 0;
    char *palavra = NULL;
    DIC_PALAVRAS *aux_dicionario;
    PALAVRAS *aux_lista;

    for(i = 0; i < num_palavras; i++)
    {
        aux_dicionario = head_dicionario[i];
        while(aux_dicionario != NULL)
        {
            for(aux_lista = head_lista_palavras; aux_lista != NULL; aux_lista = aux_lista->next)
            {
                if(strncmp(aux_lista->ch,aux_dicionario->word,strlen(aux_lista->ch))==0)
                {
                    teste2 = 1;

                    if(strcmp(aux_lista->ch,aux_dicionario->word) == 0)
                    {
                        palavra = (char*)malloc((strlen(aux_dicionario->word)+1)*sizeof(char));
                        palavra[strlen(aux_dicionario->word)]='\0';
                        strcpy(palavra,aux_dicionario->word);
                        teste1 = 1;
                        break;
                    }
                }
            }
            if(teste1 == 1)
                break;
            aux_dicionario = aux_dicionario->next;
        }
        if(teste1 == 1)
            break;
    }
    if(teste2 == 1)
        (*teste) = (*teste);
    else
        (*teste) = 3;

    return palavra;
}

void opcaoE1(int **matriz, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]){

    int t,vert_seguinte=0;
    int *caminho_vert=NULL, teste = 0, tamanho_caminho = 0,tamanho_caminho_final = 0, num_palavras = 0;
    int *vert_vistos=NULL, vert_anterior=0, valor_final = 0, valor_atual = 0;
    DIC_PALAVRAS **head_dicionario = NULL;
    PALAVRAS *head_lista_palavras = NULL;
    char *word = NULL,*l1 =  NULL,*l2 = NULL;
    char *palavra_final = NULL, *palavra_aux = NULL;
    int  *caminho_char = NULL, *caminho_final = NULL, compPalav = 0;

    // ALOCA ESPAÇO PARA O VETOR QUE VERIFICA OS VERTICES JA VISTOS E PARA O VETOR QUE VE O NUMERO DE LETRAS INTRODUZIDAS EM CADA VERTICE
    vert_vistos = (int*)malloc(cabecalho.V*sizeof(int*));
    caminho_char = (int*)malloc(1*sizeof(int*));
    // INICIALIZA O VETOR COM 0 (TODOS OS VERTICES AINDA TEM NAO VISTO)
    for(t=0; t<cabecalho.V; t++)
        vert_vistos[t] = 0;
    // ESTE VETOR SERVE DE PILHA, SEMPRE QUE SE PASSA NUM VERTICE INTRODUZ SE QUANDO NAO A MAIS TIRA SE E VAI SE AO ANTERIOR
    caminho_vert = (int*)malloc(1*sizeof(int*));
    tamanho_caminho = 1;
    // O PRIMEIRO VERTICE E O DADO PELO ENUNCIADO E INICIALIZA SE O VETOR VISTOS COM 1
    caminho_vert[0] = (cabecalho.v_inicial-1);
    vert_vistos[(cabecalho.v_inicial-1)] = 1;
    vert_anterior = -1;
    valor_atual = vertices[(cabecalho.v_inicial-1)].valor;
    // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
    teste = cria_segmento_palavra(&l1,&l2,&word,vertices[(cabecalho.v_inicial-1)].ch);
    // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
    if(word != NULL){
        head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
        // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
        num_palavras = numero_palavras(nome_ficheiro_dic,word);
        // CRIA O DICIONARIO
        head_dicionario = cria_dicionario_hash_table(nome_ficheiro_dic,num_palavras,word);
        caminho_char[0] = strlen(word);
        compPalav = compPalav + strlen(word);
        free(word);
        word = NULL;
    }
    else{
        // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
        head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
        // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
        caminho_char[0] = 1;
        num_palavras = numero_palavras_cadeia(nome_ficheiro_dic,l1,l2);
        compPalav = compPalav + 1;
        // CRIA O DICIONARIO
        head_dicionario = cria_dicionario_hash_table_cadeia(nome_ficheiro_dic,num_palavras,l1,l2);
        free(l1);
        free(l2);
        l1 = NULL;
        l2 = NULL;
    }
    palavra_aux = devolve_palavra_resposta_ao_problema_A(head_dicionario,head_lista_palavras,num_palavras,&teste);

    if(palavra_aux != NULL)
    {
        palavra_final = cria_palavra_final(palavra_aux);
        caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
        tamanho_caminho_final = tamanho_caminho;
        valor_final = valor_atual;
        free(palavra_aux);
        palavra_aux = NULL;
    }
    if((teste !=3)&&(compPalav <= cabecalho.k))
    {
        do{
            vert_seguinte = deepsearch(matriz,caminho_vert[(tamanho_caminho-1)], vert_vistos,vert_anterior);

            if(vert_seguinte != -1)
            {
                // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
                teste = cria_segmento_palavra(&l1,&l2,&word,vertices[vert_seguinte].ch);
                // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
                if(word != NULL)
                    compPalav = compPalav + strlen(word);
                else
                    compPalav = compPalav + 1;
                if((teste != 2)&&(compPalav <= cabecalho.k))
                {
                    if(word != NULL){
                        head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
                        // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = strlen(word);
                        free(word);
                        word = NULL;
                    }
                    else{
                        // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
                        head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
                        // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = 1;
                        free(l1);
                        free(l2);
                        l1 = NULL;
                        l2 = NULL;
                    }
                    vert_vistos[vert_seguinte] = 1;
                    vert_anterior = -1;
                    tamanho_caminho++;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                    valor_atual = valor_atual + vertices[vert_seguinte].valor;

                    palavra_aux = devolve_palavra_resposta_ao_problema_A(head_dicionario,head_lista_palavras,num_palavras,&teste);
                    if(palavra_aux != NULL)
                    {
                        if(palavra_final == NULL){
                            palavra_final = cria_palavra_final(palavra_aux);
                            caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                            tamanho_caminho_final = tamanho_caminho;
                            valor_final = valor_atual;
                        }
                        else{
                            if(valor_atual > valor_final){
                                free(palavra_final);
                                free(caminho_final);
                                palavra_final = NULL;
                                palavra_final = cria_palavra_final(palavra_aux);
                                caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                                tamanho_caminho_final = tamanho_caminho;
                                valor_final = valor_atual;
                            }
                        }
                        free(palavra_aux);
                        palavra_aux = NULL;
                    }
                }
                else{
                    caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                    caminho_char[(tamanho_caminho)] = 0;
                    vert_vistos[vert_seguinte] = 1;
                    tamanho_caminho++;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                    teste = 2;
                    if(word != NULL)
                        compPalav = compPalav - strlen(word);
                    else
                        compPalav = compPalav - 1;
                }
            }
            if((vert_seguinte == -1) || (teste == 3)||(teste == 2))
            {
                if(teste == 2)
                {
                    if(word != NULL){
                        free(word);
                        word = NULL;
                    }
                    else{
                        free(l1);
                        free(l2);
                        l1 = NULL;
                        l2 = NULL;
                    }
                }
                vert_anterior = caminho_vert[(tamanho_caminho-1)];
                vert_vistos[caminho_vert[(tamanho_caminho-1)]] = 0;
                if(teste != 2){
                    head_lista_palavras = realloca_tamanho_palavras_lista(head_lista_palavras,caminho_char[(tamanho_caminho-1)]);
                    valor_atual = valor_atual - vertices[caminho_vert[(tamanho_caminho-1)]].valor;
                    compPalav = compPalav - caminho_vert[(tamanho_caminho-1)];
                }
                tamanho_caminho--;
                caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho)));
            }
        }while(tamanho_caminho > 0);
    }

    if(palavra_final != NULL)
    {
        fprintf(fout, "%d %d %s %d %d 1\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
        fprintf(fout, "%s ",palavra_final);
        for(t = 0; t < tamanho_caminho_final; t++)
            fprintf(fout, "%d ",(caminho_final[t]+1));
        fprintf(fout, "%d\n\n",valor_final);
        free(palavra_final);
        free(caminho_final);
    }
    else{
        fprintf(fout, "%d %d %s %d %d -1\n\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
    }

    liberta_dicionario(head_dicionario, num_palavras);
    liberta_lista_palavras(head_lista_palavras);

    if(caminho_char != NULL)
        free(caminho_char);
    if(caminho_vert != NULL)
        free(caminho_vert);
    if(vert_vistos != NULL)
        free(vert_vistos);
}

void opcaoE2(int **matriz, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]){

    int t,vert_seguinte=0;
    int *caminho_vert=NULL, teste = 0, tamanho_caminho = 0, tamanho_caminho_final = 0, num_palavras = 0,c = 0;
    int *vert_vistos=NULL, vert_anterior;
    DIC_PALAVRAS **head_dicionario = NULL;
    PALAVRAS *head_lista_palavras = NULL;
    char *word = NULL,*l1 =  NULL,*l2 = NULL, *palavra_aux = NULL;
    char *palavra_final = NULL;
    int  *caminho_char = NULL, *caminho_final;
    int valor_final = 0, valor_atual = 0,compPalav = 0;

    vert_vistos = (int*)malloc(cabecalho.V*sizeof(int*));

    for(c = 0; c <cabecalho.V;c++)
    {
        head_lista_palavras = NULL;
        head_dicionario = NULL;
        teste = 0;
        compPalav = 0;
        valor_atual = vertices[c].valor;
        // ALOCA ESPAÇO PARA O VETOR QUE VERIFICA OS VERTICES JA VISTOS E PARA O VETOR QUE VE O NUMERO DE LETRAS INTRODUZIDAS EM CADA VERTICE
        caminho_char = (int*)malloc(1*sizeof(int*));
        // INICIALIZA O VETOR COM 0 (TODOS OS VERTICES AINDA TEM NAO VISTO)
        for(t=0; t<cabecalho.V; t++)
            vert_vistos[t] = 0;
        // ESTE VETOR SERVE DE PILHA, SEMPRE QUE SE PASSA NUM VERTICE INTRODUZ SE QUANDO NAO A MAIS TIRA SE E VAI SE AO ANTERIOR
        caminho_vert = (int*)malloc(1*sizeof(int*));
        tamanho_caminho = 1;
        // O PRIMEIRO VERTICE E O DADO PELO ENUNCIADO E INICIALIZA SE O VETOR VISTOS COM 1
        caminho_vert[0] = c;
        vert_vistos[c] = 1;
        vert_anterior = -1;
        // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
        teste = cria_segmento_palavra(&l1,&l2,&word,vertices[c].ch);
        // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
        if(word != NULL){
            head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
            // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
            caminho_char[0] = strlen(word);
            compPalav = compPalav + strlen(word);
            num_palavras = numero_palavras(nome_ficheiro_dic,word);
            // CRIA O DICIONARIO
            head_dicionario = cria_dicionario_hash_table(nome_ficheiro_dic,num_palavras,word);
            free(word);
            word = NULL;
        }
        else{
            // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
            head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
            // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
            caminho_char[0] = 1;
            num_palavras = numero_palavras_cadeia(nome_ficheiro_dic,l1,l2);
            compPalav = compPalav +1;
            // CRIA O DICIONARIO
            head_dicionario = cria_dicionario_hash_table_cadeia(nome_ficheiro_dic,num_palavras,l1,l2);
            free(l1);
            free(l2);
            l1 = NULL;
            l2 = NULL;
        }
        palavra_aux = devolve_palavra_resposta_ao_problema_A(head_dicionario,head_lista_palavras,num_palavras,&teste);

        if(palavra_aux != NULL)
        {
            if(palavra_final == NULL){
                palavra_final = cria_palavra_final(palavra_aux);
                caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                tamanho_caminho_final = tamanho_caminho;
                valor_final = valor_atual;
            }
            else{
                if(valor_atual > valor_final){
                    free(palavra_final);
                    free(caminho_final);
                    palavra_final = NULL;
                    palavra_final = cria_palavra_final(palavra_aux);
                    caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                    tamanho_caminho_final = tamanho_caminho;
                    valor_final = valor_atual;
                }
            }
            free(palavra_aux);
            palavra_aux = NULL;
        }
        if((teste !=3)&&(compPalav <= cabecalho.k))
        {
            do{
                teste = 0;
                vert_seguinte = deepsearch(matriz,caminho_vert[(tamanho_caminho-1)], vert_vistos,vert_anterior);

                if(vert_seguinte != -1)
                {
                    // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
                    teste = cria_segmento_palavra(&l1,&l2,&word,vertices[vert_seguinte].ch);
                    // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
                    if(word != NULL)
                        compPalav = compPalav + strlen(word);
                    else
                        compPalav = compPalav + 1;
                    if((teste != 2)&&(compPalav <= cabecalho.k))
                    {
                        if(word != NULL){
                            head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
                            // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
                            caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                            caminho_char[(tamanho_caminho)] = strlen(word);
                            free(word);
                            word = NULL;
                        }
                        else{
                            // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
                            head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
                            // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
                            caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                            caminho_char[(tamanho_caminho)] = 1;
                            free(l1);
                            free(l2);
                            l1 = NULL;
                            l2 = NULL;
                        }
                        vert_vistos[vert_seguinte] = 1;
                        vert_anterior = -1;
                        tamanho_caminho++;
                        caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                        caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                        valor_atual = valor_atual + vertices[vert_seguinte].valor;

                        palavra_aux = devolve_palavra_resposta_ao_problema_A(head_dicionario,head_lista_palavras,num_palavras,&teste);
                        if(palavra_aux != NULL)
                        {
                            if(palavra_final == NULL){
                                palavra_final = cria_palavra_final(palavra_aux);
                                caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                                tamanho_caminho_final = tamanho_caminho;
                                valor_final = valor_atual;
                            }
                            else{
                                if(valor_atual > valor_final){
                                    free(palavra_final);
                                    free(caminho_final);
                                    palavra_final = NULL;
                                    palavra_final = cria_palavra_final(palavra_aux);
                                    caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                                    tamanho_caminho_final = tamanho_caminho;
                                    valor_final = valor_atual;
                                }
                            }
                            free(palavra_aux);
                            palavra_aux = NULL;
                        }
                    }
                    else{
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = 0;
                        vert_vistos[vert_seguinte] = 1;
                        tamanho_caminho++;
                        caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                        caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                        teste = 2;
                        if(word != NULL)
                            compPalav = compPalav - strlen(word);
                        else
                            compPalav = compPalav - 1;
                    }
                }
                if((vert_seguinte == -1) || (teste == 3)||(teste == 2))
                {
                    if(teste == 2)
                    {
                        if(word != NULL){
                            free(word);
                            word = NULL;
                        }
                        else{
                            free(l1);
                            free(l2);
                            l1 = NULL;
                            l2 = NULL;
                        }
                    }
                    vert_anterior = caminho_vert[(tamanho_caminho-1)];
                    vert_vistos[caminho_vert[(tamanho_caminho-1)]] = 0;
                    if((teste != 2)){
                        head_lista_palavras = realloca_tamanho_palavras_lista(head_lista_palavras,caminho_char[(tamanho_caminho-1)]);
                        valor_atual = valor_atual - vertices[caminho_vert[(tamanho_caminho-1)]].valor;
                        compPalav = compPalav - caminho_vert[(tamanho_caminho-1)];
                    }
                    tamanho_caminho--;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho)));
                }
            }while(tamanho_caminho > 0);
        }
        if(head_lista_palavras != NULL)
            liberta_lista_palavras(head_lista_palavras);
        if(head_dicionario != NULL)
            liberta_dicionario(head_dicionario, num_palavras);
        if(caminho_char != NULL)
            free(caminho_char);
        if(caminho_vert != NULL)
            free(caminho_vert);
    }
    if(palavra_final != NULL)
    {
        fprintf(fout, "%d %d %s %d %d 1\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
        fprintf(fout, "%s ",palavra_final);
        for(t = 0; t < tamanho_caminho_final; t++)
            fprintf(fout, "%d ",(caminho_final[t]+1));
        fprintf(fout,"%d\n\n",valor_final);
        free(caminho_final);
        free(palavra_final);
    }
    else{
        fprintf(fout, "%d %d %s %d %d -1\n\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
    }
    if(vert_vistos != NULL)
        free(vert_vistos);
}

void opcaoF1(int **matriz, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]){

    int t,vert_seguinte=0;
    int *caminho_vert=NULL, teste = 0, tamanho_caminho = 0,tamanho_caminho_final = 0, num_palavras = 0;
    int *vert_vistos=NULL, vert_anterior;
    DIC_PALAVRAS **head_dicionario = NULL;
    PALAVRAS *head_lista_palavras = NULL;
    char *word = NULL,*l1 =  NULL,*l2 = NULL;
    char *palavra_final = NULL, *palavra_aux = NULL;
    int  *caminho_char = NULL, *caminho_final = NULL;
    int valor_atual = 0, valor_final = 0, valor = 0;

    // ALOCA ESPAÇO PARA O VETOR QUE VERIFICA OS VERTICES JA VISTOS E PARA O VETOR QUE VE O NUMERO DE LETRAS INTRODUZIDAS EM CADA VERTICE
    vert_vistos = (int*)malloc(cabecalho.V*sizeof(int*));
    caminho_char = (int*)malloc(1*sizeof(int*));
    // INICIALIZA O VETOR COM 0 (TODOS OS VERTICES AINDA TEM NAO VISTO)
    for(t=0; t<cabecalho.V; t++)
        vert_vistos[t] = 0;
    // ESTE VETOR SERVE DE PILHA, SEMPRE QUE SE PASSA NUM VERTICE INTRODUZ SE QUANDO NAO A MAIS TIRA SE E VAI SE AO ANTERIOR
    caminho_vert = (int*)malloc(1*sizeof(int*));
    tamanho_caminho = 1;
    // O PRIMEIRO VERTICE E O DADO PELO ENUNCIADO E INICIALIZA SE O VETOR VISTOS COM 1
    caminho_vert[0] = (cabecalho.v_inicial-1);
    vert_vistos[(cabecalho.v_inicial-1)] = 1;
    vert_anterior = -1;
    valor_atual = vertices[(cabecalho.v_inicial-1)].valor;
    // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
    teste = cria_segmento_palavra(&l1,&l2,&word,vertices[(cabecalho.v_inicial-1)].ch);
    // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA

    if(word != NULL){
        head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
        // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
        num_palavras = numero_palavras_sem_k(nome_ficheiro_dic,word);
        // CRIA O DICIONARIO
        head_dicionario = cria_dicionario_hash_table_sem_k(nome_ficheiro_dic,num_palavras,word);
        caminho_char[0] = strlen(word);
        free(word);
        word = NULL;
    }
    else{
        // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
        head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
        // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
        num_palavras = numero_palavras_cadeia_sem_k(nome_ficheiro_dic,l1,l2);
        // CRIA O DICIONARIO
        head_dicionario = cria_dicionario_hash_table_cadeia_sem_k(nome_ficheiro_dic,num_palavras,l1,l2);
        caminho_char[0] = 1;
        free(l1);
        free(l2);
        l1 = NULL;
        l2 = NULL;
    }
    palavra_aux = devolve_palavra_resposta_ao_problema_F(valor_atual,head_dicionario,head_lista_palavras,num_palavras,&teste);
    if(palavra_aux != NULL)
    {
        palavra_final = cria_palavra_final(palavra_aux);
        caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
        tamanho_caminho_final = tamanho_caminho;
        free(palavra_aux);
        palavra_aux = NULL;
        valor_final = valor_atual;
    }
    if((teste !=3)&&(valor_atual <= cabecalho.k))
    {
        do{
            vert_seguinte = deepsearch(matriz,caminho_vert[(tamanho_caminho-1)], vert_vistos,vert_anterior);

            if(vert_seguinte != -1)
            {
                // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
                teste = cria_segmento_palavra(&l1,&l2,&word,vertices[vert_seguinte].ch);
                // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA

                if((teste != 2)&&((valor_atual+vertices[vert_seguinte].valor) <= cabecalho.k))
                {
                    if(word != NULL){
                        head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
                        // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = strlen(word);
                        free(word);
                        word = NULL;
                    }
                    else if (l1 != NULL){
                        // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
                        head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
                        // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = 1;
                        free(l1);
                        free(l2);
                        l1 = NULL;
                        l2 = NULL;
                    }
                    vert_vistos[vert_seguinte] = 1;
                    vert_anterior = -1;
                    tamanho_caminho++;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                    valor_atual = valor_atual + vertices[vert_seguinte].valor;

                    palavra_aux = devolve_palavra_resposta_ao_problema_F(valor_atual,head_dicionario,head_lista_palavras,num_palavras,&teste);

                    if(palavra_aux != NULL)
                    {
                        if(palavra_final == NULL){
                            palavra_final = cria_palavra_final(palavra_aux);
                            caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                            tamanho_caminho_final = tamanho_caminho;
                            valor_final = valor_atual;
                        }
                        else{
                            if(strlen(palavra_aux) < strlen(palavra_final)){
                                free(palavra_final);
                                free(caminho_final);
                                palavra_final = NULL;
                                palavra_final = cria_palavra_final(palavra_aux);
                                caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                                tamanho_caminho_final = tamanho_caminho;
                                valor_final = valor_atual;
                            }
                        }
                        free(palavra_aux);
                        palavra_aux = NULL;
                    }
                }
                else{
                    caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                    caminho_char[(tamanho_caminho)] = 0;
                    vert_vistos[vert_seguinte] = 1;
                    tamanho_caminho++;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                    teste = 2;
                }
            }
            if((vert_seguinte == -1) || (teste == 3)||(teste == 2))
            {
                if(teste == 2)
                {
                    if(word != NULL){
                        free(word);
                        word = NULL;
                    }
                    else if (l1 != NULL){
                        free(l1);
                        free(l2);
                        l1 = NULL;
                        l2 = NULL;
                    }
                }
                vert_anterior = caminho_vert[(tamanho_caminho-1)];
                vert_vistos[caminho_vert[(tamanho_caminho-1)]] = 0;
                if(teste != 2){
                    head_lista_palavras = realloca_tamanho_palavras_lista(head_lista_palavras,caminho_char[(tamanho_caminho-1)]);
                    valor_atual = valor_atual - vertices[caminho_vert[(tamanho_caminho-1)]].valor;
                }
                tamanho_caminho--;
                caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho)));
            }
        }while(tamanho_caminho > 0);
    }

    if(palavra_final != NULL)
    {
        fprintf(fout, "%d %d %s %d %d 1\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
        fprintf(fout, "%s ",palavra_final);
        for(t = 0; t < tamanho_caminho_final; t++)
            fprintf(fout, "%d ",(caminho_final[t]+1));
        fprintf(fout,"%d\n\n",valor_final);
        free(palavra_final);
        free(caminho_final);
    }
    else{
        fprintf(fout, "%d %d %s %d %d -1\n\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
    }
    if(head_dicionario != NULL)
        liberta_dicionario(head_dicionario, num_palavras);
    if(head_lista_palavras != NULL)
        liberta_lista_palavras(head_lista_palavras);

    if(caminho_char != NULL)
        free(caminho_char);
    if(caminho_vert != NULL)
        free(caminho_vert);
    if(vert_vistos != NULL)
        free(vert_vistos);
}

void opcaoF2(int **matriz, VERTICES *vertices, FILE *fout, char nome_ficheiro_dic[]){

    int t,vert_seguinte=0;
    int *caminho_vert=NULL, teste = 0, tamanho_caminho = 0, tamanho_caminho_final = 0, num_palavras = 0,c = 0;
    int *vert_vistos=NULL, vert_anterior;
    DIC_PALAVRAS **head_dicionario = NULL;
    PALAVRAS *head_lista_palavras = NULL;
    char *word = NULL,*l1 =  NULL,*l2 = NULL, *palavra_aux = NULL;
    char *palavra_final = NULL;
    int  *caminho_char = NULL, *caminho_final;
    int valor_final = 0, valor_atual = 0;

    vert_vistos = (int*)malloc(cabecalho.V*sizeof(int*));

    for(c = 0; c <cabecalho.V;c++)
    {
        head_lista_palavras = NULL;
        head_dicionario = NULL;
        teste = 0;
        valor_atual = vertices[c].valor;
        // ALOCA ESPAÇO PARA O VETOR QUE VERIFICA OS VERTICES JA VISTOS E PARA O VETOR QUE VE O NUMERO DE LETRAS INTRODUZIDAS EM CADA VERTICE
        caminho_char = (int*)malloc(1*sizeof(int*));
        // INICIALIZA O VETOR COM 0 (TODOS OS VERTICES AINDA TEM NAO VISTO)
        for(t=0; t<cabecalho.V; t++)
            vert_vistos[t] = 0;
        // ESTE VETOR SERVE DE PILHA, SEMPRE QUE SE PASSA NUM VERTICE INTRODUZ SE QUANDO NAO A MAIS TIRA SE E VAI SE AO ANTERIOR
        caminho_vert = (int*)malloc(1*sizeof(int*));
        tamanho_caminho = 1;
        // O PRIMEIRO VERTICE E O DADO PELO ENUNCIADO E INICIALIZA SE O VETOR VISTOS COM 1
        caminho_vert[0] = c;
        vert_vistos[c] = 1;
        vert_anterior = -1;
        // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
        teste = cria_segmento_palavra(&l1,&l2,&word,vertices[c].ch);
        // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA
        if(word != NULL){
            head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
            // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
            caminho_char[0] = strlen(word);
            num_palavras = numero_palavras(nome_ficheiro_dic,word);
            // CRIA O DICIONARIO
            head_dicionario = cria_dicionario_hash_table(nome_ficheiro_dic,num_palavras,word);
            free(word);
            word = NULL;
        }
        else{
            // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
            head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
            // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
            caminho_char[0] = 1;
            num_palavras = numero_palavras_cadeia(nome_ficheiro_dic,l1,l2);
            // CRIA O DICIONARIO
            head_dicionario = cria_dicionario_hash_table_cadeia(nome_ficheiro_dic,num_palavras,l1,l2);
            free(l1);
            free(l2);
            l1 = NULL;
            l2 = NULL;
        }
        palavra_aux = devolve_palavra_resposta_ao_problema_F(valor_atual,head_dicionario,head_lista_palavras,num_palavras,&teste);
        if(palavra_aux != NULL)
        {
            if(palavra_final == NULL){
                palavra_final = cria_palavra_final(palavra_aux);
                caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                tamanho_caminho_final = tamanho_caminho;
                valor_final = valor_atual;
            }
            else{
                if(strlen(palavra_aux) < strlen(palavra_final)){
                    free(palavra_final);
                    free(caminho_final);
                    palavra_final = NULL;
                    palavra_final = cria_palavra_final(palavra_aux);
                    caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                    tamanho_caminho_final = tamanho_caminho;
                    valor_final = valor_atual;
                }
            }
            free(palavra_aux);
            palavra_aux = NULL;
        }
        if((teste !=3)&&(valor_atual <= cabecalho.k))
        {
            do{
                teste = 0;
                vert_seguinte = deepsearch(matriz,caminho_vert[(tamanho_caminho-1)], vert_vistos,vert_anterior);

                if(vert_seguinte != -1)
                {
                    // RETIRA DO VERTICE AS LETRAS QUE LA ESTAO
                    teste = cria_segmento_palavra(&l1,&l2,&word,vertices[vert_seguinte].ch);
                    // SE FOR SUFIXO, PREFICO OU LETRAS CRIA SE A LISTA DE PALAVRAS DESTA FORMA

                    if((teste != 2)&&((valor_atual+vertices[vert_seguinte].valor) <= cabecalho.k))
                    {
                        if(word != NULL){
                            head_lista_palavras = cria_lista_palavras(head_lista_palavras,word);
                            // NESTA POSICAO ADICIONARAM SE ESTAS LETRAS POR ISSO ADICIONA SE AO CAMINHO DE CHARS O SEU NUMERO
                            caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                            caminho_char[(tamanho_caminho)] = strlen(word);
                            free(word);
                            word = NULL;
                        }
                        else{
                            // SE FOR UMA CADEIA DE LETRAS ADICIONA SE A LISTA DESTA FORMA
                            head_lista_palavras = cria_lista_palavras_cadeia_palavras(head_lista_palavras,l1,l2);
                            // COMO E UMA CADEIA DE LETRAS APENAS INTRODUZ UMA LETRA EM CADA PALAVRA
                            caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                            caminho_char[(tamanho_caminho)] = 1;
                            free(l1);
                            free(l2);
                            l1 = NULL;
                            l2 = NULL;
                        }
                        vert_vistos[vert_seguinte] = 1;
                        vert_anterior = -1;
                        tamanho_caminho++;
                        caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                        caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                        valor_atual = valor_atual + vertices[vert_seguinte].valor;

                        palavra_aux = devolve_palavra_resposta_ao_problema_F(valor_atual,head_dicionario,head_lista_palavras,num_palavras,&teste);
                        if(palavra_aux != NULL)
                        {
                            if(palavra_final == NULL){
                                palavra_final = cria_palavra_final(palavra_aux);
                                caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                                tamanho_caminho_final = tamanho_caminho;
                                valor_final = valor_atual;
                            }
                            else{
                                if(strlen(palavra_aux) < strlen(palavra_final)){
                                    free(palavra_final);
                                    free(caminho_final);
                                    palavra_final = NULL;
                                    palavra_final = cria_palavra_final(palavra_aux);
                                    caminho_final = cria_caminho_final(caminho_vert,tamanho_caminho);
                                    tamanho_caminho_final = tamanho_caminho;
                                    valor_final = valor_atual;
                                }
                            }
                            free(palavra_aux);
                            palavra_aux = NULL;
                        }
                    }
                    else{
                        caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho+1)));
                        caminho_char[(tamanho_caminho)] = 0;
                        vert_vistos[vert_seguinte] = 1;
                        tamanho_caminho++;
                        caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                        caminho_vert[(tamanho_caminho-1)] = vert_seguinte;
                        teste = 2;
                    }
                }
                if((vert_seguinte == -1) || (teste == 3)||(teste == 2))
                {
                    if(teste == 2)
                    {
                        if(word != NULL){
                            free(word);
                            word = NULL;
                        }
                        else{
                            free(l1);
                            free(l2);
                            l1 = NULL;
                            l2 = NULL;
                        }
                    }
                    vert_anterior = caminho_vert[(tamanho_caminho-1)];
                    vert_vistos[caminho_vert[(tamanho_caminho-1)]] = 0;
                    if((teste != 2)){
                        head_lista_palavras = realloca_tamanho_palavras_lista(head_lista_palavras,caminho_char[(tamanho_caminho-1)]);
                        valor_atual = valor_atual - vertices[caminho_vert[(tamanho_caminho-1)]].valor;
                    }
                    tamanho_caminho--;
                    caminho_vert = (int*)realloc(caminho_vert,(sizeof(int)*tamanho_caminho));
                    caminho_char = (int*)realloc(caminho_char,(sizeof(int)*(tamanho_caminho)));
                }
            }while(tamanho_caminho > 0);
        }
        if(head_lista_palavras != NULL)
            liberta_lista_palavras(head_lista_palavras);
        if(head_dicionario != NULL)
            liberta_dicionario(head_dicionario, num_palavras);
        if(caminho_char != NULL)
            free(caminho_char);
        if(caminho_vert != NULL)
            free(caminho_vert);
    }

    if(palavra_final != NULL)
    {
        fprintf(fout, "%d %d %s %d %d 1\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
        fprintf(fout, "%s ",palavra_final);
        for(t = 0; t < tamanho_caminho_final; t++)
            fprintf(fout, "%d ",(caminho_final[t]+1));
        fprintf(fout,"%d\n\n",valor_final);
        free(caminho_final);
        free(palavra_final);
    }
    else{
        fprintf(fout, "%d %d %s %d %d -1\n\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
    }
    if(vert_vistos != NULL)
        free(vert_vistos);
}

char *devolve_palavra_resposta_ao_problema_F(int valor_atual, DIC_PALAVRAS **head_dicionario, PALAVRAS *head_lista_palavras, int num_palavras, int *teste){

    int i, teste1  = 0, teste2 = 0;
    char *palavra = NULL;
    DIC_PALAVRAS *aux_dicionario;
    PALAVRAS *aux_lista;
    for(i = 0; i < num_palavras; i++)
    {
        aux_dicionario = head_dicionario[i];
        while(aux_dicionario != NULL)
        {
            for(aux_lista = head_lista_palavras; aux_lista != NULL; aux_lista = aux_lista->next)
            {
                if(strncmp(aux_lista->ch,aux_dicionario->word,strlen(aux_lista->ch))==0)
                {
                    teste2 = 1;
                    if((strcmp(aux_lista->ch,aux_dicionario->word) == 0)&&(valor_atual == cabecalho.k))
                    {
                        palavra = (char*)malloc((strlen(aux_dicionario->word)+1)*sizeof(char));
                        palavra[strlen(aux_dicionario->word)]='\0';
                        strcpy(palavra,aux_dicionario->word);
                        teste1 = 1;
                        break;
                    }
                }
            }
            if(teste1 == 1)
                break;
            aux_dicionario = aux_dicionario->next;
        }
        if(teste1 == 1)
            break;
    }
    if(teste2 == 1)
        (*teste) = (*teste);
    else
        (*teste) = 3;
    return palavra;
}

