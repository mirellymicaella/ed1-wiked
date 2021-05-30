#include "Editor.h"

//Tipo listaHet e celula (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementação do TAD
typedef struct contribuicao Contribuicao;

/*Cria uma nova contribuicao
 * inputs: um editor e nome do arquivo de texto
 * output: ponteiro para a contribuicao criada
 * pre-condicao: editor existe
 * pos-condicao: nenhuma
 */
Contribuicao* CriaContribuicao (Editor* editor,char* arquivoTexto);

/*Imprime uma contribuicao completa com cabecalho e texto
 * inputs: a contribuicao e o arquivo onde sera impresso
 * output: nenhum
 * pre-condicao: contribuicao existe e arquivo existem
 * pos-condicao: contribuicao eh imripressa no arquivo
 */
void ImprimeContribuicaoCompleta(Contribuicao* cont, FILE* arquivo);

/*Imprime uma contribuicao simples como nome do editor e nome do aqruivo
 * inputs: a contribuicao, o arquivo onde sera impresso  
 * output: nenhum
 * pre-condicao: contribuicao e arquivo existem
 * pos-condicao: contribuicao eh imripressa no arquivo
 */
void ImprimeContribuicaoSimples(Contribuicao* cont, FILE* arquivo, int retirada);

/*Retorna o editor dono de uma contribuicao
 * inputs: a contribuicao 
 * output: ponteiro para o editor 
 * pre-condicao: contribuicao existe
 * pos-condicao: nenhuma
 */
Editor* RecuperaEditorContribuicao(Contribuicao* cont);

/*Retorna o nome do arquivo de uma contribuicao
 * inputs: a contribuicao 
 * output: string com o nome do arquivo
 * pre-condicao: contribuicao existe
 * pos-condicao: nenhuma
 */
char* RecuperaArquivoTextoContribuicao(Contribuicao* cont);

/*Destroi uma contribuicao
 * inputs: a contribuicao 
 * output: nenhum
 * pre-condicao: contribuicao existe
 * pos-condicao: contribuicao eh destruida
 */
void DestroiContribuicao(Contribuicao* cont);