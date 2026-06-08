#ifndef HOSPEDES_H
#define HOSPEDES_H

typedef struct tipoHospede {
    int id;
    char nome[100];
    char endereco[100];
    char cpf[15];
    char telefone[16];
    char email[100];
    char sexo;
    char estado_civil[20];
    char data_nasc[11];
} TipoHospede;

typedef struct listaHospede
{
    TipoHospede Hospedes;
    struct listaHospede *prox;
} ListaHospede;

/**
 * Percorre a lista por completo para descobrir a quantidade de posi��es
 * @param lista endere�o da lista que ser� percorrida,
 * @return retorna a quantidade de individuos inseridos
 */
int escolheIdHospede(ListaHospede *lista);

/**
 * Aloca mem�ria e inicializa o n� sentinela (cabecalho) da lista de h�spedes.
 * @return ListaHospede* Ponteiro para a lista inicializada com ID 0 e pr�ximo nulo.
 */
ListaHospede *iniciaListaHospede();

/**
 * Insere um novo h�spede no final da lista encadeada.
 * @param lista Ponteiro para o ponteiro da lista (para permitir altera��o direta).
 * @param hospede Estrutura contendo os dados do h�spede a ser inserido.
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha na aloca��o.
 */
int inserirHospede(ListaHospede **lista, TipoHospede hospede);

/**
 * Localiza um h�spede na lista atrav�s do n�mero de CPF.
 * @param lista Ponteiro para o ponteiro da lista de busca.
 * @param hospede Ponteiro para armazenar os dados do h�spede encontrado.
 * @param cpf String contendo o CPF a ser comparado.
 * @param pos Ponteiro para armazenar o endere�o do n� (Node) encontrado na lista.
 * @return int Retorna 0 se encontrado ou 1 caso a lista esteja vazia ou o CPF n�o exista.
 */
int buscarHospede(ListaHospede **lista, TipoHospede *hospede, char *cpf, ListaHospede **pos);

/**
 * Sobrescreve os dados de um h�spede em uma posi��o espec�fica da lista.
 * @param pos Ponteiro para o n� da lista que ser� alterado.
 * @param hospede Estrutura com os novos dados a serem gravados.
 * @return void
 */
void alterarHospede(ListaHospede *pos, TipoHospede hospede);

/**
 * Realiza a exclus�o l�gica de um h�spede definindo seu ID como 0.
 * @param pos Ponteiro para o n� da lista que ter� o h�spede "apagado".
 * @return void
 */
void apagarHospede(ListaHospede *pos);

/**
 * Percorre a lista e exibe no console o ID e Nome de todos os h�spedes cadastrados.
 * @param lista Ponteiro para a lista de h�spedes.
 * @return void
 */
void listarHospedes(ListaHospede *lista);

/**
 * Guarda dados de uma lista de hospedes encadeada em um arquivo bin�rio
 * @param lista n� de inicio da lista de hospedes que deseja guardar
 * @param nome_arquivo string contendo o caminho do arquivo onde deseja guardar os dados
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha ao acessar o arquivo.
 */
int salvarDadosHospedesBin(ListaHospede *lista, char *nome_arquivo);

/**
 * Resgata os dados dos hospedes de um arquivo bin�rio
 * @param nome_arquivo string contendo o caminho do arquivo de onde deseja resgatar os dados
 * @return retorna o n� para a primeira posi��o da lista encadeada gerada
 */
ListaHospede *resgataDadosHospedesBin(char *nome_arquivo);

/**
 * Guarda dados de uma lista de hospedes encadeada em um arquivo txt
 * @param lista n� de inicio da lista de hospedes que deseja guardar
 * @param nome_arquivo string contendo o caminho do arquivo onde deseja guardar os dados
 * @return int Retorna 0 para sucesso ou 1 caso ocorra falha ao acessar o arquivo.
 */
int salvarDadosHospedesTxt(ListaHospede *lista, char *nome_arquivo);

/**
 * Resgata os dados dos hospedes de um arquivo txt
 * @param nome_arquivo string contendo o caminho do arquivo de onde deseja resgatar os dados
 * @return retorna o n� para a primeira posi��o da lista encadeada gerada
 */
ListaHospede *resgataDadosHospedesTxt(char *nome_arquivo);


/**
 * libera a mem�ria alocada para a lista de hospedes
 * @param lista ponteiro para a lista de hospedes
 * @return void
 */
void liberaListaHospedes(ListaHospede *lista);

/**
 * Exibe os dados completos de um h�spede no console, formatados para f�cil leitura.
 * @param hospede Estrutura contendo os dados do h�spede a ser exibido.
 * @return void
 */
void imprimeDadosHospede(TipoHospede hospede);

/**
 * Interface para gest�o de h�spedes, permitindo cadastro, consulta, altera��o e exclus�o de dados.
 * @param modo Inteiro representando o modo de armazenamento (TXT, BIN ou MEM).
 * @return void
 */
void interfaceHospedes(ListaHospede *listaHospedes);

#endif // HOSPEDES_H
