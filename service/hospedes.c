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

int buscarHospede(ListaHospede **lista, TipoHospede *hospede, int id, ListaHospede **pos)
{
    if ((*lista)->prox == NULL)
        return 1;

    ListaHospede *aux = (*lista)->prox;

    while (aux->Hospedes.id != id && aux != NULL)
        aux = aux->prox;

    if (aux == NULL)
        return 1;

    if (aux->Hospedes.id == id)
    {
        *hospede = aux->Hospedes;
        *pos = aux;
        return 0;
    }

    return 1;
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
