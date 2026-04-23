#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../bib/hotel.h"
#include "../bib/utils.h"

#define HotelBIN "./data/bin/hotel.dat"
#define HotelTXT "./data/txt/hotel.txt"

#define BIN 1
#define TXT 2
#define MEM 3

TipoHotel *iniciaHotel()
{
    TipoHotel *hotel = malloc(sizeof(TipoHotel));

    hotel->cadastrado = false;
    strcpy(hotel->nomeFantasia, "[Dados n?o cadastrados]");
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
    strcpy(hotel->nomeFantasia, "[Dados n?o cadastrados]");
    return;
}

int salvarDadosHotelBin(TipoHotel h, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao acessar o arquivo...\n");
        return 1;
    }

    fwrite(&h, sizeof(TipoHotel), 1, arquivo);
    fclose(arquivo);
    return 0;
}

TipoHotel *resgataDadosHotelBin(char *nome_arquivo)
{
    TipoHotel *hotel = iniciaHotel();
    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao acessar o arquivo...\n");
        return hotel;
    }

    fread(hotel, sizeof(TipoHotel), 1, arquivo);
    fclose(arquivo);
    return hotel;
}

int salvarDadosHotelTxt(TipoHotel h, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao acessar o arquivo...\n");
        return 1;
    }

    fprintf(arquivo, "<tabela=hotel>\n");
    fprintf(arquivo, "  <registro>\n");
    fprintf(arquivo, "    <cadastrado>%d</cadastrado>\n", h.cadastrado);
    fprintf(arquivo, "    <nome_fantasia>%s</nome_fantasia>\n", h.nomeFantasia);
    fprintf(arquivo, "    <razao_social>%s</razao_social>\n", h.razaoSocial);
    fprintf(arquivo, "    <inscricao_estadual>%s</inscricao_estadual>\n", h.inscricaoEstadual);
    fprintf(arquivo, "    <CNPJ>%s</CNPJ>\n", h.CNPJ);
    fprintf(arquivo, "    <endereco_completo>%s</endereco_completo>\n", h.enderecoCompleto);
    fprintf(arquivo, "    <telefone>%s</telefone>\n", h.telefone);
    fprintf(arquivo, "    <email>%s</email>\n", h.email);
    fprintf(arquivo, "    <nome_responsavel>%s</nome_responsavel>\n", h.nomeResponsavel);
    fprintf(arquivo, "    <telefone_responsavel>%s</telefone_responsavel>\n", h.telefoneResponsavel);
    fprintf(arquivo, "    <horario_checkin>%s</horario_checkin>\n", h.horarioCheckin);
    fprintf(arquivo, "    <horario_checkout>%s</horario_checkout>\n", h.horarioCheckout);
    fprintf(arquivo, "    <margem_lucro>%.2f</margem_lucro>\n", h.margemLucro);
    fprintf(arquivo, "  </registro>\n");
    fprintf(arquivo, "</tabela>\n");

    fclose(arquivo);
    return 0;
}

TipoHotel *resgataDadosHotelTxt(char *nome_arquivo)
{
    TipoHotel *hotel = iniciaHotel();
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao acessar o arquivo...\n");
        return hotel;
    }

    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(hotel, 0, sizeof(TipoHotel));
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            salvarDadosHotel(*hotel, hotel);
            break;
        }

        sscanf(linha, " <cadastrado>%d", &hotel->cadastrado);
        sscanf(linha, " <nome_fantasia>%[^<]", hotel->nomeFantasia);
        sscanf(linha, " <razao_social>%[^<]", hotel->razaoSocial);
        sscanf(linha, " <inscricao_estadual>%[^<]", hotel->inscricaoEstadual);
        sscanf(linha, " <CNPJ>%[^<]", hotel->CNPJ);
        sscanf(linha, " <endereco_completo>%[^<]", hotel->enderecoCompleto);
        sscanf(linha, " <telefone>%[^<]", hotel->telefone);
        sscanf(linha, " <email>%[^<]", hotel->email);
        sscanf(linha, " <nome_responsavel>%[^<]", hotel->nomeResponsavel);
        sscanf(linha, " <telefone_responsavel>%[^<]", hotel->telefoneResponsavel);
        sscanf(linha, " <horario_checkin>%[^<]", hotel->horarioCheckin);
        sscanf(linha, " <horario_checkout>%[^<]", hotel->horarioCheckout);
        sscanf(linha, " <margem_lucro>%f", &hotel->margemLucro);
    }

    fclose(arquivo);
    return hotel;
}

void interfaceHotel(int modo)
{
    TipoHotel hotel, *dadosHotel;

    dadosHotel = resgataDadosHotelBin(HotelBIN);
    if (!dadosHotel->cadastrado)
    {
        free(dadosHotel);
        dadosHotel = resgataDadosHotelTxt(HotelTXT);
    }

    int res = 0;
    do
    {
        system("cls");
        printf("Gest∆o de dados do hotel | %s\n", dadosHotel->nomeFantasia);
        if (!dadosHotel->cadastrado)
            printf("1 - Cadastrar dados do hotel\n");
        if (dadosHotel->cadastrado)
            printf("2 - Consultar dados do hotel\n");
        if (dadosHotel->cadastrado)
            printf("3 - Alterar dados do hotel\n");
        if (dadosHotel->cadastrado)
            printf("4 - Apagar dados do hotel\n");

        printf("0 - voltar\n");
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

            printf("Insira a Raz∆o Social: ");
            scanf("%[^\n]", hotel.razaoSocial);
            fflush(stdin);

            printf("Insira a Inscriá∆o Estadual do hotel: ");
            scanf("%[^\n]", hotel.inscricaoEstadual);
            fflush(stdin);

            printf("Insira o CNPJ do hotel: ");
            scanf("%[^\n]", hotel.CNPJ);
            fflush(stdin);

            printf("Insira o endereáo completo do hotel: ");
            scanf("%[^\n]", hotel.enderecoCompleto);
            fflush(stdin);

            printf("Insira o telefone do hotel: ");
            scanf("%[^\n]", hotel.telefone);
            fflush(stdin);

            printf("Insira o email do hotel: ");
            scanf("%[^\n]", hotel.email);
            fflush(stdin);

            printf("Insira o nome do respons†vel do hotel: ");
            scanf("%[^\n]", hotel.nomeResponsavel);
            fflush(stdin);

            printf("Insira o telefone do respons†vel do hotel: ");
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
            printf("Endereáo Completo       : %s\n", hotel.enderecoCompleto);
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
                printf("5  - Endereáo Completo       : %s\n", hotel.enderecoCompleto);
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
                    printf("Insira a nova Raz∆o Social: ");
                    scanf("%[^\n]", hotel.razaoSocial);
                    fflush(stdin);
                    break;
                case 3:
                    printf("Insira a nova Inscriá∆o Estadual do hotel: ");
                    scanf("%[^\n]", hotel.inscricaoEstadual);
                    fflush(stdin);
                    break;
                case 4:
                    printf("Insira o novo CNPJ do hotel: ");
                    scanf("%[^\n]", hotel.CNPJ);
                    fflush(stdin);
                    break;
                case 5:
                    printf("Insira o novo endereáo completo do hotel: ");
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
                    printf("Insira o novo nome do respons†vel do hotel: ");
                    scanf("%[^\n]", hotel.nomeResponsavel);
                    fflush(stdin);
                    break;
                case 9:
                    printf("Insira o novo telefone do respons†vel do hotel: ");
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
                    printf("Opá∆o inv†lida!\n");
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
            if (res != 0)
            {
                printf("Opá∆o inv†lida!\n");
                system("pause");
            }
            else{
                if(modo == BIN){
                    
                    if(salvarDadosHotelBin(*dadosHotel, HotelBIN) == 1)
                    {
                        printf("Erro ao salvar dados em formato bin†rio! Os dados ser∆o mantidos da forma que estavam antes do inicio do sistema.\n");
                        system("pause");
                    }
                    else
                        apagaArquivo(HotelTXT);
                }
                if(modo == TXT)
                {
                    if(salvarDadosHotelTxt(*dadosHotel, HotelTXT) == 1)
                    {
                        printf("Erro ao salvar dados em formato texto! Os dados ser∆o mantidos da forma que estavam antes do inicio do sistema.\n");
                        system("pause");
                    }
                    else
                        apagaArquivo(HotelBIN);
                }
            }
            break;
        }
    }while (res != 0);
    return;
}
