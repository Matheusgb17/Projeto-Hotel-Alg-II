#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "../bib/operadores.h"

int escolheIdOperador(ListaOperadores *lista)
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

ListaOperadores *iniciaListaOperadores()
{
    ListaOperadores *lista = malloc(sizeof(ListaOperadores));

    lista->operador.id = 0;
    lista->prox = NULL;

    return lista;
}

int inserirOperador(ListaOperadores **lista, TipoOperador operador)
{
    ListaOperadores *aux, *novoOperador = malloc(sizeof(ListaOperadores));
    if (novoOperador)
    {
        aux = *lista;
        novoOperador->operador = operador;
        novoOperador->prox = NULL;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novoOperador;
        return 0;
    }
    return 1;
}

int buscarOperador(ListaOperadores **lista, TipoOperador *operador, char *user, ListaOperadores **pos)
{
    if ((*lista)->prox == NULL)
        return 1;

    ListaOperadores *aux = (*lista)->prox;

    while (aux != NULL && strcmp(user, aux->operador.user) != 0)
        aux = aux->prox;

    if (aux == NULL || aux->operador.id == 0)
        return 1;

    *operador = aux->operador;
    *pos = aux;
    return 0;
}

void alterarOperador(ListaOperadores *pos, TipoOperador operador)
{
    pos->operador = operador;
    return;
}

void apagarOperador(ListaOperadores *pos)
{
    pos->operador.id = 0;
    return;
}

void listarOperadores(ListaOperadores *lista)
{
    if (lista->prox == NULL)
        printf("Nenhum operador cadastrado.\n");
    else
    {
        lista = lista->prox;
        printf("\nOperadores -----------\n");
        while (lista != NULL)
        {
            if (lista->operador.id != 0)
            {
                printf("Id                 : %d\n", lista->operador.id);
                printf("Nome               : %s\n", lista->operador.nome);
                printf("Usu†rio            : %s\n", lista->operador.user);
                printf("N°vel de Permiss∆o : %d\n", lista->operador.permission);
            }
            lista = lista->prox;
        }
    }
}

void salvaDadosOperadoresBin(ListaOperadores *lista, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao acessar o arquivo...\n\n");
        system("pause");
        return;
    }

    ListaOperadores *aux = lista->prox;
    while (aux != NULL)
    {
        fwrite(&(aux->operador), sizeof(TipoOperador), 1, arquivo);
        aux = aux->prox;
    }
    fclose(arquivo);
}

ListaOperadores *resgataDadosOperadoresBin(char *nome_arquivo)
{
    TipoOperador operador;
    ListaOperadores *lista = iniciaListaOperadores();
    int res;

    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL)
        return lista;

    while (fread(&operador, sizeof(TipoOperador), 1, arquivo) == 1)
        res = inserirOperador(&lista, operador);

    if (res == 1)
        printf("Erro ao carregar operador do arquivo bin†rio!\n");

    fclose(arquivo);
    return lista;
}

void salvaDadosOperadoresTxt(ListaOperadores *lista, char *nome_arquivo)
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
        ListaOperadores *aux = lista->prox;

        fprintf(arquivo, "<tabela=operador>\n");
        while (aux != NULL)
        {
            fprintf(arquivo, "    <registro>\n");

            fprintf(arquivo, "        <codigo>%d</codigo>\n", aux->operador.id);
            fprintf(arquivo, "        <nome>%s</nome>\n", aux->operador.nome);
            fprintf(arquivo, "        <user>%s</user>\n", aux->operador.user);
            fprintf(arquivo, "        <senha>%s</senha>\n", aux->operador.senha);
            fprintf(arquivo, "        <permissao>%d</permissao>\n", aux->operador.permission);

            fprintf(arquivo, "    </registro>\n");
            aux = aux->prox;
        }
        fprintf(arquivo, "</tabela>\n");
    }
    fclose(arquivo);
}

ListaOperadores *resgataDadosOperadoresTxt(char *nome_arquivo)
{
    ListaOperadores *lista = iniciaListaOperadores();
    TipoOperador operador;

    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL)
        return lista;

    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, "<registro>") != NULL)
        {
            memset(&operador, 0, sizeof(TipoOperador));
            continue;
        }

        if (strstr(linha, "</registro>") != NULL)
        {
            inserirOperador(&lista, operador);
            continue;
        }

        sscanf(linha, " <codigo>%d", &operador.id);
        sscanf(linha, " <nome>%[^<]", operador.nome);
        sscanf(linha, " <user>%[^<]", operador.user);
        sscanf(linha, " <senha>%[^<]", operador.senha);
        sscanf(linha, " <permissao>%d", &operador.permission);
    }

    fclose(arquivo);
    return lista;
}

void interfaceOperadores()
{
    ListaOperadores *pos, *listaOperadores;
    TipoOperador operador;

    int res = 0, tam;

    do
    {
        system("cls");
        printf("Cadastro e gest∆o de Operadores!\n");
        printf("1 - Cadastrar operador\n");
        printf("2 - Buscar operador\n");
        printf("3 - Alterar operador\n");
        printf("4 - Apagar operador\n");
        printf("5 - Sair\n");

        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);

        system("cls");
        switch (res)
        {
        case 1:
            printf("Insira o nome completo do operador: ");
            scanf("%[^\n]", operador.nome);
            fflush(stdin);

            printf("Insira o nome de usu†rio do operador: ");
            scanf("%[^\n]", operador.user);
            fflush(stdin);

            printf("Insira a senha: ");
            scanf("%[^\n]", operador.senha);
            fflush(stdin);

            while (1)
            {
                system("cls");
                printf("Selecione o n°vel de permiss∆o: \n");
                printf("0 - Inativo\n");
                printf("1 - Funcion†rio\n");
                printf("2 - Recepcionista\n");
                printf("3 - Gerente de operaá‰es\n");
                printf("4 - Administrador\n\n");
                printf("5 - Verificar permiss‰es espec°ficas de cada um!\n");
                printf("=> ");
                scanf("%d", &res);
                fflush(stdin);

                if (res == 0)
                {
                    operador.permission = res;
                    break;
                }
                else if (res == 1)
                {
                    operador.permission = res;
                    break;
                }
                else if (res == 2)
                {
                    operador.permission = res;
                    break;
                }
                else if (res == 3)
                {
                    operador.permission = res;
                    break;
                }
                else if (res == 4)
                {
                    operador.permission = res;
                    break;
                }
                else if (res == 5)
                {
                    system("cls");
                    printf("Permiss‰es de cada funá∆o: \n");
                    printf("0 - Usu†rio desligado. O sistema bloqueia o login imediatamente.\n");
                    printf("1 - Acesso b†sico: consultar disponibilidade de quartos e ver lista de h¢spedes.\n");
                    printf("2 - Tudo do n°vel 1 alÇm de realizar Check-in, Check-out e cadastrar novos h¢spedes.\n");
                    printf("3 - Tudo do n°vel 2 alÇm de estornar pagamentos, alterar tarifas e gerar relat¢rios mensais.\n");
                    printf("4 - Acesso total: cadastrar novos usu†rios (operadores) e configurar o sistema.\n\n");

                    system("pause");
                }
                else
                {
                    printf("Opá∆o inv†lida!\n");
                    system("pause");
                }
            }

            operador.id = escolheIdOperador(listaOperadores);

            res = inserirOperador(&listaOperadores, operador);

            if (res == 0)
            {
                printf("Operador %s cadastrado com sucesso!\n", operador.user);
                printf("Id do operador: %d\n\n", operador.id);
                system("pause");
            }
            else
            {
                printf("Erro ao cadastrar operador!\n");
                system("pause");
            }

            break;
        case 2:
            printf("Digite o usu†rio do operador que deseja buscar: ");
            scanf("%[^\n]", operador.user);
            fflush(stdin);

            res = buscarOperador(&listaOperadores, &operador, operador.user, &pos);

            if (res == 0)
            {
                printf("Usu†rio encontrado!\n");
                printf("Id do operador     : %d\n", operador.id);
                printf("Nome completo      : %s\n", operador.nome);
                printf("Nome de usu†rio    : %s\n", operador.user);
                printf("N°vel de permiss∆o : %d\n\n", operador.permission);

                system("pause");
            }
            else
            {
                printf("Usu†rio n∆o encontrado!\n");
                system("pause");
            }
            break;
        case 3:
            printf("Digite o usu†rio do operador que deseja alterar: ");
            scanf("%[^\n]", operador.user);
            fflush(stdin);

            res = buscarOperador(&listaOperadores, &operador, operador.user, &pos);

            if (res == 0)
            {
                while (res != 5)
                {
                    tam = strlen(operador.senha) - 1;
                    printf("Usu†rio encontrado!\n");
                    printf("Digite o campo que deseja alterar: \n\n");

                    printf("Id (fixo)              : %d\n", operador.id);
                    printf("1 - Nome completo      : %s\n", operador.nome);
                    printf("2 - Nome de usu†rio    : %s\n", operador.user);
                    printf("3 - N°vel de permiss∆o : %d\n", operador.permission);
                    printf("4 - Senha              : %c%c", operador.senha[0], operador.senha[1]);
                    for (int i = 1; i < tam; i++)
                        printf("*");
                    printf("\n\n");

                    printf("5 - Salvar alteraá‰es\n");
                    printf("6 - Cancelar\n");
                    printf("=> ");
                    scanf("%d", &res);
                    fflush(stdin);

                    if (res == 6)
                    {
                        printf("Operaá∆o cancelada!\n");
                        system("pause");
                    }

                    switch (res)
                    {
                    case 1:
                        printf("Insira o nome completo do operador: ");
                        scanf("%[^\n]", operador.nome);
                        fflush(stdin);
                        break;
                    case 2:
                        printf("Insira o nome de usu†rio do operador: ");
                        scanf("%[^\n]", operador.user);
                        fflush(stdin);
                        break;
                    case 3:
                        while (1)
                        {
                            system("cls");
                            printf("Selecione o n°vel de permiss∆o: \n");
                            printf("0 - Inativo\n");
                            printf("1 - Funcion†rio\n");
                            printf("2 - Recepcionista\n");
                            printf("3 - Gerente de operaá‰es\n");
                            printf("4 - Administrador\n\n");
                            printf("5 - Verificar permiss‰es espec°ficas de cada um!\n");
                            printf("=> ");
                            scanf("%d", &res);
                            fflush(stdin);

                            if (res == 0)
                            {
                                operador.permission = res;
                                break;
                            }
                            else if (res == 1)
                            {
                                operador.permission = res;
                                break;
                            }
                            else if (res == 2)
                            {
                                operador.permission = res;
                                break;
                            }
                            else if (res == 3)
                            {
                                operador.permission = res;
                                break;
                            }
                            else if (res == 4)
                            {
                                operador.permission = res;
                                break;
                            }
                            else if (res == 5)
                            {
                                system("cls");
                                printf("Permiss‰es de cada funá∆o: \n");
                                printf("0 - Usu†rio desligado. O sistema bloqueia o login imediatamente.\n");
                                printf("1 - Acesso b†sico: consultar disponibilidade de quartos e ver lista de h¢spedes.\n");
                                printf("2 - Tudo do n°vel 1 alÇm de realizar Check-in, Check-out e cadastrar novos h¢spedes.\n");
                                printf("3 - Tudo do n°vel 2 alÇm de estornar pagamentos, alterar tarifas e gerar relat¢rios mensais.\n");
                                printf("4 - Acesso total: cadastrar novos usu†rios (operadores) e configurar o sistema.\n\n");

                                system("pause");
                            }
                            else
                            {
                                printf("Opá∆o inv†lida!\n");
                                system("pause");
                            }
                        }
                        break;
                    case 4:
                        printf("Insira a nova senha: ");
                        scanf("%[^\n]", operador.senha);
                        fflush(stdin);
                        break;
                    case 5:
                        alterarOperador(pos, operador);
                        printf("Dados atualizados!\n");
                        system("pause");
                        break;

                    default:
                        printf("Opá∆o inv†lida!\n");
                        system("pause");
                        fflush(stdin);
                        break;
                    }
                }
            }
            else
            {
                printf("Usu†rio n∆o encontrado!\n");
                system("pause");
            }
            res = 0;
            break;
        case 4:
            printf("Digite o usu†rio do operador que deseja apagar: ");
            scanf("%[^\n]", operador.user);
            fflush(stdin);

            res = buscarOperador(&listaOperadores, &operador, operador.user, &pos);

            if (res == 0)
            {
                printf("Usu†rio encontrado!\n");
                printf("Id do operador     : %d\n", operador.id);
                printf("Nome completo      : %s\n", operador.nome);
                printf("Nome de usu†rio    : %s\n", operador.user);
                printf("N°vel de permiss∆o : %d\n\n", operador.permission);

                printf("Tem certeza quedeseja apagar esse usu†rio?\n");
                printf("1 - Sim\n");
                printf("2 - N∆o\n");
                printf("=> ");
                scanf("%d", &res);
                fflush(stdin);

                if (res == 1)
                {
                    apagarOperador(pos);
                    printf("Operador apagado com sucesso!\n");
                    system("pause");
                    fflush(stdin);
                }
            }
            else
            {
                printf("Usu†rio n∆o encontrado!\n");
                system("pause");
            }
            break;
        default:
            if (res != 5)
            {
                printf("Selecione uma opá∆o v†lida!\n");
                system("pause");
                fflush(stdin);
            }
            break;
        }

    } while (res != 5);
}
