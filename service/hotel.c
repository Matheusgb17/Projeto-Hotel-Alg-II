#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "..\bib\hotel.h"

TipoHotel *iniciaHotel()
{
    TipoHotel *hotel = malloc(sizeof(TipoHotel));

    hotel->cadastrado = false;
    strcpy(hotel->nomeFantasia, "[Dados n�o cadastrados]");
    return hotel;
}

void salvarDadosHotel(TipoHotel h, TipoHotel *hotel)
{
    h.cadastrado = true;
    *hotel = h;
    return;
}

TipoHotel consultarDadosHotel(TipoHotel *h)
{
    return *h;
}

void apagarDadosHotel(TipoHotel *hotel)
{
    hotel->cadastrado = false;
    strcpy(hotel->nomeFantasia, "[Dados n�o cadastrados]");
    return;
}

void interfaceHotel()
{
    TipoHotel hotel, *dadosHotel = iniciaHotel();
    int res = 0;
    while (res != 5)
    {
        system("cls");
        printf("Gest�o de dados do hotel | %s\n", dadosHotel->nomeFantasia);
        if (!dadosHotel->cadastrado)
            printf("1 - Cadastrar dados do hotel\n");
        if (dadosHotel->cadastrado)
            printf("2 - Consultar dados do hotel\n");
        if (dadosHotel->cadastrado)
            printf("3 - Alterar dados do hotel\n");
        if (dadosHotel->cadastrado)
            printf("4 - Apagar dados do hotel\n");

        printf("5 - voltar\n");
        printf("=> ");

        scanf("%d", &res);
        fflush(stdin);

        switch (res)
        {
        case 1:
            if (dadosHotel->cadastrado)
                continue;

            system("cls");
            printf("Insira o Nome Fantasia do hotel: ");
            scanf("%[^\n]", hotel.nomeFantasia);
            fflush(stdin);

            printf("Insira a Raz�o Social: ");
            scanf("%[^\n]", hotel.razaoSocial);
            fflush(stdin);

            printf("Insira a Inscri��o Estadual do hotel: ");
            scanf("%[^\n]", hotel.inscricaoEstadual);
            fflush(stdin);

            printf("Insira o CNPJ do hotel: ");
            scanf("%[^\n]", hotel.CNPJ);
            fflush(stdin);

            printf("Insira o endere�o completo do hotel: ");
            scanf("%[^\n]", hotel.enderecoCompleto);
            fflush(stdin);

            printf("Insira o telefone do hotel: ");
            scanf("%[^\n]", hotel.telefone);
            fflush(stdin);

            printf("Insira o email do hotel: ");
            scanf("%[^\n]", hotel.email);
            fflush(stdin);

            printf("Insira o nome do respons�vel do hotel: ");
            scanf("%[^\n]", hotel.nomeResponsavel);
            fflush(stdin);

            printf("Insira o telefone do respons�vel do hotel: ");
            scanf("%[^\n]", hotel.telefoneResponsavel);
            fflush(stdin);

            printf("Insira o horario de check-in do hotel: ");
            scanf("%[^\n]", hotel.horarioCheckin);
            fflush(stdin);

            printf("Insira o horario de check-out do hotel: ");
            scanf("%[^\n]", hotel.horarioCheckout);
            fflush(stdin);

            printf("Insira a margem de lucro do hotel: ");
            scanf("%f", &hotel.margemLucro);
            fflush(stdin);

            salvarDadosHotel(hotel, dadosHotel);
            break;
        case 2:
            if (!dadosHotel->cadastrado)
                continue;

            system("cls");
            hotel = consultarDadosHotel(dadosHotel);
            printf("Nome Fantasia           : %s\n", hotel.nomeFantasia);
            printf("Razao Social            : %s\n", hotel.razaoSocial);
            printf("Inscricao Estadual      : %s\n", hotel.inscricaoEstadual);
            printf("CNPJ                    : %s\n", hotel.CNPJ);
            printf("Endere�o Completo       : %s\n", hotel.enderecoCompleto);
            printf("Telefone                : %s\n", hotel.telefone);
            printf("Email                   : %s\n", hotel.email);
            printf("Nome do Responsavel     : %s\n", hotel.nomeResponsavel);
            printf("Telefone do Responsavel : %s\n", hotel.telefoneResponsavel);
            printf("Horario de Check-in     : %s\n", hotel.horarioCheckin);
            printf("Horario de Check-out    : %s\n", hotel.horarioCheckout);
            printf("Margem de Lucro         : %.2f\n\n", hotel.margemLucro);

            system("pause");
            fflush(stdin);

            break;
        case 3:
            if (!dadosHotel->cadastrado)
                continue;

            while (res != 13)
            {
                system("cls");
                printf("Atualizando dados do hotel: \n");

                printf("1  - Nome Fantasia           : %s\n", hotel.nomeFantasia);
                printf("2  - Razao Social            : %s\n", hotel.razaoSocial);
                printf("3  - Inscricao Estadual      : %s\n", hotel.inscricaoEstadual);
                printf("4  - CNPJ                    : %s\n", hotel.CNPJ);
                printf("5  - Endere�o Completo       : %s\n", hotel.enderecoCompleto);
                printf("6  - Telefone                : %s\n", hotel.telefone);
                printf("7  - Email                   : %s\n", hotel.email);
                printf("8  - Nome do Responsavel     : %s\n", hotel.nomeResponsavel);
                printf("9  - Telefone do Responsavel : %s\n", hotel.telefoneResponsavel);
                printf("10 - Horario de Check-in     : %s\n", hotel.horarioCheckin);
                printf("11 - Horario de Check-out    : %s\n", hotel.horarioCheckout);
                printf("12 - Margem de Lucro         : %.2f\n\n", hotel.margemLucro);

                printf("13 - Salvar dados\n");
                printf("14 - Cancelar\n");
                printf("=> ");
                scanf("%d", &res);
                fflush(stdin);

                if (res == 14)
                    break;

                switch (res)
                {
                case 1:
                    printf("Insira o novo Nome Fantasia do hotel: ");
                    scanf("%[^\n]", hotel.nomeFantasia);
                    fflush(stdin);
                    break;
                case 2:
                    printf("Insira a nova Razão Social: ");
                    scanf("%[^\n]", hotel.razaoSocial);
                    fflush(stdin);
                    break;
                case 3:
                    printf("Insira a nova Inscrição Estadual do hotel: ");
                    scanf("%[^\n]", hotel.inscricaoEstadual);
                    fflush(stdin);
                    break;
                case 4:
                    printf("Insira o novo CNPJ do hotel: ");
                    scanf("%[^\n]", hotel.CNPJ);
                    fflush(stdin);
                    break;
                case 5:
                    printf("Insira o novo endereço completo do hotel: ");
                    scanf("%[^\n]", hotel.enderecoCompleto);
                    fflush(stdin);
                    break;
                case 6:
                    printf("Insira o novo telefone do hotel: ");
                    scanf("%[^\n]", hotel.telefone);
                    fflush(stdin);
                    break;
                case 7:
                    printf("Insira o novo email do hotel: ");
                    scanf("%[^\n]", hotel.email);
                    fflush(stdin);
                    break;
                case 8:
                    printf("Insira o novo nome do responsável do hotel: ");
                    scanf("%[^\n]", hotel.nomeResponsavel);
                    fflush(stdin);
                    break;
                case 9:
                    printf("Insira o novo telefone do responsável do hotel: ");
                    scanf("%[^\n]", hotel.telefoneResponsavel);
                    fflush(stdin);
                    break;
                case 10:
                    printf("Insira o novo horario de check-in do hotel: ");
                    scanf("%[^\n]", hotel.horarioCheckin);
                    fflush(stdin);
                    break;
                case 11:
                    printf("Insira o novo horario de check-out do hotel: ");
                    scanf("%[^\n]", hotel.horarioCheckout);
                    fflush(stdin);
                    break;
                case 12:
                    printf("Insira a nova margem de lucro do hotel: ");
                    scanf("%f", &hotel.margemLucro);
                    fflush(stdin);
                    break;
                case 13:
                    salvarDadosHotel(hotel, dadosHotel);
                    printf("\nDados salvos com sucesso!\n");
                    system("pause");
                    break;
                default:
                    printf("Opção inválida!\n");
                    system("pause");
                    fflush(stdin);
                    break;
                }
            }

            break;
        case 4:
            if (!dadosHotel->cadastrado)
                continue;

            printf("Tem certeza que deseja apagar todos os dados do hotel?\n");
            printf("1 - Sim\n");
            printf("2 - Cancelar\n");
            printf("=> ");
            scanf("%d", &res);

            if (res == 1)
                apagarDadosHotel(dadosHotel);
            res = 0;
            break;
        default:
            if (res != 5)
                printf("Op��o inv�lida!\n");
            system("pause");
            break;
        }
    }
    return;
}