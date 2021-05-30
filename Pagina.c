#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pagina.h"

struct pagina{
    char* nome;
    char* arquivo;
    ListaHet* contribuicoes;
    ListaHet* historicoContribuicoes;
    ListaHet* links;
};

Pagina* CriaPagina(char* nome, char* arquivo){
    Pagina* pag = (Pagina*)malloc(sizeof(Pagina));
    pag->nome=strdup(nome);
    pag->arquivo=strdup(arquivo);
    pag->contribuicoes= IniciaLista();
    pag->historicoContribuicoes= IniciaLista();
    pag->links = IniciaLista();

    return pag;
}

char* RecuperaNomePagina(Pagina* pag){
    return pag->nome;
}

char* RecuperaArquivoPagina(Pagina* pag){
    return pag->arquivo;
}

ListaHet* RecuperaContribuicoes(Pagina* pag){
    return pag->contribuicoes;
}

ListaHet* RecuperaHistoricoContribuicoes(Pagina* pag){
    return pag->contribuicoes;
}

ListaHet* RecuperaLinks(Pagina* pag){
    return pag->links;
}

void ImprimePaginaCompleta(Pagina* pag, FILE* arquivo){

    fprintf(arquivo,"%s\n\n",pag->nome);

    fprintf(arquivo,"--> Historico de contribuicoes\n");
    ImprimeContribuicoesSimples(pag->historicoContribuicoes,pag->contribuicoes, arquivo);

    fprintf(arquivo,"\n--> Links\n");
    ImprimePaginasSimples(pag->links, arquivo);

    fprintf(arquivo,"\n--> Textos\n");
    ImprimeContribuicoesCompletas(pag->contribuicoes,arquivo);

}

void ImprimePaginaSimples(Pagina* pag , FILE* arquivo){
    fprintf(arquivo,"%s %s\n",pag->nome, pag->arquivo);
}

int AdicionaContribuicaoPagina(Pagina* pag, Contribuicao* cont){
    int jaExiste = ContemItem(pag->contribuicoes,cont,CONTRIBUICAO);
    if(jaExiste)
        return 0;

    InsereLista(pag->contribuicoes,cont, CONTRIBUICAO);
    InsereLista(pag->historicoContribuicoes,cont, CONTRIBUICAO);

    return 1;
}

void DestroiPagina(Pagina* pag){
    if(pag != NULL){
        free(pag->nome);
        free(pag->arquivo);
        LiberaLista(pag->historicoContribuicoes);
        LiberaLista(pag->contribuicoes);
        LiberaLista(pag->links);
        free(pag);
    }
}