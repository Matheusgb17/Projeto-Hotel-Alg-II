#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "bib\hospedes.h"

int main()
{
    ListaHospede *pos, *listaHospedes = iniciaListaHospede();
    TipoHospede hospede;
    int res = 0;

    // Cadastro e Gestão de Hospedes
    do
    {
        system("cls");
        printf("Cadastro e gestão de Hospedes!\n");
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
            printf("2 - n�o\n");
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
            printf("Insira seu nome            : ");
            scanf("%[^\n]", hospede.nome);
            fflush(stdin);

            printf("Insira seu endere�o        : ");
            scanf("%[^\n]", hospede.endereco);
            fflush(stdin);

            printf("Insira seu cpf             : ");
            scanf("%[^\n]", hospede.cpf);
            fflush(stdin);

            printf("Insira seu telefone        : ");
            scanf("%[^\n]", hospede.telefone);
            fflush(stdin);

            while (1)
            {
                printf("\nSelecione o seu sexo       : \n");
                printf("1 - Feminino\n");
                printf("2 - Masculino\n");
                printf("3 - Outro\n=> ");
                scanf("%d", &res);
                fflush(stdin);

                if (res == 1)
                {
                    hospede.sexo = 'f';
                    break;
                }
                else if (res == 2)
                {
                    hospede.sexo = 'm';
                    break;
                }
                else if (res == 3)
                {
                    hospede.sexo = 'n';
                    break;
                }
                else
                {
                    printf("Op��o inv�lida");
                    system("pause");
                    fflush(stdin);
                }
            }

            printf("Insira seu email           : ");
            scanf("%[^\n]", hospede.email);
            fflush(stdin);

            printf("Insira seu estado civil    : ");
            scanf("%[^\n]", hospede.estado_civil);
            fflush(stdin);

            printf("Insira sua data nascimento : ");
            scanf("%[^\n]", hospede.data_nasc);
            fflush(stdin);

            hospede.id = escolheId(listaHospedes);

            res = inserirHospede(&listaHospedes, hospede);

            if (res == 0)
            {
                printf("\nHospede inserido com sucesso!\n");
                printf("O ID do hospede %s � : %d\n", hospede.nome, hospede.id);
                system("pause");
            }
            else
            {
                printf("\nFalha ao inserir hospede!\n");
                system("pause");
            }

            break;
        case 2:
            printf("Insira o id do Hospede que deseja buscar: ");
            scanf("%d", &hospede.id);
            fflush(stdin);

            res = buscarHospede(&listaHospedes, &hospede, hospede.id, &pos);
            if (res == 0)
            {
                printf("\nHospede encontrado!! -------------\n");
                printf("ID              : %d\n", hospede.id);
                printf("nome            : %s\n", hospede.nome);
                printf("endere�o        : %s\n", hospede.endereco);
                printf("cpf             : %s\n", hospede.cpf);
                printf("telefone        : %s\n", hospede.telefone);
                printf("sexo            : %c\n", hospede.sexo);
                printf("email           : %s\n", hospede.email);
                printf("estado civil    : %s\n", hospede.estado_civil);
                printf("data nascimento : %s\n", hospede.data_nasc);

                system("pause");
            }
            else
            {
                printf("\nHospede n�o encontrado!\n");
                system("pause");
            }

            break;
        case 3:
            printf("Insira o id do Hospede que deseja alterar: ");
            scanf("%d", &hospede.id);
            fflush(stdin);

            res = buscarHospede(&listaHospedes, &hospede, hospede.id, &pos);
            if (res == 0)
            {
                while (res != 9)
                {
                    printf("\nHospede encontrado!! -------------\n");
                    printf("Digite o campo que deseja alterar: \n\n");
                    printf("ID (fixo)           : %d\n", hospede.id);
                    printf("1 - nome            : %s\n", hospede.nome);
                    printf("2 - endereço        : %s\n", hospede.endereco);
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

                    printf("%d", res);

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
                        printf("Insira seu endere�o: ");
                        scanf("%[^\n]", hospede.endereco);
                        fflush(stdin);
                        break;
                    case 3:
                        printf("Insira seu cpf: ");
                        scanf("%[^\n]", hospede.cpf);
                        fflush(stdin);
                        break;
                    case 4:
                        printf("Insira seu telefone: ");
                        scanf("%[^\n]", hospede.telefone);
                        fflush(stdin);
                        break;
                    case 5:
                        while (1)
                        {
                            printf("\nSelecione o seu sexo       : \n");
                            printf("1 - Feminino\n");
                            printf("2 - Masculino\n");
                            printf("3 - Outro\n=> ");
                            scanf("%d", &res);
                            fflush(stdin);

                            if (res == 1)
                            {
                                hospede.sexo = 'f';
                                break;
                            }
                            else if (res == 2)
                            {
                                hospede.sexo = 'm';
                                break;
                            }
                            else if (res == 3)
                            {
                                hospede.sexo = 'n';
                                break;
                            }
                            else
                            {
                                printf("Op��o inv�lida");
                                system("pause");
                                fflush(stdin);
                            }
                        }
                        break;
                    case 6:
                        printf("Insira seu email: ");
                        scanf("%[^\n]", hospede.email);
                        fflush(stdin);
                        break;
                    case 7:
                        printf("Insira seu estado civil: ");
                        scanf("%[^\n]", hospede.estado_civil);
                        fflush(stdin);
                        break;
                    case 8:
                        printf("Insira sua data nascimento: ");
                        scanf("%[^\n]", hospede.data_nasc);
                        fflush(stdin);
                        break;
                    case 9:
                        alterarHospede(pos, hospede);
                        break;

                    default:
                        printf("Escolha um valor v�lido...\n");
                        system("pause");
                        break;
                    }
                }
            }
            else
            {
                printf("\nHospede n�o encontrado!\n");
                system("pause");
            }

            break;
        case 4:
            printf("Insira o id do Hospede que deseja apagar: ");
            scanf("%d", &hospede.id);
            fflush(stdin);

            res = buscarHospede(&listaHospedes, &hospede, hospede.id, &pos);
            if (res == 0)
            {
                printf("\nHospede encontrado!! -------------\n");
                printf("ID              : %d\n", hospede.id);
                printf("nome            : %s\n\n", hospede.nome);

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
                printf("\nHospede n�o encontrado!\n\n");
                system("pause");
            }
            break;
        case 34:
            listarHospedes(listaHospedes);
            system("pause");
            break;
        case 35:
            printf("\n=> %d\n", escolheId(listaHospedes));
            break;
        default:
            printf("Op��o inv�lida!\n");
            system("pause");
            fflush(stdin);
            break;
        }
    } while (1);

    return 0;
}