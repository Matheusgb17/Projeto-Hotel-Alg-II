#ifndef HOTEL_H
#define HOTEL_H

#include <stdbool.h>

typedef struct tipoHotel {
    bool cadastrado;
    char nomeFantasia[100];
    char razaoSocial[150];
    char inscricaoEstadual[20];
    char CNPJ[19];
    char enderecoCompleto[200];
    char telefone[16];
    char email[100];
    char nomeResponsavel[100];
    char telefoneResponsavel[16];
    char horarioCheckin[6];
    char horarioCheckout[6];
    float margemLucro;
} TipoHotel;

/**
 * Aloca e inicializa uma nova estrutura de hotel com valores padr�o.
 * @return TipoHotel* Ponteiro para a estrutura alocada na mem�ria.
 */
TipoHotel *iniciaHotel();

/**
 * Salva os dados de uma vari�vel local para o ponteiro de refer�ncia do hotel.
 * @param h Estrutura contendo os novos dados a serem salvos.
 * @param hotel Ponteiro para o destino onde os dados ser�o persistidos.
 * @return void
 */
void salvarDadosHotel(TipoHotel h, TipoHotel *hotel);

/**
 * Retorna os dados contidos no ponteiro do hotel.
 * @param h Ponteiro para a estrutura dos dados do hotel.
 * @return TipoHotel Uma c�pia dos dados contidos no endere�o apontado.
 */
TipoHotel consultarDadosHotel(TipoHotel *h);

/**
 * Restaura o estado da estrutura para n�o cadastrado e limpa o nome fantasia.
 * @param hotel Ponteiro para a estrutura que ter� os dados removidos.
 * @return void
 */
void apagarDadosHotel(TipoHotel *hotel);

/**
 * Fun��o para salvar os dados do hotel em um arquivo bin�rio.
 * @param h Estrutura contendo os dados a serem salvos.
 * @param nome_arquivo String contendo o nome do arquivo bin�rio onde os dados ser�o salvos.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha ao acessar o arquivo.
 */
int salvarDadosHotelBin(TipoHotel h, char *nome_arquivo);

/**
 * Fun��o para resgatar os dados do hotel a partir de um arquivo bin�rio.
 * @param nome_arquivo String contendo o nome do arquivo bin�rio a ser lido.
 * @return TipoHotel* Ponteiro para a estrutura preenchida com os dados resgatados.
 */
TipoHotel *resgataDadosHotelBin(char *nome_arquivo);

/**
 * Fun��o para salvar os dados do hotel em um arquivo texto.
 * @param h Estrutura contendo os dados a serem salvos.
 * @param nome_arquivo String contendo o nome do arquivo de texto onde os dados ser�o salvos.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha ao acessar o arquivo.
 */
int salvarDadosHotelTxt(TipoHotel h, char *nome_arquivo);

/**
 * Fun��o para resgatar os dados do hotel a partir de um arquivo de texto.
 * @param nome_arquivo String contendo o nome do arquivo de texto a ser lido.
 * @return TipoHotel* Ponteiro para a estrutura preenchida com os dados resgatados.
 */
TipoHotel *resgataDadosHotelTxt(char *nome_arquivo);

/**
 * Libera a mem�ria alocada para a estrutura do hotel.
 * @param hotel Ponteiro para a estrutura do hotel a ser liberada.
 * @return void
 */
void liberaHotel(TipoHotel *hotel);

/**
 * Interface para gest�o de hot�is, permitindo cadastro, consulta, altera��o e exclus�o de dados.
 * @param modo Inteiro representando o modo de armazenamento (TXT, BIN ou MEM).
 * @return void
 */
void interfaceHotel(TipoHotel *hotel);

#endif // HOTEL_H
