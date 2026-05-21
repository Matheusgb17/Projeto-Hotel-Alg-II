#include <stdio.h>
#include <time.h>

typedef struct {
    int id;
    int idHospede;
    int idAcomodacao;
    time_t dataEntrada;
    time_t dataSaida;
} TipoReserva;

typedef struct listaReservas {
    TipoReserva reserva;
    struct listaReservas *prox;
} ListaReservas;

typedef struct {
    time_t dataEntrada;
    time_t dataSaida;
    char facilidades[200]; // Envie uma string vazia "" se não quiser filtrar por facilidades
    int idCategoria;       // Envie 0 se o operador não quiser filtrar por categoria
    int qtdAdultos;        // Envie 0 se não quiser filtrar
    int qtdCriancas;       // Envie 0 se não quiser filtrar
} FiltroBusca;

/**
 * Função para adicionar uma nova reserva à lista de reservas.
 * @param lista Ponteiro para a lista de reservas.
 * @param novaReserva A reserva a ser adicionada.
 * @return void
 */
int adicionarReserva(ListaReservas **lista, TipoReserva novaReserva);

/**
 * Função para escolher o próximo ID disponível para uma nova reserva.
 * @param lista Ponteiro para a lista de reservas.
 * @return O próximo ID disponível (incremental).
 */
int escolheIdReserva(ListaReservas *lista);

/**
 * Função para remover uma reserva da lista de reservas com base no ID da reserva.
 * @param lista Ponteiro para a lista de reservas.
 * @param idReserva O ID da reserva a ser removida.
 * @return void
 */
void removerReserva(ListaReservas *pos);

/**
 * Função para buscar uma reserva na lista de reservas com base no ID da reserva.
 * @param lista Ponteiro para a lista de reservas.
 * @param idReserva O ID da reserva a ser buscada.
 * @return Ponteiro para a reserva encontrada ou NULL se não encontrada.
 */
int buscarReserva(ListaReservas **lista, TipoReserva *reserva, int idReserva, ListaReservas **pos);

/**
 * Função para listar todas as reservas da lista.
 * @param lista Ponteiro para a lista de reservas.
 * @return void
 */
void listarReservas(ListaReservas *lista);

/**
 * Função para verificar a disponibilidade de uma acomodação em um determinado período.
 * @param lista Ponteiro para a lista de reservas.
 * @param idAcomodacao O ID da acomodação a ser verificada.
 * @param dataEntrada A data de entrada desejada.
 * @param dataSaida A data de saída desejada.
 * @return 1 se a acomodação estiver disponível, 0 caso contrário.
 */
int verificarDisponibilidadeID(ListaReservas *lista, int idAcomodacao, time_t dataEntrada, time_t dataSaida);

/**
 * Interface para gerenciar reservas, incluindo listagem, busca, adição e remoção de reservas.
 * @param listaRes Ponteiro para a lista de reservas.
 * @param listaAcom Ponteiro para a lista de acomodações (para validação de reservas).
 * @param listaCat Ponteiro para a lista de categorias (para validação de reservas).
 * @param listaHospedes Ponteiro para a lista de hóspedes (para validação de reservas).
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha.
 */
int listarAcomodacoesParaReserva(ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaReservas *listaRes, FiltroBusca filtro);

/**
 * listar reservas por acomodação, mostrando detalhes de cada reserva vinculada a um ID de acomodação específico.
 * @param lista Ponteiro para a lista de reservas.
 * @param idAcomodacao O ID da acomodação para a qual as reservas serão listadas.
 * @return void
 */
void listarReservasPorAcomodacao(ListaReservas *lista, int idAcomodacao);

/**
 * listar reservas por hóspede, mostrando detalhes de cada reserva vinculada a um ID de hóspede específico.
 * @param lista Ponteiro para a lista de reservas.
 * @param idHospede O ID do hóspede para o qual as reservas serão listadas.
 * @return void
 */
void listarReservasPorHospede(ListaReservas *lista, int idHospede);

/**
 * Inicializa a lista de reservas alocando memória para o nó sentinela (cabeçalho).
 * @return Ponteiro para a lista de reservas inicializada.
 */
ListaReservas *iniciaListaReservas();

/**
 * Função para salvar a lista de reservas em um arquivo binário.
 * @param lista Ponteiro para a lista de reservas a ser salva.
 * @param nome_arquivo O nome do arquivo onde os dados serão salvos.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha na abertura do arquivo.
 */
int salvarDadosReservasBin(ListaReservas *lista, char *nome_arquivo);

/**
 * Função para resgatar a lista de reservas de um arquivo binário.
 * @param nome_arquivo O nome do arquivo de onde os dados serão resgatados.
 * @return Ponteiro para a lista de reservas resgatada.
 */
ListaReservas *resgataDadosReservasBin(char *nome_arquivo);

/**
 * Função para salvar a lista de reservas em um arquivo de texto.
 * @param lista Ponteiro para a lista de reservas a ser salva.
 * @param nome_arquivo O nome do arquivo onde os dados serão salvos.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha na abertura do arquivo.
 */
int salvarDadosReservasTxt(ListaReservas *lista, char *nome_arquivo);

/**
 * Função para resgatar a lista de reservas de um arquivo de texto.
 * @param nome_arquivo O nome do arquivo de onde os dados serão resgatados.
 * @return Ponteiro para a lista de reservas resgatada.
 */
ListaReservas *resgataDadosReservasTxt(char *nome_arquivo);

/**
 * Função para liberar a memória alocada para a lista de reservas.
 * @param lista Ponteiro para a lista de reservas a ser liberada.
 * @return void
 */
void liberaListaReservas(ListaReservas *lista);

/**
 * Interface para gerenciar reservas, incluindo listagem, busca, adição e remoção de reservas.
 * @param listaRes Ponteiro para a lista de reservas.
 * @param listaAcom Ponteiro para a lista de acomodações (para validação de reservas).
 * @param listaCat Ponteiro para a lista de categorias (para validação de reservas).
 * @param listaHospedes Ponteiro para a lista de hóspedes (para validação de reservas).
 * @return void
 */
void interfaceReservas(ListaReservas *listaRes, ListaAcomodacao *listaAcom, ListaCategoria *listaCat, ListaHospede *listaHospedes);
