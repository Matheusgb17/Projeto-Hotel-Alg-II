#include <stdbool.h>

typedef struct
{
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
 * Aloca e inicializa uma nova estrutura de hotel com valores padrão.
 * @return TipoHotel* Ponteiro para a estrutura alocada na memória.
 */
TipoHotel *iniciaHotel();

/**
 * Salva os dados de uma variável local para o ponteiro de referência do hotel.
 * @param h Estrutura contendo os novos dados a serem salvos.
 * @param hotel Ponteiro para o destino onde os dados serão persistidos.
 * @return void
 */
void salvarDadosHotel(TipoHotel h, TipoHotel *hotel);

/**
 * Retorna os dados contidos no ponteiro do hotel.
 * @param h Ponteiro para a estrutura dos dados do hotel.
 * @return TipoHotel Uma cópia dos dados contidos no endereço apontado.
 */
TipoHotel consultarDadosHotel(TipoHotel *h);

/**
 * Restaura o estado da estrutura para não cadastrado e limpa o nome fantasia.
 * @param hotel Ponteiro para a estrutura que terá os dados removidos.
 * @return void
 */
void apagarDadosHotel(TipoHotel *hotel);

void interfaceHotel();