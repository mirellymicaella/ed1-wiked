//Tipo editor (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementação do TAD
typedef struct editor Editor;

/*Cria um novo editor
 * inputs: nome do editor
 * output: ponteiro para o editor criado
 * pre-condicao: nenhuma
 * pos-condicao: nenhuma
 */
Editor* CriaEditor(char* nome);

/*Retorna o nome do editor
 * inputs: o editor
 * output: nome do editor
 * pre-condicao: editor existe
 * pos-condicao: nenhuma
 */
char* RecuperaNomeEditor (Editor* editor);

/*Destroi um editor
 * inputs: o editor 
 * output: nenhum
 * pre-condicao: editor existe
 * pos-condicao: editor eh destruido
 */
void DestroiEditor(Editor* editor);