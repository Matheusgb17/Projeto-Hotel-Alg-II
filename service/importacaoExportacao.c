#include "importacaoExportacao.h"
#include "../bib/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../bib/acomodacoes.h"
#include "../bib/categorias.h"
#include "../bib/compras.h"
#include "../bib/contas.h"
#include "../bib/controleDeCaixa.h"
#include "../bib/estadias.h"
#include "../bib/fornecedores.h"
#include "../bib/hospedes.h"
#include "../bib/hotel.h"
#include "../bib/operadores.h"
#include "../bib/produtos.h"
#include "../bib/reservas.h"
#include "../bib/vendas.h"

int importarDados(char *nome_arquivo, ListaAcomodacao **listaAcomod, ListaCategoria **listaCategoria, ListaNotasFiscais **listaNotas, ListaContas **listaContasPagar, ListaContas **listaContasReceber, ListaHistoricoCaixa **historicoCaixa, ListaEstadia **listaEstadias, ListaFornecedor **listaFornecedor, ListaHospede **listaHospede, TipoHotel *dadosHotel, ListaOperadores **listaOperadores, ListaProduto **listaProduto, ListaReservas **listaReservas, ListaVendas **listaVendas)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL)
        return 1;

    char linha[512];
    int tabelaAtual = 0; // Controla qual lista estamos populando

    // Variáveis temporárias para armazenar os dados do registro atual
    TipoAcomodacao acomodacao;
    TipoCategoria categoria;
    TipoNotaFiscal nota;
    TipoConta conta;
    TipoHistoricoCaixa caixa;
    TipoEstadia estadia;
    TipoFornecedor fornecedor;
    TipoHospede hospede;
    TipoHotel hotelTemp;
    TipoOperador operador;
    TipoProduto produto;
    TipoReserva reserva;
    TipoVenda venda;

    // Variáveis auxiliares para vetores dinâmicos
    int itemIdx, valInt;
    float valFloat;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        // 1. Identificar mudança de Tabela
        if (strstr(linha, "<tabela=acomodacao>")) { tabelaAtual = 1; continue; }
        if (strstr(linha, "<tabela=categorias>")) { tabelaAtual = 2; continue; }
        if (strstr(linha, "<tabela=notas_fiscais>")) { tabelaAtual = 3; continue; }
        if (strstr(linha, "<tabela=contas_pagar>")) { tabelaAtual = 4; continue; }
        if (strstr(linha, "<tabela=contas_receber>")) { tabelaAtual = 5; continue; }
        if (strstr(linha, "<tabela=historico_caixa>\n") != NULL) { tabelaAtual = 6; continue; }
        if (strstr(linha, "<tabela=estadias>")) { tabelaAtual = 7; continue; }
        if (strstr(linha, "<tabela=fornecedor>")) { tabelaAtual = 8; continue; }
        if (strstr(linha, "<tabela=hospede>")) { tabelaAtual = 9; continue; }
        if (strstr(linha, "<tabela=hotel>")) { tabelaAtual = 10; continue; }
        if (strstr(linha, "<tabela=operador>")) { tabelaAtual = 11; continue; }
        if (strstr(linha, "<tabela=produto>")) { tabelaAtual = 12; continue; }
        if (strstr(linha, "<tabela=reservas>")) { tabelaAtual = 13; continue; }
        if (strstr(linha, "<tabela=vendas>")) { tabelaAtual = 14; continue; }
        if (strstr(linha, "</tabela>")) { tabelaAtual = 0; continue; } // Sai da tabela atual

        // 2. Iniciar um novo Registro limpando o lixo de memória
        if (strstr(linha, "<registro>") != NULL)
        {
            switch (tabelaAtual) {
                case 1: memset(&acomodacao, 0, sizeof(TipoAcomodacao)); break;
                case 2: memset(&categoria, 0, sizeof(TipoCategoria)); break;
                case 3: memset(&nota, 0, sizeof(TipoNotaFiscal)); break;
                case 4: 
                case 5: memset(&conta, 0, sizeof(TipoConta)); break;
                case 6: memset(&caixa, 0, sizeof(TipoHistoricoCaixa)); break;
                case 7: memset(&estadia, 0, sizeof(TipoEstadia)); break;
                case 8: memset(&fornecedor, 0, sizeof(TipoFornecedor)); break;
                case 9: memset(&hospede, 0, sizeof(TipoHospede)); break;
                case 10: memset(&hotelTemp, 0, sizeof(TipoHotel)); break;
                case 11: memset(&operador, 0, sizeof(TipoOperador)); break;
                case 12: memset(&produto, 0, sizeof(TipoProduto)); break;
                case 13: memset(&reserva, 0, sizeof(TipoReserva)); break;
                case 14: memset(&venda, 0, sizeof(TipoVenda)); break;
            }
            continue;
        }

        // 3. Finalizar o Registro inserindo na lista correspondente
        if (strstr(linha, "</registro>") != NULL)
        {
            switch (tabelaAtual) {
                case 1: inserirAcomodacao(listaAcomod, acomodacao); break;
                case 2: inserirCategoria(listaCategoria, categoria); break;
                case 3: inserirNotaFiscal(listaNotas, nota); break;
                case 4: inserirConta(listaContasPagar, conta); break;
                case 5: inserirConta(listaContasReceber, conta); break;
                case 6: registrarEntradaCaixa(historicoCaixa, caixa); break;
                case 7: inserirEstadia(listaEstadias, estadia); break;
                case 8: inserirFornecedor(listaFornecedor, fornecedor); break;
                case 9: inserirHospede(listaHospede, hospede); break;
                case 10: salvarDadosHotel(hotelTemp, dadosHotel); break; 
                case 11: inserirOperador(listaOperadores, operador); break;
                case 12: inserirProduto(listaProduto, produto); break;
                case 13: adicionarReserva(listaReservas, reserva); break;
                case 14: inserirVenda(listaVendas, venda); break;
            }
            continue;
        }

        // 4. Capturar os dados conforme a tabela em andamento
        switch (tabelaAtual) {
            case 1: // Acomodacao
                sscanf(linha, " <codigo>%d", &acomodacao.id);
                sscanf(linha, " <descricao>%[^<]", acomodacao.descricao);
                sscanf(linha, " <facilidades>%[^<]", acomodacao.facilidades);
                sscanf(linha, " <id_categoria>%d", &acomodacao.idCategoria);
                break;
                
            case 2: // Categoria
                sscanf(linha, " <codigo>%d", &categoria.id);
                sscanf(linha, " <descricao>%[^<]", categoria.descricao);
                sscanf(linha, " <valor_diaria>%f", &categoria.valorDiaria);
                sscanf(linha, " <capacidade_adultos>%d", &categoria.capacidadeAdultos);
                sscanf(linha, " <capacidade_criancas>%d", &categoria.capacidadeCriancas);
                break;
                
            case 3: // Notas Fiscais
                sscanf(linha, " <codigo>%d", &nota.id);
                sscanf(linha, " <cnpjFornecedor>%[^<]", nota.cnpjFornecedor);
                sscanf(linha, " <freteTotal>%f", &nota.freteTotal);
                sscanf(linha, " <impostoTotal>%f", &nota.impostoTotal);
                sscanf(linha, " <quantidadeTotalUnidades>%d", &nota.quantidadeTotalUnidades);
                sscanf(linha, " <valorTotalNota>%f", &nota.valorTotalNota);
                sscanf(linha, " <qtdItensDiferentes>%d", &nota.qtdItensDiferentes);
                sscanf(linha, " <dataEmissao>%lld", (long long *)&nota.dataEmissao);
                // Leitura dinâmica do vetor de itens
                if (sscanf(linha, " <item_%d_id>%d", &itemIdx, &valInt) == 2) nota.itens[itemIdx].idProduto = valInt;
                else if (sscanf(linha, " <item_%d_qtd>%d", &itemIdx, &valInt) == 2) nota.itens[itemIdx].quantidade = valInt;
                else if (sscanf(linha, " <item_%d_custo>%f", &itemIdx, &valFloat) == 2) nota.itens[itemIdx].precoCusto = valFloat;
                break;
                
            case 4: // Contas a Pagar
            case 5: // Contas a Receber
                sscanf(linha, " <codigo>%d", &conta.id);
                sscanf(linha, " <idNota>%d", &conta.idNota);
                sscanf(linha, " <valorParcela>%f", &conta.valorParcela);
                sscanf(linha, " <numeroParcela>%d", &conta.numeroParcela);
                sscanf(linha, " <dataVencimento>%[^<]", conta.dataVencimento);
                sscanf(linha, " <statusPago>%d", &conta.statusPago);
                break;
                
            case 6: // Histórico Caixa
                sscanf(linha, " <tipo>%d", &caixa.tipo);
                sscanf(linha, " <valor>%f", &caixa.valor);
                sscanf(linha, " <descricao>%[^<]", caixa.descricao);
                sscanf(linha, " <data>%lld", (long long *)&caixa.data);
                break;
                
            case 7: // Estadias
                sscanf(linha, " <codigo>%d", &estadia.id);
                sscanf(linha, " <codigo_acomodacao>%d", &estadia.idAcomodacao);
                sscanf(linha, " <cpf_hospede>%[^<]", estadia.cpfHospede);
                sscanf(linha, " <codigo_reserva>%d", &estadia.idReserva);
                sscanf(linha, " <data_checkin>%[^<]", estadia.dataCheckIn);
                sscanf(linha, " <data_checkout_planejado>%[^<]", estadia.dataCheckOutPlanejado);
                sscanf(linha, " <data_saida_real>%[^<]", estadia.dataSaidaReal);
                sscanf(linha, " <valor_total_pago>%f", &estadia.valorTotalPago);
                sscanf(linha, " <status>%d", &estadia.status);
                break;
                
            case 8: // Fornecedor
                sscanf(linha, " <codigo>%d", &fornecedor.id);
                sscanf(linha, " <nome_fantasia>%[^<]", fornecedor.nome_fantasia);
                sscanf(linha, " <razao_social>%[^<]", fornecedor.razao_social);
                sscanf(linha, " <inscricao_estadual>%[^<]", fornecedor.inscricao_estadual);
                sscanf(linha, " <cnpj>%[^<]", fornecedor.cnpj);
                sscanf(linha, " <endereco_completo>%[^<]", fornecedor.endereco_completo);
                sscanf(linha, " <telefone>%[^<]", fornecedor.telefone);
                sscanf(linha, " <email>%[^<]", fornecedor.email);
                break;
                
            case 9: // Hospede
                sscanf(linha, " <codigo>%d", &hospede.id);
                sscanf(linha, " <nome>%[^<]", hospede.nome);
                sscanf(linha, " <endereco>%[^<]", hospede.endereco);
                sscanf(linha, " <cpf>%[^<]", hospede.cpf);
                sscanf(linha, " <telefone>%[^<]", hospede.telefone);
                sscanf(linha, " <email>%[^<]", hospede.email);
                sscanf(linha, " <sexo>%c", &hospede.sexo);
                sscanf(linha, " <est_civil>%[^<]", hospede.estado_civil);
                sscanf(linha, " <data_nascimento>%[^<]", hospede.data_nasc);
                break;
                
            case 10: // Hotel
                sscanf(linha, " <cadastrado>%d", &hotelTemp.cadastrado);
                sscanf(linha, " <nome_fantasia>%[^<]", hotelTemp.nomeFantasia);
                sscanf(linha, " <razao_social>%[^<]", hotelTemp.razaoSocial);
                sscanf(linha, " <inscricao_estadual>%[^<]", hotelTemp.inscricaoEstadual);
                sscanf(linha, " <CNPJ>%[^<]", hotelTemp.CNPJ);
                sscanf(linha, " <endereco_completo>%[^<]", hotelTemp.enderecoCompleto);
                sscanf(linha, " <telefone>%[^<]", hotelTemp.telefone);
                sscanf(linha, " <email>%[^<]", hotelTemp.email);
                sscanf(linha, " <nome_responsavel>%[^<]", hotelTemp.nomeResponsavel);
                sscanf(linha, " <telefone_responsavel>%[^<]", hotelTemp.telefoneResponsavel);
                sscanf(linha, " <horario_checkin>%[^<]", hotelTemp.horarioCheckin);
                sscanf(linha, " <horario_checkout>%[^<]", hotelTemp.horarioCheckout);
                sscanf(linha, " <margem_lucro>%f", &hotelTemp.margemLucro);
                break;

            case 11: // Operador
                sscanf(linha, " <codigo>%d", &operador.id);
                sscanf(linha, " <nome>%[^<]", operador.nome);
                sscanf(linha, " <user>%[^<]", operador.user);
                sscanf(linha, " <senha>%[^<]", operador.senha);
                sscanf(linha, " <permissao>%d", &operador.permission);
                break;

            case 12: // Produto
                sscanf(linha, " <codigo>%d", &produto.id);
                sscanf(linha, " <descricao>%[^<]", produto.descricao);
                sscanf(linha, " <estoque>%d", &produto.estoque);
                sscanf(linha, " <estoque_minimo>%d", &produto.estoque_minimo);
                sscanf(linha, " <preco_custo>%f", &produto.preco_custo);
                sscanf(linha, " <preco_venda>%f", &produto.preco_venda);
                break;

            case 13: // Reservas
                sscanf(linha, " <codigo>%d", &reserva.id);
                sscanf(linha, " <idHospede>%d", &reserva.idHospede);
                sscanf(linha, " <idAcomodacao>%d", &reserva.idAcomodacao);
                sscanf(linha, " <dataEntrada>%lld", (long long *)&reserva.dataEntrada);
                sscanf(linha, " <dataSaida>%lld", (long long *)&reserva.dataSaida);
                break;

            case 14: // Vendas
                sscanf(linha, " <codigo>%d", &venda.id);
                sscanf(linha, " <idHospede>%d", &venda.idHospede);
                sscanf(linha, " <formaPagamento>%d", &venda.formaPagamento);
                sscanf(linha, " <statusPagamento>%d", &venda.statusPagamento);
                sscanf(linha, " <qtdItens>%d", &venda.qtdItens);
                sscanf(linha, " <valorTotal>%f", &venda.valorTotal);
                sscanf(linha, " <dataVenda>%lld", (long long *)&venda.dataVenda);
                // Leitura dinâmica do vetor de itens
                if (sscanf(linha, " <item_%d_id>%d", &itemIdx, &valInt) == 2) venda.itens[itemIdx].idProduto = valInt;
                else if (sscanf(linha, " <item_%d_qtd>%d", &itemIdx, &valInt) == 2) venda.itens[itemIdx].quantidade = valInt;
                else if (sscanf(linha, " <item_%d_val>%f", &itemIdx, &valFloat) == 2) venda.itens[itemIdx].valorUnitario = valFloat;
                break;
        }
    }

    fclose(arquivo);
    return 0;
}

int exportarDados(char *nome_arquivo, ListaAcomodacao *listaAcomod, ListaCategoria *listaCategoria, ListaNotasFiscais *listaNotas, ListaContas *listaContasPagar, ListaContas *listaContasReceber, ListaHistoricoCaixa *historicoCaixa, ListaEstadia *listaEstadias, ListaFornecedor *listaFornecedor, ListaHospede *listaHospede, TipoHotel dadosHotel, ListaOperadores *listaOperadores, ListaProduto *listaProduto, ListaReservas *listaReservas, ListaVendas *listaVendas)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL)
        return 1;

    fprintf(arquivo, "<dados>\n");

    if (listaAcomod->prox != NULL)
    {
        ListaAcomodacao *auxAcomod = listaAcomod->prox;

        fprintf(arquivo, "    <tabela=acomodacao>\n");
        while (auxAcomod != NULL)
        {
            if (auxAcomod->acomodacao.id != 0)
            {
                fprintf(arquivo, "        <registro>\n");
                fprintf(arquivo, "            <codigo>%d</codigo>\n", auxAcomod->acomodacao.id);
                fprintf(arquivo, "            <descricao>%s</descricao>\n", auxAcomod->acomodacao.descricao);
                fprintf(arquivo, "            <facilidades>%s</facilidades>\n", auxAcomod->acomodacao.facilidades);
                fprintf(arquivo, "            <id_categoria>%d</id_categoria>\n", auxAcomod->acomodacao.idCategoria);
                fprintf(arquivo, "        </registro>\n");
            }
            auxAcomod = auxAcomod->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (listaCategoria->prox != NULL)
    {
        ListaCategoria *auxCat = listaCategoria->prox;

        fprintf(arquivo, "    <tabela=categorias>\n");
        while (auxCat != NULL)
        {
            fprintf(arquivo, "        <registro>\n");
            fprintf(arquivo, "            <codigo>%d</codigo>\n", auxCat->categoria.id);
            fprintf(arquivo, "            <descricao>%s</descricao>\n", auxCat->categoria.descricao);
            fprintf(arquivo, "            <valor_diaria>%.2f</valor_diaria>\n", auxCat->categoria.valorDiaria);
            fprintf(arquivo, "            <capacidade_adultos>%d</capacidade_adultos>\n", auxCat->categoria.capacidadeAdultos);
            fprintf(arquivo, "            <capacidade_criancas>%d</capacidade_criancas>\n", auxCat->categoria.capacidadeCriancas);
            fprintf(arquivo, "        </registro>\n");
            auxCat = auxCat->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (listaNotas->prox != NULL)
    {
        ListaNotasFiscais *auxNotas = listaNotas->prox;
        fprintf(arquivo, "<tabela=notas_fiscais>\n");
        while (auxNotas != NULL)
        {
            if (auxNotas->nota.id != 0)
            {
                fprintf(arquivo, "    <registro>\n");
                fprintf(arquivo, "        <codigo>%d</codigo>\n", auxNotas->nota.id);
                fprintf(arquivo, "        <cnpjFornecedor>%s</cnpjFornecedor>\n", auxNotas->nota.cnpjFornecedor);
                fprintf(arquivo, "        <freteTotal>%.2f</freteTotal>\n", auxNotas->nota.freteTotal);
                fprintf(arquivo, "        <impostoTotal>%.2f</impostoTotal>\n", auxNotas->nota.impostoTotal);
                fprintf(arquivo, "        <quantidadeTotalUnidades>%d</quantidadeTotalUnidades>\n", auxNotas->nota.quantidadeTotalUnidades);
                fprintf(arquivo, "        <valorTotalNota>%.2f</valorTotalNota>\n", auxNotas->nota.valorTotalNota);
                fprintf(arquivo, "        <qtdItensDiferentes>%d</qtdItensDiferentes>\n", auxNotas->nota.qtdItensDiferentes);
                fprintf(arquivo, "        <dataEmissao>%I64d</dataEmissao>\n", (long long)auxNotas->nota.dataEmissao);

                // Salvar os itens do vetor de compras da nota
                for (int i = 0; i < auxNotas->nota.qtdItensDiferentes; i++)
                {
                    fprintf(arquivo, "        <item_%d_id>%d</item_%d_id>\n", i, auxNotas->nota.itens[i].idProduto, i);
                    fprintf(arquivo, "        <item_%d_qtd>%d</item_%d_qtd>\n", i, auxNotas->nota.itens[i].quantidade, i);
                    fprintf(arquivo, "        <item_%d_custo>%.2f</item_%d_custo>\n", i, auxNotas->nota.itens[i].precoCusto, i);
                }
                fprintf(arquivo, "    </registro>\n");
            }
            auxNotas = auxNotas->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (listaContasPagar->prox != NULL)
    {
        ListaContas *auxContPagar = listaContasPagar->prox;
        fprintf(arquivo, "    <tabela=contas_pagar>\n");
        while (auxContPagar != NULL)
        {

            fprintf(arquivo, "        <registro>\n");
            fprintf(arquivo, "            <codigo>%d</codigo>\n", auxContPagar->conta.id);
            fprintf(arquivo, "            <idNota>%d</idNota>\n", auxContPagar->conta.idNota);
            fprintf(arquivo, "            <valorParcela>%.2f</valorParcela>\n", auxContPagar->conta.valorParcela);
            fprintf(arquivo, "            <numeroParcela>%d</numeroParcela>\n", auxContPagar->conta.numeroParcela);
            fprintf(arquivo, "            <dataVencimento>%s</dataVencimento>\n", auxContPagar->conta.dataVencimento);
            fprintf(arquivo, "            <statusPago>%d</statusPago>\n", auxContPagar->conta.statusPago);
            fprintf(arquivo, "        </registro>\n");
            auxContPagar = auxContPagar->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (listaContasReceber->prox != NULL)
    {
        ListaContas *auxContReceber = listaContasReceber->prox;
        fprintf(arquivo, "    <tabela=contas_receber>\n");
        while (auxContReceber != NULL)
        {

            fprintf(arquivo, "        <registro>\n");
            fprintf(arquivo, "            <codigo>%d</codigo>\n", auxContReceber->conta.id);
            fprintf(arquivo, "            <idNota>%d</idNota>\n", auxContReceber->conta.idNota);
            fprintf(arquivo, "            <valorParcela>%.2f</valorParcela>\n", auxContReceber->conta.valorParcela);
            fprintf(arquivo, "            <numeroParcela>%d</numeroParcela>\n", auxContReceber->conta.numeroParcela);
            fprintf(arquivo, "            <dataVencimento>%s</dataVencimento>\n", auxContReceber->conta.dataVencimento);
            fprintf(arquivo, "            <statusPago>%d</statusPago>\n", auxContReceber->conta.statusPago);
            fprintf(arquivo, "        </registro>\n");
            auxContReceber = auxContReceber->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (historicoCaixa->prox != NULL)
    {
        ListaHistoricoCaixa *auxHistCaixa = historicoCaixa->prox;
        fprintf(arquivo, "    <tabela=historico_caixa>\n");
        while (auxHistCaixa != NULL)
        {
            if (auxHistCaixa->registro.tipo != 0)
            {
                fprintf(arquivo, "        <registro>\n");
                fprintf(arquivo, "            <tipo>%d</tipo>\n", auxHistCaixa->registro.tipo);
                fprintf(arquivo, "            <valor>%.2f</valor>\n", auxHistCaixa->registro.valor);
                fprintf(arquivo, "            <descricao>%s</descricao>\n", auxHistCaixa->registro.descricao);
                fprintf(arquivo, "            <data>%lld</data>\n", (long long)auxHistCaixa->registro.data);
                fprintf(arquivo, "        </registro>\n");
            }
            auxHistCaixa = auxHistCaixa->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (listaEstadias->prox != NULL)
    {
        ListaEstadia *auxEstadias = listaEstadias->prox;

        fprintf(arquivo, "    <tabela=estadias>\n");
        while (auxEstadias != NULL)
        {
            fprintf(arquivo, "        <registro>\n");
            fprintf(arquivo, "            <codigo>%d</codigo>\n", auxEstadias->estadia.id);
            fprintf(arquivo, "            <codigo_acomodacao>%d</codigo_acomodacao>\n", auxEstadias->estadia.idAcomodacao);
            fprintf(arquivo, "            <cpf_hospede>%s</cpf_hospede>\n", auxEstadias->estadia.cpfHospede);
            fprintf(arquivo, "            <codigo_reserva>%d</codigo_reserva>\n", auxEstadias->estadia.idReserva);
            fprintf(arquivo, "            <data_checkin>%s</data_checkin>\n", auxEstadias->estadia.dataCheckIn);
            fprintf(arquivo, "            <data_checkout_planejado>%s</data_checkout_planejado>\n", auxEstadias->estadia.dataCheckOutPlanejado);
            fprintf(arquivo, "            <data_saida_real>%s</data_saida_real>\n", auxEstadias->estadia.dataSaidaReal);
            fprintf(arquivo, "            <valor_total_pago>%.2f</valor_total_pago>\n", auxEstadias->estadia.valorTotalPago);
            fprintf(arquivo, "            <status>%d</status>\n", auxEstadias->estadia.status);
            fprintf(arquivo, "        </registro>\n");
            auxEstadias = auxEstadias->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (listaFornecedor->prox != NULL)
    {
        ListaFornecedor *auxForn = listaFornecedor->prox;
        fprintf(arquivo, "    <tabela=fornecedor>\n");
        while (auxForn != NULL)
        {
            fprintf(arquivo, "        <registro>\n");
            fprintf(arquivo, "            <codigo>%d</codigo>\n", auxForn->Fornecedor.id);
            fprintf(arquivo, "            <nome_fantasia>%s</nome_fantasia>\n", auxForn->Fornecedor.nome_fantasia);
            fprintf(arquivo, "            <razao_social>%s</razao_social>\n", auxForn->Fornecedor.razao_social);
            fprintf(arquivo, "            <inscricao_estadual>%s</inscricao_estadual>\n", auxForn->Fornecedor.inscricao_estadual);
            fprintf(arquivo, "            <cnpj>%s</cnpj>\n", auxForn->Fornecedor.cnpj);
            fprintf(arquivo, "            <endereco_completo>%s</endereco_completo>\n", auxForn->Fornecedor.endereco_completo);
            fprintf(arquivo, "            <telefone>%s</telefone>\n", auxForn->Fornecedor.telefone);
            fprintf(arquivo, "            <email>%s</email>\n", auxForn->Fornecedor.email);
            fprintf(arquivo, "        </registro>\n");
            auxForn = auxForn->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (listaHospede->prox != NULL)
    {
        ListaHospede *auxHosp = listaHospede->prox;

        fprintf(arquivo, "    <tabela=hospede>\n");
        while (auxHosp != NULL)
        {
            fprintf(arquivo, "        <registro>\n");
            fprintf(arquivo, "            <codigo>%d</codigo>\n", auxHosp->Hospedes.id);
            fprintf(arquivo, "            <nome>%s</nome>\n", auxHosp->Hospedes.nome);
            fprintf(arquivo, "            <endereco>%s</endereco>\n", auxHosp->Hospedes.endereco);
            fprintf(arquivo, "            <cpf>%s</cpf>\n", auxHosp->Hospedes.cpf);
            fprintf(arquivo, "            <telefone>%s</telefone>\n", auxHosp->Hospedes.telefone);
            fprintf(arquivo, "            <email>%s</email>\n", auxHosp->Hospedes.email);
            fprintf(arquivo, "            <sexo>%c</sexo>\n", auxHosp->Hospedes.sexo);
            fprintf(arquivo, "            <est_civil>%s</est_civil>\n", auxHosp->Hospedes.estado_civil);
            fprintf(arquivo, "            <data_nascimento>%s</data_nascimento>\n", auxHosp->Hospedes.data_nasc);
            fprintf(arquivo, "        </registro>\n");
            auxHosp = auxHosp->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (dadosHotel.cadastrado == true)
    {
        fprintf(arquivo, "    <tabela=hotel>\n");
        fprintf(arquivo, "        <registro>\n");
        fprintf(arquivo, "            <cadastrado>%d</cadastrado>\n", dadosHotel.cadastrado);
        fprintf(arquivo, "            <nome_fantasia>%s</nome_fantasia>\n", dadosHotel.nomeFantasia);
        fprintf(arquivo, "            <razao_social>%s</razao_social>\n", dadosHotel.razaoSocial);
        fprintf(arquivo, "            <inscricao_estadual>%s</inscricao_estadual>\n", dadosHotel.inscricaoEstadual);
        fprintf(arquivo, "            <CNPJ>%s</CNPJ>\n", dadosHotel.CNPJ);
        fprintf(arquivo, "            <endereco_completo>%s</endereco_completo>\n", dadosHotel.enderecoCompleto);
        fprintf(arquivo, "            <telefone>%s</telefone>\n", dadosHotel.telefone);
        fprintf(arquivo, "            <email>%s</email>\n", dadosHotel.email);
        fprintf(arquivo, "            <nome_responsavel>%s</nome_responsavel>\n", dadosHotel.nomeResponsavel);
        fprintf(arquivo, "            <telefone_responsavel>%s</telefone_responsavel>\n", dadosHotel.telefoneResponsavel);
        fprintf(arquivo, "            <horario_checkin>%s</horario_checkin>\n", dadosHotel.horarioCheckin);
        fprintf(arquivo, "            <horario_checkout>%s</horario_checkout>\n", dadosHotel.horarioCheckout);
        fprintf(arquivo, "            <margem_lucro>%.2f</margem_lucro>\n", dadosHotel.margemLucro);
        fprintf(arquivo, "          </registro>\n");
        fprintf(arquivo, "    </tabela>\n");
    }

    if (listaOperadores->prox != NULL)
    {
        ListaOperadores *auxOp = listaOperadores->prox;

        fprintf(arquivo, "    <tabela=operador>\n");
        while (auxOp != NULL)
        {
            fprintf(arquivo, "        <registro>\n");
            fprintf(arquivo, "            <codigo>%d</codigo>\n", auxOp->operador.id);
            fprintf(arquivo, "            <nome>%s</nome>\n", auxOp->operador.nome);
            fprintf(arquivo, "            <user>%s</user>\n", auxOp->operador.user);
            fprintf(arquivo, "            <senha>%s</senha>\n", auxOp->operador.senha);
            fprintf(arquivo, "            <permissao>%d</permissao>\n", auxOp->operador.permission);
            fprintf(arquivo, "        </registro>\n");
            auxOp = auxOp->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (listaProduto->prox != NULL)
    {
        ListaProduto *auxProd = listaProduto->prox;
        fprintf(arquivo, "    <tabela=produto>\n");
        while (auxProd != NULL)
        {
            fprintf(arquivo, "        <registro>\n");
            fprintf(arquivo, "            <codigo>%d</codigo>\n", auxProd->Produto.id);
            fprintf(arquivo, "            <descricao>%s</descricao>\n", auxProd->Produto.descricao);
            fprintf(arquivo, "            <estoque>%d</estoque>\n", auxProd->Produto.estoque);
            fprintf(arquivo, "            <estoque_minimo>%d</estoque_minimo>\n", auxProd->Produto.estoque_minimo);
            fprintf(arquivo, "            <preco_custo>%f</preco_custo>\n", auxProd->Produto.preco_custo);
            fprintf(arquivo, "            <preco_venda>%f</preco_venda>\n", auxProd->Produto.preco_venda);
            fprintf(arquivo, "        </registro>\n");
            auxProd = auxProd->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (listaReservas->prox != NULL)
    {
        ListaReservas *auxReservas;
        auxReservas = listaReservas->prox;

        fprintf(arquivo, "    <tabela=reservas>\n");
        while (auxReservas != NULL)
        {
            if (auxReservas->reserva.id != 0)
            {
                fprintf(arquivo, "        <registro>\n");
                fprintf(arquivo, "            <codigo>%d</codigo>\n", auxReservas->reserva.id);
                fprintf(arquivo, "            <idHospede>%d</idHospede>\n", auxReservas->reserva.idHospede);
                fprintf(arquivo, "            <idAcomodacao>%d</idAcomodacao>\n", auxReservas->reserva.idAcomodacao);
                fprintf(arquivo, "            <dataEntrada>%lld</dataEntrada>\n", (long long)auxReservas->reserva.dataEntrada);
                fprintf(arquivo, "            <dataSaida>%lld</dataSaida>\n", (long long)auxReservas->reserva.dataSaida);
                fprintf(arquivo, "        </registro>\n");
            }
            auxReservas = auxReservas->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    if (listaVendas->prox != NULL)
    {
        ListaVendas *auxVend = listaVendas->prox;
        fprintf(arquivo, "    <tabela=vendas>\n");
        while (auxVend != NULL)
        {
            if (auxVend->venda.id != 0)
            {
                fprintf(arquivo, "        <registro>\n");
                fprintf(arquivo, "            <codigo>%d</codigo>\n", auxVend->venda.id);
                fprintf(arquivo, "            <idHospede>%d</idHospede>\n", auxVend->venda.idHospede);
                fprintf(arquivo, "            <formaPagamento>%d</formaPagamento>\n", auxVend->venda.formaPagamento);
                fprintf(arquivo, "            <statusPagamento>%d</statusPagamento>\n", auxVend->venda.statusPagamento);
                fprintf(arquivo, "            <qtdItens>%d</qtdItens>\n", auxVend->venda.qtdItens);
                fprintf(arquivo, "            <valorTotal>%.2f</valorTotal>\n", auxVend->venda.valorTotal);
                fprintf(arquivo, "            <dataVenda>%lld</dataVenda>\n", (long long)auxVend->venda.dataVenda);

                // Salvar os itens do vetor
                for (int i = 0; i < auxVend->venda.qtdItens; i++)
                {
                    fprintf(arquivo, "            <item_%d_id>%d</item_%d_id>\n", i, auxVend->venda.itens[i].idProduto, i);
                    fprintf(arquivo, "            <item_%d_qtd>%d</item_%d_qtd>\n", i, auxVend->venda.itens[i].quantidade, i);
                    fprintf(arquivo, "            <item_%d_val>%.2f</item_%d_val>\n", i, auxVend->venda.itens[i].valorUnitario, i);
                }
                fprintf(arquivo, "        </registro>\n");
            }
            auxVend = auxVend->prox;
        }
        fprintf(arquivo, "    </tabela>\n");
    }

    fprintf(arquivo, "</dados>\n");
    fclose(arquivo);
    return 0;
}
