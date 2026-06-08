#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bib/categorias.h"
#include "../bib/utils.h"

#define BIN 1
#define TXT 2
#define MEM 3

ListaCategoria *iniciaListaCategoria()
{
    ListaCategoria *lista = malloc(sizeof(ListaCategoria));

    if (lista)
    {
        lista->categoria.id = 0;
        lista->prox = NULL;
    }
    return lista;
}

int escolheIdCategoria(ListaCategoria *lista)
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

int inserirCategoria(ListaCategoria **lista, TipoCategoria categoria)
{
    ListaCategoria *aux, *novaCategoria = malloc(sizeof(ListaCategoria));

    if (novaCategoria)
    {
        aux = *lista;
        novaCategoria->categoria = categoria;
        novaCategoria->prox = NULL;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novaCategoria;
        return 0;
    }
    return 1;
}

int buscarCategoria(ListaCategoria **lista, TipoCategoria *categoria, int id, ListaCategoria **pos)
{

    if (lista == NULL || *lista == NULL || (*lista)->prox == NULL)
        return 1;

    ListaCategoria *aux = (*lista)->prox;

    while (aux != NULL)
    {
        // printf("DEBUG: Verificando ID %d na lista...\n", aux->categoria.id);
        if (aux->categoria.id == id && aux->categoria.id != 0)
        {
            if(categoria != NULL)
                *categoria = aux->categoria;
            if(pos != NULL)
                *pos = aux;
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

void alterarCategoria(ListaCategoria *pos, TipoCategoria categoria)
{
    pos->categoria = categoria;
}

void apagarCategoria(ListaCategoria *pos)
{
    pos->categoria.id = 0;
}

void listarCategoria(ListaCategoria *lista)
{
    if (lista->prox == NULL)
    {
        printf("Nenhuma categoria cadastrada.\n");
    }
    else
    {
        lista = lista->prox;
        printf("\nCategorias de acomodacao:\n");

        while (lista != NULL)
        {
            if (lista->categoria.id != 0)
            {
                imprimeCategoria(lista->categoria);
            }
            lista = lista->prox;
        }
    }
}

int salvarDadosCategoriasTxt(ListaCategoria *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        system("pause");
        return 1;
    }

    if (lista->prox != NULL)
    {
        ListaCategoria *aux = lista->prox;

        fprintf(arquivo, "<tabela=>categorias>\n");
        while (aux != NULL)
        {
            fprintf(arquivo, "    <registro>\n");
            fprintf(arquivo, "        <codigo>%d</codigo>\n", aux->categoria.id);
            fprintf(arquivo, "        <descricao>%s</descricao>\n", aux->categoria.descricao);
            fprintf(arquivo, "        <valor_diaria>%.2f</valor_diaria>\n", aux->categoria.valorDiaria);
            fprintf(arquivo, "        <capacidade_adultos>%d</capacidade_adultos>\n", aux->categoria.capacidadeAdultos);
            fprintf(arquivo, "        <capacidade_criancas>%d</capacidade_criancas>\n", aux->categoria.capacidadeCriancas);
            fprintf(arquivo, "    </registro>\n");
            aux = aux->prox;
        }
        fprintf(arquivo, "</tabela>\n");
    }
    fclose(arquivo);
    return 0;
}

int salvarDadosCategoriasBin(ListaCategoria *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        system("pause");
        return 1;
    }

    ListaCategoria *aux = lista->prox;

    while (aux != NULL)
    {
        if (aux->categoria.id != 0)
        {
            fwrite(&aux->categoria, sizeof(TipoCategoria), 1, arquivo);
        }
        aux = aux->prox;
    }
    fclose(arquivo);
    return 0;
}

ListaCategoria *carregarCategoriasBin(char *nome_arquivo)
{
    TipoCategoria categoria;
    ListaCategoria *lista = iniciaListaCategoria();
    int res;

    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL)
        return lista;

    while (fread(&categoria, sizeof(TipoCategoria), 1, arquivo))
        res = inserirCategoria(&lista, categoria);

    if (res == 1)
        printf("Erro ao carregar categorias do arquivo binÿrio!\n");

    fclose(arquivo);
    return lista;
}

ListaCategoria *carregarCategoriasTxt(char *nome_arquivo)
{
    ListaCategoria *lista = iniciaListaCategoria();
    TipoCategoria categoria;

    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL)
        return lista;

    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(&categoria, 0, sizeof(TipoCategoria));
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            inserirCategoria(&lista, categoria);
            continue;
        }

        sscanf(linha, " <codigo>%d", &categoria.id);
        sscanf(linha, " <descricao>%[^<]", categoria.descricao);
        sscanf(linha, " <valor_diaria>%f", &categoria.valorDiaria);
        sscanf(linha, " <capacidade_adultos>%d", &categoria.capacidadeAdultos);
        sscanf(linha, " <capacidade_criancas>%d", &categoria.capacidadeCriancas);
    }
    fclose(arquivo);
    return lista;
}

void liberaListaCategorias(ListaCategoria *lista)
{
    ListaCategoria *temp, *aux = lista;
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }
    return;
}

void imprimeCategoria(TipoCategoria categoria)
{
    printf("ID                    : %d\n", categoria.id);
    printf("Descricao             : %s\n", categoria.descricao);
    printf("Valor da diaria       : %.2f\n", categoria.valorDiaria);
    printf("Capacidade de adultos : %d\n", categoria.capacidadeAdultos);
    printf("Capacidade de criancas: %d\n", categoria.capacidadeCriancas);
    printf("-----------------------------------\n");
}

void interfaceCategoria(ListaCategoria *listaCategorias)
{
    ListaCategoria *pos;
    TipoCategoria categoria;
    int res = 0;
    int subRes = 0;

    // gestao de categorias
    do
    {
        system("cls");

        printf("--- Gestao de Categorias ---\n");
        printf("1 - Inserir categoria\n");
        printf("2 - Buscar categoria\n");
        printf("3 - Alterar categoria\n");
        printf("4 - Apagar categoria\n");
        printf("5 - Listar categorias\n");
        printf("0 - Sair\n");
        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);

        switch (res)
        {
        case 1:
            system("cls");
            printf("Descricao da categoria (ex: Luxo): ");
            scanf("%[^\n]", categoria.descricao);
            fflush(stdin);

            printf("Valor da diaria: ");
            scanf("%f", &categoria.valorDiaria);
            fflush(stdin);

            printf("Capacidade de adultos: ");
            scanf("%d", &categoria.capacidadeAdultos);
            fflush(stdin);

            printf("Capacidade de criancas: ");
            scanf("%d", &categoria.capacidadeCriancas);
            fflush(stdin);

            categoria.id = escolheIdCategoria(listaCategorias);

            if (inserirCategoria(&listaCategorias, categoria) == 0)
            {
                printf("Categoria cadastrada com sucesso! Id: %d\n", categoria.id);
            }
            else
            {
                printf("\nErro ao cadastrar!\n");
            }
            system("pause");
            break;
        case 2:
            printf("Insira o id da categoria que deseja buscar: ");
            scanf("%d", &categoria.id);
            fflush(stdin);

            int achou = buscarCategoria(&listaCategorias, &categoria, categoria.id, &pos);
            if (achou == 0)
            {
                printf("\nCategoria encontrada!! -------------\n");
                printf("ID                    : %d\n", categoria.id);
                printf("Descricao             : %s\n", categoria.descricao);
                printf("Valor da diaria       : %.2f\n", categoria.valorDiaria);
                printf("Capacidade de adultos : %d\n", categoria.capacidadeAdultos);
                printf("Capacidade de criancas: %d\n", categoria.capacidadeCriancas);

                system("pause");
            }
            else
            {
                printf("\nCategoria nao encontrada!\n");
                system("pause");
            }
            break;
        case 3:
            printf("Digite o ID da categoria que deseja alterar: ");
            scanf("%d", &categoria.id);
            fflush(stdin);

            if (buscarCategoria(&listaCategorias, &categoria, categoria.id, &pos) == 0)
            {
                subRes = 0;
                while (subRes != 5 && subRes != 6)
                {
                    system("cls");
                    printf("\nCategoria encontrada! -------------\n");
                    printf("Digite o campo que deseja alterar: \n\n");
                    printf("1 - Descricao                    : %s\n", categoria.descricao);
                    printf("2 - Valor da diaria              : R$ %.2f\n", categoria.valorDiaria);
                    printf("3 - Capacidade de adultos        : %d\n", categoria.capacidadeAdultos);
                    printf("4 - Capacidade de criancas       : %d\n", categoria.capacidadeCriancas);

                    printf("5 - Salvar dados\n");
                    printf("6 - Cancelar\n");
                    printf("=> ");

                    scanf("%d", &subRes);
                    fflush(stdin);

                    switch (subRes)
                    {
                    case 1:
                        printf("Insira a nova descricao: ");
                        scanf("%[^\n]", categoria.descricao);
                        fflush(stdin);
                        break;
                    case 2:
                        printf("Insira o novo valor da diaria: ");
                        scanf("%f", &categoria.valorDiaria);
                        fflush(stdin);
                        break;
                    case 3:
                        printf("Insira a nova capacidade de adultos: ");
                        scanf("%d", &categoria.capacidadeAdultos);
                        fflush(stdin);
                        break;
                    case 4:
                        printf("Insira a nova capacidade de criancas: ");
                        scanf("%d", &categoria.capacidadeCriancas);
                        fflush(stdin);
                        break;
                    case 5:
                        alterarCategoria(pos, categoria);
                        printf("Dados atualizados com sucesso!\n");
                        system("pause");
                        break;
                    case 6:
                        printf("Alteracao cancelada:\n");
                        system("pause");
                        break;
                    default:
                        printf("Escolha um valor valido...\n");
                        system("pause");
                        break;
                    }
                }
            }
            else
            {
                printf("Categoria nao encontrada!\n");
                system("pause");
            }
            break;

        case 4:
            printf("Digite o ID da categoria que deseja apagar: ");
            scanf("%d", &categoria.id);
            fflush(stdin);

            if (buscarCategoria(&listaCategorias, &categoria, categoria.id, &pos) == 0)
            {
                apagarCategoria(pos);
                printf("Categoria removida!\n");
            }
            else
            {
                printf("Categoria nao encontrada!\n");
            }
            system("pause");
            break;
        case 5:
            system("cls");
            listarCategoria(listaCategorias);
            system("pause");
            break;
        default:
            if (res != 0)
            {
                printf("Escolha um valor valido...\n");
                system("pause");
            }
            break;
        }
    } while (res != 0);
}