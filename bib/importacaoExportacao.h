typedef struct listaContas ListaContas;
typedef struct listaProduto ListaProduto;
typedef struct listaFornecedor ListaFornecedor;
typedef struct tipoHotel TipoHotel;
typedef struct listaHistoricoCaixa ListaHistoricoCaixa;
typedef struct listaAcomodacoes ListaAcomodacao;
typedef struct listaCategorias ListaCategoria;
typedef struct listaEstadias ListaEstadia;
typedef struct listaNotasFiscais ListaNotasFiscais;
typedef struct listaContas ListaContas;
typedef struct listaHospede ListaHospede;
typedef struct listaOperadores ListaOperadores;
typedef struct listaReservas ListaReservas; 
typedef struct listaVendas ListaVendas;

/**
 * @brief Função para importar dados de um arquivo para as listas do sistema.
 * @param nome_arquivo Nome do arquivo de importação.
 * @param listaAcomod Ponteiro para a lista de acomodações.
 * @param listaCategoria Ponteiro para a lista de categorias.
 * @param listaNotas Ponteiro para a lista de notas fiscais.
 * @param listaContasPagar Ponteiro para a lista de contas a pagar.
 * @param listaContasReceber Ponteiro para a lista de contas a receber.
 * @param historicoCaixa Ponteiro para a lista de histórico do caixa.
 * @param listaEstadia Ponteiro para a lista de estadias.
 * @param listaFornecedor Ponteiro para a lista de fornecedores.
 * @param listaHospede Ponteiro para a lista de hospedes.
 * @param dadosHotel Ponto para os dados do hotel.
 * @param listaOperadores Ponteiro para a lista de operadores.
 * @param listaProduto Ponteiro para a lista de produtos.
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaVendas Ponteiro para a lista de vendas.
 * @return Retorna 0 se a importação foi bem-sucedida, ou 1 em caso de erro.
 */
int importarDados(char *nome_arquivo, ListaAcomodacao **listaAcomod, ListaCategoria **listaCategoria, ListaNotasFiscais **listaNotas, ListaContas **listaContasPagar, ListaContas **listaContasReceber, ListaHistoricoCaixa **historicoCaixa, ListaEstadia **listaEstadia, ListaFornecedor **listaFornecedor, ListaHospede **listaHospede, TipoHotel *dadosHotel, ListaOperadores **listaOperadores, ListaProduto **listaProduto, ListaReservas **listaReservas, ListaVendas **listaVendas);

/**
 * @brief Função para exportar dados das listas do sistema para um arquivo.
 * @param nome_arquivo Nome do arquivo de exportação.
 * @param listaAcomod Ponteiro para a lista de acomodações.
 * @param listaCategoria Ponteiro para a lista de categorias.
 * @param listaNotas Ponteiro para a lista de notas fiscais.
 * @param listaContasPagar Ponteiro para a lista de contas a pagar.
 * @param listaContasReceber Ponteiro para a lista de contas a receber.
 * @param historicoCaixa Ponteiro para a lista de histórico do caixa.
 * @param listaEstadia Ponteiro para a lista de estadias.
 * @param listaFornecedor Ponteiro para a lista de fornecedores.
 * @param listaHospede Ponteiro para a lista de hospedes.
 * @param dadosHotel Ponto para os dados do hotel.
 * @param listaOperadores Ponteiro para a lista de operadores.
 * @param listaProduto Ponteiro para a lista de produtos.
 * @param listaReservas Ponteiro para a lista de reservas.
 * @param listaVendas Ponteiro para a lista de vendas.
 * @return Retorna 0 se a exportação foi bem-sucedida, ou 1 em caso de erro.
 */
int exportarDados(char *nome_arquivo, ListaAcomodacao *listaAcomod, ListaCategoria *listaCategoria, ListaNotasFiscais *listaNotas, ListaContas *listaContasPagar, ListaContas *listaContasReceber, ListaHistoricoCaixa *historicoCaixa, ListaEstadia *listaEstadia, ListaFornecedor *listaFornecedor, ListaHospede *listaHospede, TipoHotel dadosHotel, ListaOperadores *listaOperadores, ListaProduto *listaProduto, ListaReservas *listaReservas, ListaVendas *listaVendas);