#ifndef UTILS_H
#define UTILS_H

/**
 * Essa função é responsável por apagar um arquivo do sistema, caso ele exista.
 * @param nome_arquivo String contendo o nome do arquivo a ser apagado.
 * @return void
 * @warning Esta função irá apagar permanentemente o arquivo, então use com cautela.
 */
void apagaArquivo(char *nome_arquivo);

/**
 * Exibe uma mensagem de erro formatada no console.
 * @param texto String contendo a mensagem de erro a ser exibida.
 * @return void
 */
void exibeMensagemErro(char *texto);


/**
 * Exibe uma mensagem de sucesso formatada no console.
 * @param texto String contendo a mensagem de sucesso a ser exibida.
 * @return void
 */
void exibeMensagemSucesso(char *mensagem);

/**
 * Exibe uma mensagem de aviso formatada no console.
 * @param mensagem String contendo a mensagem de aviso a ser exibida.
 * @return void
 */
void exibeMensagemAviso(char *mensagem);

/**
 * Exibe uma mensagem de aviso formatada no console.
 * @param texto String contendo a mensagem de aviso a ser exibida.
 * @return void
 */
void pausarTela();

/**
 * Limpa o console, removendo todas as mensagens e informações exibidas anteriormente.
 * @return void
 */
void limparTela();

#endif // UTILS_H
