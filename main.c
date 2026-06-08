#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "bib/utils.h"

#include "bib/hotel.h"
#include "bib/hospedes.h"
#include "bib/acomodacoes.h"
#include "bib/acomodacoes.h"
#include "bib/categorias.h"

#include "bib/produtos.h"
#include "bib/fornecedores.h"

#include "bib/operadores.h"

#include "bib/reservas.h"

#include "bib/estadias.h"

#include "bib/vendas.h"
#include "bib/compras.h"

#include "bib/contas.h"
#include "bib/controleDeCaixa.h"

#define HotelBIN "./data/bin/hotel.dat"
#define HotelTXT "./data/txt/hotel.txt"

#define HospedesBIN "./data/bin/hospedes.dat"
#define HospedesTXT "./data/txt/hospedes.txt"

#define AcomodacoesBIN "./data/bin/acomodacoes.dat"
#define AcomodacoesTXT "./data/txt/acomodacoes.txt"

#define CategoriasBIN "./data/bin/categorias.dat"
#define CategoriasTXT "./data/txt/categorias.txt"

#define ProdutosBIN "./data/bin/produtos.dat"
#define ProdutosTXT "./data/txt/produtos.txt"

#define FornecedoresBIN "./data/bin/fornecedores.dat"
#define FornecedoresTXT "./data/txt/fornecedores.txt"

#define OperadoresBIN "./data/bin/operadores.dat"
#define OperadoresTXT "./data/txt/operadores.txt"

#define ReservasBIN "./data/bin/reservas.dat"
#define ReservasTXT "./data/txt/reservas.txt"

#define VendasBIN "./data/bin/vendas.dat"
#define VendasTXT "./data/txt/vendas.txt"

#define ComprasBIN "./data/bin/compras.dat"
#define ComprasTXT "./data/txt/compras.txt"

#define ContasPagarBIN "./data/bin/contas_pagar.dat"
#define ContasPagarTXT "./data/txt/contas_pagar.txt"

#define ContasReceberBIN "./data/bin/contas_receber.dat"
#define ContasReceberTXT "./data/txt/contas_receber.txt"

#define HistoricoCaixaBIN "./data/bin/historico_caixa.dat"
#define HistoricoCaixaTXT "./data/txt/historico_caixa.txt"

#define HistoricoEstadiasBIN "./data/bin/historico_estadias.dat"
#define HistoricoEstadiasTXT "./data/txt/historico_estadias.txt"

#define BIN 1
#define TXT 2
#define MEM 3

int main()
{
    int res = 0, modo;

    TipoHotel *dadosHotel;
    ListaHospede *listaHospedes;
    ListaAcomodacao *listaAcomodacao;
    ListaCategoria *listaCategoria;

    ListaProduto *listaProduto;
    ListaFornecedor *listaFornecedor;
    
    ListaOperadores *listaOperadores;
    
    ListaReservas *listaReservas;
    ListaVendas *listaVendas;
    
    ListaEstadia *listaEstadias;

    ListaNotasFiscais *listaNotasFiscais;
    ListaHistoricoCaixa *historicoCaixa;
    ListaContas *listaContasReceber;
    ListaContas *listaContasPagar;

    while (1)
    {
        system("cls");
        printf("Selecione a forma de armazenar os dados no sistema:\n");
        printf("1 - Arquivos Bin\n");
        printf("2 - Arquivos Txt\n");
        printf("3 - Em memoria (CUIDADO: todos os arquivos serao perdidos apos o encerramento do sistema)\n");
        printf("4 - Sair\n");
        printf("=> ");
        scanf("%d", &modo);
        fflush(stdin);

        if (modo == BIN || modo == TXT || modo == MEM || modo == 4)
        {
            if (modo == 4)
                return 0;
            break;
        }
        else
        {
            printf("Selecione uma opcao valida!\n");
            system("pause");
            fflush(stdin);
        }
    }

    dadosHotel = resgataDadosHotelBin(HotelBIN);
    if (!dadosHotel->cadastrado)
    {
        free(dadosHotel);
        dadosHotel = resgataDadosHotelTxt(HotelTXT);
    }

    listaHospedes = resgataDadosHospedesBin(HospedesBIN);
    if (listaHospedes->prox == NULL)
    {
        free(listaHospedes);
        listaHospedes = resgataDadosHospedesTxt(HospedesTXT);
    }

    listaAcomodacao = resgataDadosAcomodacoesBin(AcomodacoesBIN);
    if (listaAcomodacao->prox == NULL)
    {
        free(listaAcomodacao);
        listaAcomodacao = resgataDadosAcomodacoesTxt(AcomodacoesTXT);
    }

    listaCategoria = carregarCategoriasBin(CategoriasBIN);
    if (listaCategoria->prox == NULL)
    {
        free(listaCategoria);
        listaCategoria = carregarCategoriasTxt(CategoriasTXT);
    }

    listaProduto = resgataDadosProdutosBin(ProdutosBIN);
    if (listaProduto->prox == NULL)
    {
        free(listaProduto);
        listaProduto = resgataDadosProdutosTxt(ProdutosTXT);
    }

    listaFornecedor = resgataDadosFornecedoresBin(FornecedoresBIN);
    if (listaFornecedor->prox == NULL)
    {
        free(listaFornecedor);
        listaFornecedor = resgataDadosFornecedoresTxt(FornecedoresTXT);
    }

    listaOperadores = resgataDadosOperadoresBin(OperadoresBIN);
    if (listaOperadores->prox == NULL)
    {
        free(listaOperadores);
        listaOperadores = resgataDadosOperadoresTxt(OperadoresTXT);
    }

    listaReservas = resgataDadosReservasBin(ReservasBIN);
    if (listaReservas->prox == NULL)
    {
        free(listaReservas);
        listaReservas = resgataDadosReservasTxt(ReservasTXT);
    }

    listaVendas = resgataDadosVendasBin(VendasBIN);
    if (listaVendas->prox == NULL)
    {
        free(listaVendas);
        listaVendas = resgataDadosVendasTxt(VendasTXT);
    }

    listaNotasFiscais = resgataDadosNotasBin(ComprasBIN);
    if (listaNotasFiscais->prox == NULL)
    {
        free(listaNotasFiscais);
        listaNotasFiscais = resgataDadosNotasTxt(ComprasTXT);
    }

    listaContasPagar = resgataDadosContasBin(ContasPagarBIN);
    if (listaContasPagar->prox == NULL)
    {
        free(listaContasPagar);
        listaContasPagar = resgataDadosContasTxt(ContasPagarTXT);
    }

    listaContasReceber = resgataDadosContasBin(ContasReceberBIN);
    if (listaContasReceber->prox == NULL)
    {
        free(listaContasReceber);
        listaContasReceber = resgataDadosContasTxt(ContasReceberTXT);
    }

    historicoCaixa = resgataDadosHistoricoCaixaBin(HistoricoCaixaBIN);
    if (historicoCaixa->prox == NULL)
    {
        free(historicoCaixa);
        historicoCaixa = resgataDadosHistoricoCaixaTxt(HistoricoCaixaTXT);
    }

    listaEstadias = resgataDadosEstadiasBin(HistoricoEstadiasBIN);
    if(listaEstadias->prox == NULL)
    {
        free(listaEstadias);
        listaEstadias = resgataDadosEstadiasTxt(HistoricoEstadiasTXT);
    }

    do
    { // MENU PRINCIPAL =============================================================================
        system("cls");
        printf("Menu principal\n");
        printf("1 - Cadastro e Gestao\n");
        printf("2 - Reservas e Cancelamentos\n");
        printf("3 - Transacoes\n");
        printf("4 - Feedback\n");
        printf("5 - Importacao/Exportacao de dados\n");
        printf("0 - Sair do sistema\n");
        printf("=> ");

        scanf("%d", &res);
        fflush(stdin);

        switch (res)
        {
        case 1: // CADASTRO E GESTAO ====================================================
            do
            {
                system("cls");
                printf("Cadastro e gestao de hospedes\n");
                printf("1 - Dados do Hotel\n");
                printf("2 - Hospedes\n");
                printf("3 - Acomodacoes\n");
                printf("4 - Categorias de Acomodacoes\n");
                printf("5 - Produtos\n");
                printf("6 - Fornecedores\n");
                printf("7 - Operadores\n");
                printf("0 - Voltar para o Menu principal\n");
                printf("=> ");

                scanf("%d", &res);
                fflush(stdin);
                switch (res)
                {
                case 1: // hotel
                    interfaceHotel(dadosHotel);
                    break;
                case 2: // hospedes
                    interfaceHospedes(listaHospedes);
                    break;
                case 3: // acomodacoes
                    interfaceAcomodacao(listaAcomodacao, listaCategoria);
                    break;
                case 4: // categorias de acomodacoes
                    interfaceCategoria(listaCategoria);
                    break;
                case 5: // produtos
                    interfaceProduto(listaProduto);
                    break;
                case 6: // fornecedores
                    interfaceFornecedor(listaFornecedor);
                    break;
                case 7: // operadores
                    interfaceOperadores(listaOperadores);
                    break;
                default:
                    if (res != 0)
                    {
                        printf("Selecione uma opcao valida!");
                        system("pause");
                    }
                    break;
                }
            } while (res != 0);
            res = 1;
            break;
        case 2: // RESERVAS E CANCELAMENTOS =============================================
            interfaceReservas(listaReservas, listaAcomodacao, listaCategoria, listaHospedes);
            break;
        case 3: // TRANSACOES ===========================================================
            do{
                system("cls");
                printf("Cadastro e gestao de hospedes\n");
                printf("1 - Check-in e Check-out\n");
                printf("2 - Vendas (Sa¡da de produtos)\n");
                printf("3 - Compras (Entrada de produtos industrializados)\n");
                printf("4 - Controle de Caixa\n");
                printf("5 - Contas a Pagar\n");
                printf("6 - Contas a Receber\n");
                printf("0 - Voltar para o Menu principal\n");
                printf("=> ");

                scanf("%d", &res);
                fflush(stdin);

                switch (res)
                {
                case 1: // CHECK-OUT
                    interfaceEstadias(listaEstadias, listaHospedes, listaAcomodacao, listaCategoria, listaReservas, historicoCaixa);
                    break;
                case 2: // VENDAS
                    interfaceVendas(listaVendas, listaProduto, listaHospedes, historicoCaixa, listaContasReceber);
                    break;  
                case 3: // COMPRAS
                    interfaceCompras(listaNotasFiscais, listaContasPagar, listaProduto, listaFornecedor, dadosHotel, historicoCaixa);
                    break;
                case 4: // CONTROLE DE CAIXA
                    interfaceControleDeCaixa(historicoCaixa);
                    break;
                case 5: // CONTAS A PAGAR
                    interfaceContasPagar(&listaContasPagar, &historicoCaixa);
                    break;
                case 6: // CONTAS A RECEBER
                    interfaceContasReceber(&listaContasReceber, &historicoCaixa);   
                    break;
                default:
                    if (res != 0)
                    {
                        printf("Selecione uma opcao valida!");
                        system("pause");
                    }
                    break;
                }
            }while(res != 0);

            break;
        case 4: // FEEDBACK =============================================================

            break;
        case 5: // IMPORTACAO/EXPORTACAO DE DADOS =======================================

            break;
        default: // SAIR DO SISTEMA =====================================================
            if (res != 0)
            {
                printf("Escolha um valor valido!\n");
                system("pause");
            }
            else
            {
                printf("Tem certeza que deseja sair do sistema?\n");
                printf("1 - Sim\n");
                printf("2 - Nao\n");
                printf("=> ");
                scanf("%d", &res);

                if (res == 1)
                {
                    if (modo == BIN)
                    {
                        salvarDadosHotelBin(*dadosHotel, HotelBIN);
                        salvarDadosHospedesBin(listaHospedes, HospedesBIN);
                        salvarDadosAcomodacoesBin(listaAcomodacao, AcomodacoesBIN);
                        salvarDadosCategoriasBin(listaCategoria, CategoriasBIN);
                        salvarDadosProdutosBin(listaProduto, ProdutosBIN);
                        salvarDadosFornecedoresBin(listaFornecedor, FornecedoresBIN);
                        salvarDadosOperadoresBin(listaOperadores, OperadoresBIN);
                        salvarDadosReservasBin(listaReservas, ReservasBIN);
                        salvarDadosVendasBin(listaVendas, VendasBIN);
                        salvarDadosNotasBin(listaNotasFiscais, ComprasBIN);
                        salvarDadosContasBin(listaContasPagar, ContasPagarBIN);
                        salvarDadosContasBin(listaContasReceber, ContasReceberBIN);
                        salvarDadosHistoricoCaixaBin(historicoCaixa, HistoricoCaixaBIN);
                        salvarDadosEstadiasBin(listaEstadias, HistoricoEstadiasBIN);
                        apagaArquivo(HotelTXT);
                        apagaArquivo(HospedesTXT);
                        apagaArquivo(AcomodacoesTXT);
                        apagaArquivo(CategoriasTXT);
                        apagaArquivo(ProdutosTXT);
                        apagaArquivo(FornecedoresTXT);
                        apagaArquivo(OperadoresTXT);
                        apagaArquivo(ReservasTXT);
                        apagaArquivo(VendasTXT);
                        apagaArquivo(ComprasTXT);
                        apagaArquivo(ContasPagarTXT);
                        apagaArquivo(ContasReceberTXT);
                        apagaArquivo(HistoricoCaixaTXT);
                        apagaArquivo(HistoricoEstadiasTXT);
                    }
                    else if (modo == TXT)
                    {
                        salvarDadosHotelTxt(*dadosHotel, HotelTXT);
                        salvarDadosHospedesTxt(listaHospedes, HospedesTXT);
                        salvarDadosAcomodacoesTxt(listaAcomodacao, AcomodacoesTXT);
                        salvarDadosCategoriasTxt(listaCategoria, CategoriasTXT);
                        salvarDadosProdutosTxt(listaProduto, ProdutosTXT);
                        salvarDadosFornecedoresTxt(listaFornecedor, FornecedoresTXT);
                        salvarDadosOperadoresTxt(listaOperadores, OperadoresTXT);
                        salvarDadosReservasTxt(listaReservas, ReservasTXT);
                        salvarDadosVendasTxt(listaVendas, VendasTXT);
                        salvarDadosNotasTxt(listaNotasFiscais, ComprasTXT);
                        salvarDadosContasTxt(listaContasPagar, ContasPagarTXT);
                        salvarDadosContasTxt(listaContasReceber, ContasReceberTXT);
                        salvarDadosHistoricoCaixaTxt(historicoCaixa, HistoricoCaixaTXT);
                        salvarDadosEstadiasTxt(listaEstadias, HistoricoEstadiasTXT);
                        apagaArquivo(HotelBIN);
                        apagaArquivo(HospedesBIN);
                        apagaArquivo(AcomodacoesBIN);
                        apagaArquivo(CategoriasBIN);
                        apagaArquivo(ProdutosBIN);
                        apagaArquivo(FornecedoresBIN);
                        apagaArquivo(OperadoresBIN);
                        apagaArquivo(ReservasBIN);
                        apagaArquivo(VendasBIN);
                        apagaArquivo(ComprasBIN);
                        apagaArquivo(ContasPagarBIN);
                        apagaArquivo(ContasReceberBIN);
                        apagaArquivo(HistoricoCaixaBIN);
                        apagaArquivo(HistoricoEstadiasBIN);
                    }
                    liberaHotel(dadosHotel);
                    liberaListaHospedes(listaHospedes);
                    liberaListaAcomodacoes(listaAcomodacao);
                    liberaListaCategorias(listaCategoria);
                    liberaListaProdutos(listaProduto);
                    liberaListaFornecedores(listaFornecedor);
                    liberaListaOperadores(listaOperadores);
                    liberaListaReservas(listaReservas);
                    liberaListaVendas(listaVendas);
                    liberaListaNotasFiscais(listaNotasFiscais);
                    liberaListaContas(listaContasPagar);
                    liberaListaContas(listaContasReceber);
                    liberaListaHistoricoCaixa(historicoCaixa);
                    liberaListaEstadias(listaEstadias);
                    return 0;
                }
            }
            break;
        }

    } while (res != 0);
    return 0;
}
