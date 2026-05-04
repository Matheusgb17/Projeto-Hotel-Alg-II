#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct {
    int id;
    char descricao[100];
    int estoque;
    int estoque_minimo;
    float preco_custo;
    float preco_venda;
} TipoProduto;

typedef struct listaProduto
{
    TipoProduto Produto;
    struct listaProduto *prox;
} ListaProduto;

/**
 * Calcula e retorna o proximo ID disponivel para cadastro de um novo produto.
 * @param lista Ponteiro para a lista encadeada de produtos.
 * @return int O proximo ID livre gerado sequencialmente.
 */
int escolheIdProduto(ListaProduto *lista);

/**
 * Percorre a lista e imprime na tela todos os produtos cadastrados.
 * @param lista Ponteiro para a lista encadeada de produtos.
 * @return void
 */
void listarProdutos(ListaProduto *lista);

/**
 * Aloca na memoria e inicializa o no cabeca de uma nova lista de produtos.
 * @return ListaProduto* Ponteiro para a lista inicializada.
 */
ListaProduto *iniciaListaProduto();

/**
 * Insere um novo produto no final da lista encadeada.
 * @param lista Ponteiro duplo para a lista encadeada de produtos.
 * @param Produto Estrutura contendo os dados do produto a ser inserido.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha na alocacao.
 */
int inserirProduto(ListaProduto **lista, TipoProduto Produto);

/**
 * Busca um produto especifico na lista a partir do seu ID.
 * @param lista Ponteiro duplo para a lista encadeada de produtos.
 * @param produto Ponteiro onde os dados do produto encontrado serao copiados.
 * @param id Inteiro com o ID do produto a ser buscado.
 * @param pos Ponteiro duplo que armazenara a posicao do no encontrado na lista.
 * @return int Retorna 0 se o produto for encontrado, ou 1 se nao for.
 */
int buscarProduto(ListaProduto **lista, TipoProduto *produto, int id, ListaProduto **pos);

/**
 * Substitui os dados de um produto existente em uma posicao especifica da lista.
 * @param pos Ponteiro para o no da lista que sera alterado.
 * @param Produto Estrutura contendo os novos dados do produto.
 * @return void
 */
void alterarProduto(ListaProduto *pos, TipoProduto Produto);

/**
 * Realiza a exclusao logica de um produto, zerando o seu ID.
 * @param pos Ponteiro para o no da lista que sera "apagado".
 * @return void
 */
void apagarProduto(ListaProduto *pos);

/**
 * Imprime na tela os dados detalhados de todos os produtos ativos na lista.
 * @param lista Ponteiro para a lista encadeada de produtos.
 * @return void
 */
void listarProduto(ListaProduto *lista);

/**
 * Salva a lista encadeada de produtos em um arquivo binario.
 * @param lista Ponteiro para a lista encadeada de produtos.
 * @param nome_arquivo String contendo o nome/caminho do arquivo binario.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha ao abrir o arquivo.
 */
int salvarDadosProdutosBin(ListaProduto *lista, char *nome_arquivo);

/**
 * Resgata os dados dos produtos salvos em um arquivo binario e os insere em uma nova lista.
 * @param nome_arquivo String contendo o nome/caminho do arquivo binario.
 * @return ListaProduto* Ponteiro para a nova lista preenchida com os dados.
 */
ListaProduto *resgataDadosProdutosBin(char *nome_arquivo);

/**
 * Salva a lista encadeada de produtos em um arquivo de texto (formato XML-like).
 * @param lista Ponteiro para a lista encadeada de produtos.
 * @param nome_arquivo String contendo o nome/caminho do arquivo de texto.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha ao abrir o arquivo.
 */
int salvarDadosProdutosTxt(ListaProduto *lista, char *nome_arquivo);

/**
 * Resgata os dados dos produtos salvos em um arquivo de texto e os insere em uma nova lista.
 * @param nome_arquivo String contendo o nome/caminho do arquivo de texto.
 * @return ListaProduto* Ponteiro para a nova lista preenchida com os dados.
 */
ListaProduto *resgataDadosProdutosTxt(char *nome_arquivo);

/**
 * Interface interativa via terminal para gestao de produtos (CRUD).
 * @param listaProduto Ponteiro para a lista de produtos carregada na memoria.
 * @param modo Inteiro representando o modo de armazenamento atual do sistema.
 * @return void
 */
void interfaceProduto(ListaProduto *listaProduto, int modo);

#endif