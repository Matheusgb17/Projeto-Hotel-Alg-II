#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../bib/estadias.h"
#include "../bib/utils.h"

#define BIN 1
#define TXT 2
#define MEM 3

// essas 2 funcoes ficam assim por enquanto
float obterTotalConsumoHospede(int idHospede) { return 150.50; }
void registrarRecebimentoCaixa(float valor) { return; }

ListaEstadia *iniciaListaEstadia()
{
    ListaEstadia *lista = malloc(sizeof(ListaEstadia));
    if (lista)
    {
        lista->estadia.id = 0;
        lista->prox = NULL;
    }
    return lista;
}

int escolheIdEstadia(ListaEstadia *lista)
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

int inserirEstadia(ListaEstadia **lista, TipoEstadia estadia)
{
    ListaEstadia *aux, *novaEstadia = malloc(sizeof(ListaEstadia));

    if (novaEstadia)
    {
        aux = *lista;
        novaEstadia->estadia = estadia;
        novaEstadia->prox = NULL;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novaEstadia;
        return 0;
    }
    return 1;
}

int buscarEstadia(ListaEstadia **lista, TipoEstadia *estadia, int id, ListaEstadia **pos)
{

    if (lista == NULL || *lista == NULL)
        return 1;

    ListaEstadia *aux = (*lista)->prox;

    while (aux != NULL)
    {
        if (aux->estadia.id == id)
        {
            if (estadia != NULL)
            {
                *estadia = aux->estadia;
            }

            if (pos != NULL)
            {
                *pos = aux;
            }
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

int calcularDiferencaDias(char *dataInicio, char *dataFim)
{
    int diaI, mesI, anoI, diaF, mesF, anoF;
    sscanf(dataInicio, "%d/%d/%d", &diaI, &mesI, &anoI);
    sscanf(dataFim, "%d/%d/%d", &diaF, &mesF, &anoF);

    struct tm tm_i = {0}, tm_f = {0};
    tm_i.tm_mday = diaI;
    tm_i.tm_mon = mesI - 1;
    tm_i.tm_year = anoI - 1900;
    tm_f.tm_mday = diaF;
    tm_f.tm_mon = mesF - 1;
    tm_f.tm_year = anoF - 1900;

    int dias = difftime(mktime(&tm_f), mktime(&tm_i)) / (60 * 60 * 24);
    return (dias <= 0) ? 1 : dias;
}

void alterarEstadia(ListaEstadia *pos, TipoEstadia estadia)
{
    pos->estadia = estadia;
}

void apagarEstadia(ListaEstadia *pos)
{
    pos->estadia.id = 0;
}

void listarEstadias(ListaEstadia *lista)
{
    if (lista->prox == NULL)
    {
        exibeMensagemAviso("Nenhuma estadia cadastrada.");
    }
    else
    {
        lista = lista->prox;
        while (lista != NULL)
        {
            if (lista->estadia.id != 0)
            {
                imprimeDadosEstadia(lista->estadia);
            }
            lista = lista->prox;
        }
    }
}

int salvarDadosEstadiasTxt(ListaEstadia *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL)
    {
        exibeMensagemErro("Erro ao abrir o arquivo!");
        pausarTela();
        return 1;
    }

    if (lista->prox != NULL)
    {
        ListaEstadia *aux = lista->prox;

        fprintf(arquivo, "<tabela=>estadias>\n");
        while (aux != NULL)
        {
            fprintf(arquivo, "    <registro>\n");
            fprintf(arquivo, "        <codigo>%d</codigo>\n", aux->estadia.id);
            fprintf(arquivo, "        <codigo_acomodacao>%d</codigo_acomodacao>\n", aux->estadia.idAcomodacao);
            fprintf(arquivo, "        <cpf_hospede>%s</cpf_hospede>\n", aux->estadia.cpfHospede);
            fprintf(arquivo, "        <codigo_reserva>%d</codigo_reserva>\n", aux->estadia.idReserva);
            fprintf(arquivo, "        <data_checkin>%s</data_checkin>\n", aux->estadia.dataCheckIn);
            fprintf(arquivo, "        <data_checkout_planejado>%s</data_checkout_planejado>\n", aux->estadia.dataCheckOutPlanejado);
            fprintf(arquivo, "        <data_saida_real>%s</data_saida_real>\n", aux->estadia.dataSaidaReal);
            fprintf(arquivo, "        <valor_total_pago>%.2f</valor_total_pago>\n", aux->estadia.valorTotalPago);
            fprintf(arquivo, "        <status>%d</status>\n", aux->estadia.status);
            fprintf(arquivo, "    </registro>\n");
            aux = aux->prox;
        }
        fprintf(arquivo, "</tabela>\n");
    }
    fclose(arquivo);
    return 0;
}

int salvarDadosEstadiasBin(ListaEstadia *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");

    if (arquivo == NULL)
    {
        exibeMensagemErro("Erro ao abrir o arquivo!");
        pausarTela();
        return 1;
    }

    ListaEstadia *aux = lista->prox;

    while (aux != NULL)
    {
        if (aux->estadia.id != 0)
        {
            fwrite(&aux->estadia, sizeof(TipoEstadia), 1, arquivo);
        }
        aux = aux->prox;
    }
    fclose(arquivo);
    return 0;
}

ListaEstadia *carregarEstadiasBin(char *nome_arquivo)
{
    TipoEstadia estadia;
    ListaEstadia *lista = iniciaListaEstadia();
    int res = 0;

    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL)
        return lista;

    while (fread(&estadia, sizeof(TipoEstadia), 1, arquivo))
        res = inserirEstadia(&lista, estadia);

    if (res == 1)
        exibeMensagemErro("Erro ao carregar estadias do arquivo binario!");

    fclose(arquivo);
    return lista;
}

ListaEstadia *carregarEstadiasTxt(char *nome_arquivo)
{
    ListaEstadia *lista = iniciaListaEstadia();
    TipoEstadia estadia;

    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL)
        return lista;

    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(&estadia, 0, sizeof(TipoEstadia));
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            inserirEstadia(&lista, estadia);
            continue;
        }

        sscanf(linha, " <codigo>%d", &estadia.id);
        sscanf(linha, " <codigo_acomodacao>%d", &estadia.idAcomodacao);
        sscanf(linha, " <cpf_hospede>%[^<]", estadia.cpfHospede);
        sscanf(linha, " <codigo_reserva>%d", &estadia.idReserva);
        sscanf(linha, " <data_checkin>%[^<]", estadia.dataCheckIn);
        sscanf(linha, " <data_checkout_planejado>%[^<]", estadia.dataCheckOutPlanejado);
        sscanf(linha, " <data_saida_real>%[^<]", estadia.dataSaidaReal);
        sscanf(linha, " <valor_total_pago>%f", &estadia.valorTotalPago);
        sscanf(linha, " <status>%d", &estadia.status);
    }
    fclose(arquivo);
    return lista;
}

void liberaListaEstadias(ListaEstadia *lista)
{
    ListaEstadia *temp, *aux = lista;
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }
    return;
}

void imprimeDadosEstadia(TipoEstadia estadia)
{
    printf("Id da estadia           : %d\n", estadia.id);
    printf("Id da acomodacao        : %d\n", estadia.idAcomodacao);
    printf("CPF do hospede          : %s\n", estadia.cpfHospede);
    printf("Id da reserva           : %d\n", estadia.idReserva);
    printf("Data de check-in        : %s\n", estadia.dataCheckIn);
    printf("Data de saida planejada : %s\n", estadia.dataCheckOutPlanejado);
    printf("-----------------------------------\n");
    return;
}



void interfaceEstadias(ListaEstadia *listaEstad, ListaHospede *listaHospede, ListaAcomodacao *listaAcomod, ListaCategoria *listaCat, ListaReservas *listaReservas)
{
    ListaEstadia *pos;
    ListaReservas *posReserva;
    ListaHospede *posHospede;

    TipoEstadia estadia;
    TipoReserva reservaAux;
    TipoHospede hospedeAux;
    int res = 0;
    int subRes = 0;

    TipoAcomodacao acomodAux;
    TipoCategoria catAux;
    int idBusca, dias, opcaoPagamento;
    float valorDiariasTotal, consumoFrigobar, saldoDevedor;

    // gestao de estadias
    do
    {
        limparTela();
        printf("--- Gestao de Estadias ---\n");
        printf("1 - Efetuar check-in\n");
        printf("2 - Efetuar check-out\n");
        printf("3 - Buscar estadia\n");
        printf("4 - Alterar dados da estadia\n");
        printf("5 - Apagar estadia\n");
        printf("6 - Listar estadias\n");
        printf("0 - Sair\n");
        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);
        limparTela();

        switch (res)
        {
        case 1: // ----------------- INSERIR ESTADIA (CHECK-IN) -----------------
            if(listaReservas->prox == NULL || listaReservas->prox == 0)
            {
                printf("Nenhuma reserva cadastrada no sistema! Nao e possivel fazer Check-in.\n");
                pausarTela();
                break;
            }

            while (1)
            {
                limparTela();
                printf("--- EFETUAR CHECK-IN ---\n\n");
                printf("-----------------------------------\n");
                printf("Reservas Cadastradas no Sistema:\n");
                printf("-----------------------------------\n");

                listarReservas(listaReservas);

                printf("\nEscolha o ID da reserva para efetuar o Check-in:\n");
                printf("=> ID da Reserva: ");
                scanf("%d", &estadia.idReserva);
                fflush(stdin);

                if (buscarReserva(&listaReservas, &reservaAux, estadia.idReserva, &posReserva) == 0)
                {
                    // Verifica se o quarto ja possui uma estadia ativa
                    int quartoOcupado = 0;
                    ListaEstadia *auxE = listaEstad->prox;
                    while (auxE != NULL)
                    {
                        if (auxE->estadia.idAcomodacao == reservaAux.idAcomodacao &&
                            auxE->estadia.status == 1)
                        {
                            quartoOcupado = 1;
                            break;
                        }
                        auxE = auxE->prox;
                    }

                    if (quartoOcupado)
                    {
                        printf("Erro: Acomodacao %d ja esta ocupada! Escolha outra reserva.\n",
                               reservaAux.idAcomodacao);
                        pausarTela();
                    }
                    else
                    {
                        limparTela();
                        break;
                    }
                }
                else
                {
                    printf("Erro: Reserva id %d nao encontrada! Tente novamente.\n", estadia.idReserva);
                    pausarTela();
                }
            }

            // preencher os campos da estadia a partir da reserva encontrada
            estadia.idAcomodacao = reservaAux.idAcomodacao;
            estadia.idHospede    = reservaAux.idHospede;
            estadia.status       = 1; // 1 = ativa

            // Percorre a lista de hospedes para achar o CPF pelo idHospede da reserva
            {
                ListaHospede *auxH = listaHospede->prox;
                memset(estadia.cpfHospede, 0, sizeof(estadia.cpfHospede));
                while (auxH != NULL)
                {
                    if (auxH->Hospedes.id == reservaAux.idHospede)
                    {
                        strcpy(estadia.cpfHospede, auxH->Hospedes.cpf);
                        break;
                    }
                    auxH = auxH->prox;
                }
            }

            // Converte as datas time_t da reserva para string DD/MM/AAAA
            {
                struct tm *tmPtr;
                tmPtr = localtime(&reservaAux.dataEntrada);
                strftime(estadia.dataCheckIn, sizeof(estadia.dataCheckIn), "%d/%m/%Y", tmPtr);
                tmPtr = localtime(&reservaAux.dataSaida);
                strftime(estadia.dataCheckOutPlanejado, sizeof(estadia.dataCheckOutPlanejado), "%d/%m/%Y", tmPtr);
            }
            memset(estadia.dataSaidaReal, 0, sizeof(estadia.dataSaidaReal));

            // calcular valorDiariasTotal antes de usar
            buscarAcomodacao(&listaAcomod, &acomodAux, estadia.idAcomodacao, NULL);
            buscarCategoria(&listaCat, &catAux, acomodAux.idCategoria, NULL);
            dias = calcularDiferencaDias(estadia.dataCheckIn, estadia.dataCheckOutPlanejado);
            valorDiariasTotal = dias * catAux.valorDiaria;

            printf("\nReserva %d localizada com sucesso!\n", estadia.idReserva);
            printf("Acomodacao: %d\n", estadia.idAcomodacao);
            printf("Diaria: R$ %.2f\n", catAux.valorDiaria);
            printf("Dias previstos: %d\n", dias);
            printf("Valor total das diarias: R$ %.2f\n\n", valorDiariasTotal);

            printf("Deseja realizar o pagamento das diarias agora no check-in?\n");
            printf("1 - Sim (pagar antecipado)\n");
            printf("2 - Nao (pagar no Check-out)\n");
            printf("=> ");
            scanf("%d", &opcaoPagamento);
            fflush(stdin);

            if (opcaoPagamento == 1)
            {
                estadia.valorTotalPago = valorDiariasTotal;
                registrarRecebimentoCaixa(valorDiariasTotal);
                printf("\n[CAIXA] Pagamento de R$ %.2f recebido!\n", valorDiariasTotal);
            }
            else
            {
                estadia.valorTotalPago = 0.0; // fica pendente para a saida
            }

            estadia.id = escolheIdEstadia(listaEstad);
            if (inserirEstadia(&listaEstad, estadia) == 0)
            {
                removerReserva(posReserva);
                printf("\nCheck-in realizado com sucesso! Id da Estadia: %d\n", estadia.id);
            }
            else
            {
                printf("\nErro ao alocar memoria para a estadia!\n");
            }
            pausarTela();
            break;

        case 2: // ----------------- EFETUAR CHECK-OUT -----------------
            printf("--- EFETUAR CHECK-OUT ---\n\n");
            printf("Insira o ID da estadia que deseja encerrar: ");
            scanf("%d", &idBusca);
            fflush(stdin);

            // Busca a estadia ativa pelo ID
            if (buscarEstadia(&listaEstad, &estadia, idBusca, &pos) == 0 && estadia.status == 1)
            {
                printf("\nDigite a data atual de Saida (DD/MM/AAAA): ");
                scanf("%10s", estadia.dataSaidaReal);
                fflush(stdin);

                // Recalcula os dias de estadia reais ate a data de hoje
                dias = calcularDiferencaDias(estadia.dataCheckIn, estadia.dataSaidaReal);

                buscarAcomodacao(&listaAcomod, &acomodAux, estadia.idAcomodacao, NULL);
                buscarCategoria(&listaCat, &catAux, acomodAux.idCategoria, NULL);

                float totalDiariasReais = dias * catAux.valorDiaria;
                consumoFrigobar = obterTotalConsumoHospede(estadia.id);
                saldoDevedor = consumoFrigobar;

                // Se ele escolheu nao pagar no check-in, cobra as diarias agora
                if (estadia.valorTotalPago == 0.0)
                {
                    saldoDevedor += totalDiariasReais;
                    estadia.valorTotalPago = totalDiariasReais;
                }

                estadia.status = 2;

                printf("\n=========================================\n");
                printf("            EXTRATO DE CHECK-OUT         \n");
                printf("=========================================\n");
                printf("Total de Dias Utilizados: %d\n", dias);
                printf("Custo total de Diarias  : R$ %.2f\n", totalDiariasReais);
                printf("Consumo Extra (Frigobar): R$ %.2f\n", consumoFrigobar);
                printf("-----------------------------------------\n");
                printf("VALOR TOTAL A PAGAR AGORA: R$ %.2f\n", saldoDevedor);
                printf("=========================================\n\n");

                if (saldoDevedor > 0)
                {
                    registrarRecebimentoCaixa(saldoDevedor);
                    printf("[CAIXA] Recebimento registrado com sucesso.\n");
                }

                alterarEstadia(pos, estadia);
                printf("\nCheck-out efetuado! Volte sempre.\n");
            }
            else
            {
                printf("\nEstadia ativa nao encontrada ou ja finalizada!\n");
            }
            pausarTela();
            break;

        case 3:
            limparTela();
            printf("Insira o id da estadia que deseja buscar: ");
            fflush(stdin);
            scanf("%d", &estadia.id);
            fflush(stdin);

            int achou = buscarEstadia(&listaEstad, &estadia, estadia.id, &pos);
            if (achou == 0)
            {
                limparTela();
                buscarReserva(&listaReservas, &reservaAux, estadia.idReserva, &posReserva);
                buscarHospede(&listaHospede, &hospedeAux, estadia.cpfHospede, &posHospede);
                printf("\nEstadia encontrada!! -------------\n");
                printf("ID da Estadia          : %d\n", estadia.id);
                printf("ID da Reserva          : %d\n", estadia.idReserva);
                printf("Nome do Hospede        : %s\n", hospedeAux.nome);
                printf("CPF do Hospede         : %s\n", estadia.cpfHospede);
                printf("Quarto Designado       : %d\n", estadia.idAcomodacao);
                printf("Data de Check-in       : %s\n", estadia.dataCheckIn);
                printf("Data Prevista de Saida : %s\n", estadia.dataCheckOutPlanejado);
                printf("Status da Estadia      : %s\n", estadia.status == 1 ? "Ativa (Ocupado)" : "Finalizada (Check-out feito)");
                printf("----------------------------------\n");
                pausarTela();
            }
            else
            {
                printf("\nEstadia nao encontrada!\n");
                pausarTela();
            }
            res = 1;
            break;

        case 4: // ----------------- ALTERAR ESTADIA -----------------
            printf("Digite o ID da estadia que deseja alterar: ");
            scanf("%d", &estadia.id);
            fflush(stdin);

            if (buscarEstadia(&listaEstad, &estadia, estadia.id, &pos) == 0)
            {
                subRes = 0;
                while (subRes != 5 && subRes != 6)
                {
                    limparTela();
                    printf("\nEstadia encontrada! -------------\n");
                    printf("Digite o campo que deseja alterar: \n\n");
                    printf("1 - ID da Acomodacao             : %d\n", estadia.idAcomodacao);
                    printf("2 - CPF do Hospede               : %s\n", estadia.cpfHospede);
                    printf("3 - Data de Check-In             : %s\n", estadia.dataCheckIn);
                    printf("4 - Check-Out Planejado          : %s\n", estadia.dataCheckOutPlanejado);

                    printf("5 - Salvar dados\n");
                    printf("6 - Cancelar\n");
                    printf("=> ");

                    scanf("%d", &subRes);
                    fflush(stdin);

                    switch (subRes)
                    {
                    case 1:
                        printf("Insira o novo ID da acomodacao: ");
                        scanf("%d", &estadia.idAcomodacao);
                        fflush(stdin);
                        break;
                    case 2:
                        printf("Insira o novo CPF do hospede: ");
                        scanf("%14s", estadia.cpfHospede);
                        fflush(stdin);
                        break;
                    case 3:
                        printf("Insira a nova data de Check-In: ");
                        scanf("%10s", estadia.dataCheckIn);
                        fflush(stdin);
                        break;
                    case 4:
                        printf("Insira a nova data de Check-Out Planejado: ");
                        scanf("%10s", estadia.dataCheckOutPlanejado);
                        fflush(stdin);
                        break;
                    case 5:
                        alterarEstadia(pos, estadia);
                        printf("Dados da estadia atualizados com sucesso!\n");
                        pausarTela();
                        break;
                    case 6:
                        printf("Alteracao cancelada.\n");
                        pausarTela();
                        break;
                    default:
                        printf("Escolha um valor valido...\n");
                        pausarTela();
                        break;
                    }
                }
            }
            else
            {
                printf("Estadia nao encontrada!\n");
                pausarTela();
            }
            break;

        case 5: // ----------------- APAGAR ESTADIA -----------------
            printf("Digite o ID da estadia que deseja apagar: ");
            scanf("%d", &estadia.id);
            fflush(stdin);

            if (buscarEstadia(&listaEstad, &estadia, estadia.id, &pos) == 0)
            {
                apagarEstadia(pos);
                printf("Estadia removida do historico!\n");
            }
            else
            {
                printf("Estadia nao encontrada!\n");
            }
            pausarTela();
            break;

        case 6: // ----------------- LISTAR ESTADIAS -----------------
            limparTela();
            printf("Estadias registradas:\n");
            listarEstadias(listaEstad);
            pausarTela();
            break;

        default:
            if (res != 0)
            {
                printf("Escolha um valor valido...\n");
                pausarTela();
            }
            break;
        }
    } while (res != 0);
}