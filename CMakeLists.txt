# Para executar pelo prompt:

# gcc main.c service/hospedes.c service/categorias.c service/hotel.c service/operadores.c service/produtos.c service/fornecedores.c service/utils.c service/acomodacoes.c service/reservas.c -I bib -o output/marismar-plaza.exe
# ./output/marismar-plaza.exe

cmake_minimum_required(VERSION 3.31)
project(Projeto_Hotel_Alg_II C)

set(CMAKE_C_STANDARD 11)

include_directories(bib)

add_executable(Projeto_Hotel_Alg_II
        bib/fornecedores.h
        bib/hospedes.h
        service/fornecedores.c
        service/hospedes.c
        main.c
        service/categorias.c
        bib/categorias.h
        service/acomodacoes.c
        bib/acomodacoes.h
        service/produtos.c
        bib/produtos.h
        service/hotel.c
        service/operadores.c
        service/utils.c
        service/reservas.c
        service/estadias.c
        bib/utils.h


)


# Para executar pelo prompt:

# gcc main.c service/hospedes.c -I bib -o output/marismar-plaza.exe
# ./output/marismar-plaza.exe
