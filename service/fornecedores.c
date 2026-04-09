#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../bib/fornecedores.h"

int escolheIdFornecedor(ListaFornecedor *lista)
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

int listarFornecedores(ListaFornecedor *lista){
    if (lista->prox != NULL) {
        printf("Nenhum fornecedor cadastrado");
        return;
    } else {
        lista = lista->prox;
        printf("\nFornecedor ---------\n");
        while (lista != NULL) {
            printf("Id: %d\n", lista->Fornecedor.id);
            printf("Nome: %s\n", lista->Fornecedor.nome_fantasia);
            lista = lista->prox;
        }
    }
}

ListaFornecedor *iniciaListaFornecedor()
{
    ListaFornecedor *Lista = malloc(sizeof(ListaFornecedor));

    Lista->Fornecedor.id = 0;
    Lista->prox = NULL;

    return Lista;
}

int inserirFornecedor(ListaFornecedor **lista, TipoFornecedor Fornecedor)
{
    ListaFornecedor *aux, *novoFornecedor = malloc(sizeof(ListaFornecedor));
    if (novoFornecedor)
    {
        aux = *lista;
        novoFornecedor->Fornecedor = Fornecedor;
        novoFornecedor->prox = NULL;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novoFornecedor;
        return 0;
    }
    printf("Erro ao inserir...\n");
    return 1;
}

int buscarFornecedor(ListaFornecedor **lista, TipoFornecedor *Fornecedor, char *CNPJ, ListaFornecedor **pos)
{
    if ((*lista)->prox == NULL)
        return 1;

    ListaFornecedor *aux = (*lista)->prox;

    while (strcmp(aux->Fornecedor.cnpj, CNPJ) != 0 && aux != NULL)
        aux = aux->prox;

    if (aux == NULL)
        return 1;

    if (strcmp(aux->Fornecedor.cnpj, CNPJ) == 0)
    {
        *Fornecedor = aux->Fornecedor;
        *pos = aux;
        return 0;
    }

    return 1;
}

void alterarFornecedor(ListaFornecedor *pos, TipoFornecedor Fornecedor)
{
    pos->Fornecedor = Fornecedor;
    return;
}

void apagarFornecedor(ListaFornecedor *pos)
{
    pos->Fornecedor.id = 0;
    return;
}

void listarFornecedor(ListaFornecedor *lista)
{
    if (lista->prox == NULL)
    {
        printf("Nenhum Fornecedor cadastrado");
        system("pause");
    }
    else
    {
        lista = lista->prox;
        printf("\nFornecedor ---------\n");
        while (lista != NULL)
        {
            printf("Id   : %d\n", lista->Fornecedor.id);
            printf("Nome : %s\n\n", lista->Fornecedor.nome_fantasia);
            lista = lista->prox;
        }
    }
}

void interfaceFornecedor(){

    ListaFornecedor *pos, *listaFornecedor = iniciaListaFornecedor();
    TipoFornecedor fornecedor;
    int res = 0;

    do {
        system("cls");
        printf("Cadastro e gestão de fornecedores!\n");
        printf("1 - Inserir fornecedor\n");
        printf("2 - Buscar fornecedor\n");
        printf("3 - Alterar fornecedor\n");
        printf("4 - Apagar fornecedor\n");
        printf("5- Listar fornecedores\n");
        printf("6 - Sair\n");

        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);
        system("cls");

        if (res == 6) {
            break;
        }

        switch (res) {
            //Inserir fornecedor
            case 1:
                printf("Insira o nome: ");
                scanf("%[^\n]", fornecedor.nome_fantasia);
                fflush(stdin);

                printf("Insira a razão social: ");
                scanf("%[^\n]", fornecedor.razao_social);
                fflush(stdin);

                printf("Insira a inscrição estadual: ");
                scanf("%[^\n]", fornecedor.inscricao_estadual);
                fflush(stdin);

                printf("Insira o CNPJ: ");
                scanf("%[^\n]", fornecedor.cnpj);
                fflush(stdin);

                printf("Insira o endereço completo\n");
                scanf("%[^\n]", fornecedor.endereco_completo);
                fflush(stdin);

                printf("Insira o telefone: ");
                scanf("%[^\n]", fornecedor.telefone);
                fflush(stdin);

                printf("Insira o email: ");
                scanf("%[^\n]", fornecedor.email);
                fflush(stdin);

                fornecedor.id = escolheIdFornecedor(listaFornecedor);

                res = inserirFornecedor(&listaFornecedor, fornecedor);

                if (res == 0) {
                    printf("\nFuncionário inserido com sucesso!\n");
                    printf("\nO ID do fornecedor %s é: %d\n", fornecedor.nome_fantasia, fornecedor.id);
                    system("pause");
                } else {
                    printf("\nFalha ao inserir o funcionário!\n");
                    system("pause");
                }

                break;

                //Buscar fornecedor
            case 2:
                printf("Insira o CNPJ do fornecedor que deseja buscar: ");
                scanf("%[^\n]", &fornecedor.cnpj);
                fflush(stdin);

                res = buscarFornecedor(&listaFornecedor, &fornecedor, fornecedor.cnpj, &pos);
                if (res == 0) {
                    printf("\nFornecedor encontrado! -------------\n");
                    printf("ID                     : %d\n", fornecedor.id);
                    printf("Nome                   : %s\n", fornecedor.nome_fantasia);
                    printf("Razao social           : %s\n", fornecedor.razao_social);
                    printf("Inscrição estadual   : %s\n", fornecedor.inscricao_estadual);
                    printf("CNPJ                   : %s\n", fornecedor.cnpj);
                    printf("Endereco completo      : %s\n", fornecedor.endereco_completo);
                    printf("Telefone               : %s\n", fornecedor.telefone);
                    printf("Email                  : %s\n", fornecedor.email);
                    system("pause");
                } else {
                    printf("\nFornecedor não encontrado!\n");
                    system("pause");
                }

                break;

            //Alterar funcionario
            case 3:

                printf("Insira o CNPJ do fornecedor que deseja alterar: ");
                scanf("%[^\n]", &fornecedor.cnpj);
                fflush(stdin);

                res = buscarFornecedor(&listaFornecedor, &fornecedor, fornecedor.cnpj, &pos);
                if (res == 0) {
                    while (res != 9) {
                        system("cls");
                        printf("\nFornecedor encontrado! -------------\n");
                        printf("ID (Fixo)                     : %d\n", fornecedor.id);
                        printf("1- Nome                   : %s\n", fornecedor.nome_fantasia);
                        printf("2- Razao social           : %s\n", fornecedor.razao_social);
                        printf("3- Inscrição estadual     : %s\n", fornecedor.inscricao_estadual);
                        printf("4- CNPJ                   : %s\n", fornecedor.cnpj);
                        printf("5- Endereco completo      : %s\n", fornecedor.endereco_completo);
                        printf("6- Telefone               : %s\n", fornecedor.telefone);
                        printf("7- Email                  : %s\n", fornecedor.email);

                        printf("8- Salvar dados\n");
                        printf("0- Cancelar \n");
                        printf("=> ");
                        scanf("%d", &res);

                        if (res == 0) {
                            break;
                        }

                        fflush(stdin);

                        switch (res) {
                            case 1:
                                printf("Insira o novo nome: \n");
                                scanf("%[^\n]", fornecedor.nome_fantasia);
                                fflush(stdin);
                                break;
                            case 2:
                                printf("Insira a nova razão social: \n");
                                scanf("%[^\n]", fornecedor.razao_social);
                                fflush(stdin);
                                break;
                            case 3:
                                printf("Insira a nova inscrição estadual: \n");
                                scanf("%[^\n]", fornecedor.inscricao_estadual);
                                fflush(stdin);
                                break;
                            case 4:
                                printf("Insira o novo CNPJ: \n");
                                scanf("%[^\n]", fornecedor.nome_fantasia);
                                fflush(stdin);
                                break;
                            case 5:
                                printf("Insira o novo endereço: \n");
                                scanf("%[^\n]", fornecedor.endereco_completo);
                                fflush(stdin);
                                break;
                            case 6:
                                printf("Insira o novo telefoen: \n");
                                scanf("%[^\n]", fornecedor.telefone);
                                fflush(stdin);
                                break;
                            case 7:
                                printf("Insira o novo e-mail: \n");
                                scanf("%[^\n]", fornecedor.email);
                                fflush(stdin);
                                break;
                            case 8:
                                alterarFornecedor(pos, fornecedor);
                                break;
                            default:
                                printf("Insira uma opção válida...");
                                system("pause");
                                break;
                        }
                    }
                } else {
                    printf("\nFornecedor não encontrado!\n");
                    system("pause");
                }

                break;

            case 4:
                printf("Digite o CNPJ do fornecedor que deseja apagar: ");
                scanf("%[^\n]", &fornecedor.cnpj);
                fflush(stdin);

                res = buscarFornecedor(&listaFornecedor, &fornecedor, fornecedor.cnpj, &pos);

                if (res == 0) {
                    printf("Fornecedor encontrado!\n");
                    printf("1- ID                     : %d\n", fornecedor.id);
                    printf("2- Nome                   : %s\n", fornecedor.nome_fantasia);
                    printf("3- Razao social           : %s\n", fornecedor.razao_social);
                    printf("4- Inscrição estadual     : %s\n", fornecedor.inscricao_estadual);
                    printf("5- CNPJ                   : %s\n", fornecedor.cnpj);
                    printf("6- Endereco completo      : %s\n", fornecedor.endereco_completo);
                    printf("7- Telefone               : %s\n", fornecedor.telefone);
                    printf("8- Email                  : %s\n", fornecedor.email);

                    printf("Tem certeza que deseja apagar esse fornecedor?\n");
                    printf("1- Sim \n");
                    printf("2- Não \n");
                    printf("=> ");
                    scanf("%d", &res);
                    fflush(stdin);

                    if (res == 1) {
                        apagarFornecedor(pos);
                        printf("\nFornecedor apagado com sucesso!\n");
                        system("pause");
                        fflush(stdin);
                    }
                } else {
                    printf("Usuário não encontrado!\n");
                    system("pause");
                }
                break;
            case 5:
                listarFornecedor(listaFornecedor);
                break;
            default:
                if (res != 6) {
                    printf("Selecione uma opção válida!\n");
                    system("pause");
                    fflush(stdin);
                }
                break;
        }
    } while (res != 6);
}


