#ifndef COMPRAS_H
#define COMPRAS_H

#include "produtos.h"
#include "fornecedores.h"
#include "hotel.h"

//struct de nota fiscal
typedef struct {
    int idProduto;
    int quantidade;
    float precoCusto;
} ItemNota;

typedef struct {
    int id;
    char cnpjFornecedor[15];
    float freteTotal;
    float impostoTotal;
    int quantidadeTotalUnidades; 
    float valorTotalNota;        
    ItemNota itens[50];          
    int qtdItensDiferentes;
    time_t dataEmissao;
} TipoNotaFiscal;

typedef struct listaNotasFiscais {
    TipoNotaFiscal nota;
    struct listaNotasFiscais *prox;
} ListaNotasFiscais;

//struct de contas a pagar
typedef struct {
    int id;
    int idNota;
    float valorParcela;
    int numeroParcela;
    char dataVencimento[11];
    int statusPago;
} TipoContaPagar;

typedef struct listaContasPagar {
    TipoContaPagar conta;
    struct listaContasPagar *prox;
} ListaContasPagar;

//nota fiscal
ListaNotasFiscais *iniciaListaNotasFiscais();

int escolheIdNota(ListaNotasFiscais *lista);

int inserirNotaFiscal(ListaNotasFiscais **lista, TipoNotaFiscal nota);

int salvarDadosNotasBin(ListaNotasFiscais *lista, char *nome_arquivo);

ListaNotasFiscais *resgataDadosNotasBin(char *nome_arquivo);

int salvarDadosNotasTxt(ListaNotasFiscais *lista, char *nome_arquivo);

ListaNotasFiscais *resgataDadosNotasTxt(char *nome_arquivo);

//contas a pagar
ListaContasPagar *iniciaListaContasPagar();

int escolheIdContaPagar(ListaContasPagar *lista);

int inserirContaPagar(ListaContasPagar **lista, TipoContaPagar conta);

int salvarDadosContasPagarBin(ListaContasPagar *lista, char *nome_arquivo);

ListaContasPagar *resgataDadosContasPagarBin(char *nome_arquivo);

int salvarDadosContasPagarTxt(ListaContasPagar *lista, char *nome_arquivo);

ListaContasPagar *resgataDadosContasPagarTxt(char *nome_arquivo);

//interface
void interfaceCompras(ListaNotasFiscais *listaNotas, ListaContasPagar *listaContas, ListaProduto *listaProdutos, ListaFornecedor *listaFornecedores, TipoHotel *dadosHotel);

#endif