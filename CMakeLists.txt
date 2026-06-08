# Para executar pelo prompt:

# gcc main.c service/hospedes.c service/categorias.c service/hotel.c service/operadores.c service/produtos.c service/fornecedores.c service/utils.c service/acomodacoes.c service/reservas.c -I bib -o output/marismar-plaza.exe
# ./output/marismar-plaza.exe

cmake_minimum_required(VERSION 3.20)
project(Projeto_Hotel_Alg_II C)

set(CMAKE_C_STANDARD 99)

include_directories(bib)

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
        service/vendas.c
        service/compras.c
        service/controleDeCaixa.c
        service/contas.c
)