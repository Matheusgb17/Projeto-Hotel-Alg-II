#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bib/acomodacoes.h"
#include "../bib/utils.h"

#define AcomodacoesBIN "./data/bin/acomodacoes.dat"
#define AcomodacoesTXT "./data/txt/acomodacoes.txt"

#define BIN 1
#define TXT 2

ListaAcomodacao* iniciaListaAcomodacao() {
    ListaAcomodacao *lista = malloc(sizeof(ListaAcomodacao));

    if (lista) {
        lista->acomodacao.id = 0;
        lista->prox = NULL;
    }
    return lista;
}

int escolheIdAcomodacao(ListaAcomodacao *lista) {
    int maiorId = 0;
    ListaAcomodacao *aux = lista->prox;

    while (aux != NULL) {
        if (aux->acomodacao.id > maiorId) {
            maiorId = aux->acomodacao.id;
        }
        aux = aux->prox;
    }
    return maiorId + 1;
}
int inserirAcomodacao(ListaAcomodacao **lista, TipoAcomodacao acomodacao) {
    ListaAcomodacao *aux, *novaAcomodacao = malloc(sizeof(ListaAcomodacao));

    if (novaAcomodacao) {
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

int buscarAcomodacao(ListaAcomodacao **lista, TipoAcomodacao *acomodacao, int id, ListaAcomodacao **pos) {

    if (lista == NULL || *lista == NULL)
        return 1;

    ListaAcomodacao *aux = (*lista)->prox;

    while (aux != NULL) {
        //printf("DEBUG: Comparando ID digitado (%d) com ID no no (%d)\n", id, aux->acomodacao.id);
        if (aux->acomodacao.id == id && aux->acomodacao.id != 0) {
            if (acomodacao != NULL) *acomodacao = aux->acomodacao;
            if (pos != NULL) *pos = aux;
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

void alterarAcomodacao(ListaAcomodacao *pos, TipoAcomodacao acomodacao) {
    pos->acomodacao = acomodacao;
}

void apagarAcomodacao(ListaAcomodacao *pos) {
    pos->acomodacao.id = 0;
}

void listarAcomodacao(ListaAcomodacao *lista, ListaCategoria *listaCat) {
    if (lista->prox == NULL) {
        printf("Nenhuma acomodacao cadastrada.\n");
    } else {
        lista = lista->prox;
        printf("\nAcomodacoes cadastradas:\n");

        while (lista != NULL) {
            if (lista->acomodacao.id != 0) {
                printf("ID           : %d\n", lista->acomodacao.id);
                printf("Descricao    : %s\n", lista->acomodacao.descricao);
                printf("Facilidades  : %s\n", lista->acomodacao.facilidades);
                printf("ID categoria : %d\n", lista->acomodacao.idCategoria);
                printf("-----------------------------------\n");
            }
            lista = lista->prox;
        }
    }
}

void salvaDadosAcomodacoesBin(ListaAcomodacao *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao acessar o arquivo...\n\n");
        system("pause");
        return;
    }
    ListaAcomodacao *aux = lista->prox;
    while (aux != NULL)
    {
        if (aux->acomodacao.id != 0) {
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

void salvaDadosAcomodacoesTxt(ListaAcomodacao *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao acessar o arquivo...\n\n");
        system("pause");
        return;
    }

    if (lista->prox != NULL)
    {
        ListaAcomodacao *aux = lista->prox;

        fprintf(arquivo, "<tabela=acomodacao>\n");
        while (aux != NULL)
        {
            if (aux->acomodacao.id != 0) {
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

void interfaceAcomodacao(int modo) {
    ListaAcomodacao *pos, *listaAcomod;
    ListaCategoria *posCat, *listaCat;
    TipoAcomodacao acomodacao;
    TipoCategoria catAux;
    int res = 0;
    int subRes = 0;

    listaAcomod = resgataDadosAcomodacoesBin(AcomodacoesBIN);
    if (listaAcomod->prox == NULL) {
        free(listaAcomod);
        listaAcomod = resgataDadosAcomodacoesTxt(AcomodacoesTXT);
    }

    if (listaAcomod->prox == NULL) {
        //printf("DEBUG: A lista de acomodacoes esta VAZIA apos o carregamento!\n");
        system("pause");
    } else {
        printf("DEBUG: Lista carregada com sucesso.\n");
        system("pause");
    }

    listaCat = iniciaListaCategoria();
    carregarCategorias(&listaCat);

    do {
        system("cls");

        printf("--- Gestao de Acomodacoes ---\n");
        printf("1 - Inserir acomodacao\n");
        printf("2 - Buscar acomodacao\n");
        printf("3 - Alterar acomodacao\n");
        printf("4 - Apagar acomodacao\n");
        printf("5 - Listar acomodacoes\n");
        printf("6 - Sair\n");
        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);

        switch (res) {
            case 1:
                system("cls");
                printf("Descricao: ");
                scanf("%[^\n]", acomodacao.descricao);
                fflush(stdin);

                printf("Facilidades: ");
                scanf("%[^\n]", acomodacao.facilidades);
                fflush(stdin);

                printf("ID da categoria: ");
                scanf("%d", &acomodacao.idCategoria);
                fflush(stdin);

                acomodacao.id = escolheIdAcomodacao(listaAcomod);

                // verifica se o idCategoria existe
                if (buscarCategoria(&listaCat, &catAux, acomodacao.idCategoria, &posCat) == 0) {
                    acomodacao.id = escolheIdAcomodacao(listaAcomod);
                    if (inserirAcomodacao(&listaAcomod, acomodacao) == 0) {
                        printf("\n Acomodacao cadastrada com sucesso! ID: %d\n", acomodacao.id);
                    } else {
                        printf("\nErro ao alocar memoria!\n");
                    }
                } else {
                    printf("\nErro: Categoria id %d nao encontrada! Cadastro cancelado.\n", acomodacao.idCategoria);
                }

                system("pause");
                break;
            case 2:
                printf("Insira o id da acomodacao que deseja buscar: ");
                fflush(stdin);
                scanf("%d", &acomodacao.id);
                fflush(stdin);

                int achou = buscarAcomodacao(&listaAcomod, &acomodacao, acomodacao.id, &pos);
                if (achou == 0)
                {
                    printf("\nAcomodacao encontrada!! -------------\n");
                    printf("ID           : %d\n", acomodacao.id);
                    printf("Descricao    : %s\n", acomodacao.descricao);
                    printf("Facilidades  : %s\n", acomodacao.facilidades);
                    printf("ID Categoria : %d\n", acomodacao.idCategoria);

                    system("pause");
                }
                else
                {
                    printf("\nAcomodacao nao encontrada!\n");
                    system("pause");
                }
                break;
            case 3:
                printf("Digite o ID da acomodacao que deseja alterar: ");
                scanf("%d", &acomodacao.id);
                fflush(stdin);

                if (buscarAcomodacao(&listaAcomod, &acomodacao, acomodacao.id, &pos) == 0){
                    subRes = 0;
                    while (subRes != 4 && subRes != 5) {
                        system("cls");
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

                        switch (subRes) {
                            case 1:
                                printf("Insira a nova descricao: ");
                                scanf("%[^\n]", acomodacao.descricao);
                                fflush(stdin);
                                break;
                            case 2:
                                printf("Insira as novas facilidades: ");
                                scanf("%[^\n]", acomodacao.facilidades);
                                fflush(stdin);
                                break;
                            case 3:
                                printf("Insira o novo ID Categoria: ");
                                scanf("%d", &acomodacao.idCategoria);
                                fflush(stdin);
                                break;
                            case 4:
                                if (buscarCategoria(&listaCat, &catAux, acomodacao.idCategoria, &posCat) == 0) {
                                    alterarAcomodacao(pos, acomodacao);
                                    printf("Dados atualizados!\n");
                                } else {
                                    printf("Erro: Categoria nao existe! Alteracao nao pode ser feita.\n");
                                    subRes = 0;
                                }
                                system("pause");
                                break;
                            case 5:
                                printf("Alteracao cancelada:\n");
                                system("pause");
                                break;
                            default:
                                printf("Escolha um valor valido...\n");
                                system("pause");
                                break;
                        }
                    }
                } else {
                    printf("Acomodacao nao encontrada!\n");
                    system("pause");
                }
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
                        system("pause");
                    }
                }
                else
                {
                    printf("\nAcomodacao nao encontrada!\n\n");
                    system("pause");
                }
                break;
            case 5:
                system("cls");
                listarAcomodacao(listaAcomod, listaCat);
                system("pause");
                break;
            case 6:
                system("cls");
                printf("Salvando dados e encerrando modulo...");
                if (modo == BIN) {
                    salvaDadosAcomodacoesBin(listaAcomod, AcomodacoesBIN);
                    apagaArquivo(AcomodacoesTXT);
                }
                else if (modo == TXT) {
                    salvaDadosAcomodacoesTxt(listaAcomod, AcomodacoesTXT);
                    apagaArquivo(AcomodacoesBIN);
                }
                printf("Dados salvos com sucesso!\n");
                system("pause");
                break;
            default:
                printf("Opcao invalida\n");
                system("pause");
                break;
        }
    } while (res != 6);
}
