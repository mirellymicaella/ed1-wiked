#ifndef _PAGINA_H
#define _PAGINA_H

#include "ListaHet.h"
#include "Contribuicao.h"

//Tipo listaHet e celula (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementação do TAD
typedef struct pagina Pagina;

/*Cria uma nova pagina
 * inputs: nome da pagina, nome do arquivo da pagina
 * output: ponteiro para a pagina criada
 * pre-condicao: nenhuma
 * pos-condicao: nenhuma
 */
Pagina* CriaPagina(char* nome, char* arquivo);

/*Retorna o nome de uma pagina
 * inputs: a pagina
 * output: string com o nome da pagina
 * pre-condicao: pagina existe
 * pos-condicao: nenhuma
 */
char* RecuperaNomePagina(Pagina* pag);

/*Retorna o nome do arquivo de uma pagina
 * inputs: a pagina
 * output: string com o nome do arquivo da pagina
 * pre-condicao: pagina existe
 * pos-condicao: nenhuma
 */
char* RecuperaArquivoPagina(Pagina* pag);

/*Retorna a lista de contribuicoes de uma pagina
 * inputs: a pagina
 * output: ponteiro para a lista de contribuicoes da pagina
 * pre-condicao: pagina existe
 * pos-condicao: nenhuma
 */
ListaHet* RecuperaContribuicoes(Pagina* pag);

/*Retorna a lista de links de uma pagina
 * inputs: a pagina
 * output: ponteiro para a lista de links da pagina
 * pre-condicao: pagina existe
 * pos-condicao: nenhuma
 */
ListaHet* RecuperaLinks(Pagina* pag);

/*Retorna a lista de historico contribuicoes de uma pagina
 * inputs: a pagina
 * output: ponteiro para a lista de historico contribuicoes da pagina
 * pre-condicao: pagina existe
 * pos-condicao: nenhuma
 */
ListaHet* RecuperaHistoricoContribuicoes(Pagina* pag);

/*Imprime uma pagina completa
 * inputs: a pagina, o arquivo onde sera impressa
 * output: nenhum
 * pre-condicao: pagina e arquivo existem
 * pos-condicao: a pagina eh impressa no arquivo
 */
void ImprimePaginaCompleta(Pagina* pag, FILE* arquivo);

/*Imprime uma pagina simples (com nome da pagina e nome do arquivo)
 * inputs: a pagina, o arquivo onde sera impressa
 * output: nenhum
 * pre-condicao: pagina e arquivo existem
 * pos-condicao: a pagina eh impressa no arquivo
 */
void ImprimePaginaSimples(Pagina* pag, FILE* arquivo);

/*Adiciona uma contribuicao na lista de contribuicoes e 
    na lista de historico de contribuicoes de uma pagina
 * inputs: a pagina, a contribuicao
 * output: 0 se a contribuicao ja existe na pagina, 1 se foi inserida com sucesso
 * pre-condicao: pagina e contribuicao existem
 * pos-condicao: a contribuicao eh adicionada na pagina
 */
int AdicionaContribuicaoPagina(Pagina* pag, Contribuicao* cont);

/*Destroi uma pagina
 * inputs: a pagina 
 * output: nenhum
 * pre-condicao: pagina existe
 * pos-condicao: pagina eh destruida
 */
void DestroiPagina(Pagina* pag);

#endif