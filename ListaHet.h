#ifndef _LISTAHET_H
#define _LISTAHET_H

#include "Contribuicao.h"
#include "Editor.h"

//Constantes para tipo de item
#define PAGINA 1
#define CONTRIBUICAO 2
#define EDITOR 3
#define LINK 4

//Tipo listaHet e celula (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementação do TAD
typedef struct listaHet ListaHet;
typedef struct celula Celula;

/*Inicializa uma lista vazia
 * inputs: nenhum
 * output: ponteiro para a lista inicializada
 * pre-condicao: nenhuma
 * pos-condicao: lista de retorno existe
 */
ListaHet* IniciaLista();

/*Imprime as paginas da wiked
 * inputs: lista de paginas da wiked
 * output: nenhum
 * pre-condicao: lista existe
 * pos-condicao: os arquivos das paginas são criados e preenchidos
 */
void ImprimeWiked(ListaHet* lista);

/*Imprime as contribuicoes simples na pagina
 * inputs: lista de paginas da wiked, arquivo onde as constribuicoes serao impressas
 * output: nenhum
 * pre-condicao: lista de contribuicoes,lista de historico e arquivo existem
 * pos-condicao: as contribuicoes simples são impressas no arquivo 
 */
void ImprimeContribuicoesSimples(ListaHet* historicoConts, ListaHet* conts, FILE* arquivo);

/*Imprime as contribuicoes completas na pagina
 * inputs: lista de paginas da wiked, arquivo onde as constribuicoes serao impressas 
 * output: nenhum
 * pre-condicao: lista de contribuicoes e arquivo existem
 * pos-condicao: as contribuicoes simples são impressas no arquivo
 */
void ImprimeContribuicoesCompletas(ListaHet* lista, FILE* arquivo);

/*Imprime as paginas simples 
 * inputs: lista de paginas, arquivo onde as paginas serao impressas
 * output: nenhum
 * pre-condicao: lista de paginas e arquivo existem
 * pos-condicao: as paginas sao impressas no arquivo 
 */
void ImprimePaginasSimples(ListaHet* lista, FILE* arquivo);

/*Insere um item na lista
 * inputs: lista , item, tipo do item
 * output: 0 se o item ja existe na lista, 1 se o item foi inserido com sucesso
 * pre-condicao: lista e item existem, tipo eh valido
 * pos-condicao: o item eh inserido na lista
 */
int InsereLista(ListaHet* lista, void* item, int tipo);

/*Verifica se um item esta contido na lista
 * inputs: lista , item, tipo do item
 * output: 1 se o item esta contido na lista, 0 se o item nao esta contido
 * pre-condicao: lista e item existem, tipo eh valido
 * pos-condicao: nenhuma
 */
int ContemItem(ListaHet* lista, void* item, int tipo);

/*Busca um item pelo nome na lista
 * inputs: lista , item, tipo do item
 * output: ponteiro para o item correspondente ou NULL se o item nao existe na lista
 * pre-condicao: lista existe, tipo eh valido
 * pos-condicao: nenhuma
 */
void* Busca(ListaHet* lista,char* nome , int tipo);  

/*Retira um item da lista
 * inputs: lista , chave de busca, tipo do item
 * output: ponteiro para o item correspondente ou NULL se o item nao existe na lista
 * pre-condicao: lista existe, tipo eh valido
 * pos-condicao: o item eh retirado da lista
 */
void* Retira(ListaHet* lista,char* chave,int tipo);

/*Verifica se ha caminho de uma pagina para outra
 * inputs: pagina origem, pagina destino
 * output: 1 se ha caminho, 0 se nao ha
 * pre-condicao: paginas existem
 * pos-condicao: nenhuma
 */
int Caminho(void* pagOrigem, void* pagDestino);

/*Verifica todas as paginas bsucando caminho
 * inputs: pagina a ser verificada, lista mapa de paginas
 * output: nenhum
 * pre-condicao: pagina, mapa e lista de paginas existem
 * pos-condicao: o mapa sera preenchido com todas as paginas verificadas
 */
void VerificaCaminhos(void* pagina, ListaHet* mapa);

/*Libera as celulas da lista
 * inputs: lista
 * output: nenhum
 * pre-condicao: lista existe
 * pos-condicao: lista e suas celulas sao liberadas
 */
void LiberaLista(ListaHet* lista);

/*Destroi a lista e seus itens
 * inputs: lista, tipo 
 * output: nenhum
 * pre-condicao: lista existe, tipo eh valido
 * pos-condicao: lista e seus itens sao liberados 
 */
void DestroiLista(ListaHet* lista, int tipo);

#endif