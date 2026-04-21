#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bib/categorias.h"

ListaCategoria *iniciaListaCategoria() {
    ListaCategoria *lista = malloc(sizeof(ListaCategoria));

    if (lista) {
        lista->categoria.id = 0;
        lista->prox = NULL;
    }
    return lista;
}

int escolheIdCategoria(ListaCategoria *lista) {
    int cont = 0;
    lista = lista->prox;

    while (lista != NULL) {
        cont++;
        lista = lista->prox;
    }
    return cont + 1;
}

int inserirCategoria(ListaCategoria **lista, TipoCategoria categoria) {
    ListaCategoria *aux, *novaCategoria = malloc(sizeof(ListaCategoria));

    if (novaCategoria) {
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

int buscarCategoria(ListaCategoria **lista, TipoCategoria *categoria, int id, ListaCategoria **pos) {

    if (lista == NULL || *lista == NULL || (*lista)->prox == NULL)
        return 1;

    ListaCategoria *aux = (*lista)->prox;

    while (aux != NULL) {
        //printf("DEBUG: Verificando ID %d na lista...\n", aux->categoria.id);
        if (aux->categoria.id == id && aux->categoria.id != 0) {
            *categoria = aux->categoria;
            *pos = aux;
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

void alterarCategoria(ListaCategoria *pos, TipoCategoria categoria) {
    pos->categoria = categoria;
}

void apagarCategoria(ListaCategoria *pos) {
    pos->categoria.id = 0;
}

void listarCategoria(ListaCategoria *lista) {
    if (lista->prox == NULL) {
        printf("Nenhuma categoria cadastrada.\n");
    } else {
        lista = lista->prox;
        printf("\nCategorias de acomodacao:\n");

        while (lista != NULL) {
            if (lista->categoria.id != 0) {
                printf("Id                    : %d\n", lista->categoria.id);
                printf("Descricao             : %s\n", lista->categoria.descricao);
                printf("Valor da diaria       : %.2f\n", lista->categoria.valorDiaria);
                printf("Capacidade de adultos : %d\n", lista->categoria.capacidadeAdultos);
                printf("Capacidade de criancas: %d\n", lista->categoria.capacidadeCriancas);
                printf("-----------------------------------\n");
            }
            lista = lista->prox;
        }
    }
}

void salvarCategoriasTXT(ListaCategoria *lista) {
    FILE *arquivo = fopen("../dados/categorias.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    ListaCategoria *aux = lista->prox;

    while (aux != NULL) {
        if (aux->categoria.id != 0) {
            fprintf(arquivo, "%d;%s;%.2f;%d;%d\n\n",
                aux->categoria.id,
                aux->categoria.descricao,
                aux->categoria.valorDiaria,
                aux->categoria.capacidadeAdultos,
                aux->categoria.capacidadeCriancas);
        }
        aux = aux->prox;
    }
    fclose(arquivo);
    printf("Dados exportados para categorias.txt com sucesso!\n");
}

void salvarCategoriasBIN(ListaCategoria *lista) {
    FILE *arquivo = fopen("../dados/categorias.bin", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    ListaCategoria *aux = lista->prox;

    while (aux != NULL) {
        if (aux->categoria.id != 0) {
            fwrite(&aux->categoria, sizeof(TipoCategoria), 1, arquivo);
        }
        aux = aux->prox;
    }
    fclose(arquivo);
    printf("Dados salvos em categorias.bin com sucesso!\n");
}

void carregarCategorias(ListaCategoria **lista) {
    FILE *arquivo = fopen("categorias.bin", "rb");

    if (arquivo == NULL) {
        return;
    }

    TipoCategoria catTemporaria;

    while (fread(&catTemporaria, sizeof(TipoCategoria), 1, arquivo)) {
        inserirCategoria(lista, catTemporaria);
    }
    fclose(arquivo);
    //printf("Dados carregados com sucesso!\n");
}

void interfaceCategoria() {
    ListaCategoria *pos, *listaCategorias = iniciaListaCategoria();
    TipoCategoria categoria;
    int res = 0;
    int subRes = 0;

    carregarCategorias(&listaCategorias);

    // gestao de categorias
    do {
        system("cls");

        printf("--- Gestao de Categorias ---\n");
        printf("1 - Inserir categoria\n");
        printf("2 - Buscar categoria\n");
        printf("3 - Alterar categoria\n");
        printf("4 - Apagar categoria\n");
        printf("5 - Listar categorias\n");
        printf("6 - Salvar dados em txt\n");
        printf("7 - Salvar dados em bin\n");
        printf("8 - Sair\n");
        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);

        switch (res) {
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

                if (inserirCategoria(&listaCategorias, categoria) == 0) {
                    printf("Categoria cadastrada com sucesso! Id: %d\n", categoria.id);
                } else {
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

                if (buscarCategoria(&listaCategorias, &categoria, categoria.id, &pos) == 0){
                    subRes = 0;
                    while (subRes != 5 && subRes != 6) {
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

                        switch (subRes) {
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
                } else {
                    printf("Categoria nao encontrada!\n");
                    system("pause");
                }
                break;

            case 4:
                printf("Digite o ID da categoria que deseja apagar: ");
                scanf("%d", &categoria.id);
                fflush(stdin);

                if (buscarCategoria(&listaCategorias, &categoria, categoria.id, &pos) == 0) {
                    apagarCategoria(pos);
                    printf("Categoria removida!\n");
                } else {
                    printf("Categoria nao encontrada!\n");
                }
                system("pause");
                break;
            case 5:
                system("cls");
                listarCategoria(listaCategorias);
                system("pause");
                break;
            case 6:
                salvarCategoriasTXT(listaCategorias);
                system("pause");
                break;
            case 7:
                salvarCategoriasBIN(listaCategorias);
                system("pause");
                break;
            case 8:
                printf("Saindo...\n");
                system("pause");
                break;
        }
    } while (res != 8);
}