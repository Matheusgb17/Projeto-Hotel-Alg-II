#ifndef FORNECEDORES_H
#define FORNECEDORES_H

typedef struct {
    int id;
    char nome_fantasia[100];
    char razao_social[100];
    char inscricao_estadual[100];
    char cnpj[12];
    char endereco_completo[200];
    char telefone[12];
    char email[100];
} TipoFornecedor;

typedef struct listaFornecedor
{
    TipoFornecedor Fornecedor;
    struct listaFornecedor *prox;
} ListaFornecedor;

/**
 * Calcula e retorna o proximo ID disponivel para cadastro de um novo fornecedor.
 * @param lista Ponteiro para a lista encadeada de fornecedores.
 * @return int O proximo ID livre gerado sequencialmente.
 */
int escolheIdFornecedor(ListaFornecedor *lista);

/**
 * Percorre a lista e imprime na tela o ID e o Nome Fantasia dos fornecedores.
 * @param lista Ponteiro para a lista encadeada de fornecedores.
 * @return int Retorna 0 apos listar os itens.
 */
int listarFornecedores(ListaFornecedor *lista);

/**
 * Aloca na memoria e inicializa o no cabeca de uma nova lista de fornecedores.
 * @return ListaFornecedor* Ponteiro para a lista inicializada.
 */
ListaFornecedor *iniciaListaFornecedor();

/**
 * Insere um novo fornecedor no final da lista encadeada.
 * @param lista Ponteiro duplo para a lista encadeada de fornecedores.
 * @param Fornecedor Estrutura contendo os dados do fornecedor a ser inserido.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha na alocacao.
 */
int inserirFornecedor(ListaFornecedor **lista, TipoFornecedor Fornecedor);

/**
 * Busca um fornecedor especifico na lista a partir do seu CNPJ.
 * @param lista Ponteiro duplo para a lista encadeada de fornecedores.
 * @param Fornecedor Ponteiro onde os dados do fornecedor encontrado serao copiados.
 * @param CNPJ String contendo o CNPJ do fornecedor a ser buscado.
 * @param pos Ponteiro duplo que armazenara a posicao do no encontrado na lista.
 * @return int Retorna 0 se o fornecedor for encontrado, ou 1 se nao for.
 */
int buscarFornecedor(ListaFornecedor **lista, TipoFornecedor *Fornecedor, char *CNPJ, ListaFornecedor **pos);

/**
 * Substitui os dados de um fornecedor existente em uma posicao especifica da lista.
 * @param pos Ponteiro para o no da lista que sera alterado.
 * @param Fornecedor Estrutura contendo os novos dados do fornecedor.
 * @return void
 */
void alterarFornecedor(ListaFornecedor *pos, TipoFornecedor Fornecedor);

/**
 * Realiza a exclusao logica de um fornecedor, zerando o seu ID.
 * @param pos Ponteiro para o no da lista que sera "apagado".
 * @return void
 */
void apagarFornecedor(ListaFornecedor *pos);

/**
 * Imprime na tela os dados detalhados de todos os fornecedores ativos na lista.
 * @param lista Ponteiro para a lista encadeada de fornecedores.
 * @return void
 */
void listarFornecedor(ListaFornecedor *lista);

/**
 * Salva a lista encadeada de fornecedores em um arquivo binario.
 * @param lista Ponteiro para a lista encadeada de fornecedores.
 * @param nome_arquivo String contendo o nome/caminho do arquivo binario.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha ao abrir o arquivo.
 */
int salvarDadosFornecedoresBin(ListaFornecedor *lista, char *nome_arquivo);

/**
 * Resgata os dados dos fornecedores salvos em um arquivo binario e os insere em uma nova lista.
 * @param nome_arquivo String contendo o nome/caminho do arquivo binario.
 * @return ListaFornecedor* Ponteiro para a nova lista preenchida com os dados.
 */
ListaFornecedor *resgataDadosFornecedoresBin(char *nome_arquivo);

/**
 * Salva a lista encadeada de fornecedores em um arquivo de texto (formato XML-like).
 * @param lista Ponteiro para a lista encadeada de fornecedores.
 * @param nome_arquivo String contendo o nome/caminho do arquivo de texto.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha ao abrir o arquivo.
 */
int salvarDadosFornecedoresTxt(ListaFornecedor *lista, char *nome_arquivo);

/**
 * Resgata os dados dos fornecedores salvos em um arquivo de texto e os insere em uma nova lista.
 * @param nome_arquivo String contendo o nome/caminho do arquivo de texto.
 * @return ListaFornecedor* Ponteiro para a nova lista preenchida com os dados.
 */
ListaFornecedor *resgataDadosFornecedoresTxt(char *nome_arquivo);

/**
 * Libera a memoria alocada para a lista de fornecedores.
 * @param lista Ponteiro para a lista de fornecedores.
 * @return void
 */
void liberaListaFornecedores(ListaFornecedor *lista);

/**
 * Interface interativa via terminal para gestao de fornecedores (CRUD).
 * @param listaFornecedores Ponteiro para a lista de fornecedores carregada na memoria.
 * @param modo Inteiro representando o modo de armazenamento atual do sistema.
 * @return void
 */
void interfaceFornecedor(ListaFornecedor *listaFornecedores);

#endif