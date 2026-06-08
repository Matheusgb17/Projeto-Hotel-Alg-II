#ifndef ESTADIAS_H
#define ESTADIAS_H

#define EstadiasBIN "./data/bin/estadias.dat"
#define EstadiasTXT "./data/txt/estadias.txt"

#include <stdio.h>
#include <time.h>
#include "hospedes.h"
#include "acomodacoes.h"
#include "reservas.h"

typedef struct listaHistoricoCaixa ListaHistoricoCaixa;

typedef struct {
    int id;
    int idAcomodacao;
    char cpfHospede[15];
    int idHospede;
    int idReserva;
    char dataCheckIn[11];
    char dataCheckOutPlanejado[11];
    char dataSaidaReal[11];
    float valorTotalPago;
    int status;
} TipoEstadia;

typedef struct listaEstadias {
    TipoEstadia estadia;
    struct listaEstadias *prox;
} ListaEstadia;

/**
 * Aloca memória e inicializa o nó sentinela (cabeçalho) da lista.
 * @return ListaEstadia* Ponteiro para a lista inicializada.
 */
ListaEstadia *iniciaListaEstadia();

/**
 * Percorre a lista para definir o próximo ID único disponível para a estadia.
 * @param lista Ponteiro para a lista de estadias.
 * @return int O novo ID gerado.
 */
int escolheIdEstadia(ListaEstadia *lista);

/**
 * Insere uma nova estadia no final da lista encadeada (Efetua o Check-in).
 * @param lista Ponteiro para o ponteiro da lista (permite alteração direta).
 * @param estadia Estrutura com os dados a serem inseridos.
 * @return int Retorna 0 para sucesso ou 1 para falha de alocação.
 */
int inserirEstadia(ListaEstadia **lista, TipoEstadia estadia);

/**
 * Localiza uma estadia ativa na lista através do número do quarto (idAcomodacao).
 * @param lista Ponteiro para o ponteiro da lista de busca.
 * @param estadia Ponteiro para armazenar os dados da estadia encontrada.
 * @param idQuarto O número do quarto a ser buscado.
 * @param pos Ponteiro para armazenar o endereço do nó encontrado na memória.
 * @return int Retorna 0 se encontrado ou 1 caso não exista.
 */
int buscarEstadias(ListaEstadia **lista, TipoEstadia *estadia, int idQuarto, ListaEstadia **pos);

/**
 * Sobrescreve/atualiza os dados de uma estadia em um nó específico (Utilizado para efetuar o Check-out).
 * @param pos Endereço do nó na lista que será alterado.
 * @param estadia Novos dados (como data de saída real e valores) a serem gravados.
 */
void alterarEstadia(ListaEstadia *pos, TipoEstadia estadia);

/**
 * Realiza a exclusão lógica definindo o ID da estadia ou status como 0 (Cancelamento por erro de digitação).
 * @param pos Endereço do nó que será "apagado".
 */
void apagarEstadia(ListaEstadia *pos);

/**
 * Percorre a lista e exibe todas as estadias ativas/finalizadas no console.
 * @param lista Ponteiro para a lista a ser exibida.
 */
void listarEstadias(ListaEstadia *lista);

/**
 * Salva a lista encadeada em um arquivo de texto legível.
 * @param lista Ponteiro para a lista de estadias.
 * @param nome_arquivo Nome do arquivo onde os dados serão salvos.
 * @return int Retorna 0 para sucesso ou 1 para falha de acesso ao arquivo.
 */
int salvarDadosEstadiasTxt(ListaEstadia *lista, char *nome_arquivo);

/**
 * Salva a lista encadeada em formato binário (idêntico à memória).
 * @param lista Ponteiro para a lista de estadias.
 * @param nome_arquivo Nome do arquivo onde os dados serão salvos.
 * @return int Retorna 0 para sucesso ou 1 para falha de acesso ao arquivo.
 */
int salvarDadosEstadiasBin(ListaEstadia *lista, char *nome_arquivo);

/**
 * Carrega os dados salvos do arquivo binário para a memória ao iniciar o programa.
 * @param nome_arquivo Nome do arquivo de onde os dados serão lidos.
 * @return ListaEstadia* Ponteiro para a lista preenchida com os dados do arquivo.
 */
ListaEstadia *resgataDadosEstadiasBin(char *nome_arquivo);

/**
 * Carrega os dados salvos do arquivo de texto para a memória ao iniciar o programa.
 * @param nome_arquivo Nome do arquivo de onde os dados serão lidos.
 * @return ListaEstadia* Ponteiro para a lista preenchida com os dados do arquivo.
 */
ListaEstadia *resgataDadosEstadiasTxt(char *nome_arquivo);

/**
 * Exibe os dados completos de uma estadia e extrato financeiro no console.
 * @param estadia Estrutura contendo os dados da estadia a ser exibida.
 * @return void
 */
void imprimeDadosEstadia(TipoEstadia estadia);

/**
 * Libera a memória alocada para a lista de estadias.
 * @param lista Ponteiro para a lista de estadias.
 * @return void
 */
void liberaListaEstadias(ListaEstadia *lista);


int calcularDiferencaDias(char *dataInicio, char *dataFim);

int executarCheckIn(ListaEstadia **listaEstadia, ListaHospede *listaHospede, ListaAcomodacao *listaAcomod, ListaCategoria *listaCat, TipoReserva reservaAux, int opcaoPagamento, int *idEstadiaCriado, TipoHospede *hospedeAux, TipoAcomodacao *acomodAux, TipoCategoria *catAux, int *totalDias, float *custoTotal, char *dtEntradaForm, char *dtSaidaForm);

/**
 * Interface de menu para gestão de transações, Check-in e Check-out.
 */
void interfaceEstadias(ListaEstadia *listaEstad, ListaHospede *listaHospede, ListaAcomodacao *listaAcomod, ListaCategoria *listaCat, ListaReservas *listaReservas, ListaHistoricoCaixa *historicoCaixa);

#endif