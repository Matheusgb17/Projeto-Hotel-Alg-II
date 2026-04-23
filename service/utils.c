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