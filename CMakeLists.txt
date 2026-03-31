cmake_minimum_required(VERSION 4.2)
project(Marismar_Plaza C)

set(CMAKE_C_STANDARD 11)

include_directories(bib)

add_executable(Marismar_Plaza
        bib/hospedes.h
        service/hospedes.c
        main.c)

# Para executar pelo prompt:

# gcc main.c service/hospedes.c -I bib -o output/marismar-plaza.exe
# ./output/marismar-plaza.exe
