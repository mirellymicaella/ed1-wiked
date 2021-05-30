#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ListaHet.h"
#include "Pagina.h"

int main(int argc, char const *argv[]){

    //Verifica se foi digitado o endereço do arquivo
    if (argc < 2){ 
        printf("ERRO: O diretório de arquivos de configuração não foi informado\n");
        return 0;
    }

    FILE* arquivoEntrada = fopen(argv[1], "r");
    FILE* arquivoLog = fopen("./saidas/log.txt", "w");

    //Verifica se o arquivo digitado eh um endereço valido
    if (arquivoEntrada == NULL){
        printf("Não foi possivel encontrar o arquivo %s \n",argv[1]);
        return 0;
    }
    //Verifica se o arquivo de log foi criado 
    if (arquivoLog == NULL){
        printf("Não foi possivel criar o arquivo de log na pasta './saida' \n");
        return 0;
    }
    ListaHet* paginas = IniciaLista();
    ListaHet* editores = IniciaLista();
    ListaHet* contribuicoes = IniciaLista();

    Pagina* pagina;
    Pagina* pagina2;
    Editor* editor;
    Contribuicao* cont;

    char comando[50];
    char vet[3][50];

    do{
        fscanf(arquivoEntrada,"%s", comando);

        if(strcmp(comando,"INSEREPAGINA")==0){
            fscanf(arquivoEntrada,"%s %s", vet[0], vet[1]);
            pagina = CriaPagina(vet[0],vet[1]);

            if(!InsereLista(paginas,pagina,PAGINA)){
                fprintf(arquivoLog,"ERRO INSEREPAGINA: a pagina %s ja existe.\n\n",vet[0]);                                       
                DestroiPagina(pagina);
            }
        }
        if(strcmp(comando,"INSEREEDITOR")==0){
            fscanf(arquivoEntrada,"%s", vet[0]);
            editor = CriaEditor(vet[0]);

            if(!InsereLista(editores,editor, EDITOR)){
                fprintf(arquivoLog,"ERRO INSEREEDITOR: o editor %s ja existe.\n\n",vet[0]);  
                DestroiEditor(editor);
            }
        }
        if(strcmp(comando,"INSERECONTRIBUICAO")==0){
            fscanf(arquivoEntrada,"%s %s %s", vet[0], vet[1], vet[2]);
            pagina=Busca(paginas,vet[0],PAGINA);
            editor=Busca(editores,vet[1],EDITOR);
            cont = Busca(contribuicoes, vet[2],CONTRIBUICAO);        

            if(!pagina)
                fprintf(arquivoLog,"ERRO INSERECONTRIBUICAO:a pagina %s nao existe\n\n",vet[0]); 
            else if (!editor) 
                fprintf(arquivoLog,"ERRO INSERECONTRIBUICAO:o editor %s nao existe\n\n",vet[1]); 
            else {
                //Se a contribuicao nao existe na wiked ela eh criada
                if(!cont)
                    cont=CriaContribuicao(editor,vet[2]);
            
                if(!AdicionaContribuicaoPagina(pagina,cont))
                    fprintf(arquivoLog,"ERRO INSERECONTRIBUICAO: a contribuicao %s ja existe na pagina %s.\n\n",vet[2], vet[0]);     
                else
                    InsereLista(contribuicoes,cont, CONTRIBUICAO);   
            }                  
        }
        if(strcmp(comando,"INSERELINK")==0){
            fscanf(arquivoEntrada,"%s %s", vet[0],vet[1]);
            pagina= Busca(paginas,vet[0],PAGINA);
            pagina2= Busca(paginas,vet[1],PAGINA);

            if(!pagina)
                fprintf(arquivoLog,"ERRO INSERELINK:a pagina %s nao existe\n\n",vet[0]); 
            else if (!pagina2)
                fprintf(arquivoLog,"ERRO INSERELINK:a pagina %s nao existe\n\n",vet[1]); 
            else if (!InsereLista(RecuperaLinks(pagina),pagina2,PAGINA))
                fprintf(arquivoLog,"ERRO INSERELINK:a pagina %s ja contem link para a pagina %s\n\n",vet[0],vet[1]);      
        }
        if(strcmp(comando,"RETIRAPAGINA")==0){
            fscanf(arquivoEntrada,"%s", vet[0]);
            pagina = Retira(paginas, vet[0], PAGINA); 

            if(!pagina)
                fprintf(arquivoLog,"ERRO RETIRAPAGINA: a pagina %s nao existe.\n\n",vet[0]);           
            else
                DestroiPagina(pagina);          
        }
        if(strcmp(comando,"RETIRACONTRIBUICAO")==0){
            fscanf(arquivoEntrada,"%s %s %s", vet[0], vet[1], vet[2]);
            pagina=Busca(paginas,vet[0],PAGINA);
            editor=Busca(editores,vet[1],EDITOR);
            
            if(strcmp(vet[1],RecuperaNomeEditor(editor)))
                fprintf(arquivoLog,"ERRO RETIRACONTRIBUICAO: apenas o editor da contribuiçao tem permissao para exclui-la.");
            else           
                Retira(RecuperaContribuicoes(pagina),vet[2], CONTRIBUICAO);
        }
        if(strcmp(comando,"RETIRALINK")==0){
            fscanf(arquivoEntrada,"%s %s", vet[0],vet[1]);
            pagina= Busca(paginas,vet[0],PAGINA);
            pagina2= Busca(paginas,vet[1],PAGINA);

            if(!pagina)
                fprintf(arquivoLog,"ERRO RETIRALINK:a pagina %s nao existe\n\n",vet[0]); 
            else if (!pagina2)
                fprintf(arquivoLog,"ERRO RETIRALINK:a pagina %s nao existe\n\n",vet[1]); 
            else
                Retira(RecuperaLinks(pagina),RecuperaNomePagina(pagina2),LINK);
        }
        if(strcmp(comando,"IMPRIMEPAGINA")==0){
            fscanf(arquivoEntrada,"%s", vet[0]);
            pagina= Busca(paginas,vet[0],PAGINA);

            if(!pagina)
                fprintf(arquivoLog,"ERRO IMPRIMEPAGINA:a pagina %s nao existe\n\n",vet[0]); 
            else{
                //Criando o arquivo da pagina
                char saida[50] = "./saida";

                strcat(saida,RecuperaArquivoPagina(pagina));
                FILE* arquivo= fopen(saida,"w");
                if (!arquivo){
                    perror("Erro ao abrir o arquivo.");
                    exit(1);
                }
                ImprimePaginaCompleta(pagina, arquivo);
                fclose(arquivo);
            }
        }
        if(strcmp(comando,"IMPRIMEWIKED")==0){
            ImprimeWiked(paginas);
        }
        if(strcmp(comando,"CAMINHO")==0){
            fscanf(arquivoEntrada,"%s %s", vet[0],vet[1]);
            pagina= Busca(paginas,vet[0],PAGINA);
            pagina2= Busca(paginas,vet[1],PAGINA);

            if(!pagina)
                fprintf(arquivoLog,"ERRO CAMINHO:a pagina %s nao existe\n\n",vet[0]); 
            else if (!pagina2)  
                fprintf(arquivoLog,"ERRO CAMINHO:a pagina %s nao existe\n\n",vet[1]);
            else{              
                if(Caminho(pagina,pagina2))
                    fprintf(arquivoLog,"HA CAMINHO DA PAGINA %s PARA %s\n\n", vet[0],vet[1]);
                else
                    fprintf(arquivoLog,"NAO HA CAMINHO DA PAGINA %s PARA %s\n\n",vet[0],vet[1]);
            }
        }
        
        fscanf(arquivoEntrada,"%*c");
    } while (strcmp(comando,"FIM")!=0);

    DestroiLista(paginas,PAGINA);
    DestroiLista(editores,EDITOR);

    DestroiLista(contribuicoes,CONTRIBUICAO);


    fclose(arquivoEntrada);
    fclose(arquivoLog);

    return 0;
}
