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

int escolheIdFornecedor(ListaFornecedor *lista);

int listarFornecedores(ListaFornecedor *lista);

ListaFornecedor *iniciaListaFornecedor();

int inserirFornecedor(ListaFornecedor **lista, TipoFornecedor Fornecedor);

int buscarFornecedor(ListaFornecedor **lista, TipoFornecedor *Fornecedor, char *CNPJ, ListaFornecedor **pos);

void alterarFornecedor(ListaFornecedor *pos, TipoFornecedor Fornecedor);

void apagarFornecedor(ListaFornecedor *pos);

void listarFornecedor(ListaFornecedor *lista);

void interfaceFornecedor(ListaFornecedor *listaFornecedores, int modo);

#endif
