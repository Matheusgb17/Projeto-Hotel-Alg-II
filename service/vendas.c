#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "../bib/vendas.h"
#include "../bib/produtos.h"
#include "../bib/hospedes.h"
#include "utils.h"
// #include "../bib/caixa.h"


ListaVendas *iniciaListaVendas()
{
    ListaVendas *lista = malloc(sizeof(ListaVendas));
    if (lista != NULL) {
        lista->venda.id = 0;
        lista->prox = NULL;
    }
    return lista;
}

int escolheIdVenda(ListaVendas *lista)
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

int inserirVenda(ListaVendas **lista, TipoVenda venda)
{
    ListaVendas *aux, *novaVenda = malloc(sizeof(ListaVendas));
    if (novaVenda != NULL)
    {
        aux = *lista;
        novaVenda->venda = venda;
        novaVenda->prox = NULL;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novaVenda;
        return 0;
    }
    return 1;
}

void gerarReciboVenda(TipoVenda venda, TipoHospede hospede, ListaProduto *listaProdutos)
{
    char nomeArquivo[100];
    sprintf(nomeArquivo, "recibo_consumo_venda_%d.txt", venda.id);

    FILE *f = fopen(nomeArquivo, "w");
    if (f == NULL)
    {
        exibeMensagemErro("Erro ao gerar recibo fisico.");
        return;
    }

    fprintf(f, "========================================================\n");
    fprintf(f, "              MARISMAR PLAZA - NOTA DE CONSUMO          \n");
    fprintf(f, "========================================================\n");
    fprintf(f, "Venda ID: %d\n", venda.id);
    fprintf(f, "Hospede : %s\n", hospede.nome);
    fprintf(f, "CPF     : %s\n", hospede.cpf);
    fprintf(f, "Data    : %s", ctime(&venda.dataVenda));
    fprintf(f, "--------------------------------------------------------\n");
    fprintf(f, "QTD  | DESCRICAO DO PRODUTO        | V. UN   | SUBTOTAL \n");
    fprintf(f, "--------------------------------------------------------\n");

    TipoProduto prodTemp;
    ListaProduto *posProd;

    for (int i = 0; i < venda.qtdItens; i++)
    {
        buscarProduto(&listaProdutos, &prodTemp, venda.itens[i].idProduto, &posProd);
        float subtotal = venda.itens[i].quantidade * venda.itens[i].valorUnitario;
        fprintf(f, "%-4d | %-27s | R$%-5.2f | R$%.2f\n",
                venda.itens[i].quantidade,
                prodTemp.descricao,
                venda.itens[i].valorUnitario,
                subtotal);
    }

    fprintf(f, "--------------------------------------------------------\n");
    fprintf(f, "TOTAL A PAGAR NA CONTA: R$ %.2f\n", venda.valorTotal);
    fprintf(f, "========================================================\n\n\n");
    fprintf(f, "      ____________________________________________\n");
    fprintf(f, "                Assinatura do Hospede\n");

    fclose(f);
    exibeMensagemSucesso("Recibo gerado com suceeso!");
}

int salvarDadosVendasBin(ListaVendas *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) return 1;

    ListaVendas *aux = lista->prox;
    while (aux != NULL)
    {
        if (aux->venda.id != 0)
        {
            fwrite(&(aux->venda), sizeof(TipoVenda), 1, arquivo);
        }
        aux = aux->prox;
    }
    fclose(arquivo);
    return 0;
}

ListaVendas *resgataDadosVendasBin(char *nome_arquivo)
{
    TipoVenda venda;
    ListaVendas *lista = iniciaListaVendas();
    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL) return lista;

    while (fread(&venda, sizeof(TipoVenda), 1, arquivo) == 1)
    {
        inserirVenda(&lista, venda);
    }

    fclose(arquivo);
    return lista;
}

int salvarDadosVendasTxt(ListaVendas *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) return 1;

    if (lista->prox != NULL)
    {
        ListaVendas *aux = lista->prox;
        fprintf(arquivo, "<tabela=vendas>\n");
        while (aux != NULL)
        {
            if (aux->venda.id != 0)
            {
                fprintf(arquivo, "    <registro>\n");
                fprintf(arquivo, "        <codigo>%d</codigo>\n", aux->venda.id);
                fprintf(arquivo, "        <idHospede>%d</idHospede>\n", aux->venda.idHospede);
                fprintf(arquivo, "        <formaPagamento>%d</formaPagamento>\n", aux->venda.formaPagamento);
                fprintf(arquivo, "        <statusPagamento>%d</statusPagamento>\n", aux->venda.statusPagamento);
                fprintf(arquivo, "        <qtdItens>%d</qtdItens>\n", aux->venda.qtdItens);
                fprintf(arquivo, "        <valorTotal>%.2f</valorTotal>\n", aux->venda.valorTotal);
                fprintf(arquivo, "        <dataVenda>%lld</dataVenda>\n", (long long)aux->venda.dataVenda);

                // Salvar os itens do vetor
                for(int i = 0; i < aux->venda.qtdItens; i++) {
                    fprintf(arquivo, "        <item_%d_id>%d</item_%d_id>\n", i, aux->venda.itens[i].idProduto, i);
                    fprintf(arquivo, "        <item_%d_qtd>%d</item_%d_qtd>\n", i, aux->venda.itens[i].quantidade, i);
                    fprintf(arquivo, "        <item_%d_val>%.2f</item_%d_val>\n", i, aux->venda.itens[i].valorUnitario, i);
                }
                fprintf(arquivo, "    </registro>\n");
            }
            aux = aux->prox;
        }
        fprintf(arquivo, "</tabela>\n");
    }
    fclose(arquivo);
    return 0;
}

ListaVendas *resgataDadosVendasTxt(char *nome_arquivo)
{
    ListaVendas *lista = iniciaListaVendas();
    TipoVenda venda;
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) return lista;

    char linha[256];
    long long tempData;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(&venda, 0, sizeof(TipoVenda));
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            inserirVenda(&lista, venda);
            continue;
        }

        sscanf(linha, " <codigo>%d", &venda.id);
        sscanf(linha, " <idHospede>%d", &venda.idHospede);
        sscanf(linha, " <formaPagamento>%d", &venda.formaPagamento);
        sscanf(linha, " <statusPagamento>%d", &venda.statusPagamento);
        sscanf(linha, " <qtdItens>%d", &venda.qtdItens);
        sscanf(linha, " <valorTotal>%f", &venda.valorTotal);

        if (sscanf(linha, " <dataVenda>%lld", &tempData) == 1) {
            venda.dataVenda = (time_t)tempData;
        }

        for(int i = 0; i < 50; i++) {
            char tagId[30], tagQtd[30], tagVal[30];
            sprintf(tagId, " <item_%d_id>%%d", i);
            sprintf(tagQtd, " <item_%d_qtd>%%d", i);
            sprintf(tagVal, " <item_%d_val>%%f", i);

            sscanf(linha, tagId, &venda.itens[i].idProduto);
            sscanf(linha, tagQtd, &venda.itens[i].quantidade);
            sscanf(linha, tagVal, &venda.itens[i].valorUnitario);
        }
    }
    fclose(arquivo);
    return lista;
}

void interfaceVendas(ListaVendas *listaVendas, ListaProduto *listaProdutos, ListaHospede *listaHospedes)
{
    int res = 0;

    do
    {
        system("cls");
        printf("--- Saida de Produtos ---\n");
        printf("1 - Nova Venda\n");
        printf("0 - Voltar\n");
        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);

        if (res == 1)
        {
            TipoVenda novaVenda;
            novaVenda.id = escolheIdVenda(listaVendas);
            novaVenda.qtdItens = 0;
            novaVenda.valorTotal = 0.0;
            novaVenda.dataVenda = time(NULL);

            int continuar = 1;

            //carrinho
            while (continuar == 1 && novaVenda.qtdItens < 50)
            {
                system("cls");
                printf("--- CARRINHO DE COMPRAS (Total Parcial: R$ %.2f) ---\n\n", novaVenda.valorTotal);
                listarProdutos(listaProdutos);

                int idBusca, qtdDesejada;
                printf("\nDigite o ID do produto desejado: ");
                scanf("%d", &idBusca);
                fflush(stdin);

                TipoProduto produtoSelecionado;
                ListaProduto *posProduto;

                if (buscarProduto(&listaProdutos, &produtoSelecionado, idBusca, &posProduto) == 0)
                {
                    printf("\nProduto selecionado: %s\nEstoque atual: %d | Preco Unit.: R$ %.2f\n",
                           produtoSelecionado.descricao, produtoSelecionado.estoque, produtoSelecionado.preco_venda);

                    printf("Digite a quantidade desejada: ");
                    scanf("%d", &qtdDesejada);
                    fflush(stdin);

                    if (qtdDesejada <= 0) {
                        printf("\nQuantidade invalida.\n");
                    }
                    else if (qtdDesejada > produtoSelecionado.estoque)
                    {
                        printf("\nEstoque insuficiente para esta operacao!\n");
                    }
                    else
                    {
                        //salta item no carrinho
                        novaVenda.itens[novaVenda.qtdItens].idProduto = produtoSelecionado.id;
                        novaVenda.itens[novaVenda.qtdItens].quantidade = qtdDesejada;
                        novaVenda.itens[novaVenda.qtdItens].valorUnitario = produtoSelecionado.preco_venda;

                        novaVenda.valorTotal += (produtoSelecionado.preco_venda * qtdDesejada);
                        novaVenda.qtdItens++;

                        printf("\nProduto adicionado ao carrinho com sucesso!\n");
                    }
                }
                else
                {
                    printf("\nProduto nao encontrado!\n");
                }

                printf("\nDeseja adicionar mais produtos a esta venda?\n1 - Sim\n2 - Nao\n=> ");
                scanf("%d", &continuar);
                fflush(stdin);
            }

            //fechamento da venda
            if (novaVenda.qtdItens > 0)
            {
                system("cls");
                printf("--- FINALIZAR VENDA ---\n");
                printf("Total a pagar: R$ %.2f\n\n", novaVenda.valorTotal);
                printf("Forma de Pagamento:\n");
                printf("1 - A vista\n");
                printf("2 - Para anotar\n");
                printf("=> ");
                scanf("%d", &novaVenda.formaPagamento);
                fflush(stdin);

                int vendaConfirmada = 0;

                if (novaVenda.formaPagamento == 1)
                {
                    //Pagamento a vista
                    novaVenda.idHospede = 0;
                    novaVenda.statusPagamento = 1;

                    //MATHEUS KKK AQUI:
                    // registrarEntradaCaixa(novaVenda.valorTotal);
                    //n precisa ser esse nome de função, botei so um exemplo

                    printf("\nPagamento a vista confirmado! O valor foi enviado ao Caixa.\n");
                    vendaConfirmada = 1;
                }
                else if (novaVenda.formaPagamento == 2)
                {
                    //Pagamento anotado:
                    TipoHospede hospedeTemp;
                    ListaHospede *posHospede;

                    while (1)
                    {
                        printf("\nDigite o CPF do hospede para faturar a conta: ");
                        scanf(" %s", hospedeTemp.cpf);
                        fflush(stdin);

                        if (buscarHospede(&listaHospedes, &hospedeTemp, hospedeTemp.cpf, &posHospede) == 0)
                        {
                            novaVenda.idHospede = hospedeTemp.id;
                            novaVenda.statusPagamento = 0;

                            gerarReciboVenda(novaVenda, hospedeTemp, listaProdutos);
                            vendaConfirmada = 1;
                            break;
                        }
                        else
                        {
                            printf("Hospede nao encontrado! Deseja tentar novamente?\n1 - Sim\n2 - Cancelar Venda\n=> ");
                            int tentaDnv;
                            scanf("%d", &tentaDnv);
                            fflush(stdin);
                            if (tentaDnv != 1) break;
                        }
                    }
                }
                else {
                    printf("\nOpcao de pagamento invalida. Venda cancelada.\n");
                }

                //conclui a venda e desconta do estoque so se confirmada
                if (vendaConfirmada) {
                    TipoProduto prodAtualiza;
                    ListaProduto *posProdAtualiza;

                    for (int i = 0; i < novaVenda.qtdItens; i++)
                    {
                        if (buscarProduto(&listaProdutos, &prodAtualiza, novaVenda.itens[i].idProduto, &posProdAtualiza) == 0) {
                            prodAtualiza.estoque -= novaVenda.itens[i].quantidade;
                            alterarProduto(posProdAtualiza, prodAtualiza);
                        }
                    }

                    inserirVenda(&listaVendas, novaVenda);
                    printf("\nVenda concluida com sucesso! Estoques atualizados.\n");
                }
                system("pause");
            }
            else
            {
                printf("\nVenda cancelada. Nenhum item validado no carrinho.\n");
                system("pause");
            }
        }
    } while (res != 0);
}