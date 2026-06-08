#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PAGO 1
#define PENDENTE 0

#include "../bib/contas.h"
#include "../bib/controleDeCaixa.h"
#include "../bib/utils.h"

ListaContas *iniciaListaContas()
{
    ListaContas *lista = malloc(sizeof(ListaContas));
    if (lista != NULL)
    {
        lista->conta.id = 0;
        lista->prox = NULL;
    }
    return lista;
}

int escolheIdConta(ListaContas *lista)
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

int inserirConta(ListaContas **lista, TipoConta conta)
{
    ListaContas *aux, *nova = malloc(sizeof(ListaContas));
    if (nova != NULL)
    {
        aux = *lista;
        nova->conta = conta;
        nova->prox = NULL;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = nova;
        return 0;
    }
    return 1;
}

int buscarConta(ListaContas **lista, TipoConta *conta, int idBusca, ListaContas **pos)
{
    ListaContas *aux = (*lista)->prox;
    while (aux != NULL)
    {
        if (aux->conta.id == idBusca)
        {
            *conta = aux->conta;
            *pos = aux;
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

void alterarConta(TipoConta novaConta, ListaContas **pos)
{
    (*pos)->conta = novaConta;
}

void apagarConta(ListaContas **pos)
{
    (*pos)->conta.id = 0;
}

void imprimeConta(TipoConta conta)
{
    printf("Id                    : %d\n", conta.id);
    printf("Id da Nota            : %d\n", conta.idNota);
    printf("Valor da Parcela      : %.2f\n", conta.valorParcela);
    printf("Numero da Parcela     : %d\n", conta.numeroParcela);
    printf("Data de vencimento    : %s\n", conta.dataVencimento);
    printf("Status de pagamento   : %s\n", conta.statusPago == PAGO ? "Pago" : "Pendente");
    printf("-----------------------------------\n");
}

void imprimeContas(ListaContas *lista)
{
    if (lista->prox == NULL)
    {
        exibeMensagemAviso("Nenhuma conta cadastrada.\n");
    }
    else
    {
        lista = lista->prox;

        while (lista != NULL)
        {
            if (lista->conta.id != 0)
            {
                imprimeConta(lista->conta);
            }
            lista = lista->prox;
        }
    }
}

int salvarDadosContasTxt(ListaContas *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL)
        return 1;

    if (lista->prox != NULL)
    {
        ListaContas *aux = lista->prox;
        fprintf(arquivo, "<tabela=contas>\n");
        while (aux != NULL)
        {
            if (aux->conta.id != 0)
            {
                fprintf(arquivo, "    <registro>\n");
                fprintf(arquivo, "        <codigo>%d</codigo>\n", aux->conta.id);
                fprintf(arquivo, "        <idNota>%d</idNota>\n", aux->conta.idNota);
                fprintf(arquivo, "        <valorParcela>%.2f</valorParcela>\n", aux->conta.valorParcela);
                fprintf(arquivo, "        <numeroParcela>%d</numeroParcela>\n", aux->conta.numeroParcela);
                fprintf(arquivo, "        <dataVencimento>%s</dataVencimento>\n", aux->conta.dataVencimento);
                fprintf(arquivo, "        <statusPago>%d</statusPago>\n", aux->conta.statusPago);
                fprintf(arquivo, "    </registro>\n");
            }
            aux = aux->prox;
        }
        fprintf(arquivo, "</tabela>\n");
    }
    fclose(arquivo);
    return 0;
}

ListaContas *resgataDadosContasTxt(char *nome_arquivo)
{
    ListaContas *lista = iniciaListaContas();
    TipoConta conta;

    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL)
        return lista;

    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(&conta, 0, sizeof(TipoConta));
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            inserirConta(&lista, conta);
            continue;
        }

        sscanf(linha, " <codigo>%d", &conta.id);
        sscanf(linha, " <idNota>%d", &conta.idNota);
        sscanf(linha, " <valorParcela>%f", &conta.valorParcela);
        sscanf(linha, " <numeroParcela>%d", &conta.numeroParcela);
        sscanf(linha, " <dataVencimento>%10s", conta.dataVencimento);
        sscanf(linha, " <statusPago>%d", &conta.statusPago);
    }
    fclose(arquivo);
    return lista;
}

int salvarDadosContasBin(ListaContas *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL)
        return 1;

    ListaContas *aux = lista->prox;
    while (aux != NULL)
    {
        if (aux->conta.id != 0)
        {
            fwrite(&(aux->conta), sizeof(TipoConta), 1, arquivo);
        }
        aux = aux->prox;
    }
    fclose(arquivo);
    return 0;
}

ListaContas *resgataDadosContasBin(char *nome_arquivo)
{
    ListaContas *lista = iniciaListaContas();
    TipoConta conta;
    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL)
        return lista;

    while (fread(&conta, sizeof(TipoConta), 1, arquivo))
    {
        inserirConta(&lista, conta);
    }
    fclose(arquivo);
    return lista;
}

int inserirContaPagar(ListaContas **listaAPagar, TipoConta conta)
{
    conta.statusPago = PENDENTE;
    return inserirConta(listaAPagar, conta);
}

void baixarContaPagar(ListaContas **pos, TipoConta conta, ListaHistoricoCaixa **historicoCaixa)
{
    conta.statusPago = PAGO;
    alterarConta(conta, pos);
    registrarSaidaCaixa(historicoCaixa, converterContaParaHistorico(conta, SAIDA));
    return;
}

void listarContasPagarPendentes(ListaContas *lista)
{
    if (lista->prox == NULL)
    {
        exibeMensagemAviso("Nenhuma conta a pagar cadastrada.\n");
    }
    else
    {
        lista = lista->prox;

        while (lista != NULL)
        {
            if (lista->conta.id != 0 && lista->conta.statusPago == PENDENTE)
            {
                imprimeConta(lista->conta);
            }
            lista = lista->prox;
        }
    }
}

void listarContasPagarPagas(ListaContas *lista)
{
    if (lista->prox == NULL)
    {
        exibeMensagemAviso("Nenhuma conta a pagar cadastrada.\n");
    }
    else
    {
        lista = lista->prox;

        while (lista != NULL)
        {
            if (lista->conta.id != 0 && lista->conta.statusPago == PAGO)
            {
                imprimeConta(lista->conta);
            }
            lista = lista->prox;
        }
    }
}

int inserirContaReceber(ListaContas **listaAReceber, TipoConta conta)
{
    conta.statusPago = PENDENTE;
    return inserirConta(listaAReceber, conta);
}

void baixarContaReceber(ListaContas **pos, TipoConta conta, ListaHistoricoCaixa **historicoCaixa)
{
    conta.statusPago = PAGO;
    alterarConta(conta, pos);
    registrarEntradaCaixa(historicoCaixa, converterContaParaHistorico(conta, ENTRADA));
    return;
}

void listarContasReceberPendentes(ListaContas *lista)
{
    if (lista->prox == NULL)
    {
        exibeMensagemAviso("Nenhuma conta a receber cadastrada.\n");
    }
    else
    {
        lista = lista->prox;

        while (lista != NULL)
        {
            if (lista->conta.id != 0 && lista->conta.statusPago == PENDENTE)
            {
                imprimeConta(lista->conta);
            }
            lista = lista->prox;
        }
    }
}

void listarContasReceberPagas(ListaContas *lista)
{
    if (lista->prox == NULL)
    {
        exibeMensagemAviso("Nenhuma conta a receber cadastrada.\n");
    }
    else
    {
        lista = lista->prox;

        while (lista != NULL)
        {
            if (lista->conta.id != 0 && lista->conta.statusPago == PAGO)
            {
                imprimeConta(lista->conta);
            }
            lista = lista->prox;
        }
    }
}

void liberaListaContas(ListaContas *lista)
{
    ListaContas *aux = lista;
    while (aux != NULL)
    {
        ListaContas *temp = aux;
        aux = aux->prox;
        free(temp);
    }
}

void interfaceContasPagar(ListaContas **listaContasPagar, ListaHistoricoCaixa **historicoCaixa)
{
    int res = 0, idBusca;
    TipoConta conta;
    ListaContas *pos;
    TipoHistoricoCaixa movimentacao;

    do
    {
        limparTela();
        printf("=== Contas a Pagar ===\n");
        printf("1 - Inserir nova conta a pagar\n");
        printf("2 - Baixar conta a pagar (Pagar)\n");
        printf("3 - Listar contas pendentes\n");
        printf("4 - Listar historico de contas pagas\n");
        printf("5 - Alterar dados da conta\n");
        printf("6 - Excluir conta\n");
        printf("0 - Voltar ao menu principal\n");
        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);

        switch (res)
        {
        case 1:
            conta.id = escolheIdConta(*listaContasPagar);

            printf("\nID da Nota: ");
            scanf("%d", &conta.idNota);
            fflush(stdin);

            printf("Valor da Parcela (R$): ");
            scanf("%f", &conta.valorParcela);
            fflush(stdin);

            printf("Numero da Parcela: ");
            scanf("%d", &conta.numeroParcela);
            fflush(stdin);

            printf("Data de Vencimento (DD/MM/AAAA): ");
            scanf(" %10[^\n]", conta.dataVencimento);
            fflush(stdin);

            if (inserirContaPagar(listaContasPagar, conta) == 0)
                printf("\nConta registrada! ID gerado: %d\n", conta.id);
            else
                printf("\nErro ao alocar memoria para a conta.\n");

            pausarTela();
            break;

        case 2:
            printf("\nDigite o ID da conta que deseja pagar: ");
            scanf("%d", &idBusca);
            fflush(stdin);

            if (buscarConta(listaContasPagar, &conta, idBusca, &pos) == 0)
            {
                if (conta.statusPago == PENDENTE)
                {
                    baixarContaPagar(&pos, conta, historicoCaixa);
                    movimentacao.valor = conta.valorParcela;
                    sprintf(movimentacao.descricao, "Pagamento ref. Conta Pagar ID %d - Parcela %d", conta.id, conta.numeroParcela);
                    movimentacao.data = time(NULL);
                    registrarSaidaCaixa(historicoCaixa, movimentacao);

                    printf("\nConta %d baixada e saida de caixa registrada com sucesso!\n", conta.id);
                }
                else
                {
                    printf("\nEsta conta ja consta como PAGA no sistema.\n");
                }
            }
            else
            {
                printf("\nConta nao localizada.\n");
            }
            pausarTela();
            break;

        case 3:
            printf("\n--- Contas a Pagar (PENDENTES) ---\n");
            listarContasPagarPendentes(*listaContasPagar);
            pausarTela();
            break;

        case 4:
            printf("\n--- Historico de Contas Pagas ---\n");
            listarContasPagarPagas(*listaContasPagar);
            pausarTela();
            break;

        case 5:
            printf("\nDigite o ID da conta para alterar: ");
            scanf("%d", &idBusca);
            fflush(stdin);
            if (buscarConta(listaContasPagar, &conta, idBusca, &pos) == 0)
            {
                printf("Novo ID da Nota: ");
                scanf("%d", &conta.idNota);
                fflush(stdin);

                printf("Novo Valor da Parcela (R$): ");
                scanf("%f", &conta.valorParcela);
                fflush(stdin);

                printf("Novo Numero da Parcela: ");
                scanf("%d", &conta.numeroParcela);
                fflush(stdin);

                printf("Nova Data de Vencimento (DD/MM/AAAA): ");
                scanf(" %10[^\n]", conta.dataVencimento);
                fflush(stdin);

                alterarConta(conta, &pos);
                printf("\nDados atualizados!\n");
            }
            else
            {
                printf("\nConta nao localizada.\n");
            }
            pausarTela();
            break;

        case 6:
            printf("\nDigite o ID da conta para EXCLUIR: ");
            scanf("%d", &idBusca);
            fflush(stdin);
            if (buscarConta(listaContasPagar, &conta, idBusca, &pos) == 0)
            {
                apagarConta(&pos);
                printf("\nConta excluida logicamente do sistema.\n");
            }
            else
            {
                printf("\nConta nao localizada.\n");
            }
            pausarTela();
            break;
        }
    } while (res != 0);
}

void interfaceContasReceber(ListaContas **listaContasReceber, ListaHistoricoCaixa **historicoCaixa)
{
    int res = 0, idBusca;
    TipoConta conta;
    ListaContas *pos;
    TipoHistoricoCaixa movimentacao;

    do
    {
        limparTela();
        printf("=== Contas a Receber ===\n");
        printf("1 - Lancar conta a receber (Cartao/Prazo)\n");
        printf("2 - Baixar conta a receber (Confirmar recebimento)\n");
        printf("3 - Listar contas pendentes\n");
        printf("4 - Listar historico de contas recebidas\n");
        printf("5 - Alterar dados da conta\n");
        printf("6 - Excluir conta\n");
        printf("0 - Voltar ao menu principal\n");
        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);

        switch (res)
        {
        case 1:
            conta.id = escolheIdConta(*listaContasReceber);

            printf("\nID da Nota: ");
            scanf("%d", &conta.idNota);
            fflush(stdin);

            printf("Valor da Parcela (R$): ");
            scanf("%f", &conta.valorParcela);
            fflush(stdin);

            printf("Numero da Parcela: ");
            scanf("%d", &conta.numeroParcela);
            fflush(stdin);

            printf("Data de Vencimento (DD/MM/AAAA): ");
            scanf(" %10[^\n]", conta.dataVencimento);
            fflush(stdin);

            if (inserirContaReceber(listaContasReceber, conta) == 0)
                printf("\nLancamento registrado! ID gerado: %d\n", conta.id);
            else
                printf("\nErro ao alocar memoria.\n");

            pausarTela();
            break;

        case 2:
            printf("\nDigite o ID da conta recebida: ");
            scanf("%d", &idBusca);
            fflush(stdin);

            if (buscarConta(listaContasReceber, &conta, idBusca, &pos) == 0)
            {
                if (conta.statusPago == PENDENTE)
                {
                    baixarContaReceber(&pos, conta, historicoCaixa); // Passa o histórico aqui
                    printf("\nConta %d baixada e entrada de caixa registrada com sucesso!\n", conta.id);
                }
                else
                {
                    printf("\nEsta conta ja consta como RECEBIDA.\n");
                }
            }
            else
            {
                printf("\nConta nao localizada.\n");
            }
            pausarTela();
            break;

        case 3:
            printf("\n--- Contas a Receber (PENDENTES) ---\n");
            listarContasReceberPendentes(*listaContasReceber);
            pausarTela();
            break;

        case 4:
            printf("\n--- Historico de Contas Recebidas ---\n");
            listarContasReceberPagas(*listaContasReceber);
            pausarTela();
            break;

        case 5:
            printf("\nDigite o ID da conta para alterar: ");
            scanf("%d", &idBusca);
            fflush(stdin);
            if (buscarConta(listaContasReceber, &conta, idBusca, &pos) == 0)
            {
                printf("Novo ID da Nota: ");
                scanf("%d", &conta.idNota);
                fflush(stdin);

                printf("Novo Valor da Parcela (R$): ");
                scanf("%f", &conta.valorParcela);
                fflush(stdin);

                printf("Novo Numero da Parcela: ");
                scanf("%d", &conta.numeroParcela);
                fflush(stdin);

                printf("Nova Data de Vencimento (DD/MM/AAAA): ");
                scanf(" %10[^\n]", conta.dataVencimento);
                fflush(stdin);

                alterarConta(conta, &pos);
                printf("\nDados atualizados!\n");
            }
            else
            {
                printf("\nConta nao localizada.\n");
            }
            pausarTela();
            break;

        case 6:
            printf("\nDigite o ID da conta para EXCLUIR: ");
            scanf("%d", &idBusca);
            fflush(stdin);
            if (buscarConta(listaContasReceber, &conta, idBusca, &pos) == 0)
            {
                apagarConta(&pos);
                printf("\nConta excluida logicamente.\n");
            }
            else
            {
                printf("\nConta nao localizada.\n");
            }
            pausarTela();
            break;
        }
    } while (res != 0);
}