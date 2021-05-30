#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contribuicao.h"

struct contribuicao{
    Editor* editor;
    char* arquivoTexto;
};

Contribuicao* CriaContribuicao (Editor* editor,char* arquivoTexto){
    Contribuicao* cont = (Contribuicao*)malloc(sizeof(Contribuicao));
    cont->editor=editor;
    cont->arquivoTexto=strdup(arquivoTexto);

    return cont;
}

void ImprimeContribuicaoCompleta(Contribuicao* cont, FILE* arquivo){
    fprintf(arquivo,"-------- %s (%s) --------\n\n",
        cont->arquivoTexto,RecuperaNomeEditor(cont->editor));

    //Abre o arquivo da contribuicao que esta na pasta ./entrada
    char path [20]= "./entrada/";
    strcat(path,cont->arquivoTexto);
    FILE* texto = fopen(path,"r");
    if (!texto){
        perror("Erro ao abrir o arquivo. ");
        exit(1);
    }

    //Aloca uma string para ler cada linha do arquivo de texto
    size_t len= 300; 
    char *linha= malloc(len);
    
    //Enquanto ha linhas no arquivo de texto
    while (getline(&linha, &len, texto) > 0){
        //A linha é printada no arquivo da pagina
        fprintf(arquivo,"%s", linha);
    }
    fprintf(arquivo,"\n\n");

    free(linha);
    fclose(texto);
}

void ImprimeContribuicaoSimples(Contribuicao* cont, FILE* arquivo, int retirada){
    char r[20] = " ";
    if(retirada)
        strcpy(r,"<retirada>");

    fprintf(arquivo,"%s %s %s\n",RecuperaNomeEditor(cont->editor), cont->arquivoTexto, r);
}

Editor* RecuperaEditorContribuicao(Contribuicao* cont){
    return cont->editor;
}

char* RecuperaArquivoTextoContribuicao(Contribuicao* cont){
    return cont->arquivoTexto;
}

void DestroiContribuicao(Contribuicao* cont){
    if(cont!=NULL){
        //printf("Destruida: %s\n",cont->arquivoTexto);
        free(cont->arquivoTexto);
        free(cont);
    }
}