#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaHet.h"
#include "Pagina.h"

struct celula{
    Celula* prox;
    void* item;
    int tipo;
};

struct listaHet{
    Celula* Prim;
    Celula* Ult;
};

ListaHet* IniciaLista(){
    ListaHet* lista = (ListaHet*)malloc(sizeof(ListaHet));
    lista->Prim=NULL;
    lista->Ult=NULL;

    return lista;
}

int InsereLista(ListaHet* lista, void* item, int tipo){
    int jaExiste = ContemItem(lista,item,tipo);

    if(jaExiste )
        return 0;

    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->item = item;
    nova->tipo = tipo;
    nova->prox = NULL;

    if(lista->Prim == NULL ){
        lista->Prim = nova;
        lista->Ult = nova;
    }else{
        lista->Ult->prox = nova;
        lista->Ult = nova; 
    }
    return 1;
}

void ImprimeWiked(ListaHet* lista){
    Celula* p;
    FILE* arquivo;
    char path[50] ;
    
    for(p = lista->Prim; p != NULL ; p=p->prox){
        strcpy(path,"./saidas/");
        strcat(path,RecuperaArquivoPagina(p->item));

        arquivo= fopen(path,"w");
        if (!arquivo){
            perror("Erro ao abrir o arquivo.");
            exit(1);
        }
        ImprimePaginaCompleta(p->item, arquivo);
        fprintf(arquivo,"\n");
        fclose(arquivo);
    }
}

void ImprimeContribuicoesSimples(ListaHet* historicoConts, ListaHet* conts, FILE* arquivo){
    Celula* p;
    Contribuicao* c;
    char retirada=0;

    for(p = historicoConts->Prim; p != NULL ; p=p->prox){
        c = Busca(conts,RecuperaArquivoTextoContribuicao(p->item),CONTRIBUICAO);

        if(c == NULL)
            retirada = 1;
        else
            retirada = 0;

        ImprimeContribuicaoSimples(p->item, arquivo, retirada);
    }
}

void ImprimeContribuicoesCompletas(ListaHet* lista, FILE* arquivo){
    Celula* p;

    for(p = lista->Prim; p != NULL ; p=p->prox)
        ImprimeContribuicaoCompleta(p->item, arquivo);

}

void ImprimePaginasSimples(ListaHet* lista, FILE* arquivo){
    Celula* p;

    for(p = lista->Prim; p != NULL ; p=p->prox)
        ImprimePaginaSimples(p->item,arquivo);
}

void* Retira(ListaHet* lista,char* chave,int tipo){
    Celula* p = lista->Prim;
    void* item;
    Celula* ant =  NULL;

    if(tipo==PAGINA){
        //Encontra a pagina que sera retirada
        Pagina* pag =(Pagina*)Busca(lista,chave,PAGINA);

        if(pag==NULL)
            return NULL;

        for(p = lista->Prim; p!= NULL ; p=p->prox)
           Retira(RecuperaLinks(p->item),chave,LINK);
        
        //Encontra a celula da pagina que sera retirada
        p = lista->Prim;
        while (p!=NULL && strcmp(RecuperaNomePagina(p->item),chave)!=0){
            ant = p;
            p = p->prox;
        }
    }
    if(tipo==LINK)
        while (p!=NULL && strcmp(RecuperaNomePagina(p->item),chave)!=0){
            ant = p;
            p = p->prox;
        }
    if(tipo==EDITOR)
        while (p!=NULL && strcmp(RecuperaNomeEditor(p->item),chave)!=0){
            ant = p;
            p = p->prox;
        }
    if(tipo==CONTRIBUICAO)
        while (p!=NULL && strcmp(RecuperaArquivoTextoContribuicao(p->item),chave)!=0){
            ant = p;
            p = p->prox;
        }

    if(p==NULL)
        return NULL; 

    item = p->item;   
    
    //se for unico
    if(p == lista->Prim && p== lista->Ult)
        lista->Prim = lista->Ult = NULL;
    else if (p == lista->Prim) //se for o primeiro
        lista->Prim = p->prox;
    else if (p == lista->Ult){ //se for o ultimo
        lista->Ult=ant;
        lista->Ult->prox= NULL;
    }else   //caso comum
        ant->prox = p->prox;
    free(p);

    return item;
}

void* Busca(ListaHet* lista, char* nome, int tipo){    
    Celula* p;

    if(lista->Prim == NULL)
        return NULL;
    

    if(tipo==EDITOR)
        for(p = lista->Prim; p != NULL ; p=p->prox)
            if(strcmp(RecuperaNomeEditor(p->item),nome)==0)
                return p->item;

    if(tipo==PAGINA)
        for(p = lista->Prim; p != NULL ; p=p->prox)
            if(strcmp(RecuperaNomePagina(p->item),nome)==0)
                return p->item;

    if(tipo==CONTRIBUICAO)
        for(p = lista->Prim; p != NULL ; p=p->prox)
            if(strcmp(RecuperaArquivoTextoContribuicao(p->item),nome)==0)
                return p->item;


    return NULL;
}

int ContemItem(ListaHet* lista, void* item, int tipo){    
    if(lista->Prim == NULL){
        return 0;
    }

    if(tipo==EDITOR)
        if(Busca(lista,RecuperaNomeEditor(item),EDITOR))
            return 1;

    if(tipo==PAGINA)
        if(Busca(lista,RecuperaNomePagina(item),PAGINA))
            return 1;

    if(tipo==CONTRIBUICAO)
        if(Busca(lista,RecuperaArquivoTextoContribuicao(item),CONTRIBUICAO))
            return 1;
    
    return 0;
}

int Caminho(void* pagOrigem, void* pagDestino){
    ListaHet* mapa = IniciaLista();

    VerificaCaminhos(pagOrigem, mapa);

    if(Busca(mapa,RecuperaNomePagina(pagDestino),PAGINA) == NULL){
         LiberaLista(mapa);
        return 0;
    }else{
        LiberaLista(mapa);
       return 1;
    }
}

void VerificaCaminhos(void* pagina, ListaHet* mapa){
    InsereLista(mapa, pagina, PAGINA);

    ListaHet* listaLink = RecuperaLinks(pagina);
    Celula* p;
    char* nomePag;

    for (p = listaLink->Prim; p!=NULL; p = p->prox) {
        nomePag = RecuperaNomePagina(p->item);

        if(Busca(mapa,nomePag,PAGINA) == NULL){
            VerificaCaminhos(p->item, mapa);
        }
    }
}

void LiberaLista(ListaHet* lista){
    Celula* p = lista->Prim;
    Celula* t;

    while( p != NULL){
        t = p;
        p = p->prox;
        free(t);
    }

    free(lista);
}

void DestroiLista(ListaHet* lista, int tipo){
    Celula* p = lista->Prim;
    Celula* t;

    while( p != NULL){
        t = p->prox;
        
        if(tipo==PAGINA){
            #include "Pagina.h"
            DestroiPagina(p->item);
        }
        else if(tipo==CONTRIBUICAO){
            DestroiContribuicao(p->item);
        }else{
            DestroiEditor(p->item);
        }
        p = t;
    }
    free(p);
    free(t);
    LiberaLista(lista);
}

