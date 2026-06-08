#ifndef CONTAS_H
#define CONTAS_H

typedef struct listaHistoricoCaixa ListaHistoricoCaixa;

typedef struct tipoConta {
    int id;
    int idNota;
    float valorParcela;
    int numeroParcela;
    char dataVencimento[11];
    int statusPago;
} TipoConta;

typedef struct listaContas {
    TipoConta conta;
    struct listaContas *prox;
} ListaContas;

/**
 * Função para inicializar a lista de contas
 * @return Ponteiro para a lista de contas alocada e inicializada
 */
ListaContas *iniciaListaContas();

/**
 * Função para escolher o próximo ID disponível para uma nova conta
 * @param lista Ponteiro para a lista de contas 
 * @return Próximo ID disponível (inteiro)
 */
int escolheIdConta(ListaContas *lista);

/**
 * Função para inserir uma nova conta na lista
 * @param lista Ponteiro para a lista de contas
 * @param conta Estrutura do tipo TipoConta contendo os dados da nova conta a ser inserida
 * @return 0 se a inserção for bem-sucedida, 1 caso contrário
 */
int inserirConta(ListaContas **lista, TipoConta conta);

/**
 * Função para buscar uma conta na lista pelo ID
 * @param lista Ponteiro para a lista de contas
 * @param conta Ponteiro para uma estrutura do tipo TipoConta onde os dados da conta encontrada serão armazenados
 * @param idBusca ID da conta a ser buscada
 * @param pos Ponteiro para um ponteiro do tipo ListaContas onde a posição da conta encontrada será armazenada
 * @return 0 se a conta for encontrada, 1 caso contrário
 */
int buscarConta(ListaContas **lista, TipoConta *conta, int idBusca, ListaContas **pos);

/**
 * Função para alterar os dados de uma conta existente
 * @param novaConta Estrutura do tipo TipoConta contendo os novos dados da conta
 * @param pos Ponteiro para um ponteiro do tipo ListaContas onde a posição da conta a ser alterada está armazenada
 * @return void
 */
void alterarConta(TipoConta novaConta, ListaContas **pos);

/**
 * Função para apagar uma conta da lista (marcando seu ID como 0 para exclusão lógica)
 * @param pos Ponteiro para um ponteiro do tipo ListaContas onde a posição da conta a ser apagada está armazenada
 * @return void
 */
void apagarConta(ListaContas **pos);

/**
 * Função para imprimir os dados de uma única conta formatados na tela
 * @param conta Estrutura do tipo TipoConta a ser impressa
 * @return void
 */
void imprimeConta(TipoConta conta);

/**
 * Função para percorrer e imprimir todas as contas válidas de uma lista
 * @param lista Ponteiro para a lista de contas
 * @return void
 */
void imprimeContas(ListaContas *lista);

/**
 * Função para salvar os dados das contas em um arquivo de texto
 * @param lista Ponteiro para a lista de contas a ser salva
 * @param nome_arquivo Nome do arquivo onde os dados serão salvos
 * @return 0 se a operação for bem-sucedida, 1 caso contrário
 */
int salvarDadosContasTxt(ListaContas *lista, char *nome_arquivo);

/**
 * Função para resgatar os dados das contas de um arquivo de texto
 * @param nome_arquivo Nome do arquivo de onde os dados serão resgatados
 * @return Ponteiro para a lista de contas resgatada
 */
ListaContas *resgataDadosContasTxt(char *nome_arquivo);

/**
 * Função para salvar os dados das contas em um arquivo binário
 * @param lista Ponteiro para a lista de contas a ser salva
 * @param nome_arquivo Nome do arquivo onde os dados serão salvos
 * @return 0 se a operação for bem-sucedida, 1 caso contrário
 */
int salvarDadosContasBin(ListaContas *lista, char *nome_arquivo);

/**
 * Função para resgatar os dados das contas de um arquivo binário
 * @param nome_arquivo Nome do arquivo de onde os dados serão resgatados
 * @return Ponteiro para a lista de contas resgatada
 */
ListaContas *resgataDadosContasBin(char *nome_arquivo);

/**
 * Função para inserir especificamente uma conta a pagar definindo seu status inicial como pendente
 * @param listaAPagar Ponteiro para a lista de contas a pagar
 * @param conta Estrutura do tipo TipoConta contendo os dados
 * @return 0 se a inserção for bem-sucedida, 1 caso contrário
 */
int inserirContaPagar(ListaContas **listaAPagar, TipoConta conta);

/**
 * Função para alterar o status de uma conta a pagar para PAGO
 * @param pos Ponteiro para a posição do nó da conta na lista
 * @param conta Estrutura do tipo TipoConta a ser atualizada
 * @return void
 */
void baixarContaPagar(ListaContas **pos, TipoConta conta, ListaHistoricoCaixa **historicoCaixa);

/**
 * Função para listar exclusivamente as contas a pagar que possuem status PENDENTE
 * @param lista Ponteiro para a lista de contas a pagar
 * @return void
 */
void listarContasPagarPendentes(ListaContas *lista);

/**
 * Função para listar exclusivamente o histórico de contas a pagar com status PAGO
 * @param lista Ponteiro para a lista de contas a pagar
 * @return void
 */
void listarContasPagarPagas(ListaContas *lista);

/**
 * Função para inserir especificamente uma conta a receber definindo seu status inicial como pendente
 * @param listaAReceber Ponteiro para a lista de contas a receber
 * @param conta Estrutura do tipo TipoConta contendo os dados
 * @return 0 se a inserção for bem-sucedida, 1 caso contrário
 */
int inserirContaReceber(ListaContas **listaAReceber, TipoConta conta);

/**
 * Função para alterar o status de uma conta a receber para PAGO
 * @param pos Ponteiro para a posição do nó da conta na lista
 * @param conta Estrutura do tipo TipoConta a ser atualizada
 * @return void
 */
void baixarContaReceber(ListaContas **pos, TipoConta conta, ListaHistoricoCaixa **historicoCaixa);

/**
 * Função para listar exclusivamente as contas a receber que possuem status PENDENTE
 * @param lista Ponteiro para a lista de contas a receber
 * @return void
 */
void listarContasReceberPendentes(ListaContas *lista);

/**
 * Função para listar exclusivamente o histórico de contas a receber com status PAGO
 * @param lista Ponteiro para a lista de contas a receber
 * @return void
 */
void listarContasReceberPagas(ListaContas *lista);

/**
 * Função que exibe e gerencia o menu de iteração com o usuário para o módulo de Contas a Pagar
 * @param listaContasPagar Ponteiro para a lista de contas a pagar
 * @param historicoCaixa Ponteiro para a lista do histórico de movimentações do caixa
 * @return void
 */
void interfaceContasPagar(ListaContas **listaContasPagar, ListaHistoricoCaixa **historicoCaixa);

/**
 * Função para liberar toda a memória alocada para a lista de contas, percorrendo e desalocando cada nó
 * @param lista Ponteiro para a lista de contas a ser liberada
 * @return void
 */
void liberaListaContas(ListaContas *lista);

/**
 * Função que exibe e gerencia o menu de iteração com o usuário para o módulo de Contas a Receber
 * @param listaContasReceber Ponteiro para a lista de contas a receber
 * @param historicoCaixa Ponteiro para a lista do histórico de movimentações do caixa
 * @return void
 */
void interfaceContasReceber(ListaContas **listaContasReceber, ListaHistoricoCaixa **historicoCaixa);

#endif // CONTAS_H
