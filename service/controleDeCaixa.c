#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../bib/contas.h"
#include "../bib/controleDeCaixa.h"
#include "../bib/utils.h"

#define ENTRADA 1
#define SAIDA 2

ListaHistoricoCaixa *iniciaListaHistoricoCaixa()
{
    ListaHistoricoCaixa *lista = malloc(sizeof(ListaHistoricoCaixa));
    if (lista != NULL)
    {
        lista->registro.tipo = 0;
        lista->registro.valor = 0.0;
        strcpy(lista->registro.descricao, "");
        lista->registro.data = 0;
        lista->prox = NULL;
    }
    return lista;
}

TipoHistoricoCaixa converterContaParaHistorico(TipoConta conta, int tipo)
{
    TipoHistoricoCaixa registro;
    registro.tipo = tipo;
    registro.valor = conta.valorParcela;
    snprintf(registro.descricao, sizeof(registro.descricao), "Conta %s - ID: %d", tipo == ENTRADA ? "Receber" : "Pagar", conta.id);
    registro.data = time(NULL);

    return registro;
}

int registrarEntradaCaixa(ListaHistoricoCaixa **lista, TipoHistoricoCaixa registro)
{
    registro.tipo = ENTRADA;
    ListaHistoricoCaixa *aux, *novoRegistro = malloc(sizeof(ListaHistoricoCaixa));
    if (novoRegistro != NULL)
    {
        aux = *lista;
        novoRegistro->registro = registro;
        novoRegistro->prox = NULL;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novoRegistro;
        return 0;
    }
    return 1;
}

int registrarSaidaCaixa(ListaHistoricoCaixa **lista, TipoHistoricoCaixa registro)
{
    registro.tipo = SAIDA;
    ListaHistoricoCaixa *aux, *novoRegistro = malloc(sizeof(ListaHistoricoCaixa));
    if (novoRegistro != NULL)
    {
        aux = *lista;
        novoRegistro->registro = registro;
        novoRegistro->prox = NULL;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novoRegistro;
        return 0;
    }
    return 1;
}

void imprimeMovimentacaoCaixa(TipoHistoricoCaixa registro)
{
    char dataStr[20];
    struct tm *dataInfo = localtime(&registro.data);
    strftime(dataStr, sizeof(dataStr), "%d/%m/%Y %H:%M:%S", dataInfo);

    printf("Tipo: %s\n", registro.tipo == ENTRADA ? "Entrada" : "Saida");
    printf("Valor: R$ %.2f\n", registro.valor);
    printf("Descricao: %s\n", registro.descricao);
    printf("Data: %s\n", dataStr);
    printf("-----------------------------------\n");
}

void imprimeHistoricoCaixa(ListaHistoricoCaixa *lista)
{
    if (lista->prox == NULL)
    {
        exibeMensagemAviso("Nenhuma movimentacao registrada no caixa.\n");
    }
    else
    {
        lista = lista->prox;

        while (lista != NULL)
        {
            if (lista->registro.tipo != 0)
            {
                imprimeMovimentacaoCaixa(lista->registro);
            }
            lista = lista->prox;
        }
    }
}

float exibirSaldoCaixa(ListaHistoricoCaixa *lista)
{
    float saldo = 0.0;
    if (lista->prox == NULL)
    {
        exibeMensagemAviso("Nenhuma movimentacao registrada no caixa.\n");
    }
    else
    {
        lista = lista->prox;

        while (lista != NULL)
        {
            if (lista->registro.tipo == ENTRADA)
            {
                saldo += lista->registro.valor;
            }
            else if (lista->registro.tipo == SAIDA)
            {
                saldo -= lista->registro.valor;
            }
            lista = lista->prox;
        }
        return saldo;
    }
}

ListaHistoricoCaixa *resgataDadosHistoricoCaixaBin(char *nome_arquivo)
{
    ListaHistoricoCaixa *lista = iniciaListaHistoricoCaixa();
    TipoHistoricoCaixa registro;
    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL)
        return lista;

    while (fread(&registro, sizeof(TipoHistoricoCaixa), 1, arquivo) == 1)
    {
        registrarEntradaCaixa(&lista, registro);
    }

    fclose(arquivo);
    return lista;
}

ListaHistoricoCaixa *resgataDadosHistoricoCaixaTxt(char *nome_arquivo)
{
    ListaHistoricoCaixa *lista = iniciaListaHistoricoCaixa();
    TipoHistoricoCaixa registro;

    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL)
        return lista;
        
    char linha[256];
    long long tempData;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(&registro, 0, sizeof(TipoHistoricoCaixa)); // Limpa a struct
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            registrarEntradaCaixa(&lista, registro);
            continue;
        }

        sscanf(linha, " <tipo>%d", &registro.tipo);
        sscanf(linha, " <valor>%f", &registro.valor);
        sscanf(linha, " <descricao>%[^<]", registro.descricao);

        if (sscanf(linha, " <data>%lld", &tempData) == 1)
        {
            registro.data = (time_t)tempData;
        }
    }
    fclose(arquivo);
    return lista;
}

void salvarDadosHistoricoCaixaBin(ListaHistoricoCaixa *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL)
        return;

    ListaHistoricoCaixa *aux = lista->prox;
    while (aux != NULL)
    {
        if (aux->registro.tipo != 0)
        {
            fwrite(&(aux->registro), sizeof(TipoHistoricoCaixa), 1, arquivo);
        }
        aux = aux->prox;
    }
    fclose(arquivo);
}

void salvarDadosHistoricoCaixaTxt(ListaHistoricoCaixa *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL){
        printf("\narq n achado!~\n\n");
        pausarTela();
        return;
    }

    ListaHistoricoCaixa *aux = lista->prox;
    if (aux != NULL)
    {
        fprintf(arquivo, "<tabela>\n");
        while (aux != NULL)
        {
            if (aux->registro.tipo != 0)
            {
                fprintf(arquivo, "    <registro>\n");
                fprintf(arquivo, "        <tipo>%d</tipo>\n", aux->registro.tipo);
                fprintf(arquivo, "        <valor>%.2f</valor>\n", aux->registro.valor);
                fprintf(arquivo, "        <descricao>%s</descricao>\n", aux->registro.descricao);
                fprintf(arquivo, "        <data>%lld</data>\n", (long long)aux->registro.data);
                fprintf(arquivo, "    </registro>\n");
            }
            aux = aux->prox;
        }
        fprintf(arquivo, "</tabela>\n");
    }
    fclose(arquivo);
}

void liberaListaHistoricoCaixa(ListaHistoricoCaixa *lista)
{
    ListaHistoricoCaixa *aux = lista;
    while (aux != NULL)
    {
        ListaHistoricoCaixa *temp = aux;
        aux = aux->prox;
        free(temp);
    }
}

void interfaceControleDeCaixa(ListaHistoricoCaixa *historicoCaixa)
{
    int res = 0, op;
    TipoHistoricoCaixa movimentacao;

    do
    {
        limparTela();
        printf("--- Controle de Caixa ---\n");
        printf("1 - Registrar Recebimento\n");
        printf("2 - Registrar Pagamento\n");
        printf("3 - Exibir Extrato de Movimentacoes\n");
        printf("4 - Exibir Saldo Atual do Caixa\n");
        printf("0 - Voltar ao Menu Principal\n");

        printf("=> ");
        scanf("%d", &res);

        switch (res)
        {
        case 1:
            printf("\nValor recebido (R$): ");
            scanf("%f", &movimentacao.valor);
            fflush(stdin);

            if (movimentacao.valor == 0)
            {
                printf("Operacao cancelada.\n");
                pausarTela();
                continue;
            }

            printf("Descricao do recebimento: ");
            scanf(" %[^\n]", movimentacao.descricao);
            fflush(stdin);

            movimentacao.data = time(NULL);
            op = registrarEntradaCaixa(&historicoCaixa, movimentacao);
            if (op == 0)
            {
                printf("\nRecebimento registrado com sucesso!\n");
            }
            else
            {
                exibeMensagemAviso("Erro ao registrar recebimento!\n");
            }
            pausarTela();

            break;
        case 2:
            // Logica para registrar saida
            printf("\nValor da sangria (R$0.00): R$");
            scanf("%f", &movimentacao.valor);
            fflush(stdin);

            printf("Descricao da sangria: ");
            scanf(" %[^\n]", movimentacao.descricao);
            fflush(stdin);

            movimentacao.data = time(NULL);
            op = registrarSaidaCaixa(&historicoCaixa, movimentacao);
            if (op == 0)
            {
                printf("\nSangria registrada com sucesso!\n");
            }
            else
            {
                exibeMensagemAviso("Erro ao registrar sangria!\n");
            }
            pausarTela();
            break;
        case 3:
            imprimeHistoricoCaixa(historicoCaixa);
            pausarTela();
            break;
        case 4:
            printf("\nSaldo atual do caixa: R$ %.2f\n", exibirSaldoCaixa(historicoCaixa));
            pausarTela();
            break;
        default:
            if (res != 0)
            {
                exibeMensagemAviso("Opcao invalida! Tente novamente.\n");
                pausarTela();
            }
            break;
        }
    } while (res != 0);
}