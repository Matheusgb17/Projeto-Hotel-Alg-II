#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "bib/hotel.h"
#include "bib/hospedes.h"
#include "bib/acomodacoes.h"
#include "bib/categorias.h"
#include "bib/produtos.h"
#include "bib/fornecedores.h"
#include "bib/acomodacoes.h"
#include "bib/operadores.h"
#include "bib/utils.h"

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
    // ListaFornecedor *listaFornecedor;
    ListaOperadores *listaOperadores;

    while (1)
    {
        system("cls");
        printf("Selecione a forma de armazenar os dados no sistema:\n");
        printf("1 - Arquivos Bin\n");
        printf("2 - Arquivos Txt\n");
        printf("3 - Em mem¢ria (CUIDADO: todos os arquivos serï¿½o perdidos apï¿½s o encerramento do sistema)\n");
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
            printf("Selecione uma op‡Æo v lida!\n");
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
    if (listaCategoria->prox == NULL)    {
        free(listaCategoria);
        listaCategoria = carregarCategoriasTxt(CategoriasTXT);
    }

    listaProduto = resgataDadosProdutosBin(ProdutosBIN);
    if (listaProduto->prox == NULL){    
        free(listaProduto);
        listaProduto = resgataDadosProdutosTxt(ProdutosTXT);
    }   

    // listaFornecedor = resgataDadosFornecedoresBin(FornecedoresBIN);
    // if (listaFornecedor->prox == NULL){    
    //     free(listaFornecedor);
    //     listaFornecedor = resgataDadosFornecedoresTxt(FornecedoresTXT);
    // }

    listaOperadores = resgataDadosOperadoresBin(OperadoresBIN);
    if (listaOperadores->prox == NULL){    
        free(listaOperadores);
        listaOperadores = resgataDadosOperadoresTxt(OperadoresTXT);
    }

    do
    { // MENU PRINCIPAL =============================================================================
        system("cls");
        printf("Menu principal\n");
        printf("1 - Cadastro e GestÆo\n");
        printf("2 - Reservas e Cancelamentos\n");
        printf("3 - Transa‡äes\n");
        printf("4 - Feedback\n");
        printf("5 - Importa‡Æo/Exporta‡Æo de dados\n");
        printf("0 - Sair do sistema\n");
        printf("=> ");

        scanf("%d", &res);
        fflush(stdin);

        switch (res)
        {
        case 1: // CADASTRO E GESTÇO ====================================================
            do
            {
                system("cls");
                printf("Cadastro e gestÆo de hospedes\n");
                printf("1 - Dados do Hotel\n");
                printf("2 - H¢spedes\n");
                printf("3 - Acomoda‡äes\n");
                printf("4 - Categorias de Acomoda‡Æo\n");
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
                    interfaceHotel(dadosHotel, modo);
                    break;
                case 2: // hospedes
                    interfaceHospedes(listaHospedes, modo);
                    break;
                case 3: // acomoda‡äes
                    interfaceAcomodacao(listaAcomodacao, listaCategoria, modo);
                    break;
                case 4: // categorias de acomoda‡äes
                    interfaceCategoria(listaCategoria, modo);
                    break;
                case 5: // produtos
                    interfaceProduto(listaProduto, modo);
                    break;
                case 6: // fornecedores
                    break;
                case 7: // operadores
                    interfaceOperadores(listaOperadores, modo);
                    break;
                default:
                    if (res != 0)
                    {
                        printf("Selecione uma op‡Æo v lida!");
                        system("pause");
                    }
                    break;
                }
            } while (res != 0);
            res = 1;
            break;
        case 2: // RESERVAS E CANCELAMENTOS =============================================

            break;
        case 3: // TRANSACOES ===========================================================

            break;
        case 4: // FEEDBACK =============================================================

            break;
        case 5: // IMPORTA€ÇO/EXPORTA€ÇO DE DADOS =======================================

            break;
        default: // SAIR DO SISTEMA =====================================================
            if (res != 0)
            {
                printf("Escolha um valor v lido!\n");
                system("pause");
            }
            else
            {
                printf("Tem certeza que deseja sair do sistema?\n");
                printf("1 - Sim\n");
                printf("2 - NÆo\n");
                printf("=> ");
                scanf("%d", &res);

                if (res == 1){
                    if(modo == BIN){
                        salvarDadosHotelBin(*dadosHotel, HotelBIN);
                        salvarDadosHospedesBin(listaHospedes, HospedesBIN);
                        salvarDadosAcomodacoesBin(listaAcomodacao, AcomodacoesBIN);
                        salvarDadosCategoriasBin(listaCategoria, CategoriasBIN);
                        salvarDadosProdutosBin(listaProduto, ProdutosBIN);
                        // salvarDadosFornecedoresBin(listaFornecedor, FornecedoresBIN);
                        salvarDadosOperadoresBin(listaOperadores, OperadoresBIN);
                        apagaArquivo(HotelTXT);
                        apagaArquivo(HospedesTXT);
                        apagaArquivo(AcomodacoesTXT);
                        apagaArquivo(CategoriasTXT);
                        apagaArquivo(ProdutosTXT);
                        // apagaArquivo(FornecedoresTXT);
                        apagaArquivo(OperadoresTXT);
                    }
                    else if(modo == TXT){
                        salvarDadosHotelTxt(*dadosHotel, HotelTXT);
                        salvarDadosHospedesTxt(listaHospedes, HospedesTXT);
                        salvarDadosAcomodacoesTxt(listaAcomodacao, AcomodacoesTXT);
                        salvarDadosCategoriasTxt(listaCategoria, CategoriasTXT);
                        salvarDadosProdutosTxt(listaProduto, ProdutosTXT);
                        // salvarDadosFornecedoresTxt(listaFornecedor, FornecedoresTXT);
                        salvarDadosOperadoresTxt(listaOperadores, OperadoresTXT);
                        apagaArquivo(HotelBIN);
                        apagaArquivo(HospedesBIN);
                        apagaArquivo(AcomodacoesBIN);
                        apagaArquivo(CategoriasBIN);
                        apagaArquivo(ProdutosBIN);
                        // apagaArquivo(FornecedoresBIN);
                        apagaArquivo(OperadoresBIN);
                    }
                    return 0;
                }
            }
            break;
        }

    } while (res != 0);
    return 0;
}