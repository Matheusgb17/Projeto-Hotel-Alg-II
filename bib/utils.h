
/**
 * Essa função é responsável por apagar um arquivo do sistema, caso ele exista. Ela recebe o nome do arquivo como parâmetro e utiliza a função remove() da biblioteca padrão do C para realizar a exclusão. Se o arquivo for apagado com sucesso, uma mensagem de confirmação é exibida. Caso contrário, uma mensagem de erro é mostrada indicando que o arquivo não pôde ser encontrado ou apagado.
 * @param nome_arquivo String contendo o nome do arquivo a ser apagado.
 * @return void
 * @warning Esta função irá apagar permanentemente o arquivo, então use com cautela.
 */
void apagaArquivo(char *nome_arquivo);