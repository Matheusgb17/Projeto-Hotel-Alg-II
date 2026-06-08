#ifndef COMPRAS_H
#define COMPRAS_H

#include <time.h>

typedef struct listaContas ListaContas;
typedef struct listaProduto ListaProduto;
typedef struct listaFornecedor ListaFornecedor;
typedef struct tipoHotel TipoHotel;
typedef struct listaHistoricoCaixa ListaHistoricoCaixa;

typedef struct itemCompra {
    int idProduto;
    int quantidade;
    float precoCusto;
} ItemCompra;

typedef struct tipoNotaFiscal {
    int id;
    char cnpjFornecedor[20];
    float freteTotal;
    float impostoTotal;
    int quantidadeTotalUnidades;
    float valorTotalNota;
    int qtdItensDiferentes;
    time_t dataEmissao;
    ItemCompra itens[50]; // Suporta até 50 produtos diferentes por nota
} TipoNotaFiscal;

// Estrutura do nó da lista encadeada de notas fiscais
typedef struct listaNotasFiscais {
    TipoNotaFiscal nota;
    struct listaNotasFiscais *prox;
} ListaNotasFiscais;

/**
 * Função para inicializar a lista de notas fiscais
 * @return Ponteiro para a lista de notas fiscais alocada e inicializada
 */
ListaNotasFiscais *iniciaListaNotasFiscais();

/**
 * Função para escolher o próximo ID disponível para uma nova nota fiscal
 * @param lista Ponteiro para a lista de notas fiscais
 * @return Próximo ID disponível (inteiro)
 */
int escolheIdNota(ListaNotasFiscais *lista);

/**
 * Função para inserir uma nova nota fiscal na lista
 * @param lista Ponteiro para a lista de notas fiscais
 * @param nota Estrutura do tipo TipoNotaFiscal contendo os dados da nova nota
 * @return 0 se a inserção for bem-sucedida, 1 caso contrário
 */
int inserirNotaFiscal(ListaNotasFiscais **lista, TipoNotaFiscal nota);

/**
 * Função para salvar os dados das notas fiscais em um arquivo binário
 * @param lista Ponteiro para a lista de notas fiscais a ser salva
 * @param nome_arquivo Nome do arquivo onde os dados serão salvos
 * @return 0 se a operação for bem-sucedida, 1 caso contrário
 */
int salvarDadosNotasBin(ListaNotasFiscais *lista, char *nome_arquivo);

/**
 * Função para resgatar os dados das notas fiscais de um arquivo binário
 * @param nome_arquivo Nome do arquivo de onde os dados serão resgatados
 * @return Ponteiro para a lista de notas fiscais resgatada
 */
ListaNotasFiscais *resgataDadosNotasBin(char *nome_arquivo);

/**
 * Função para salvar os dados das notas fiscais em um arquivo de texto
 * @param lista Ponteiro para a lista de notas fiscais a ser salva
 * @param nome_arquivo Nome do arquivo onde os dados serão salvos
 * @return 0 se a operação for bem-sucedida, 1 caso contrário
 */
int salvarDadosNotasTxt(ListaNotasFiscais *lista, char *nome_arquivo);

/**
 * Função para resgatar os dados das notas fiscais de um arquivo de texto
 * @param nome_arquivo Nome do arquivo de onde os dados serão resgatados
 * @return Ponteiro para a lista de notas fiscais resgatada
 */
ListaNotasFiscais *resgataDadosNotasTxt(char *nome_arquivo);

/**
 * Função para liberar toda a memória alocada para a lista de notas fiscais, percorrendo e desalocando cada nó
 * @param lista Ponteiro para a lista de notas fiscais a ser liberada
 * @return void
 */
void liberaListaNotasFiscais(ListaNotasFiscais *lista);

/**
 * Função que exibe e gerencia o menu de iteração com o usuário para o módulo de Compras
 * @param listaNotas Ponteiro para a lista de notas fiscais
 * @param listaContas Ponteiro para a lista unificada de contas a pagar
 * @param listaProdutos Ponteiro para a lista de produtos (estoque)
 * @param listaFornecedores Ponteiro para a lista de fornecedores
 * @param dadosHotel Ponteiro para a estrutura com as configurações e dados gerais do hotel
 * @param historicoCaixa Ponteiro para o fluxo financeiro do caixa
 * @return void
 */
void interfaceCompras(ListaNotasFiscais *listaNotas, ListaContas *listaContas, ListaProduto *listaProdutos, ListaFornecedor *listaFornecedores, TipoHotel *dadosHotel, ListaHistoricoCaixa *historicoCaixa);

#endif // COMPRAS_H
