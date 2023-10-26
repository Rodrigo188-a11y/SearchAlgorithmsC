#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"
#include "functions.h"
#include "dicionario.h"
#include "auxiliar_opcoes.h"

int main(int argc, char *argv[])
{
    char *aux1, *aux2, *dict, *graph0, *nomefout, vstring[30];
    int lenargv2 = 0, i, parcount=0, lvstring, **marestas, j, v1=0, v2=0, lixo=0, erro = 0;
    FILE *fgraph0, *fout;
    graph0 = ".graph";
    dict = ".dict";
    aux2 = ".";
    // VE SE O TERMINAL TEM 3 PALAVRAS
    if(argc != 3)
        exit(0);

    aux1 = strstr(argv[1], aux2);

    if(aux1 == NULL)
        exit(0);

    if(strcmp(aux1, dict) != 0)
        exit(0);

    aux1 = strstr(argv[2], aux2);

    if(aux1 == NULL)
        exit(0);

    if(strcmp(aux1, graph0) != 0)
        exit(0);

    fgraph0 = fopen(argv[2], "r");

    if(fgraph0 == NULL)
        exit(0);

    lenargv2 = strlen(argv[2]);

    // CRIA ESPACO PARA GUARDAR O NOME DO FICHEIRO DE SAIDA
    nomefout = (char*)malloc((lenargv2+1)*sizeof(char));

    // COPIA DO TERMINAL O NOME DO FICHEIRO DE SAIDA
    strcpy(nomefout, argv[2]);
    // INTRODUZ A PALAVRA WORDZ NO FICHEIRO DE SAIDA
    nomefout[lenargv2-6] = 'w';
    nomefout[lenargv2-5] = 'o';
    nomefout[lenargv2-4] = 'r';
    nomefout[lenargv2-3] = 'd';
    nomefout[lenargv2-2] = 'z';
    // ABRE O FICHEIRO DE SAIDA
    fout = fopen(nomefout, "w");

    do{
        // LE O CABECALHO E GUARDA O NA VARIAVEL GLOBAL
        erro = 0;
        parcount = fscanf(fgraph0, "%d %d %s %d %d", &cabecalho.V, &cabecalho.E, cabecalho.O, &cabecalho.k, &cabecalho.v_inicial);
        if((cabecalho.V < 1) || (cabecalho.E < 1))
            erro = 1;
        if(cabecalho.k < 0)
            erro = 1;
        if((cabecalho.v_inicial < 0)||(cabecalho.v_inicial > cabecalho.V))
            erro = 1;
        // SE O CABECALHO TIVER 5 ARGUMENTOS ESTA CORRETO E RETIRA O RESTO DO FICHEIRO
        if((parcount == 5) && (erro !=1))
        {
            // ALOCA MEMORIA PARA AS LINHAS DA MATRIZ DE ADJACENCIAS
            marestas = (int**)malloc(cabecalho.V*sizeof(int*));
            // ALOCA MEMORIA PARA AS COLUNAS DE CADA LINHA DA MATRIZ DE ASJACENCIAS
            for(i=0; i<cabecalho.V; i++)
                marestas[i] = (int*)malloc(cabecalho.V*sizeof(int));
            // INICIALIZA A MATRIZ DE ADJACENCIA A 0
            for(i=0; i<cabecalho.V; i++)
            {
                for(j=0;j<cabecalho.V;j++)
                    marestas[i][j] = 0;
            }
            // ALOCA ESPACO PARA UM VETOR DE ESTRUTURAS QUE GUARDAM O QUE ESTA NOS VERTICES
            VERTICES *vertices;
            vertices = (VERTICES*)malloc((cabecalho.V)*sizeof(VERTICES));
            // LE O FICHEIRO E INTRODUZ O QUE LA ESTA NOS VERTICES
            for(i=0; i<cabecalho.V; i++)
            {
                if(fscanf(fgraph0, "%d", &lixo) == 1)
                    lixo = lixo+1;
                if(fscanf(fgraph0, "%s", vstring) == 1)
                    lixo = lixo+1;
                lvstring = strlen(vstring);
                vertices[i].ch = (char*)malloc(lvstring*sizeof(char)+1);
                strcpy(vertices[i].ch, vstring);
                if(fscanf(fgraph0, "%d", &(vertices[i].valor)) == 1)
                    lixo = lixo+1;
            }
            // LE O FICHEIRO E INTRODUZ AS ARESTAS NA MATRIZ DE ADJACENCIA
            for(i=0; i<cabecalho.E; i++)
            {
                if(fscanf(fgraph0, "%d %d", &v1, &v2) == 2)
                    lixo = lixo+1;
                marestas[v1-1][v2-1] = -1;
                marestas[v2-1][v1-1] = -1;
            }
            // ENVIA OS DADOS RETIRADOS PARA RESOLVER A OPCAO CORRETA
            opcoes(marestas,vertices,fout,argv[1]);

            // LIBERTA A MATRIZ DE ADJACENCIA
            for(i=0; i<cabecalho.V; i++)
                free(marestas[i]);

            free(marestas);
            // LIBERTA O VETOR DE VERTICES
            for(j=0; j<cabecalho.V; j++)
                free(vertices[j].ch);

            free(vertices);
        }
        if(erro == 1)
            fprintf(fout, "%d %d %s %d %d -1 \n\n", cabecalho.V, cabecalho.E, cabecalho.O, cabecalho.k, cabecalho.v_inicial);
        // VE SE EXISTE OUTRO ENUNCIADO E SE SIM CORRE O PROGRAMA OUTRA VEZ
    }while(parcount == 5);

    // FECHA O FICHEIRO ABERTO E AS VARIAVEIS ALOCADAS DINAMICAMENTE
    fclose(fgraph0);

    fclose(fout);

    free(nomefout);

    return 0;
}
