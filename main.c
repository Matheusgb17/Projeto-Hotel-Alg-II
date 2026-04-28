#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "bib/hospedes.h"
#include "bib/categorias.h"
#include "bib/produtos.h"
#include "bib/fornecedores.h"
#include "bib/acomodacoes.h"
#include "bib/produtos.h"

#define BIN 1
#define TXT 2
#define MEM 3

int main()
{
    int res = 0, modo;

    while (1)
    {
        system("cls");
        printf("Selecione a forma de armazenar os dados no sistema:\n");
        printf("1 - Arquivos Bin\n");
        printf("2 - Arquivos Txt\n");
        printf("3 - Em mem�ria (CUIDADO: todos os arquivos ser�o perdidos ap�s o encerramento do sistema)\n");
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
            printf("Selecione uma op��o v�lida!\n");
            system("pause");
            fflush(stdin);
        }
    }

    do
    { // MENU PRINCIPAL =============================================================================
        system("cls");
        printf("Menu principal\n");
        printf("1 - Cadastro e Gest�o\n");
        printf("2 - Reservas e Cancelamentos\n");
        printf("3 - Transa��es\n");
        printf("4 - Feedback\n");
        printf("5 - Importa��o/Exporta��o de dados\n");
        printf("0 - Sair do sistema\n");
        printf("=> ");

        scanf("%d", &res);
        fflush(stdin);

        switch (res)
        {
        case 1: // CADASTRO E GEST�O ====================================================
            do
            {
                system("cls");
                printf("Cadastro e gest�o de hospedes\n");
                printf("1 - Dados do Hotel\n");
                printf("2 - H�spedes\n");
                printf("3 - Acomoda��es\n");
                printf("4 - Categorias de Acomoda��o\n");
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
                    // interfaceHotel(modo);
                    break;
                case 2: // hospedes
                    //interfaceHospedes(modo);
                    break;
                case 3: // acomoda��es
                    // interfaceAcomodacao(modo);
                    break;
                case 4: // categorias de acomoda��es
                        // interfaceCategoria(modo);
                    break;
                case 5:
                        interfaceProduto(modo);
                    break;
                case 6:
                        // interfaceFornecedor();
                    break;
                case 7: // operadores
                    //interfaceOperadores(modo);
                    break;
                default:
                    if (res != 0)
                    {
                        printf("Selecione uma op��o v�lida!");
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
        case 5: // IMPORTA��O/EXPORTA��O DE DADOS =======================================

            break;
        default: // SAIR DO SISTEMA =====================================================
            if (res != 0)
            {
                printf("Escolha um valor v�lido!\n");
                system("pause");
            }
            else
            {
                printf("Tem certeza que deseja sair do sistema?\n");
                printf("1 - Sim\n");
                printf("2 - N�o\n");
                printf("=> ");
                scanf("%d", &res);

                if (res == 1)
                    return 0;
                res = 0;
            }
            break;
        }

    } while (res != 0);
    return 0;
}