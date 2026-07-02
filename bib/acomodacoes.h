#ifndef ACOMODACOES_H
#define ACOMODACOES_H

#include "categorias.h"
#include "reservas.h"

typedef struct tipoAcomodacao {
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
 * Percorre a lista e exibe os IDs já registrados para auxiliar o usuário na escolha de um novo ID.
 * @param lista Ponteiro para a lista de acomodações.
 * @return void
 */
void listarIdsJaRegistradosAcomodacao(ListaAcomodacao *lista);

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
 * Libera a memória alocada para a lista de acomodações.
 * @param lista Ponteiro para a lista de acomodações.
 * @return void
 */
void liberaListaAcomodacoes(ListaAcomodacao *lista);

/**
 * Função para imprimir os dados de uma única acomodação formatados na tela
 * @param acomodacao Estrutura do tipo TipoAcomodacao a ser impressa
 * @param categoria Estrutura do tipo TipoCategoria vinculada a ela
 * @return void
 */
void imprimeAcomodacao(TipoAcomodacao acomodacao, TipoCategoria categoria);

/**
 * Interface de menu para gestão do cadastro de acomodações.
 * @param listaAcomod Ponteiro para a lista de acomodações.
 * @param listaCat Ponteiro para a lista de categorias.
 */
void interfaceAcomodacao(ListaAcomodacao *listaAcomod, ListaCategoria *listaCat);


/**
 * Relatório de acomodações na tela ou em formato CSV
 * @param listaAcom Ponteiro para a lista de acomodações.
 * @param listaCat Ponteiro para a lista de categorias.
 * @param listaRes Ponteiro para a lista de reservas.
 * @param codMin Codigo inicial da listagem.
 * @param codMax Codigo final da listagem.
 * @param filtro
 * @param opcaoDestino
 * @param arquivoCSV
 * @return
 */
int relatorioAcomodacoes(ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaReservas *listaRes, int codMin, int codMax, FiltroBusca filtro, int opcaoDestino, FILE *arquivoCSV);

/**
 * Função que emite o relatório de acomodações na tela ou em formato CSV.
 * @param listaAcom Ponteiro para a lista de acomodações.
 * @param listaCat Ponteiro para a lista de categorias.
 * @param listaRes Ponteiro para a lista de reservas (utilizado no filtro de datas).
 * @param codMin Código inicial da listagem (0 para ignorar).
 * @param codMax Código final da listagem (0 para ignorar).
 * @param filtro Estrutura FiltroBusca contendo categoria e/ou período desejado.
 * @param opcaoDestino Define o destino da saída (1 para Tela, 2 para Arquivo CSV).
 * @param arquivoCSV Ponteiro para o arquivo onde os dados serão salvos (se opcaoDestino for 2).
 * @return int Retorna 1 se encontrou registros, 0 se nenhum registro atendeu aos critérios.
 */
int relatorioAcomodacoes(ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaReservas *listaRes, int codMin, int codMax, FiltroBusca filtro, int opcaoDestino, FILE *arquivoCSV);

/**
 * Função de interface que gerencia os filtros e a criação do arquivo para o relatório de movimentação.
 * @param listaAcom Ponteiro para a lista de acomodações.
 * @param listaCat Ponteiro para a lista de categorias.
 * @param listaRes Ponteiro para a lista de reservas.
 * @param opcaoDestino Define o destino da saída (1 para Tela, 2 para Arquivo CSV).
 * @return void
 */
void interfaceRelatorioMovAcomodacoes(ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaReservas *listaRes, int opcaoDestino);

/**
 * Função que faz o cálculo, varre as listas e gera a saída de movimentação de acomodações em tela ou CSV.
 * @param listaAcom Ponteiro para a lista de acomodações.
 * @param listaCat Ponteiro para a lista de categorias.
 * @param listaRes Ponteiro para a lista de reservas.
 * @param idAcomFiltro O ID da acomodação para filtro (0 para ignorar).
 * @param minDiarias Quantidade mínima de diárias ocupadas para filtro.
 * @param minRendimento Valor mínimo de rendimento gerado em reais (R$) para filtro.
 * @param opcaoDestino Define o destino da saída (1 para Tela, 2 para Arquivo CSV).
 * @param arquivoCSV Ponteiro para o arquivo onde os dados serão salvos (se opcaoDestino for 2).
 * @return int Retorna 1 se encontrou registros, 0 se nenhum registro atendeu aos critérios.
 */
int relatorioMovimentacaoAcomodacoes(ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaReservas *listaRes, int idAcomFiltro, int minDiarias, float minRendimento, int opcaoDestino, FILE *arquivoCSV);

/**
 * Função de interface para capturar os filtros e chamar o relatório de listagem de acomodações.
 * @param listaAcom Ponteiro para a lista de acomodações.
 * @param listaCat Ponteiro para a lista de categorias.
 * @param listaRes Ponteiro para a lista de reservas.
 * @param opcaoDestino Define o destino da saída (1 para Tela, 2 para Arquivo CSV).
 * @return void
 */
void interfaceRelatorioAcomodacoes(ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaReservas *listaRes, int opcaoDestino);

#endif // ACOMODACOES_H
