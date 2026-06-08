#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "../bib/utils.h"

void apagaArquivo(char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo != NULL)
        fclose(arquivo);
}

void exibeMensagemErro(char *mensagem)
{
    printf("\n[ERRO] %s\n", mensagem);
}

void exibeMensagemSucesso(char *mensagem)
{
    printf("\n[SUCESSO] %s\n", mensagem);
}

void exibeMensagemAviso(char *mensagem)
{
    printf("\n[AVISO] %s\n", mensagem);
}

void pausarTela()
{
    printf("\n");
    system("pause");
}

void limparTela()
{
    system("cls");
}