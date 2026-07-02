#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../bib/acomodacoes.h"

#include "estadias.h"
#include "../bib/categorias.h"
#include "../bib/utils.h"

#define BIN 1
#define TXT 2

ListaAcomodacao *iniciaListaAcomodacao()
{
    ListaAcomodacao *lista = malloc(sizeof(ListaAcomodacao));

    if (lista)
    {
        lista->acomodacao.id = 0;
        lista->prox = NULL;
    }
    return lista;
}

int inserirAcomodacao(ListaAcomodacao **lista, TipoAcomodacao acomodacao)
{
    ListaAcomodacao *aux, *novaAcomodacao = malloc(sizeof(ListaAcomodacao));

    if (novaAcomodacao)
    {
        novaAcomodacao->acomodacao = acomodacao;
        novaAcomodacao->prox = NULL;
        aux = *lista;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novaAcomodacao;
        return 0;
    }
    return 1;
}

int buscarAcomodacao(ListaAcomodacao **lista, TipoAcomodacao *acomodacao, int id, ListaAcomodacao **pos)
{
    if (lista == NULL || *lista == NULL)
        return 1;

    ListaAcomodacao *aux = (*lista)->prox;

    while (aux != NULL)
    {
        if (aux->acomodacao.id == id)
        {
            *acomodacao = aux->acomodacao;
            *pos = aux;
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

void alterarAcomodacao(ListaAcomodacao *pos, TipoAcomodacao acomodacao)
{
    pos->acomodacao = acomodacao;
}

void apagarAcomodacao(ListaAcomodacao *pos)
{
    pos->acomodacao.id = 0;
}

void listarAcomodacao(ListaAcomodacao *lista, ListaCategoria *listaCat)
{
    TipoCategoria categoriaTemp;
    if (lista->prox == NULL)
    {
        exibeMensagemAviso("Nenhuma acomodacao cadastrada.\n");
    }
    else
    {
        lista = lista->prox;
        exibeMensagemAviso("\nAcomodacoes cadastradas:\n");

        while (lista != NULL)
        {
            if (lista->acomodacao.id != 0)
            {
                buscarCategoria(&listaCat, &categoriaTemp, lista->acomodacao.idCategoria, NULL);
                imprimeAcomodacao(lista->acomodacao, categoriaTemp);
            }
            lista = lista->prox;
        }
    }
}

void listarIdsJaRegistradosAcomodacao(ListaAcomodacao *lista)
{
    if (lista->prox == NULL)
    {
        exibeMensagemAviso("Nenhuma acomodacao cadastrada.\n");
    }
    else
    {
        int cont = 0;
        lista = lista->prox;
        exibeMensagemAviso("\nIDs de acomodacoes ja cadastradas:\n");

        while (lista != NULL)
        {
            cont++;
            if (lista->acomodacao.id != 0)
            {
                printf("%d ", lista->acomodacao.id);
            }
            lista = lista->prox;
            if (cont % 10 == 0)
                printf("\n");
        }
    }
    printf("\n");
    pausarTela();
    return;
}

void salvarDadosAcomodacoesBin(ListaAcomodacao *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao acessar o arquivo...\n\n");
        pausarTela();
        return;
    }
    ListaAcomodacao *aux = lista->prox;
    while (aux != NULL)
    {
        if (aux->acomodacao.id != 0)
        {
            fwrite(&(aux->acomodacao), sizeof(TipoAcomodacao), 1, arquivo);
        }
        aux = aux->prox;
    }
    fclose(arquivo);
}

ListaAcomodacao *resgataDadosAcomodacoesBin(char *nome_arquivo)
{
    TipoAcomodacao acomodacao;
    ListaAcomodacao *lista = iniciaListaAcomodacao();
    int res;

    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL)
        return lista;

    while (fread(&acomodacao, sizeof(TipoAcomodacao), 1, arquivo) == 1)
        res = inserirAcomodacao(&lista, acomodacao);

    if (res == 1)
        printf("Erro ao cadastrar acomodacao!");

    fclose(arquivo);
    return lista;
}

void salvarDadosAcomodacoesTxt(ListaAcomodacao *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao acessar o arquivo...\n\n");
        pausarTela();
        return;
    }

    if (lista->prox != NULL)
    {
        ListaAcomodacao *aux = lista->prox;

        fprintf(arquivo, "<tabela=acomodacao>\n");
        while (aux != NULL)
        {
            if (aux->acomodacao.id != 0)
            {
                fprintf(arquivo, "    <registro>\n");
                fprintf(arquivo, "        <codigo>%d</codigo>\n", aux->acomodacao.id);
                fprintf(arquivo, "        <descricao>%s</descricao>\n", aux->acomodacao.descricao);
                fprintf(arquivo, "        <facilidades>%s</facilidades>\n", aux->acomodacao.facilidades);
                fprintf(arquivo, "        <id_categoria>%d</id_categoria>\n", aux->acomodacao.idCategoria);
                fprintf(arquivo, "    </registro>\n");
            }
            aux = aux->prox;
        }
        fprintf(arquivo, "</tabela>\n");
    }
    fclose(arquivo);
    printf("Dados salvos em TXT com sucesso!\n");
}

ListaAcomodacao *resgataDadosAcomodacoesTxt(char *nome_arquivo)
{
    ListaAcomodacao *lista = iniciaListaAcomodacao();
    TipoAcomodacao acomod;

    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL)
        return lista;

    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(&acomod, 0, sizeof(TipoAcomodacao));
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            inserirAcomodacao(&lista, acomod);
            continue;
        }

        if (strstr(linha, "<codigo>"))
            sscanf(linha, " <codigo>%d", &acomod.id);
        else if (strstr(linha, "<descricao>"))
            sscanf(linha, " <descricao>%[^<]", acomod.descricao);
        else if (strstr(linha, "<facilidades>"))
            sscanf(linha, " <facilidades>%[^<]", acomod.facilidades);
        else if (strstr(linha, "<id_categoria>"))
            sscanf(linha, " <id_categoria>%d", &acomod.idCategoria);
    }
    fclose(arquivo);
    return lista;
}

void liberaListaAcomodacoes(ListaAcomodacao *lista)
{
    ListaAcomodacao *temp, *aux = lista;
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }
    return;
}

void interfaceRelatorioAcomodacoes(ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaReservas *listaRes, int opcaoDestino) {
    int codMin = 0, codMax = 0;
    int filtrarData = 0, dia, mes, ano;
    FiltroBusca filtro;
    FILE *arquivoCSV = NULL;
    char caminhoArquivo[150];
    struct tm tm_entrada = {0};
    struct tm tm_saida = {0};

    // Zera todos os campos do filtro por segurança
    memset(&filtro, 0, sizeof(FiltroBusca));

    system("cls");
    printf("--- Filtros: Listagem de Acomodacoes ---\n");

    printf("Codigo inicial (0 para listar desde o primeiro): ");
    scanf("%d", &codMin);
    fflush(stdin);

    printf("Codigo final (0 para listar ate o ultimo): ");
    scanf("%d", &codMax);
    fflush(stdin);

    printf("ID da Categoria (0 para listar todas): ");
    scanf("%d", &filtro.idCategoria);
    fflush(stdin);

    printf("Deseja buscar acomodacoes disponiveis em um periodo? (1-Sim / 0-Nao): ");
    scanf("%d", &filtrarData);
    fflush(stdin);

    if (filtrarData == 1) {
        printf("Data de Entrada (DD/MM/AAAA): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
        fflush(stdin);
        tm_entrada.tm_mday = dia;
        tm_entrada.tm_mon = mes - 1;
        tm_entrada.tm_year = ano - 1900;
        filtro.dataEntrada = mktime(&tm_entrada);

        printf("Data de Saida (DD/MM/AAAA): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
        fflush(stdin);
        tm_saida.tm_mday = dia;
        tm_saida.tm_mon = mes - 1;
        tm_saida.tm_year = ano - 1900;
        filtro.dataSaida = mktime(&tm_saida);
    }

    // Preparação do arquivo CSV, caso o operador tenha escolhido a opção 2
    if (opcaoDestino == 2) {
        printf("\nDigite o nome/caminho do arquivo CSV (ex: relatorio_acomodacoes.csv): ");
        scanf("%[^\n]", caminhoArquivo);
        fflush(stdin);

        arquivoCSV = fopen(caminhoArquivo, "w");
        if (arquivoCSV == NULL) {
            printf("Erro ao criar o arquivo CSV!\n");
            system("pause");
            return;
        }
        // Cabeçalho do CSV
        fprintf(arquivoCSV, "ID_Acomodacao;Descricao;Facilidades;Valor_Diaria;Cap_Adultos;Cap_Criancas\n");
    }

    printf("\nGerando relatorio...\n\n");

    // Chama a função principal passando todos os filtros coletados
    relatorioAcomodacoes(listaAcom, listaCat, listaRes, codMin, codMax, filtro, opcaoDestino, arquivoCSV);

    if (opcaoDestino == 2 && arquivoCSV != NULL) {
        fclose(arquivoCSV);
        printf("\nRelatorio salvo com sucesso em: %s\n", caminhoArquivo);
    }

    system("pause");
}

int relatorioAcomodacoes(ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaReservas *listaRes, int codMin, int codMax, FiltroBusca filtro, int opcaoDestino, FILE *arquivoCSV)
{
    ListaAcomodacao *auxAcom = listaAcom->prox;
    int encontrouAlgum = 0;

    TipoCategoria categoriaTemp;
    ListaCategoria *posCat;
    ListaReservas *auxRes;
    int conflito;

    while (auxAcom != NULL)
    {
        buscarCategoria(&listaCat, &categoriaTemp, auxAcom->acomodacao.idCategoria, &posCat);

        //FILTROS

        //Filtrar por faixa de código
        if ((codMin > 0 && auxAcom->acomodacao.id < codMin) ||
            (codMax > 0 && auxAcom->acomodacao.id > codMax)) {
            auxAcom = auxAcom->prox;
            continue;
        }

        //Filtrar por Categoria
        if (filtro.idCategoria != 0 && auxAcom->acomodacao.idCategoria != filtro.idCategoria) {
            auxAcom = auxAcom->prox;
            continue;
        }

        //Filtrar por data disponível
        if (filtro.dataEntrada != 0 && filtro.dataSaida != 0) {
            conflito = 0;

            if (listaRes != NULL) {
                auxRes = listaRes->prox;
                while (auxRes != NULL) {
                    if (auxRes->reserva.idAcomodacao == auxAcom->acomodacao.id) {

                        if (filtro.dataEntrada < auxRes->reserva.dataSaida &&
                            filtro.dataSaida > auxRes->reserva.dataEntrada) {
                            conflito = 1;
                            break;
                        }
                    }
                    auxRes = auxRes->prox;
                }
            }

            if (conflito == 1) {
                auxAcom = auxAcom->prox;
                continue;
            }
        }

        encontrouAlgum = 1;

        if (opcaoDestino == 1)
        {
            imprimeAcomodacao(auxAcom->acomodacao, categoriaTemp);
        }
        else if (opcaoDestino == 2 && arquivoCSV != NULL)
        {
            //CSV:
            fprintf(arquivoCSV, "%d;%s;%s;%.2f;%d;%d\n",
                    auxAcom->acomodacao.id,
                    auxAcom->acomodacao.descricao,
                    auxAcom->acomodacao.facilidades,
                    categoriaTemp.valorDiaria,
                    categoriaTemp.capacidadeAdultos,
                    categoriaTemp.capacidadeCriancas);
        }
        auxAcom = auxAcom->prox;
    }

    if (encontrouAlgum == 0 && opcaoDestino == 1) {
        printf("Nenhuma acomodacao atende aos criterios dos filtros.\n");
    }

    return encontrouAlgum;
}


void imprimeDadosDiaria(ListaAcomodacao acomodacoes, int totalDiarias, float rendimentoTotal) {
    printf("ID Acomodacao       : %d\n", acomodacoes.acomodacao.id);
    printf("Descricao           : %s\n", acomodacoes.acomodacao.descricao);
    printf("Diarias Ocupadas    : %d\n", totalDiarias);
    printf("Rendimento Total    : R$%.2f\n", rendimentoTotal);
    printf("-----------------------------------\n");
}

int relatorioMovimentacaoAcomodacoes(ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaReservas *listaRes, int idAcomFiltro, int minDiarias, float minRendimento, int opcaoDestino, FILE *arquivoCSV) {
    ListaAcomodacao *auxAcom = listaAcom->prox;
    int encontrouAlgum = 0;

    TipoCategoria categoriaTemp;
    ListaCategoria *posCat;
    ListaReservas *auxRes;

    while (auxAcom != NULL) {

        //Filtros:

        //Filtrar por dados da acomodação por id:
        if (idAcomFiltro != 0 && auxAcom->acomodacao.id != idAcomFiltro) {
            auxAcom = auxAcom->prox;
            continue;
        }

        buscarCategoria(&listaCat, &categoriaTemp, auxAcom->acomodacao.idCategoria, &posCat);

        int totalDiarias = 0;
        float rendimentoTotal = 0.0;
        auxRes = listaRes->prox;
        while (auxRes != NULL) {
            if (auxRes->reserva.idAcomodacao == auxAcom->acomodacao.id) {

                int dias = (int)(difftime(auxRes->reserva.dataSaida, auxRes->reserva.dataEntrada) / 86400.0);

                if (dias == 0) {
                    dias = 1;
                }

                totalDiarias += dias;
                rendimentoTotal += (dias * categoriaTemp.valorDiaria);
            }
            auxRes = auxRes->prox;
        }

        //Quantas diárias estiveram ocupadas:
        if (totalDiarias < minDiarias) {
            auxAcom = auxAcom->prox;
            continue;
        }

        //Quanto rendeu em hospedagem:
        if (rendimentoTotal < minRendimento) {
            auxAcom = auxAcom->prox;
            continue;
        }

        encontrouAlgum = 1;

        if (opcaoDestino == 1) {
            imprimeDadosDiaria(*auxAcom, totalDiarias, rendimentoTotal);
        }
        else if (opcaoDestino == 2 && arquivoCSV != NULL) {
            fprintf(arquivoCSV, "%d;%s;%d;%.2f\n",
                    auxAcom->acomodacao.id,
                    auxAcom->acomodacao.descricao,
                    totalDiarias,
                    rendimentoTotal);
        }

        auxAcom = auxAcom->prox;
    }

    if (encontrouAlgum == 0 && opcaoDestino == 1) {
        printf("Nenhuma movimentacao atende aos criterios dos filtros.\n");
    }

    return encontrouAlgum;
}

void interfaceRelatorioMovAcomodacoes(ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaReservas *listaRes, int opcaoDestino) {
    int idAcomFiltro = 0;
    int minDiarias = 0;
    float minRendimento = 0.0;
    FILE *arquivoCSV = NULL;
    char caminhoArquivo[150];

    system("cls");
    printf("--- Filtros: Movimentacao de Acomodacoes ---\n");
    printf("Digite o ID da acomodacao (ou 0 para todas): ");
    scanf("%d", &idAcomFiltro);

    printf("Quantidade minima de diarias ocupadas (ou 0 para ignorar): ");
    scanf("%d", &minDiarias);

    printf("Rendimento minimo gerado (R$) (ou 0 para ignorar): ");
    scanf("%f", &minRendimento);
    fflush(stdin);

    //CSV
    if (opcaoDestino == 2) {
        printf("Digite o nome/caminho do arquivo CSV (ex: relatorio_movimentacao.csv): ");
        scanf("%[^\n]", caminhoArquivo);
        fflush(stdin);

        arquivoCSV = fopen(caminhoArquivo, "w");
        if (arquivoCSV == NULL) {
            printf("Erro ao criar o arquivo CSV!\n");
            pausarTela();
            return;
        }
        //cabeçalho CSV
        fprintf(arquivoCSV, "ID_Acomodacao;Descricao;Total_Diarias_Ocupadas;Rendimento_Total\n");
    }

    printf("\nGerando relatorio...\n\n");

    relatorioMovimentacaoAcomodacoes(listaAcom, listaCat, listaRes, idAcomFiltro, minDiarias, minRendimento, opcaoDestino, arquivoCSV);

    if (opcaoDestino == 2 && arquivoCSV != NULL) {
        fclose(arquivoCSV);
        printf("\nRelatorio salvo com sucesso em: %s\n", caminhoArquivo);
    }

    pausarTela();
}


void imprimeAcomodacao(TipoAcomodacao acomodacao, TipoCategoria categoria)
{
    printf("ID                  : %d\n", acomodacao.id);
    printf("Descricao           : %s\n", acomodacao.descricao);
    printf("Facilidades         : %s\n", acomodacao.facilidades);
    printf("Valor diaria        : R$%.2f\n", categoria.valorDiaria);
    printf("Capacidade adultos  : %d\n", categoria.capacidadeAdultos);
    printf("Capacidade criancas : %d\n", categoria.capacidadeCriancas);
    printf("-----------------------------------\n");
}


void interfaceAcomodacao(ListaAcomodacao *listaAcomod, ListaCategoria *listaCat)
{
    ListaAcomodacao *pos;
    ListaCategoria *posCat;
    TipoAcomodacao acomodacao;
    TipoCategoria catAux;
    int res = 0;
    int subRes = 0;

    do
    {
        limparTela();
        printf("--- Gestao de Acomodacoes ---\n");
        printf("1 - Inserir acomodacao\n");
        printf("2 - Buscar acomodacao\n");
        printf("3 - Alterar acomodacao\n");
        printf("4 - Apagar acomodacao\n");
        printf("5 - Listar acomodacoes\n");
        printf("0 - Sair\n");
        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);

        switch (res)
        {
        case 1:
            if (listaCat->prox == NULL)
            {
                printf("Nenhuma categoria cadastrada! Cadastre uma categoria antes de cadastrar uma acomodacao.\n");
                pausarTela();
                break;
            }
            while (1)
            {
                limparTela();
                printf("ID (numero de quarto) da acomodacao: \n");
                printf("1 - Listar acomodacoes ja cadastradas\n");
                printf("2 - Digitar ID\n");
                printf("=> ");
                scanf("%d", &res);
                fflush(stdin);

                if (res == 1)
                {
                    listarIdsJaRegistradosAcomodacao(listaAcomod);
                }
                else if (res == 2)
                {
                    printf("ID da acomodacao: ");
                    scanf("%d", &acomodacao.id);
                    fflush(stdin);

                    if (buscarAcomodacao(&listaAcomod, &acomodacao, acomodacao.id, &pos) == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("Acomodacao ja cadastrada, tente novamente!\n");
                        pausarTela();
                    }
                }
                else
                {
                    printf("Escolha um valor valido...\n");
                    pausarTela();
                }
            }

            printf("Descricao da acomodacao: ");
            scanf("%[^\n]", acomodacao.descricao);
            fflush(stdin);

            printf("Facilidades: ");
            scanf("%[^\n]", acomodacao.facilidades);
            fflush(stdin);

            while (1)
            {
                limparTela();
                listarCategoria(listaCat);
                printf("\nEscolha o ID da categoria para essa acomodacao:\n");
                printf("=> ID da Categoria: ");
                scanf("%d", &acomodacao.idCategoria);

                fflush(stdin);

                if (buscarCategoria(&listaCat, &catAux, acomodacao.idCategoria, &posCat) == 0)
                {
                    break;
                }
                else
                {
                    printf("Erro: Categoria id %d nao encontrada! Tente novamente.\n", acomodacao.idCategoria);
                    pausarTela();
                }
            }
            res = inserirAcomodacao(&listaAcomod, acomodacao);
            if (res == 0)
            {
                printf("\nAcomodacao inserida com sucesso!\n");
                printf("O ID da acomodacao �: %d\n", acomodacao.id);
            }
            else
            {
                printf("\nErro ao inserir a acomodacao!\n");
            }
            pausarTela();
            res = 1;
            break;
        case 2:
            printf("Insira o id da acomodacao que deseja buscar: ");
            fflush(stdin);
            scanf("%d", &acomodacao.id);
            fflush(stdin);

            int achou = buscarAcomodacao(&listaAcomod, &acomodacao, acomodacao.id, &pos);
            if (achou == 0)
            {
                buscarCategoria(&listaCat, &catAux, acomodacao.idCategoria, &posCat);
                printf("\nAcomodacao encontrada!! -------------\n");
                printf("ID                  : %d\n", acomodacao.id);
                printf("Descricao           : %s\n", acomodacao.descricao);
                printf("Facilidades         : %s\n", acomodacao.facilidades);
                printf("Descri��o           : %s\n", catAux.descricao);
                printf("Valor diaria        : R$%.2f\n", catAux.valorDiaria);
                printf("Capacidade adultos  : %d\n", catAux.capacidadeAdultos);
                printf("Capacidade criancas : %d\n\n", catAux.capacidadeCriancas);

                pausarTela();
            }
            else
            {
                printf("\nAcomodacao nao encontrada!\n");
                pausarTela();
            }
            res = 1;
            break;
        case 3:
            printf("Digite o ID da acomodacao que deseja alterar: ");
            scanf("%d", &acomodacao.id);
            fflush(stdin);

            if (buscarAcomodacao(&listaAcomod, &acomodacao, acomodacao.id, &pos) == 0)
            {
                subRes = 0;
                while (subRes != 4 && subRes != 5)
                {
                    limparTela();
                    printf("\nAcomodacao encontrada! -------------\n");
                    printf("Digite o campo que deseja alterar: \n\n");
                    printf("1 - Descricao                    : %s\n", acomodacao.descricao);
                    printf("2 - Facilidades                  : R$ %s\n", acomodacao.facilidades);
                    printf("3 - ID Categoria                 : %d\n", acomodacao.idCategoria);

                    printf("4 - Salvar dados\n");
                    printf("5 - Cancelar\n");
                    printf("=> ");

                    scanf("%d", &subRes);
                    fflush(stdin);
                    if (subRes == 1)
                    {
                        apagarAcomodacao(pos);
                        printf("Acomodacao apagada!\n\n");
                        pausarTela();
                    }
                    else
                    {
                        printf("\nAcomodacao nao encontrada!\n\n");
                        pausarTela();
                    }
                }
            }
            res = 1;
            break;

        case 4:
            printf("Insira o id da acomodacao que deseja apagar: ");
            scanf(" %d", &acomodacao.id);
            fflush(stdin);

            int buscaRes = buscarAcomodacao(&listaAcomod, &acomodacao, acomodacao.id, &pos);
            if (buscaRes == 0)
            {
                printf("\nAcomodacao encontrada!! -------------\n");
                printf("ID                      : %d\n", acomodacao.id);
                printf("Descricao               : %s\n", acomodacao.descricao);
                printf("Facilidades             : %s\n", acomodacao.facilidades);
                printf("ID Categoria            : %d\n", acomodacao.idCategoria);

                printf("Tem certeza que deseja apagar essa acomodacao?\n");
                printf("1 - Apagar\n");
                printf("2 - Cancelar\n");
                printf("=> ");

                scanf("%d", &subRes);
                fflush(stdin);
                if (subRes == 1)
                {
                    apagarAcomodacao(pos);
                    printf("Acomodacao apagada!\n\n");
                    pausarTela();
                }
                printf("Dados salvos com sucesso!\n");
                pausarTela();
            }
            res = 1;
            break;
        case 5:
            limparTela();
            listarAcomodacao(listaAcomod, listaCat);
            pausarTela();
            break;
        default:
            if (res != 0)
            {
                printf("Opcao invalida\n");
                pausarTela();
                break;
            }
        }
    } while (res != 0);
    return;
}