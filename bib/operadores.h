#ifndef OPERADORES_H
#define OPERADORES_H

typedef struct tipoOperador {
    int id;
    char nome[100];
    char user[20];
    char senha[11];
    int permission;
} TipoOperador;

typedef struct listaOperadores{
    TipoOperador operador;
    struct listaOperadores *prox;
} ListaOperadores;

/**
 * Percorre a lista por completo para descobrir a quantidade de posi��es e definir o pr�ximo ID.
 * @param lista Ponteiro para a lista que ser� percorrida.
 * @return int Retorna a quantidade de indiv�duos inseridos mais 1 (novo ID).
 */
int escolheIdOperador(ListaOperadores *lista);

/**
 * Aloca memria e inicializa o n sentinela (cabecalho) da lista de operadores.
 * @return ListaOperadores* Ponteiro para a lista inicializada com ID 0 e prximo nulo.
 */
ListaOperadores *iniciaListaOperadores();

/**
 * Insere um novo operador no final da lista encadeada.
 * @param lista Ponteiro para o ponteiro da lista (para permitir altera��o direta).
 * @param operador Estrutura contendo os dados do operador a ser inserido.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha na aloca��o.
 */
int inserirOperador(ListaOperadores **lista, TipoOperador operador);

/**
 * Localiza um operador na lista atrav�s do n�mero de ID.
 * @param lista Ponteiro para o ponteiro da lista de busca.
 * @param operador Ponteiro para armazenar os dados do operador encontrado.
 * @param user Vetor contendo o Usu�rio a ser buscado na lista.
 * @param pos Ponteiro para armazenar o endere�o do n� encontrado na lista.
 * @return int Retorna 0 se encontrado ou 1 caso a lista esteja vazia ou o ID n�o exista.
 */
int buscarOperador(ListaOperadores **lista, TipoOperador *operador, char *user, ListaOperadores **pos);

/**
 * Sobrescreve os dados de um operador em uma posi��o espec�fica da lista.
 * @param pos Ponteiro para o n� da lista que ser� alterado.
 * @param operador Estrutura com os novos dados a serem gravados.
 * @return void
 */
void alterarOperador(ListaOperadores *pos, TipoOperador operador);

/**
 * Realiza a exclus�o l�gica de um operador definindo seu ID como 0.
 * @param pos Ponteiro para o n� da lista que ter� o operador "apagado".
 * @return void
 */
void apagarOperador(ListaOperadores *pos);

/**
 * Percorre a lista e exibe no console os dados de todos os operadores cadastrados.
 * @param lista Ponteiro para a lista de operadores.
 * @return void
 */
void listarOperadores(ListaOperadores *lista);

/**
 * Fun��o para salvar os dados dos operadores em um arquivo bin�rio.
 * @param lista Ponteiro para a lista de operadores a ser salva.
 * @param nome_arquivo String contendo o nome do arquivo bin�rio onde os dados ser�o salvos.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha ao acessar o arquivo.
 */
int salvarDadosOperadoresBin(ListaOperadores *lista, char *nome_arquivo);

/**
 * Fun��o para resgatar os dados dos operadores a partir de um arquivo bin�rio.
 * @param nome_arquivo String contendo o nome do arquivo bin�rio a ser lido.
 * @return ListaOperadores* Ponteiro para a lista preenchida com os dados resgatados.
 */
ListaOperadores *resgataDadosOperadoresBin(char *nome_arquivo);

/**
 * Fun��o para salvar os dados dos operadores em um arquivo texto.
 * @param lista Ponteiro para a lista de operadores a ser salva.
 * @param nome_arquivo String contendo o nome do arquivo de texto onde os dados ser�o salvos.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha ao acessar o arquivo.
 */
int salvarDadosOperadoresTxt(ListaOperadores *lista, char *nome_arquivo);

/**
 * Fun��o para resgatar os dados dos operadores a partir de um arquivo de texto.
 * @param nome_arquivo String contendo o nome do arquivo de texto a ser lido.
 * @return ListaOperadores* Ponteiro para a lista preenchida com os dados resgatados.
 */
void liberaListaOperadores(ListaOperadores *lista);

/**
 * Fun��o para resgatar os dados dos operadores a partir de um arquivo de texto.
 * @param nome_arquivo String contendo o nome do arquivo de texto a ser lido.
 * @return ListaOperadores* Ponteiro para a lista preenchida com os dados resgatados.
 */
ListaOperadores *resgataDadosOperadoresTxt(char *nome_arquivo);

/**
 * Exibe os dados de um operador no console.
 * @param operador Estrutura contendo os dados do operador a ser exibido.
 * @return void
 */
void imprimeDadosOperador(TipoOperador operador);

/**
 * Fun��o que exibe e gerencia o menu de itera��o com o usu�rio para o m�dulo de Operadores
 * @param listaOperadores Ponteiro para a lista de operadores a ser manipulada.
 * @return void
 */
void interfaceOperadores(ListaOperadores *listaOperadores);

#endif // OPERADORES_H