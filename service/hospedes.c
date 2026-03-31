#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "..\bib\hospedes.h"

int escolheId(ListaHospede *lista)
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

ListaHospede *iniciaListaHospede()
{
    ListaHospede *Lista = malloc(sizeof(ListaHospede));

    Lista->Hospedes.id = 0;
    Lista->prox = NULL;

    return Lista;
}

int inserirHospede(ListaHospede **lista, TipoHospede hospede)
{
    ListaHospede *aux, *novoHospede = malloc(sizeof(ListaHospede));
    if (novoHospede)
    {
        aux = *lista;
        novoHospede->Hospedes = hospede;
        novoHospede->prox = NULL;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novoHospede;
        return 0;
    }
    printf("Erro ao inserir...\n");
    return 1;
}

int buscarHospede(ListaHospede **lista, TipoHospede *hospede, char *cpf, ListaHospede **pos)
{
    if ((*lista)->prox == NULL)
        return 1;

    ListaHospede *aux = (*lista)->prox;

    while (aux != NULL && strcmp(aux->Hospedes.cpf, cpf) != 0)
        aux = aux->prox;

    if (aux == NULL)
        return 1;

    *hospede = aux->Hospedes;
    *pos = aux;
    return 0;
}

void alterarHospede(ListaHospede *pos, TipoHospede hospede)
{
    pos->Hospedes = hospede;
    return;
}

void apagarHospede(ListaHospede *pos)
{
    pos->Hospedes.id = 0;
    return;
}

void listarHospedes(ListaHospede *lista)
{
    if (lista->prox == NULL)
    {
        printf("Nenhum hospede cadastrado");
        return;
    }
    else
    {
        lista = lista->prox;
        printf("\nHospedes ---------\n");
        while (lista != NULL)
        {
            printf("Id   : %d\n", lista->Hospedes.id);
            printf("Nome : %s\n\n", lista->Hospedes.nome);
            lista = lista->prox;
        }
    }
}

void interfaceHospedes()
{
    ListaHospede *pos, *listaHospedes = iniciaListaHospede();
    TipoHospede hospede;
    int res = 0;

    // Cadastro e GestÆo de Hospedes
    do
    {
        system("cls");
        printf("Cadastro e gestÆo de Hospedes!\n");
        printf("1 - Inserir hospede\n");
        printf("2 - Buscar hospede\n");
        printf("3 - Alterar hospede\n");
        printf("4 - Apagar hospede\n");
        printf("5 - Sair\n");

        printf("=> ");
        scanf("%d", &res);
        fflush(stdin);
        system("cls");

        if (res == 5)
        {
            printf("\nTem certeza que deseja sair?\n");
            printf("1 - sim\n");
            printf("2 - nÆo\n");
            printf("=> ");
            scanf("%d", &res);
            fflush(stdin);

            if (res == 1)
                break;
            else
                continue;
        }

        switch (res)
        {
        case 1:
            printf("Insira o nome: ");
            scanf("%[^\n]", hospede.nome);
            fflush(stdin);

            printf("Insira o endere‡o: ");
            scanf("%[^\n]", hospede.endereco);
            fflush(stdin);

            printf("Insira o cpf: ");
            scanf("%[^\n]", hospede.cpf);
            fflush(stdin);

            printf("Insira o telefone: ");
            scanf("%[^\n]", hospede.telefone);
            fflush(stdin);

            while (1)
            {
                printf("\nSelecione o sexo       : \n");
                printf("1 - Feminino\n");
                printf("2 - Masculino\n");
                printf("3 - Outro\n=> ");
                scanf("%d", &res);
                fflush(stdin);

                if (res == 1)
                {
                    hospede.sexo = 'F';
                    break;
                }
                else if (res == 2)
                {
                    hospede.sexo = 'M';
                    break;
                }
                else if (res == 3)
                {
                    hospede.sexo = 'O';
                    break;
                }
                else
                {
                    printf("Op‡Æo inv lida");
                    system("pause");
                    fflush(stdin);
                }
            }

            printf("Insira o email: ");
            scanf("%[^\n]", hospede.email);
            fflush(stdin);

            printf("Insira o estado civil: ");
            scanf("%[^\n]", hospede.estado_civil);
            fflush(stdin);

            printf("Insira a data nascimento: ");
            scanf("%[^\n]", hospede.data_nasc);
            fflush(stdin);

            hospede.id = escolheId(listaHospedes);

            res = inserirHospede(&listaHospedes, hospede);

            if (res == 0)
            {
                printf("\nHospede inserido com sucesso!\n");
                printf("O ID do hospede %s: %d\n", hospede.nome, hospede.id);
                system("pause");
            }
            else
            {
                printf("\nFalha ao inserir hospede!\n");
                system("pause");
            }

            break;
        case 2:
            printf("Insira o cpf do Hospede que deseja buscar: ");
            scanf("%[^\n]", &hospede.cpf);
            fflush(stdin);

            res = buscarHospede(&listaHospedes, &hospede, hospede.cpf, &pos);
            if (res == 0)
            {
                printf("\nHospede encontrado!! -------------\n");
                printf("ID              : %d\n", hospede.id);
                printf("nome            : %s\n", hospede.nome);
                printf("endere‡o        : %s\n", hospede.endereco);
                printf("cpf             : %s\n", hospede.cpf);
                printf("telefone        : %s\n", hospede.telefone);
                printf("sexo            : %c\n", hospede.sexo);
                printf("email           : %s\n", hospede.email);
                printf("estado civil    : %s\n", hospede.estado_civil);
                printf("data nascimento : %s\n\n", hospede.data_nasc);

                system("pause");
            }
            else
            {
                printf("\nHospede nÆo encontrado!\n");
                system("pause");
            }

            break;
        case 3:
            printf("Insira o cpf do Hospede que deseja alterar: ");
            scanf("%[^\n]", &hospede.cpf);
            fflush(stdin);

            res = buscarHospede(&listaHospedes, &hospede, hospede.cpf, &pos);
            if (res == 0)
            {
                while (res != 9)
                {
                    system("cls");
                    printf("\nHospede encontrado!! -------------\n");
                    printf("Digite o campo que deseja alterar: \n\n");
                    printf("ID (fixo)           : %d\n", hospede.id);
                    printf("1 - nome            : %s\n", hospede.nome);
                    printf("2 - endere‡o        : %s\n", hospede.endereco);
                    printf("3 - cpf             : %s\n", hospede.cpf);
                    printf("4 - telefone        : %s\n", hospede.telefone);
                    printf("5 - sexo            : %c\n", hospede.sexo);
                    printf("6 - email           : %s\n", hospede.email);
                    printf("7 - estado civil    : %s\n", hospede.estado_civil);
                    printf("8 - data nascimento : %s\n\n", hospede.data_nasc);

                    printf("9 - salvar dados\n");
                    printf("0 - cancelar\n");
                    printf("=> ");

                    scanf("%d", &res);

                    if (res == 0)
                        break;

                    fflush(stdin);
                    switch (res)
                    {
                    case 1:
                        printf("Insira o novo nome: ");
                        scanf("%[^\n]", hospede.nome);
                        fflush(stdin);
                        break;
                    case 2:
                        printf("Insira o novo endere‡o: ");
                        scanf("%[^\n]", hospede.endereco);
                        fflush(stdin);
                        break;
                    case 3:
                        printf("Insira o novo cpf: ");
                        scanf("%[^\n]", hospede.cpf);
                        fflush(stdin);
                        break;
                    case 4:
                        printf("Insira o novo telefone: ");
                        scanf("%[^\n]", hospede.telefone);
                        fflush(stdin);
                        break;
                    case 5:
                        while (1)
                        {
                            printf("\nSelecione o novo sexo       : \n");
                            printf("1 - Feminino\n");
                            printf("2 - Masculino\n");
                            printf("3 - Outro\n=> ");
                            scanf("%d", &res);
                            fflush(stdin);

                            if (res == 1)
                            {
                                hospede.sexo = 'F';
                                break;
                            }
                            else if (res == 2)
                            {
                                hospede.sexo = 'M';
                                break;
                            }
                            else if (res == 3)
                            {
                                hospede.sexo = 'O';
                                break;
                            }
                            else
                            {
                                printf("Op‡Æo inv lida");
                                system("pause");
                                fflush(stdin);
                            }
                        }
                        break;
                    case 6:
                        printf("Insira o novo email: ");
                        scanf("%[^\n]", hospede.email);
                        fflush(stdin);
                        break;
                    case 7:
                        printf("Insira o novo estado civil: ");
                        scanf("%[^\n]", hospede.estado_civil);
                        fflush(stdin);
                        break;
                    case 8:
                        printf("Insira a nova data nascimento: ");
                        scanf("%[^\n]", hospede.data_nasc);
                        fflush(stdin);
                        break;
                    case 9:
                        alterarHospede(pos, hospede);
                        break;

                    default:
                        printf("Escolha um valor v lido...\n");
                        system("pause");
                        break;
                    }
                }
            }
            else
            {
                printf("\nHospede nÆo encontrado!\n");
                system("pause");
            }

            break;
        case 4:
            printf("Insira o cpf do Hospede que deseja apagar: ");
            scanf("%[^\n]", &hospede.cpf);
            fflush(stdin);

            res = buscarHospede(&listaHospedes, &hospede, hospede.cpf, &pos);
            if (res == 0)
            {
                printf("\nHospede encontrado!! -------------\n");
                printf("ID              : %d\n", hospede.id);
                printf("nome            : %s\n", hospede.nome);
                printf("cpf             : %s\n", hospede.cpf);
                printf("sexo            : %c\n", hospede.sexo);
                printf("telefone        : %s\n", hospede.telefone);

                printf("Tem certeza que deseja apagar esse hospede?\n");
                printf("1 - Apagar\n");
                printf("2 - Cancelar\n");
                printf("=> ");

                scanf("%d", &res);
                fflush(stdin);
                if (res == 1)
                {
                    apagarHospede(pos);
                    printf("Hospede apagado!\n\n");
                    system("pause");
                }
            }
            else
            {
                printf("\nHospede nÆo encontrado!\n\n");
                system("pause");
            }
            break;
        case 34:
            listarHospedes(listaHospedes);
            system("pause");
            break;
        case 35:
            printf("\n=> %d\n", escolheId(listaHospedes));
            system("pause");
            break;
        default:
            printf("Op‡Æo inv lida!\n");
            system("pause");
            fflush(stdin);
            break;
        }
    } while (1);

    return;
}