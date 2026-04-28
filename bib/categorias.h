#ifndef CATEGORIAS_H
#define CATEGORIAS_H
#include <stdio.h>

typedef struct {
    int id;
    char descricao[100];
    float valorDiaria;
    int capacidadeAdultos;
    int capacidadeCriancas;

} TipoCategoria;

typedef struct listaCategorias {
    TipoCategoria categoria;
    struct listaCategorias *prox;
} ListaCategoria;


/**
 * Aloca memória e inicializa o nó sentinela (cabeçalho) da lista.
 * @return ListaCategoria* Ponteiro para a lista inicializada.
 */
ListaCategoria *iniciaListaCategoria();

/**
 * Percorre a lista para definir o próximo ID único disponível.
 * @param lista Ponteiro para a lista de categorias.
 * @return int O novo ID gerado.
 */
int escolheIdCategoria(ListaCategoria *lista);

/**
 * Insere uma nova categoria no final da lista encadeada.
 * @param lista Ponteiro para o ponteiro da lista (permite alteração direta).
 * @param categoria Estrutura com os dados a serem inseridos.
 * @return int Retorna 0 para sucesso ou 1 para falha de alocação.
 */
int inserirCategoria(ListaCategoria **lista, TipoCategoria categoria);

/**
 * Localiza uma categoria na lista através do seu ID.
 * @param lista Ponteiro para o ponteiro da lista de busca.
 * @param categoria Ponteiro para armazenar os dados da categoria encontrada.
 * @param id O código único a ser buscado.
 * @param pos Ponteiro para armazenar o endereço do nó encontrado na memória.
 * @return int Retorna 0 se encontrado ou 1 caso não exista.
 */
int buscarCategoria(ListaCategoria **lista, TipoCategoria *categoria, int id, ListaCategoria **pos);

/**
 * Sobrescreve os dados de uma categoria em um nó específico.
 * @param pos Endereço do nó na lista que será alterado.
 * @param categoria Novos dados a serem gravados.
 */
void alterarCategoria(ListaCategoria *pos, TipoCategoria categoria);

/**
 * Realiza a exclusão lógica definindo o ID como 0.
 * @param pos Endereço do nó que será "apagado".
 */
void apagarCategoria(ListaCategoria *pos);

/**
 * Percorre a lista e exibe todas as categorias no console.
 * @param lista Ponteiro para a lista a ser exibida.
 */
void listarCategoria(ListaCategoria *lista);

/**
 * Salva a lista encadeada em um arquivo de texto legível.
 * @param lista Ponteiro para a lista de categorias.
 * @param nome_arquivo Nome do arquivo onde os dados serão salvos.
 * @return int Retorna 0 para sucesso ou 1 para falha de acesso ao arquivo.
 */
int salvarDadosCategoriasTxt(ListaCategoria *lista, char *nome_arquivo);

/**
 * Salva a lista encadeada em formato binário (idêntico à memória).
 * @param lista Ponteiro para a lista de categorias.
 * @param nome_arquivo Nome do arquivo onde os dados serão salvos.
 * @return int Retorna 0 para sucesso ou 1 para falha de acesso ao arquivo.
 */
int salvarDadosCategoriasBin(ListaCategoria *lista, char *nome_arquivo);

/**
 * Carrega os dados salvos do arquivo para a memória ao iniciar o programa.
 * @param nome_arquivo Nome do arquivo de onde os dados serão lidos.
 * @return ListaCategoria* Ponteiro para a lista preenchida com os dados do arquivo.
 */
ListaCategoria *carregarCategoriasBin(char *nome_arquivo);

/**
 * Carrega os dados salvos do arquivo de texto para a memória ao iniciar o programa.
 * @param nome_arquivo Nome do arquivo de onde os dados serão lidos.
 * @return ListaCategoria* Ponteiro para a lista preenchida com os dados do arquivo.
 */
ListaCategoria *carregarCategoriasTxt(char *nome_arquivo);

void interfaceCategoria(ListaCategoria *listaCategorias, int modo);

#endif