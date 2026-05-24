#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "../bib/compras.h"
#include "../bib/produtos.h"
#include "../bib/fornecedores.h"
#include "../bib/hotel.h"
#include "utils.h"
// #include "../bib/caixa.h"


ListaNotasFiscais *iniciaListaNotasFiscais() {
    ListaNotasFiscais *lista = malloc(sizeof(ListaNotasFiscais));

    if(lista != NULL) {
        lista->nota.id = 0;
        lista->prox = NULL;
    }
    return lista;
}

int escolheIdNota(ListaNotasFiscais *lista) {
    int cont = 0;
    lista = lista->prox;

    while (lista != NULL) {
        cont++;
        lista = lista->prox;
    }
    return cont + 1;
}

int inserirNotaFiscal(ListaNotasFiscais **lista, TipoNotaFiscal nota) {
    ListaNotasFiscais *aux, *nova = malloc(sizeof(ListaNotasFiscais));
    if (nova != NULL) {
        aux = *lista;
        nova->nota = nota;
        nova->prox = NULL;
        while (aux->prox != NULL) aux = aux->prox;
        aux->prox = nova;
        return 0;
    }
    return 1;
}

ListaContasPagar *iniciaListaContasPagar() {
    ListaContasPagar *lista = malloc(sizeof(ListaContasPagar));
    if(lista != NULL) {
        lista->conta.id = 0;
        lista->prox = NULL;
    }
    return lista;
}

int escolheIdContaPagar(ListaContasPagar *lista) {
    int cont = 0;
    lista = lista->prox;
    while (lista != NULL) {
        cont++;
        lista = lista->prox;
    }
    return cont + 1;
}

int inserirContaPagar(ListaContasPagar **lista, TipoContaPagar conta) {
    ListaContasPagar *aux, *nova = malloc(sizeof(ListaContasPagar));
    if (nova != NULL) {
        aux = *lista;
        nova->conta = conta;
        nova->prox = NULL;
        while (aux->prox != NULL) aux = aux->prox;
        aux->prox = nova;
        return 0;
    }
    return 1;
}


int salvarDadosNotasBin(ListaNotasFiscais *lista, char *nome_arquivo) {

    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) return 1;

    ListaNotasFiscais *aux = lista->prox;
    while (aux != NULL) {
        if (aux->nota.id != 0)
        {
            fwrite(&(aux->nota), sizeof(TipoNotaFiscal), 1, arquivo);
        }
        aux = aux->prox;
    }
    fclose(arquivo);
    return 0;
}

ListaNotasFiscais *resgataDadosNotasBin(char *nome_arquivo)
{
    TipoNotaFiscal nota;
    ListaNotasFiscais *lista = iniciaListaNotasFiscais();
    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL) return lista;

    while (fread(&nota, sizeof(TipoNotaFiscal), 1, arquivo) == 1)
    {
        inserirNotaFiscal(&lista, nota);
    }

    fclose(arquivo);
    return lista;
}

int salvarDadosContasPagarBin(ListaContasPagar *lista, char *nome_arquivo) {

    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo ==  NULL) return 1;

    ListaContasPagar *aux = lista->prox;
    while (aux != NULL) {
        if (aux->conta.id != 0) fwrite(&(aux->conta), sizeof(TipoContaPagar), 1, arquivo);
        aux = aux->prox;
    }

    fclose(arquivo);
    return 0;
}

ListaContasPagar *resgataDadosContasPagarBin(char *nome_arquivo) {

    TipoContaPagar conta;
    ListaContasPagar *lista = iniciaListaContasPagar();
    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL) return lista;

    while (fread(&conta, sizeof(TipoContaPagar), 1, arquivo) == 1)
    {
        inserirContaPagar(&lista, conta);
    }

    fclose(arquivo);
    return lista;
}

int salvarDadosNotasTxt(ListaNotasFiscais *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) return 1;

    if (lista->prox != NULL)
    {
        ListaNotasFiscais *aux = lista->prox;
        fprintf(arquivo, "<tabela=notas_fiscais>\n");
        while (aux != NULL)
        {
            if (aux->nota.id != 0)
            {
                fprintf(arquivo, "    <registro>\n");
                fprintf(arquivo, "        <codigo>%d</codigo>\n", aux->nota.id);
                fprintf(arquivo, "        <cnpjFornecedor>%s</cnpjFornecedor>\n", aux->nota.cnpjFornecedor);
                fprintf(arquivo, "        <freteTotal>%.2f</freteTotal>\n", aux->nota.freteTotal);
                fprintf(arquivo, "        <impostoTotal>%.2f</impostoTotal>\n", aux->nota.impostoTotal);
                fprintf(arquivo, "        <quantidadeTotalUnidades>%d</quantidadeTotalUnidades>\n", aux->nota.quantidadeTotalUnidades);
                fprintf(arquivo, "        <valorTotalNota>%.2f</valorTotalNota>\n", aux->nota.valorTotalNota);
                fprintf(arquivo, "        <qtdItensDiferentes>%d</qtdItensDiferentes>\n", aux->nota.qtdItensDiferentes);
                fprintf(arquivo, "        <dataEmissao>%lld</dataEmissao>\n", (long long)aux->nota.dataEmissao);

                // Salvar os itens do vetor de compras da nota
                for(int i = 0; i < aux->nota.qtdItensDiferentes; i++) {
                    fprintf(arquivo, "        <item_%d_id>%d</item_%d_id>\n", i, aux->nota.itens[i].idProduto, i);
                    fprintf(arquivo, "        <item_%d_qtd>%d</item_%d_qtd>\n", i, aux->nota.itens[i].quantidade, i);
                    fprintf(arquivo, "        <item_%d_custo>%.2f</item_%d_custo>\n", i, aux->nota.itens[i].precoCusto, i);
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

ListaNotasFiscais *resgataDadosNotasTxt(char *nome_arquivo)
{
    ListaNotasFiscais *lista = iniciaListaNotasFiscais();
    TipoNotaFiscal nota;
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) return lista;

    char linha[256];
    long long tempData;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(&nota, 0, sizeof(TipoNotaFiscal)); // Limpa a struct
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            inserirNotaFiscal(&lista, nota);
            continue;
        }

        sscanf(linha, " <codigo>%d", &nota.id);
        sscanf(linha, " <cnpjFornecedor>%[^<]", nota.cnpjFornecedor);
        sscanf(linha, " <freteTotal>%f", &nota.freteTotal);
        sscanf(linha, " <impostoTotal>%f", &nota.impostoTotal);
        sscanf(linha, " <quantidadeTotalUnidades>%d", &nota.quantidadeTotalUnidades);
        sscanf(linha, " <valorTotalNota>%f", &nota.valorTotalNota);
        sscanf(linha, " <qtdItensDiferentes>%d", &nota.qtdItensDiferentes);

        if (sscanf(linha, " <dataEmissao>%lld", &tempData) == 1) {
            nota.dataEmissao = (time_t)tempData;
        }

        for(int i = 0; i < 50; i++) {
            char tagId[30], tagQtd[30], tagCusto[30];
            sprintf(tagId, " <item_%d_id>%%d", i);
            sprintf(tagQtd, " <item_%d_qtd>%%d", i);
            sprintf(tagCusto, " <item_%d_custo>%%f", i);

            sscanf(linha, tagId, &nota.itens[i].idProduto);
            sscanf(linha, tagQtd, &nota.itens[i].quantidade);
            sscanf(linha, tagCusto, &nota.itens[i].precoCusto);
        }
    }
    fclose(arquivo);
    return lista;
}

int salvarDadosContasPagarTxt(ListaContasPagar *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) return 1;

    if (lista->prox != NULL)
    {
        ListaContasPagar *aux = lista->prox;
        fprintf(arquivo, "<tabela=contas_pagar>\n");
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

ListaContasPagar *resgataDadosContasPagarTxt(char *nome_arquivo)
{
    ListaContasPagar *lista = iniciaListaContasPagar();
    TipoContaPagar conta;
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) return lista;

    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(&conta, 0, sizeof(TipoContaPagar));
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            inserirContaPagar(&lista, conta);
            continue;
        }

        sscanf(linha, " <codigo>%d", &conta.id);
        sscanf(linha, " <idNota>%d", &conta.idNota);
        sscanf(linha, " <valorParcela>%f", &conta.valorParcela);
        sscanf(linha, " <numeroParcela>%d", &conta.numeroParcela);
        sscanf(linha, " <dataVencimento>%[^<]", conta.dataVencimento); // %[^<] pega a string toda ate a tag fechar
        sscanf(linha, " <statusPago>%d", &conta.statusPago);
    }
    fclose(arquivo);
    return lista;
}
void interfaceCompras(ListaNotasFiscais *listaNotas, ListaContasPagar *listaContas, ListaProduto *listaProdutos, ListaFornecedor *listaFornecedores, TipoHotel *dadosHotel) {
    int res = 0;

    do {
        system("cls");
        printf("--- Entrada de Produtos Industrializados ---\n");
        printf("1 - Lancar Nova Nota Fiscal de Entrada\n");
        printf("2 - Listar Contas a Pagar (Pendentes)\n");
        printf("0 - Voltar\n");
        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);

        if (res == 1) {
            TipoNotaFiscal nota;
            nota.id = escolheIdNota(listaNotas);
            nota.quantidadeTotalUnidades = 0;
            nota.valorTotalNota = 0.0;
            nota.qtdItensDiferentes = 0;
            nota.dataEmissao = time(NULL);

            TipoFornecedor fornecedorTemp;
            ListaFornecedor *posFornecedor;

            //dados da nota e do fornecedor
            while(1) {
                system("cls");
                printf("Digite o CNPJ do Fornecedor da Nota: ");
                scanf(" %[^\n]", nota.cnpjFornecedor);
                fflush(stdin);

                if (buscarFornecedor(&listaFornecedores, &fornecedorTemp, nota.cnpjFornecedor, &posFornecedor) == 0) {
                    printf("Fornecedor selecionado: %s\n", fornecedorTemp.nome_fantasia);
                    break;
                } else {
                    printf("Fornecedor nao encontrado! Deseja tentar novamente?\n1 - Sim\n2 - Cancelar Lancamento\n=> ");
                    int t; scanf("%d", &t); fflush(stdin);
                    if (t != 1) return;
                }
            }

            printf("\nValor total do FRETE cobrado na nota: ");
            scanf("%f", &nota.freteTotal);
            fflush(stdin);

            printf("Valor total do IMPOSTO cobrado na nota: ");
            scanf("%f", &nota.impostoTotal);
            fflush(stdin);

            //inserindo os produtos na nota
            int continuar = 1;
            float somaCustoProdutos = 0.0;

            while(continuar == 1 && nota.qtdItensDiferentes < 50) {
                system("cls");
                printf("--- INSERINDO PRODUTOS NA NOTA (Itens: %d) ---\n", nota.qtdItensDiferentes);
                
                int idBusca;
                printf("\nDigite o ID do produto comprado (ou 0 para listar os produtos do sistema): ");
                scanf("%d", &idBusca);
                fflush(stdin);

                if (idBusca == 0) {
                    listarProdutos(listaProdutos);
                    system("pause");
                    continue;
                }

                TipoProduto prodTemp;
                ListaProduto *posProd;

                if (buscarProduto(&listaProdutos, &prodTemp, idBusca, &posProd) == 0) {
                    nota.itens[nota.qtdItensDiferentes].idProduto = prodTemp.id;
                    
                    printf("\nProduto Localizado: %s\n", prodTemp.descricao);
                    
                    printf("Quantidade comprada (unidades): ");
                    scanf("%d", &nota.itens[nota.qtdItensDiferentes].quantidade);
                    fflush(stdin);

                    printf("Preco de Custo Unitario (R$): ");
                    scanf("%f", &nota.itens[nota.qtdItensDiferentes].precoCusto);
                    fflush(stdin);

                    //somatorios globais da nota
                    nota.quantidadeTotalUnidades += nota.itens[nota.qtdItensDiferentes].quantidade;
                    somaCustoProdutos += (nota.itens[nota.qtdItensDiferentes].quantidade * nota.itens[nota.qtdItensDiferentes].precoCusto);
                    
                    nota.qtdItensDiferentes++;
                    printf("\nItem registrado na Nota Fiscal!\n");
                } else {
                    printf("\nProduto nao encontrado no cadastro do sistema!\n");
                }

                printf("\nDeseja inserir mais produtos nesta nota?\n1 - Sim\n2 - Nao\n=> ");
                scanf("%d", &continuar);
                fflush(stdin);
            }

            //calculando preços e venda
            if (nota.qtdItensDiferentes > 0) {
                nota.valorTotalNota = somaCustoProdutos + nota.freteTotal + nota.impostoTotal;
                
                float freteUnitario = nota.freteTotal / nota.quantidadeTotalUnidades;
                float impostoUnitario = nota.impostoTotal / nota.quantidadeTotalUnidades;
                float margemLucroReal = dadosHotel->margemLucro / 100.0;

                system("cls");
                printf("--- RESUMO DA NOTA FISCAL ---\n");
                printf("Fornecedor  : %s\n", fornecedorTemp.nome_fantasia);
                printf("Total Itens : %d unidades\n", nota.quantidadeTotalUnidades);
                printf("Rateio Frete: R$ %.2f por item\n", freteUnitario);
                printf("Rateio Imp. : R$ %.2f por item\n", impostoUnitario);
                printf("VALOR TOTAL : R$ %.2f\n", nota.valorTotalNota);

                for(int i = 0; i < nota.qtdItensDiferentes; i++) {
                    TipoProduto prodAtualiza;
                    ListaProduto *posProdAtualiza;
                    
                    if(buscarProduto(&listaProdutos, &prodAtualiza, nota.itens[i].idProduto, &posProdAtualiza) == 0) {
                        // Formula Exata do Trabalho (Markup por absorção)
                        float custoBase = nota.itens[i].precoCusto + freteUnitario + impostoUnitario;
                        float lucroRateado = custoBase * margemLucroReal;
                        float novoPrecoVenda = custoBase + lucroRateado;

                        //atualiza sistema
                        prodAtualiza.estoque += nota.itens[i].quantidade;
                        prodAtualiza.preco_custo = nota.itens[i].precoCusto;
                        prodAtualiza.preco_venda = novoPrecoVenda;

                        alterarProduto(posProdAtualiza, prodAtualiza);
                        
                        printf("> %-15s | Estoque Novo: %-3d | Novo Preco Venda: R$ %.2f\n", 
                            prodAtualiza.descricao, prodAtualiza.estoque, prodAtualiza.preco_venda);
                    }
                }
                
                //pagamento ao fornecedor
                printf("\nForma de Pagamento ao Fornecedor:\n");
                printf("1 - A vista (Deduzir integralmente do Caixa do Hotel)\n");
                printf("2 - A prazo (Dar entrada + Parcelas no Contas a Pagar)\n");
                printf("=> ");
                int formaPgto;
                scanf("%d", &formaPgto);
                fflush(stdin);

                if (formaPgto == 1) {
                    
                    //AQUI MATHEUS:
                    // registrarSaidaCaixa(nota.valorTotalNota);

                    
                    printf("\n[!] Pagamento a vista registrado. Valor deduzido do Caixa!\n");
                } 
                else if (formaPgto == 2) {
                    float valorEntrada;
                    int parcelas;

                    printf("\nValor da entrada a vista (R$): ");
                    scanf("%f", &valorEntrada);
                    fflush(stdin);

                    //AQUI TB MATHEUS:
                    // registrarSaidaCaixa(valorEntrada);

                    
                    float restante = nota.valorTotalNota - valorEntrada;
                    printf("Quantidade de parcelas para o restante (R$ %.2f): ", restante);
                    scanf("%d", &parcelas);
                    fflush(stdin);

                    float valorDaParcela = restante / parcelas;

                    printf("\nGerando boletos no Contas a Pagar...\n");
                    for (int p = 1; p <= parcelas; p++) {
                        TipoContaPagar novaConta;
                        novaConta.id = escolheIdContaPagar(listaContas);
                        novaConta.idNota = nota.id;
                        novaConta.valorParcela = valorDaParcela;
                        novaConta.numeroParcela = p;
                        novaConta.statusPago = 0;
                        
                        sprintf(novaConta.dataVencimento, "30/12/2026");

                        inserirContaPagar(&listaContas, novaConta);
                        printf("- Parcela %d/%d (R$ %.2f) gerada com sucesso.\n", p, parcelas, valorDaParcela);
                    }
                }
                
                inserirNotaFiscal(&listaNotas, nota); //
                printf("\nOperacao de Entrada concluida!\n");
                system("pause");
            } else {
                printf("\nOperacao cancelada. Nenhum produto inserido.\n");
                system("pause");
            }
        } 
        else if (res == 2) {
            //relatorio de contas a pagar
            system("cls");
            printf("--- CONTAS A PAGAR (PENDENTES) ---\n");
            ListaContasPagar *aux = listaContas->prox;
            int temConta = 0;
            
            while (aux != NULL) {
                if (aux->conta.statusPago == 0) {
                    printf("ID Conta: %d | Ref. Nota: %d | Parcela %d | Vencimento: %s | Valor: R$ %.2f\n", 
                        aux->conta.id, aux->conta.idNota, aux->conta.numeroParcela, aux->conta.dataVencimento, aux->conta.valorParcela);
                    temConta = 1;
                }
                aux = aux->prox;
            }
            if (!temConta) printf("\nNao ha contas pendentes no momento!\n");
            system("pause");
        }
    } while (res != 0);
}