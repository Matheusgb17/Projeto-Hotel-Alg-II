#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../bib/produtos.h"

#define ProdutosBIN "./data/bin/produtos.dat"
#define ProdutosTXT "./data/txt/produtos.txt"

#define BIN 1
#define TXT 2
#define MEM 3

// ;)
int escolheIdProduto(ListaProduto *lista)
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

void listarProdutos(ListaProduto *lista)
{
    if (lista->prox == NULL)
    {
        printf("Nenhum Produto cadastrado\n");
    }
    else
    {
        lista = lista->prox;
        printf("\nProduto ---------\n");
        while (lista != NULL)
        {
            if (lista->Produto.id != 0)
            {
                printf("Id                     : %d\n", lista->Produto.id);
                printf("Descri‡Æo              : %s\n\n", lista->Produto.descricao);
                printf("Estoque                : %d\n", lista->Produto.estoque);
                printf("Estoque minimo         : %d\n", lista->Produto.estoque_minimo);
                printf("Preco custo            : R$%.2f\n", lista->Produto.preco_custo);
                printf("Preco venda            : R$%.2f\n", lista->Produto.preco_venda);
                printf("-------------------\n");
            }
            lista = lista->prox;
        }
        system("pause");
    }
}

ListaProduto *iniciaListaProduto()
{
    ListaProduto *Lista = malloc(sizeof(ListaProduto));

    Lista->Produto.id = 0;
    Lista->prox = NULL;

    return Lista;
}

int inserirProduto(ListaProduto **lista, TipoProduto Produto)
{
    ListaProduto *aux, *novoProduto = malloc(sizeof(ListaProduto));
    if (novoProduto)
    {
        aux = *lista;
        novoProduto->Produto = Produto;
        novoProduto->prox = NULL;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novoProduto;
        return 0;
    }
    printf("Erro ao inserir...\n");
    return 1;
}

int buscarProduto(ListaProduto **lista, TipoProduto *produto, int id, ListaProduto **pos)
{
    if (id == 0)
    {
        return 1;
    }

    if ((*lista)->prox == NULL)
        return 1;

    ListaProduto *aux = (*lista)->prox;

    while (aux != NULL && (aux->Produto.id != id))
        aux = aux->prox;

    if (aux == NULL)
        return 1;

    if (id == aux->Produto.id)
    {
        *produto = aux->Produto;
        *pos = aux;
        return 0;
    }

    return 1;
}

void alterarProduto(ListaProduto *pos, TipoProduto Produto)
{
    pos->Produto = Produto;
    return;
}

void apagarProduto(ListaProduto *pos)
{
    pos->Produto.id = 0;
    return;
}

void listarProduto(ListaProduto *lista)
{
    if (lista->prox == NULL)
    {
        printf("Nenhum Produto cadastrado\n");
        system("pause");
    }
    else
    {
        lista = lista->prox;
        printf("\nProduto ---------\n");
        while (lista != NULL)
        {
            printf("Id                     : %d\n", lista->Produto.id);
            printf("Descri‡Æo              : %s\n\n", lista->Produto.descricao);
            printf("Estoque                : %d\n", lista->Produto.estoque);
            printf("Estoque minimo         : %d\n", lista->Produto.estoque_minimo);
            printf("Preco custo            : %f\n", lista->Produto.preco_custo);
            printf("Preco venda            : %f\n", lista->Produto.preco_venda);
            printf("-------------------\n");
            lista = lista->prox;
        }
        system("pause");
    }
}

int salvarDadosProdutosBin(ListaProduto *lista, char *nome_arquivo)
{
    FILE *arq = fopen(nome_arquivo, "wb");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo...\n\n");
        system("pause");
        return 1;
    }

    ListaProduto *aux = lista->prox;
    while (aux != NULL)
    {
        fwrite(&(aux->Produto), sizeof(TipoProduto), 1, arq);
        aux = aux->prox;
    }
    fclose(arq);
    return 0;
}

ListaProduto *resgataDadosProdutosBin(char *nome_arquivo)
{
    TipoProduto produto;
    ListaProduto *lista = iniciaListaProduto();
    int res;

    FILE *arq = fopen(nome_arquivo, "rb");
    if (arq == NULL)
    {
        return lista;
    }

    while (fread(&produto, sizeof(TipoProduto), 1, arq) == 1)
        res = inserirProduto(&lista, produto);

    if (res == 1)
        printf("Erro ao carregar produto do arquivo binario!\n");

    fclose(arq);
    return lista;
}

int salvarDadosProdutosTxt(ListaProduto *lista, char *nome_arquivo)
{
    FILE *arq = fopen(nome_arquivo, "w");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo...\n\n");
        system("pause");
        return 1;
    }

    if (lista->prox != NULL)
    {
        ListaProduto *aux = lista->prox;
        fprintf(arq, "<tabela=produto>\n");
        while (aux != NULL)
        {
            fprintf(arq, "        <registro>\n");
            fprintf(arq, "        <codigo>%d</codigo>\n", aux->Produto.id);
            fprintf(arq, "        <descricao>%s</descricao>\n", aux->Produto.descricao);
            fprintf(arq, "        <estoque>%d</estoque>\n", aux->Produto.estoque);
            fprintf(arq, "        <estoque_minimo>%d</estoque_minimo>\n", aux->Produto.estoque_minimo);
            fprintf(arq, "        <preco_custo>%f</preco_custo>\n", aux->Produto.preco_custo);
            fprintf(arq, "        <preco_venda>%f</preco_venda>\n", aux->Produto.preco_venda);

            fprintf(arq, "        </registro>\n");
            aux = aux->prox;
        }
        fprintf(arq, "</tabela>\n");
    }
    fclose(arq);
    return 0;
}

ListaProduto *resgataDadosProdutosTxt(char *nome_arquivo)
{
    ListaProduto *lista = iniciaListaProduto();
    TipoProduto produto;

    FILE *arq = fopen(nome_arquivo, "r");
    if (arq == NULL)
    {
        return lista;
    }

    char linha[256];

    while (fgets(linha, sizeof(linha), arq) != NULL)
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(&produto, 0, sizeof(TipoProduto));
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            inserirProduto(&lista, produto);
            continue;
        }

        sscanf(linha, " <codigo>%d", &produto.id);
        sscanf(linha, " <descricao>%[^<]", produto.descricao);
        sscanf(linha, " <estoque>%d", &produto.estoque);
        sscanf(linha, " <estoque_minimo>%d", &produto.estoque_minimo);
        sscanf(linha, " <preco_custo>%f", &produto.preco_custo);
        sscanf(linha, " <preco_venda>%f", &produto.preco_venda);
    }
    fclose(arq);
    return lista;
}

void liberaListaProdutos(ListaProduto *lista)
{
    ListaProduto *temp, *aux = lista;
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }
}

void interfaceProduto(ListaProduto *listaProduto)
{
    ListaProduto *pos;
    TipoProduto Produto;
    int res = 0;

    do
    {
        system("cls");
        printf("Cadastro e gestao de Produtos!\n");
        printf("1 - Inserir Produto\n");
        printf("2 - Buscar Produto\n");
        printf("3 - Alterar Produto\n");
        printf("4 - Apagar Produto\n");
        printf("5 - Listar Produtos\n");
        printf("0 - Sair\n");

        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);
        system("cls");

        if (res == 0)
        {
            break;
        }

        switch (res)
        {
        // Inserir Produto
        case 1:
            printf("Insira o nome: ");
            scanf(" %[^\n]", Produto.descricao);
            fflush(stdin);

            printf("Insira o estoque: ");
            scanf("%d", &Produto.estoque);
            fflush(stdin);

            printf("Insira o estoque minimo: ");
            scanf("%d", &Produto.estoque_minimo);
            fflush(stdin);

            printf("Insira o preco de custo: ");
            scanf("%f", &Produto.preco_custo);
            fflush(stdin);

            printf("Insira o preco de venda: ");
            scanf("%f", &Produto.preco_venda);
            fflush(stdin);

            Produto.id = escolheIdProduto(listaProduto);

            res = inserirProduto(&listaProduto, Produto);

            if (res == 0)
            {
                printf("\nProduto inserido com sucesso!\n");
                printf("\nO ID do Produto %s e: %d\n", Produto.descricao, Produto.id);
                system("pause");
            }
            else
            {
                printf("\nFalha ao inserir o produto!\n");
                system("pause");
            }
            res = 1;
            break;

            // Buscar Produto
        case 2:
            printf("Insira o ID do Produto que deseja buscar: ");
            scanf("%d", &Produto.id);
            fflush(stdin);

            res = buscarProduto(&listaProduto, &Produto, Produto.id, &pos);
            if (res == 0)
            {
                printf("\nProduto encontrado! -------------\n");
                printf("ID                     : %d\n", Produto.id);
                printf("Descricao              : %s\n", Produto.descricao);
                printf("Estoque                : %d\n", Produto.estoque);
                printf("Estoque minimo         : %d\n", Produto.estoque_minimo);
                printf("Preco custo            : R$%.2f\n", Produto.preco_custo);
                printf("Preco venda            : R$%.2f\n", Produto.preco_venda);
                system("pause");
            }
            else
            {
                printf("\nProduto nao encontrado!\n");
                system("pause");
            }

            break;

        // Alterar funcionario
        case 3:

            printf("Insira o ID do Produto que deseja alterar: ");
            scanf("%d", &Produto.id);
            fflush(stdin);

            res = buscarProduto(&listaProduto, &Produto, Produto.id, &pos);
            if (res == 0)
            {
                while (res != 7)
                {
                    system("cls");
                    printf("\nProduto encontrado! -------------\n");
                    printf("ID (fixo)                 : %d\n", Produto.id);
                    printf("1- Descricao              : %s\n", Produto.descricao);
                    printf("2- Estoque                : %d\n", Produto.estoque);
                    printf("3- Estoque minimo         : %d\n", Produto.estoque_minimo);
                    printf("4- Preco custo            : R$%.2f\n", Produto.preco_custo);
                    printf("5- Preco venda            : R$%.2f\n", Produto.preco_venda);

                    printf("6- Salvar dados\n");
                    printf("0- Cancelar \n");
                    printf("=> ");
                    scanf("%d", &res);

                    if (res == 0)
                    {
                        break;
                    }

                    fflush(stdin);

                    switch (res)
                    {
                    case 1:
                        printf("Insira a nova descricao: \n");
                        scanf(" %[^\n]", Produto.descricao);
                        fflush(stdin);
                        break;
                    case 2:
                        printf("Insira o estoque: \n");
                        scanf("%d", &Produto.estoque);
                        fflush(stdin);
                        break;
                    case 3:
                        printf("Insira o estoque minimo: \n");
                        scanf("%d", &Produto.estoque_minimo);
                        fflush(stdin);
                        break;
                    case 4:
                        printf("Insira o preco de custo: R$");
                        scanf("%f", &Produto.preco_custo);
                        fflush(stdin);
                        break;
                    case 5:
                        printf("Insira o preco de venda: R$");
                        scanf("%f", &Produto.preco_venda);
                        fflush(stdin);
                        break;
                    case 6:
                        alterarProduto(pos, Produto);
                        break;
                    default:
                        printf("Insira uma opcao valida...");
                        system("pause");
                        break;
                    }
                }
            }
            else
            {
                printf("\nProduto nao encontrado!\n");
                system("pause");
            }

            break;

        case 4:
            printf("Digite o ID do Produto que deseja apagar: ");
            scanf("%d", &Produto.id);
            fflush(stdin);

            res = buscarProduto(&listaProduto, &Produto, Produto.id, &pos);

            if (res == 0)
            {
                printf("1- ID                     : %d\n", Produto.id);
                printf("2- Descricao              : %s\n", Produto.descricao);
                printf("3- Estoque                : %d\n", Produto.estoque);
                printf("4- Estoque minimo         : %d\n", Produto.estoque_minimo);
                printf("5- Preco custo            : R$%.2f\n", Produto.preco_custo);
                printf("6- Preco venda            : R$%.2f\n", Produto.preco_venda);

                printf("Tem certeza que deseja apagar esse Produto?\n");
                printf("1- Sim \n");
                printf("2- Nao \n");
                printf("=> ");
                scanf("%d", &res);
                fflush(stdin);

                if (res == 1)
                {
                    apagarProduto(pos);
                    printf("\nProduto apagado com sucesso!\n");
                    system("pause");
                    fflush(stdin);
                }
            }
            else
            {
                printf("Usuario nao encontrado!\n");
                system("pause");
            }
            break;
        case 5:
            listarProdutos(listaProduto);
            break;
        default:
            if (res != 6)
            {
                printf("Selecione uma opcao valida!\n");
                system("pause");
                fflush(stdin);
            }
            break;
        }
    } while (res != 0);
}