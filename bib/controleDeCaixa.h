#ifndef CONTROLEDECAIXA_H
#define CONTROLEDECAIXA_H

#include <time.h>
#include "contas.h"

#define ENTRADA 1
#define SAIDA 2

typedef struct tipoHistoricoCaixa {
    int tipo; // 1 - Entrada, 2 - Saída
    float valor;
    char descricao[100];
    time_t data;
} TipoHistoricoCaixa;

typedef struct listaHistoricoCaixa {
    TipoHistoricoCaixa registro;
    struct listaHistoricoCaixa *prox;
} ListaHistoricoCaixa;

typedef struct {
    time_t dataInicio;
    time_t dataFim;
} FiltroControleCaixa;

/**
 * Função para inicializar a lista do histórico de movimentações do caixa
 * @return Ponteiro para a lista de histórico de caixa alocada e inicializada
 */
ListaHistoricoCaixa *iniciaListaHistoricoCaixa();

/**
 * Função para converter os dados de uma conta (a pagar ou a receber) em um registro de movimentação de caixa
 * @param conta Estrutura do tipo TipoConta contendo os dados da conta
 * @param tipo Inteiro indicando o tipo de movimentação (ENTRADA ou SAIDA)
 * @return Estrutura do tipo TipoHistoricoCaixa contendo os dados formatados para o histórico de caixa
 */
TipoHistoricoCaixa converterContaParaHistorico(TipoConta conta, int tipo);

/**
 * Função para registrar uma nova entrada de dinheiro (recebimento) no caixa
 * @param lista Ponteiro para a lista de histórico de caixa
 * @param registro Estrutura do tipo TipoHistoricoCaixa contendo os dados da entrada
 * @return 0 se o registro for bem-sucedido, 1 caso contrário
 */
int registrarEntradaCaixa(ListaHistoricoCaixa **lista, TipoHistoricoCaixa registro);

/**
 * Função para registrar uma nova saída de dinheiro (pagamento ou sangria) do caixa
 * @param lista Ponteiro para a lista de histórico de caixa
 * @param registro Estrutura do tipo TipoHistoricoCaixa contendo os dados da saída
 * @return 0 se o registro for bem-sucedido, 1 caso contrário
 */
int registrarSaidaCaixa(ListaHistoricoCaixa **lista, TipoHistoricoCaixa registro);

/**
 * Função para imprimir os dados de uma única movimentação de caixa na tela
 * @param registro Estrutura do tipo TipoHistoricoCaixa a ser impressa
 * @return void
 */
void imprimeMovimentacaoCaixa(TipoHistoricoCaixa registro);

/**
 * Função para imprimir o extrato completo de todas as movimentações registradas
 * @param lista Ponteiro para a lista de histórico de caixa
 * @return void
 */
void imprimeHistoricoCaixa(ListaHistoricoCaixa *lista);

/**
 * Função para calcular o saldo consolidado do caixa (Entradas - Saídas)
 * @param lista Ponteiro para a lista de histórico de caixa
 * @return O valor final do saldo (float)
 */
float exibirSaldoCaixa(ListaHistoricoCaixa *lista);

/**
 * Função para salvar os dados do histórico de caixa em um arquivo de texto
 * @param lista Ponteiro para a lista de histórico de caixa a ser salva
 * @param nome_arquivo Nome do arquivo onde os dados serão salvos
 * @return void
 */
void salvarDadosHistoricoCaixaBin(ListaHistoricoCaixa *lista, char *nome_arquivo);

/**
 * Função para resgatar os dados do histórico de caixa de um arquivo binário
 * @param nome_arquivo Nome do arquivo de onde os dados serão resgatados
 * @return Ponteiro para a lista de histórico de caixa resgatada
 */
void salvarDadosHistoricoCaixaTxt(ListaHistoricoCaixa *lista, char *nome_arquivo);

/**
 * Função para resgatar os dados do histórico de caixa de um arquivo de texto
 * @param nome_arquivo Nome do arquivo de onde os dados serão resgatados
 * @return Ponteiro para a lista de histórico de caixa resgatada
 */
ListaHistoricoCaixa *resgataDadosHistoricoCaixaBin(char *nome_arquivo);

/**
 * Função para resgatar os dados do histórico de caixa de um arquivo de texto
 * @param nome_arquivo Nome do arquivo de onde os dados serão resgatados
 * @return Ponteiro para a lista de histórico de caixa resgatada
 */
ListaHistoricoCaixa *resgataDadosHistoricoCaixaTxt(char *nome_arquivo);

/**
 * Função para liberar toda a memória alocada para a lista do histórico de caixa, percorrendo e desalocando cada nó
 * @param lista Ponteiro para a lista de histórico de caixa a ser liberada
 * @return void
 */
void liberaListaHistoricoCaixa(ListaHistoricoCaixa *lista);

/**
 * Função que exibe e gerencia o menu de iteração com o usuário para o Controle de Caixa
 * @param listaContas Ponteiro para a lista de contas a pagar/receber
 * @param historicoCaixa Ponteiro para a lista do histórico de movimentações do caixa
 * @return void
 */
void interfaceControleDeCaixa(ListaHistoricoCaixa *historicoCaixa);

#endif // CONTROLEDECAIXA_H
