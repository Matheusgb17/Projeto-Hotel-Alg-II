#ifndef VENDAS_H
#define VENDAS_H

typedef struct tipoHospede TipoHospede;
typedef struct listaHospede ListaHospede;
typedef struct listaProduto ListaProduto;
typedef struct listaHistoricoCaixa ListaHistoricoCaixa;
typedef struct listaContas ListaContas;

#include <time.h>

// Estrutura auxiliar para guardar os itens comprados na venda
typedef struct itemVenda {
    int idProduto;
    int quantidade;
    float valorUnitario;
} ItemVenda;

// Estrutura principal que guarda os dados de uma venda
typedef struct tipoVenda {
    int id;
    int idHospede;          // 0 se for venda no balcão/cliente não cadastrado
    int formaPagamento;     // 1 - A vista, 2 - Anotado/Fiado
    int statusPagamento;    // 1 - Pago, 0 - Pendente
    int qtdItens;
    float valorTotal;
    time_t dataVenda;
    ItemVenda itens[50];    // Suporta até 50 produtos diferentes por venda
} TipoVenda;

// Estrutura do nó da lista encadeada de vendas
typedef struct listaVendas {
    TipoVenda venda;
    struct listaVendas *prox;
} ListaVendas;

/**
 * Função para inicializar a lista de vendas
 * @return Ponteiro para a lista de vendas alocada e inicializada
 */
ListaVendas *iniciaListaVendas();

/**
 * Função para escolher o próximo ID disponível para uma nova venda
 * @param lista Ponteiro para a lista de vendas
 * @return Próximo ID disponível (inteiro)
 */
int escolheIdVenda(ListaVendas *lista);

/**
 * Função para inserir uma nova venda na lista
 * @param lista Ponteiro para a lista de vendas
 * @param venda Estrutura do tipo TipoVenda contendo os dados da transação
 * @return 0 se a inserção for bem-sucedida, 1 caso contrário
 */
int inserirVenda(ListaVendas **lista, TipoVenda venda);

/**
 * Função para gerar um recibo de consumo em arquivo .txt para o hóspede
 * @param venda Estrutura do tipo TipoVenda com os dados do consumo
 * @param hospede Estrutura do tipo TipoHospede com os dados do cliente
 * @param listaProdutos Ponteiro para a lista de produtos (para buscar as descrições)
 * @return void
 */
void gerarReciboVenda(TipoVenda venda, TipoHospede hospede, ListaProduto *listaProdutos);

/**
 * Função para salvar os dados das vendas em um arquivo binário
 * @param lista Ponteiro para a lista de vendas a ser salva
 * @param nome_arquivo Nome do arquivo onde os dados serão salvos
 * @return 0 se a operação for bem-sucedida, 1 caso contrário
 */
int salvarDadosVendasBin(ListaVendas *lista, char *nome_arquivo);

/**
 * Função para resgatar os dados das vendas de um arquivo binário
 * @param nome_arquivo Nome do arquivo de onde os dados serão resgatados
 * @return Ponteiro para a lista de vendas resgatada
 */
ListaVendas *resgataDadosVendasBin(char *nome_arquivo);

/**
 * Função para salvar os dados das vendas em um arquivo de texto
 * @param lista Ponteiro para a lista de vendas a ser salva
 * @param nome_arquivo Nome do arquivo onde os dados serão salvos
 * @return 0 se a operação for bem-sucedida, 1 caso contrário
 */
int salvarDadosVendasTxt(ListaVendas *lista, char *nome_arquivo);

/**
 * Função para resgatar os dados das vendas de um arquivo de texto
 * @param nome_arquivo Nome do arquivo de onde os dados serão resgatados
 * @return Ponteiro para a lista de vendas resgatada
 */
ListaVendas *resgataDadosVendasTxt(char *nome_arquivo);

/**
 * Função para liberar toda a memória alocada para a lista de vendas, percorrendo e desalocando cada nó
 * @param lista Ponteiro para a lista de vendas a ser liberada
 * @return void
 */
void liberaListaVendas(ListaVendas *lista);

/**
 * Função que exibe e gerencia o menu de iteração com o usuário para o módulo de Vendas (PDV)
 * @param listaVendas Ponteiro para a lista de vendas
 * @param listaProdutos Ponteiro para a lista de estoque/produtos
 * @param listaHospedes Ponteiro para a lista de clientes cadastrados
 * @param historicoCaixa Ponteiro para a lista de movimentações do caixa
 * @param listaContasReceber Ponteiro para a lista de contas a receber do hotel
 * @return void
 */
void interfaceVendas(ListaVendas *listaVendas, ListaProduto *listaProdutos, ListaHospede *listaHospedes, ListaHistoricoCaixa *historicoCaixa, ListaContas *listaContasReceber);

#endif // VENDAS_H


