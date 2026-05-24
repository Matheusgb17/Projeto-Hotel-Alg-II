# Para executar pelo prompt:

# gcc main.c service/hospedes.c service/categorias.c service/hotel.c service/operadores.c service/produtos.c service/fornecedores.c service/utils.c service/acomodacoes.c service/reservas.c -I bib -o output/marismar-plaza.exe
# ./output/marismar-plaza.exe

cmake_minimum_required(VERSION 3.20)
project(Projeto_Hotel_Alg_II C)

# Define o padrão do C (pode usar 99 ou 11)
set(CMAKE_C_STANDARD 99)

# Inclui a pasta onde estão os seus arquivos de cabeçalho (.h)
# Pelo seu comentário do gcc, ela se chama "bib"
include_directories(bib)

# Lista todos os seus arquivos .c para o CLion compilar e indexar
add_executable(marismar-plaza
        main.c
        service/hospedes.c
        service/categorias.c
        service/hotel.c
        service/operadores.c
        service/produtos.c
        service/fornecedores.c
        service/utils.c
        service/acomodacoes.c
        service/reservas.c
)