#ifndef VENDAS_H
#define VENDAS_H

#include "produtos.h"
#include "hospedes.h"
#include "hotel.h"

typedef struct {
    int idProduto;
    int quantidade;
    float valorUnitario;
} ItemVenda;

typedef struct {
    int id;
    int idHospede;
    int formaPagamento;
    int statusPagamento;
    ItemVenda itens[50];
    int qtdItens;
    float valorTotal;
    time_t dataVenda;
} TipoVenda;

typedef struct listaVendas {
    TipoVenda venda;
    struct listaVendas *prox;
} ListaVendas;

ListaVendas *iniciaListaVendas();

int escolheIdVenda(ListaVendas *lista);

int inserirVenda(ListaVendas **lista, TipoVenda venda);

void gerarReciboVenda(TipoVenda venda, TipoHospede hospede, ListaProduto *listaProdutos);

int salvarDadosVendasBin(ListaVendas *lista, char *nome_arquivo);

ListaVendas *resgataDadosVendasBin(char *nome_arquivo);

int salvarDadosVendasTxt(ListaVendas *lista, char *nome_arquivo);

ListaVendas *resgataDadosVendasTxt(char *nome_arquivo);

void interfaceVendas(ListaVendas *listaVendas, ListaProduto *listaProdutos, ListaHospede *listaHospedes, TipoHotel *dadosHotel);

#endif
