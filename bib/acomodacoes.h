#ifndef ACOMODACOES_H
#define ACOMODACOES_H

#include <stdio.h>
#include "categorias.h"

typedef struct {
    int id;
    char descricao[100];
    char facilidades[200];
    int idCategoria;
} TipoAcomodacao;

typedef struct listaAcomodacoes {
    TipoAcomodacao acomodacao;
    struct listaAcomodacoes *prox;
} ListaAcomodacao;

/**
 * Aloca memória e inicializa o nó sentinela (cabeçalho) da lista de acomodações.
 * @return ListaAcomodacao* Ponteiro para a lista inicializada com ID 0 e próximo nulo.
 */
ListaAcomodacao *iniciaListaAcomodacao();

/**
 * Percorre a lista por completo para descobrir a quantidade de posições e definir o próximo ID.
 * @param lista Endereço da lista que será percorrida.
 * @return int O novo ID único gerado.
 */
int escolheIdAcomodacao(ListaAcomodacao *lista);

/**
 * Insere uma nova acomodação no final da lista encadeada.
 * @param lista Ponteiro para o ponteiro da lista (para permitir alteração direta).
 * @param acomodacao Estrutura contendo os dados da acomodação a ser inserida.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha na alocação.
 */
int inserirAcomodacao(ListaAcomodacao **lista, TipoAcomodacao acomodacao);

/**
 * Localiza uma acomodação na lista através do seu ID único.
 * @param lista Ponteiro para o ponteiro da lista de busca.
 * @param acomodacao Ponteiro para armazenar os dados da acomodação encontrada.
 * @param id O código único a ser buscado.
 * @param pos Ponteiro para armazenar o endereço do nó (Node) encontrado na lista.
 * @return int Retorna 0 se encontrado ou 1 caso não exista.
 */
int buscarAcomodacao(ListaAcomodacao **lista, TipoAcomodacao *acomodacao, int id, ListaAcomodacao **pos);

/**
 * Sobrescreve os dados de uma acomodação em uma posição específica da lista.
 * @param pos Ponteiro para o nó da lista que será alterado.
 * @param acomodacao Estrutura com os novos dados a serem gravados.
 */
void alterarAcomodacao(ListaAcomodacao *pos, TipoAcomodacao acomodacao);

/**
 * Realiza a exclusão lógica de uma acomodação definindo seu ID como 0.
 * @param pos Ponteiro para o nó da lista que terá a acomodação "apagada".
 */
void apagarAcomodacao(ListaAcomodacao *pos);

/**
 * Percorre a lista e exibe as acomodações cadastradas.
 * @param lista Ponteiro para a lista de acomodações.
 * @param listaCat Ponteiro para a lista de categorias (para validação/exibição).
 */
void listarAcomodacao(ListaAcomodacao *lista, ListaCategoria *listaCat);

/**
 * Guarda dados de uma lista de acomodações encadeada em um arquivo binário.
 * @param lista Nó de início da lista que deseja guardar.
 * @param nome_arquivo String contendo o caminho do arquivo.
 */
void salvarDadosAcomodacoesBin(ListaAcomodacao *lista, char *nome_arquivo);

/**
 * Resgata os dados das acomodações de um arquivo binário.
 * @param nome_arquivo String contendo o caminho do arquivo de origem.
 * @return ListaAcomodacao* Retorna o ponteiro para a lista encadeada gerada.
 */
ListaAcomodacao *resgataDadosAcomodacoesBin(char *nome_arquivo);

/**
 * Guarda dados de uma lista de acomodações encadeada em um arquivo TXT (Tags).
 * @param lista Nó de início da lista que deseja guardar.
 * @param nome_arquivo String contendo o caminho do arquivo.
 */
void salvarDadosAcomodacoesTxt(ListaAcomodacao *lista, char *nome_arquivo);

/**
 * Resgata os dados das acomodações de um arquivo TXT (Tags).
 * @param nome_arquivo String contendo o caminho do arquivo de origem.
 * @return ListaAcomodacao* Retorna o ponteiro para a lista encadeada gerada.
 */
ListaAcomodacao *resgataDadosAcomodacoesTxt(char *nome_arquivo);

/**
 * Interface de menu para gestão do cadastro de acomodações.
 * @param listaAcomod Ponteiro para a lista de acomodações.
 * @param listaCat Ponteiro para a lista de categorias.
 */
void interfaceAcomodacao(ListaAcomodacao *listaAcomod, ListaCategoria *listaCat, int modo);

#endif