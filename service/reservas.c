#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "../bib/acomodacoes.h"
#include "../bib/categorias.h"
#include "../bib/hospedes.h"
#include "../bib/reservas.h"
#include "../bib/utils.h"

#include <stdio.h>
#include <time.h>

int escolheIdReserva(ListaReservas *lista)
{
    int cont = 0;
    lista = lista->prox;

    while (lista != NULL)
    {
        cont++;
        lista = lista->prox;
    }

    return cont + 1;
}

int adicionarReserva(ListaReservas **lista, TipoReserva novaReserva)
{
    // garantir que n�o havera sombreamento de reservas
    ListaReservas *aux, *novo = malloc(sizeof(ListaReservas));
    if (novo)
    {
        novo->reserva = novaReserva;
        novo->prox = NULL;

        aux = *lista;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
        return 0;
    }
    return 1;
}

void listarAcomodacoesParaReserva(ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaReservas *listaRes, FiltroBusca filtro)
{
    // 1. DECLARA��O DE TODAS AS VARI�VEIS NO IN�CIO
    ListaAcomodacao *auxAcom;
    TipoCategoria categoriaTemp;
    ListaCategoria *posCat; // Vari�vel para receber a posi��o da categoria na busca
    int encontrouAlgum;
    int conflito;
    ListaReservas *auxRes;

    // 2. INICIALIZA��O
    auxAcom = listaAcom->prox;
    encontrouAlgum = 0;

    printf("\n================ ACOMODACOES DISPONIVEIS ================\n");
    printf("Analise as opcoes abaixo e anote o ID desejado para reserva.\n\n");

    while (auxAcom != NULL)
    {
        // Resgata a categoria
        buscarCategoria(&listaCat, &categoriaTemp, auxAcom->acomodacao.idCategoria, &posCat);

        // Filtro de Categoria
        if (filtro.idCategoria != 0 && auxAcom->acomodacao.idCategoria != filtro.idCategoria)
        {
            auxAcom = auxAcom->prox;
            continue;
        }

        // Filtro de Capacidade (qtd de pessoas)
        if (filtro.qtdAdultos > 0 || filtro.qtdCriancas > 0)
        {
            if (categoriaTemp.capacidadeAdultos < filtro.qtdAdultos ||
                categoriaTemp.capacidadeCriancas < filtro.qtdCriancas)
            {
                auxAcom = auxAcom->prox;
                continue;
            }
        }

        conflito = 0;
        auxRes = listaRes->prox;

        // Filtro de Datas (Evitar Sombreamento)
        while (auxRes != NULL)
        {
            if (auxRes->reserva.idAcomodacao == auxAcom->acomodacao.id)
            {
                if (filtro.dataEntrada < auxRes->reserva.dataSaida &&
                    filtro.dataSaida > auxRes->reserva.dataEntrada)
                {
                    conflito = 1;
                    break;
                }
            }
            auxRes = auxRes->prox;
        }

        if (conflito == 1)
        {
            auxAcom = auxAcom->prox;
            continue;
        }

        // Exibi��o detalhada para o operador com os dados mesclados
        printf("ID                  : %d\n", auxAcom->acomodacao.id);
        printf("Descricao           : %s\n", auxAcom->acomodacao.descricao);
        printf("Facilidades         : %s\n", auxAcom->acomodacao.facilidades);
        printf("Categoria           : %s\n", categoriaTemp.descricao);
        printf("Valor diaria        : R$ %.2f\n", categoriaTemp.valorDiaria);
        printf("Capacidade adultos  : %d\n", categoriaTemp.capacidadeAdultos);
        printf("Capacidade criancas : %d\n", categoriaTemp.capacidadeCriancas);
        printf("---------------------------------------------------------\n");

        encontrouAlgum = 1;
        auxAcom = auxAcom->prox;
    }

    if (encontrouAlgum == 0)
    {
        printf("Nenhuma acomodacao atende aos criterios essenciais nestas datas.\n");
    }
    printf("=========================================================\n");
}

void removerReserva(ListaReservas *pos)
{
    pos->reserva.id = 0;
}

int buscarReserva(ListaReservas **lista, TipoReserva *reserva, int idReserva, ListaReservas **pos)
{
    ListaReservas *aux = (*lista)->prox;
    while (aux != NULL)
    {
        if (aux->reserva.id == idReserva)
        {
            *reserva = aux->reserva;
            *pos = aux;
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

void listarReservas(ListaReservas *lista)
{
    lista = lista->prox;
    while (lista)
    {
        if(lista->reserva.id == 0) {
            lista = lista->prox;
            continue;
        }
        
        printf("ID               : %d\n", lista->reserva.id);
        printf("ID do H�spede    : %d\n", lista->reserva.idHospede);
        printf("ID da Acomoda��o : %d\n", lista->reserva.idAcomodacao);
        printf("Data de Entrada  : %s", ctime(&lista->reserva.dataEntrada));
        printf("Data de Sa�da    : %s", ctime(&lista->reserva.dataSaida));
        printf("-----------------------------\n");
        lista = lista->prox;
    }

    system("pause");
    return;
}

void listarReservasPorAcomodacao(ListaReservas *lista, int idAcomodacao)
{
    ListaReservas *aux = lista->prox;
    int encontrou = 0;

    while (aux != NULL)
    {
        if (aux->reserva.idAcomodacao == idAcomodacao)
        {
            printf("ID               : %d\n", aux->reserva.id);
            printf("ID do H�spede    : %d\n", aux->reserva.idHospede);
            printf("ID da Acomoda��o : %d\n", aux->reserva.idAcomodacao);
            printf("Data de Entrada  : %s", ctime(&aux->reserva.dataEntrada));
            printf("Data de Sa�da    : %s", ctime(&aux->reserva.dataSaida));
            printf("-----------------------------\n");
            encontrou = 1;
        }
        aux = aux->prox;
    }

    if (!encontrou)
    {
        printf("Nenhuma reserva encontrada para a acomoda��o ID %d.\n", idAcomodacao);
    }

    system("pause");
    return;
}

void listarReservasPorHospede(ListaReservas *lista, int idHospede)
{
    ListaReservas *aux = lista->prox;
    int encontrou = 0;

    while (aux != NULL)
    {
        if (aux->reserva.idHospede == idHospede)
        {
            printf("ID               : %d\n", aux->reserva.id);
            printf("ID do H�spede    : %d\n", aux->reserva.idHospede);
            printf("ID da Acomoda��o : %d\n", aux->reserva.idAcomodacao);
            printf("Data de Entrada  : %s\n", ctime(&aux->reserva.dataEntrada));
            printf("Data de Sa�da    : %s\n", ctime(&aux->reserva.dataSaida));
            printf("-----------------------------\n");
            encontrou = 1;
        }
        aux = aux->prox;
    }

    if (!encontrou)
    {
        printf("Nenhuma reserva encontrada para o h�spede ID %d.\n", idHospede);
    }

    system("pause");
    return;
}

ListaReservas *iniciaListaReservas()
{
    ListaReservas *Lista;

    Lista = malloc(sizeof(ListaReservas));
    Lista->reserva.id = 0;
    Lista->prox = NULL;

    return Lista;
}

int salvarDadosReservasBin(ListaReservas *lista, char *nome_arquivo)
{
    FILE *arquivo;
    ListaReservas *aux;

    arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL)
    {
        return 1;
    }

    aux = lista->prox;
    while (aux != NULL)
    {
        if (aux->reserva.id != 0)
        {
            fwrite(&(aux->reserva), sizeof(TipoReserva), 1, arquivo);
        }
        aux = aux->prox;
    }

    fclose(arquivo);
    return 0;
}

ListaReservas *resgataDadosReservasBin(char *nome_arquivo)
{
    TipoReserva reserva;
    ListaReservas *lista;
    FILE *arquivo;
    int res;

    lista = iniciaListaReservas();
    arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL)
        return lista;

    while (fread(&reserva, sizeof(TipoReserva), 1, arquivo) == 1)
    {
        res = adicionarReserva(&lista, reserva);
    }

    if (res == 1)
        printf("Erro ao carregar reservas do arquivo binario!\n");

    fclose(arquivo);
    return lista;
}

int salvarDadosReservasTxt(ListaReservas *lista, char *nome_arquivo)
{
    FILE *arquivo;
    ListaReservas *aux;

    arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL)
    {
        return 1;
    }

    if (lista->prox != NULL)
    {
        aux = lista->prox;

        fprintf(arquivo, "<tabela=reservas>\n");
        while (aux != NULL)
        {
            if (aux->reserva.id != 0)
            {
                fprintf(arquivo, "    <registro>\n");
                fprintf(arquivo, "        <codigo>%d</codigo>\n", aux->reserva.id);
                fprintf(arquivo, "        <idHospede>%d</idHospede>\n", aux->reserva.idHospede);
                fprintf(arquivo, "        <idAcomodacao>%d</idAcomodacao>\n", aux->reserva.idAcomodacao);
                fprintf(arquivo, "        <dataEntrada>%lld</dataEntrada>\n", (long long)aux->reserva.dataEntrada);
                fprintf(arquivo, "        <dataSaida>%lld</dataSaida>\n", (long long)aux->reserva.dataSaida);
                fprintf(arquivo, "    </registro>\n");
            }
            aux = aux->prox;
        }
        fprintf(arquivo, "</tabela>\n");
    }
    fclose(arquivo);
    return 0;
}

ListaReservas *resgataDadosReservasTxt(char *nome_arquivo)
{
    ListaReservas *lista;
    TipoReserva reserva;
    FILE *arquivo;
    char linha[256];
    long long tempEntrada;
    long long tempSaida;

    lista = iniciaListaReservas();
    arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL)
        return lista;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(&reserva, 0, sizeof(TipoReserva));
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            adicionarReserva(&lista, reserva);
            continue;
        }

        sscanf(linha, " <codigo>%d", &reserva.id);
        sscanf(linha, " <idHospede>%d", &reserva.idHospede);
        sscanf(linha, " <idAcomodacao>%d", &reserva.idAcomodacao);

        // L� como long long e converte de volta para o formato de tempo nativo do C
        if (sscanf(linha, " <dataEntrada>%lld", &tempEntrada) == 1)
        {
            reserva.dataEntrada = (time_t)tempEntrada;
        }

        if (sscanf(linha, " <dataSaida>%lld", &tempSaida) == 1)
        {
            reserva.dataSaida = (time_t)tempSaida;
        }
    }
    fclose(arquivo);

    return lista;
}

void liberaListaReservas(ListaReservas *lista)
{
    ListaReservas *temp, *aux = lista;
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }
}

void interfaceReservas(ListaReservas *listaRes, ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaHospede *listaHospedes)
{
    TipoReserva reservaBusca;
    TipoReserva novaReserva;
    ListaReservas *pos;
    FiltroBusca filtro;
    TipoHospede hospedeTemp;
    ListaHospede *posHospede;

    struct tm dataEntrada_tm;
    struct tm dataSaida_tm;

    int res;
    int dia, mes, ano;
    int idEscolhido, idHospede, idBusca;

    res = 0;
    memset(&dataEntrada_tm, 0, sizeof(struct tm));
    memset(&dataSaida_tm, 0, sizeof(struct tm));

    do
    {
        system("cls");
        printf("\nM�dulo de Reservas ---\n");
        printf("1 - Adicionar reserva (Com Busca)\n");
        printf("2 - Cancelar reserva\n");
        printf("3 - Listar reservas\n");
        printf("4 - Filtrar Acomoda��es Dispon�veis\n");
        printf("5 - Verificar reservas por acomoda��o\n");
        printf("6 - Verificar reservas por h�spede\n");
        printf("0 - Sair\n");
        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);

        switch (res)
        {
        case 1: // ADICIONAR RESERVA (FILTROS DE BUSCA)
            system("cls");
            printf("--- Nova Reserva: Filtros de Busca ---\n\n");
            // Coleta Data de Entrada
            printf("Data de Entrada (DD/MM/AAAA): ");
            scanf("%d/%d/%d", &dia, &mes, &ano);
            fflush(stdin);
            dataEntrada_tm.tm_mday = dia;
            dataEntrada_tm.tm_mon = mes - 1;
            dataEntrada_tm.tm_year = ano - 1900;
            filtro.dataEntrada = mktime(&dataEntrada_tm);

            // Coleta Data de Sa�da
            printf("Data de Saida (DD/MM/AAAA): ");
            scanf("%d/%d/%d", &dia, &mes, &ano);
            fflush(stdin);
            dataSaida_tm.tm_mday = dia;
            dataSaida_tm.tm_mon = mes - 1;
            dataSaida_tm.tm_year = ano - 1900;
            filtro.dataSaida = mktime(&dataSaida_tm);

            // Coleta Filtros Opcionais
            printf("ID da Categoria desejada (0 para ignorar): \n");
            listarCategorias(listaCat);
            printf("ID da Categoria: ");
            scanf("%d", &filtro.idCategoria);
            fflush(stdin);

            printf("Quantidade de Adultos (0 para ignorar): ");
            scanf("%d", &filtro.qtdAdultos);
            fflush(stdin);

            printf("Quantidade de Criancas (0 para ignorar): ");
            scanf("%d", &filtro.qtdCriancas);
            fflush(stdin);

            system("cls");
            listarAcomodacoesParaReserva(listaAcom, listaCat, listaRes, filtro);

            printf("\nDigite o ID do quarto escolhido: ");
            scanf("%d", &idEscolhido);
            fflush(stdin);

            if (idEscolhido == 0)
            {
                printf("Operacao cancelada.\n");
                system("pause");
                break;
            }

            while (1)
            {
                printf("Digite o CPF do Hospede vinculado a reserva: ");
                scanf("%s", hospedeTemp.cpf);
                fflush(stdin);

                if (buscarHospede(&listaHospedes, &hospedeTemp, hospedeTemp.cpf, &posHospede) == 0)
                {
                    idHospede = hospedeTemp.id;
                    break;
                }
                else
                {
                    printf("Hospede nao encontrado, tente novamente.\n");
                    system("pause");
                }
            }

            novaReserva.id = escolheIdReserva(listaRes); // Chama a fun��o para gerar ID incremental
            novaReserva.idHospede = idHospede;
            novaReserva.idAcomodacao = idEscolhido;
            novaReserva.dataEntrada = filtro.dataEntrada;
            novaReserva.dataSaida = filtro.dataSaida;

            printf("\nHospede da reserva: %s\n", hospedeTemp.nome);
            printf("CPF: %s\n", hospedeTemp.cpf);

            res = adicionarReserva(&listaRes, novaReserva);
            if (res == 0)
            {
                printf("\nReserva cadastrada com sucesso! ID: %d\n", novaReserva.id);
            }
            else
            {
                printf("\nErro ao cadastrar reserva!\n");
            }
            res = 1;
            system("pause");
            break;
        case 2: // CANCELAR RESERVA
            printf("\nDigite o ID da reserva que deseja cancelar: ");
            scanf("%d", &idBusca);
            fflush(stdin);

            if (buscarReserva(&listaRes, &reservaBusca, idBusca, &pos) == 0)
            {
                removerReserva(pos);
                printf("Reserva ID %d removida com sucesso!\n", idBusca);
                system("pause");
            }
            else
            {
                printf("Reserva nao encontrada!\n");
                system("pause");
            }
            break;
        case 3: // LISTAR RESERVAS
            system("cls");
            printf("--- Lista de Reservas Ativas ---\n\n");
            listarReservas(listaRes);
            break;
        case 4:
            system("cls");
            printf("--- Filtro de Acomoda��es Dispon�veis ---\n\n");

            // Coleta Data de Entrada
            printf("Data de Entrada (DD/MM/AAAA): ");
            scanf("%d/%d/%d", &dia, &mes, &ano);
            fflush(stdin);
            dataEntrada_tm.tm_mday = dia;
            dataEntrada_tm.tm_mon = mes - 1;
            dataEntrada_tm.tm_year = ano - 1900;
            filtro.dataEntrada = mktime(&dataEntrada_tm);

            // Coleta Data de Sa�da
            printf("Data de Saida (DD/MM/AAAA): ");
            scanf("%d/%d/%d", &dia, &mes, &ano);
            fflush(stdin);
            dataSaida_tm.tm_mday = dia;
            dataSaida_tm.tm_mon = mes - 1;
            dataSaida_tm.tm_year = ano - 1900;
            filtro.dataSaida = mktime(&dataSaida_tm);

            // Coleta Filtros Opcionais
            printf("ID da Categoria desejada (0 para ignorar): \n");
            listarCategorias(listaCat);
            printf("ID da Categoria: ");
            scanf("%d", &filtro.idCategoria);
            fflush(stdin);

            printf("Quantidade de Adultos (0 para ignorar): ");
            scanf("%d", &filtro.qtdAdultos);
            fflush(stdin);

            printf("Quantidade de Criancas (0 para ignorar): ");
            scanf("%d", &filtro.qtdCriancas);
            fflush(stdin);

            system("cls");
            listarAcomodacoesParaReserva(listaAcom, listaCat, listaRes, filtro);
            system("pause");
            break;
        case 5:
            printf("Digite o ID da acomodacao para listar as reservas vinculadas a ela: ");
            scanf("%d", &idBusca);
            fflush(stdin);
            system("cls");
            printf("--- Reservas para Acomoda��o ID %d ---\n\n", idBusca);
            listarReservasPorAcomodacao(listaRes, idBusca);
            break;
        case 6:
            printf("Digite o cpf do h�spede para listar suas reservas: ");
            scanf("%s", hospedeTemp.cpf);
            fflush(stdin);

            if (buscarHospede(&listaHospedes, &hospedeTemp, hospedeTemp.cpf, &posHospede) == 0)
            {
                idBusca = hospedeTemp.id;

                system("cls");
                printf("--- Reservas para H�spede ID %d ---\n\n", idBusca);
                listarReservasPorHospede(listaRes, idBusca);
            }
            else
            {
                printf("H�spede n�o encontrado!\n");
                system("pause");
            }
            break;
        default:
            if (res != 0)
            {
                printf("Escolha uma opcao valida!\n");
                system("pause");
            }
            break;
        }

    } while (res != 0);
}