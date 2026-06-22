#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../bib/fornecedores.h"
#include "utils.h"

#define FornecedoresBIN "./data/bin/fornecedores.dat"
#define FornecedoresTXT "./data/txt/fornecedores.txt"

#define BIN 1
#define TXT 2
#define MEM 3

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

int listarFornecedores(ListaFornecedor *lista)
{
    if (lista->prox == NULL)
    {
        exibeMensagemErro("Nenhum fornecedor cadastrado");
    }
    else
    {
        lista = lista->prox;
        exibeMensagemSucesso("Fornecedores: ");
        while (lista != NULL)
        {
            if (lista->Fornecedor.id != 0)
            {
                imprimeDadosFornecedor(lista->Fornecedor);
            }
            lista = lista->prox;
        }
        system("pause");
    }
    return 0;
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
    exibeMensagemErro("Erro ao inserir...");
    return 1;
}

int buscarFornecedor(ListaFornecedor **lista, TipoFornecedor *Fornecedor, char *CNPJ, ListaFornecedor **pos)
{
    if ((*lista)->prox == NULL)
        return 1;

    ListaFornecedor *aux = (*lista)->prox;

    while (aux != NULL && strcmp(aux->Fornecedor.cnpj, CNPJ) != 0)
        aux = aux->prox;

    if (aux == NULL || aux->Fornecedor.id == 0)
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
        exibeMensagemErro("Nenhum Fornecedor cadastrado.");
        system("pause");
    }
    else
    {
        lista = lista->prox;
        exibeMensagemSucesso("Fornecedores: ");
        while (lista != NULL)
        {
            imprimeDadosFornecedor(lista->Fornecedor);
            lista = lista->prox;
        }
        system("pause");
    }
}

int salvarDadosFornecedoresBin(ListaFornecedor *lista, char *nome_arquivo)
{
    FILE *arq = fopen(nome_arquivo, "wb");
    if (arq == NULL)
    {
        exibeMensagemErro("Erro ao abrir arquivo...");
        system("pause");
        return 1;
    }

    ListaFornecedor *aux = lista->prox;
    while (aux != NULL)
    {
        fwrite(&(aux->Fornecedor), sizeof(TipoFornecedor), 1, arq);
        aux = aux->prox;
    }
    fclose(arq);
    return 0;
}

ListaFornecedor *resgataDadosFornecedoresBin(char *nome_arquivo)
{
    TipoFornecedor fornecedor;
    ListaFornecedor *lista = iniciaListaFornecedor();
    int res;

    FILE *arq = fopen(nome_arquivo, "rb");
    if (arq == NULL)
    {
        return lista;
    }

    while (fread(&fornecedor, sizeof(TipoFornecedor), 1, arq) == 1)
        res = inserirFornecedor(&lista, fornecedor);

    if (res == 1)
        exibeMensagemErro("Erro ao carregar fornecedor do arquivo binario!");

    fclose(arq);
    return lista;
}

int salvarDadosFornecedoresTxt(ListaFornecedor *lista, char *nome_arquivo)
{
    FILE *arq = fopen(nome_arquivo, "w");
    if (arq == NULL)
    {
        exibeMensagemErro("Erro ao abrir arquivo...");
        system("pause");
        return 1;
    }

    if (lista->prox != NULL)
    {
        ListaFornecedor *aux = lista->prox;
        fprintf(arq, "<tabela=fornecedor>\n");
        while (aux != NULL)
        {
            fprintf(arq, "    <registro>\n");
            fprintf(arq, "        <codigo>%d</codigo>\n", aux->Fornecedor.id);
            fprintf(arq, "        <nome_fantasia>%s</nome_fantasia>\n", aux->Fornecedor.nome_fantasia);
            fprintf(arq, "        <razao_social>%s</razao_social>\n", aux->Fornecedor.razao_social);
            fprintf(arq, "        <inscricao_estadual>%s</inscricao_estadual>\n", aux->Fornecedor.inscricao_estadual);
            fprintf(arq, "        <cnpj>%s</cnpj>\n", aux->Fornecedor.cnpj);
            fprintf(arq, "        <endereco_completo>%s</endereco_completo>\n", aux->Fornecedor.endereco_completo);
            fprintf(arq, "        <telefone>%s</telefone>\n", aux->Fornecedor.telefone);
            fprintf(arq, "        <email>%s</email>\n", aux->Fornecedor.email);
            fprintf(arq, "    </registro>\n");
            aux = aux->prox;
        }
        fprintf(arq, "</tabela>\n");
    }
    fclose(arq);
    return 0;
}

ListaFornecedor *resgataDadosFornecedoresTxt(char *nome_arquivo)
{
    ListaFornecedor *lista = iniciaListaFornecedor();
    TipoFornecedor fornecedor;

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
            memset(&fornecedor, 0, sizeof(TipoFornecedor));
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            inserirFornecedor(&lista, fornecedor);
            continue;
        }

        sscanf(linha, " <codigo>%d", &fornecedor.id);
        sscanf(linha, " <nome_fantasia>%[^<]", fornecedor.nome_fantasia);
        sscanf(linha, " <razao_social>%[^<]", fornecedor.razao_social);
        sscanf(linha, " <inscricao_estadual>%[^<]", fornecedor.inscricao_estadual);
        sscanf(linha, " <cnpj>%[^<]", fornecedor.cnpj);
        sscanf(linha, " <endereco_completo>%[^<]", fornecedor.endereco_completo);
        sscanf(linha, " <telefone>%[^<]", fornecedor.telefone);
        sscanf(linha, " <email>%[^<]", fornecedor.email);
    }
    fclose(arq);
    return lista;
}

void liberaListaFornecedores(ListaFornecedor *lista)
{
    ListaFornecedor *temp, *aux = lista;
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }
}

void imprimeDadosFornecedor(TipoFornecedor fornecedor)
{
    printf("Id               : %d\n", fornecedor.id);
    printf("Nome             : %s\n", fornecedor.nome_fantasia);
    printf("Razao social     : %s\n", fornecedor.razao_social);
    printf("CNPJ             : %s\n", fornecedor.cnpj);
    printf("Endereco         : %s\n", fornecedor.endereco_completo);
    printf("Telefone         : %s\n", fornecedor.telefone);
    printf("E-mail           : %s\n", fornecedor.email);
    printf("-----------------------------\n");
    return;
}

void interfaceFornecedor(ListaFornecedor *listaFornecedor)
{
    ListaFornecedor *pos;
    TipoFornecedor fornecedor;
    int res = 0;

    do
    {
        system("cls");
        printf("Cadastro e gestao de Fornecedores!\n");
        printf("1 - Inserir fornecedor\n");
        printf("2 - Buscar fornecedor\n");
        printf("3 - Alterar fornecedor\n");
        printf("4 - Apagar fornecedor\n");
        printf("5 - Listar fornecedores\n");
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
        // Inserir fornecedor
        case 1:
            printf("Insira o nome: ");
            scanf(" %[^\n]", fornecedor.nome_fantasia);
            fflush(stdin);

            printf("Insira a razao social: ");
            scanf(" %[^\n]", fornecedor.razao_social);
            fflush(stdin);

            printf("Insira a inscricao estadual: ");
            scanf(" %[^\n]", fornecedor.inscricao_estadual);
            fflush(stdin);

            printf("Insira o CNPJ: ");
            scanf(" %[^\n]", fornecedor.cnpj);
            fflush(stdin);

            printf("Insira o endereco completo: \n");
            scanf(" %[^\n]", fornecedor.endereco_completo);
            fflush(stdin);

            printf("Insira o telefone: ");
            scanf(" %[^\n]", fornecedor.telefone);
            fflush(stdin);

            printf("Insira o email: ");
            scanf(" %[^\n]", fornecedor.email);
            fflush(stdin);

            fornecedor.id = escolheIdFornecedor(listaFornecedor);

            res = inserirFornecedor(&listaFornecedor, fornecedor);

            if (res == 0)
            {
                printf("\nFornecedor inserido com sucesso!\n");
                printf("\nO ID do fornecedor %s e: %d\n", fornecedor.nome_fantasia, fornecedor.id);
                system("pause");
            }
            else
            {
                printf("\nFalha ao inserir o fornecedor!\n");
                system("pause");
            }
            res = 1;
            break;

        // Buscar fornecedor
        case 2:
            printf("Insira o CNPJ do fornecedor que deseja buscar: ");
            scanf(" %[^\n]", fornecedor.cnpj);
            fflush(stdin);

            res = buscarFornecedor(&listaFornecedor, &fornecedor, fornecedor.cnpj, &pos);
            if (res == 0)
            {
               imprimeDadosFornecedor(fornecedor);
            }
            else
            {
                printf("\nFornecedor nao encontrado!\n");
                system("pause");
            }
            break;

        // Alterar fornecedor
        case 3:
            printf("Insira o CNPJ do fornecedor que deseja alterar: ");
            scanf(" %[^\n]", fornecedor.cnpj);
            fflush(stdin);

            res = buscarFornecedor(&listaFornecedor, &fornecedor, fornecedor.cnpj, &pos);
            if (res == 0)
            {
                while (res != 9)
                {
                    system("cls");
                    printf("\nFornecedor encontrado! -------------\n");
                    printf("ID (Fixo)                 : %d\n", fornecedor.id);
                    printf("1- Nome                   : %s\n", fornecedor.nome_fantasia);
                    printf("2- Razao social           : %s\n", fornecedor.razao_social);
                    printf("3- Inscricao estadual     : %s\n", fornecedor.inscricao_estadual);
                    printf("4- CNPJ                   : %s\n", fornecedor.cnpj);
                    printf("5- Endereco completo      : %s\n", fornecedor.endereco_completo);
                    printf("6- Telefone               : %s\n", fornecedor.telefone);
                    printf("7- Email                  : %s\n", fornecedor.email);

                    printf("8- Salvar dados\n");
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
                        printf("Insira o novo nome: \n");
                        scanf(" %[^\n]", fornecedor.nome_fantasia);
                        fflush(stdin);
                        break;
                    case 2:
                        printf("Insira a nova razao social: \n");
                        scanf(" %[^\n]", fornecedor.razao_social);
                        fflush(stdin);
                        break;
                    case 3:
                        printf("Insira a nova inscricao estadual: \n");
                        scanf(" %[^\n]", fornecedor.inscricao_estadual);
                        fflush(stdin);
                        break;
                    case 4:
                        printf("Insira o novo CNPJ: \n");
                        scanf(" %[^\n]", fornecedor.cnpj);
                        fflush(stdin);
                        break;
                    case 5:
                        printf("Insira o novo endereco: \n");
                        scanf(" %[^\n]", fornecedor.endereco_completo);
                        fflush(stdin);
                        break;
                    case 6:
                        printf("Insira o novo telefone: \n");
                        scanf(" %[^\n]", fornecedor.telefone);
                        fflush(stdin);
                        break;
                    case 7:
                        printf("Insira o novo e-mail: \n");
                        scanf(" %[^\n]", fornecedor.email);
                        fflush(stdin);
                        break;
                    case 8:
                        alterarFornecedor(pos, fornecedor);
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
                printf("\nFornecedor nao encontrado!\n");
                system("pause");
            }
            break;

        // Apagar fornecedor
        case 4:
            printf("Digite o CNPJ do fornecedor que deseja apagar: ");
            scanf(" %[^\n]", fornecedor.cnpj);
            fflush(stdin);

            res = buscarFornecedor(&listaFornecedor, &fornecedor, fornecedor.cnpj, &pos);

            if (res == 0)
            {
                imprimeDadosFornecedor(fornecedor);

                printf("\nTem certeza que deseja apagar esse fornecedor?\n");
                printf("1- Sim \n");
                printf("2- Nao \n");
                printf("=> ");
                scanf("%d", &res);
                fflush(stdin);

                if (res == 1)
                {
                    apagarFornecedor(pos);
                    printf("\nFornecedor apagado com sucesso!\n");
                    system("pause");
                    fflush(stdin);
                }
            }
            else
            {
                printf("Fornecedor nao encontrado!\n");
                system("pause");
            }
            break;

        case 5:
            listarFornecedores(listaFornecedor);
            break;

        default:
            if (res != 0)
            {
                printf("Selecione uma opcao valida!\n");
                system("pause");
                fflush(stdin);
            }
            break;
        }
    } while (res != 0);
}