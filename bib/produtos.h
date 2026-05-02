#ifndef PRODUTOS_H
#define PRODUTOS_H

// ➢ Código (único)
// ➢ Descrição
// ➢ Estoque
// ➢ Estoque mínimo
// ➢ Preço de Custo
// ➢ Preço de Venda

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

int escolheIdProduto(ListaProduto *lista);

void listarProdutos(ListaProduto *lista);

ListaProduto *iniciaListaProduto();

int inserirProduto(ListaProduto **lista, TipoProduto Produto);

int buscarProduto(ListaProduto **lista, TipoProduto *Produto, int id, ListaProduto **pos);

void alterarProduto(ListaProduto *pos, TipoProduto Produto);

void apagarProduto(ListaProduto *pos);

void listarProduto(ListaProduto *lista);

ListaProduto *resgataDadosProdutosBin(char *nome_arquivo);

ListaProduto *resgataDadosProdutosTxt(char *nome_arquivo);

int salvaDadosProdutosBin(ListaProduto *lista, char *nome_arquivo);

int salvarProdutosTxt(ListaProduto *lista, char *nome_arquivo);

void interfaceProduto();

#endif