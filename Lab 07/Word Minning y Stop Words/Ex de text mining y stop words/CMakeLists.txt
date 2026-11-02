cmake_minimum_required(VERSION 4.3)
project(Ex_de_text_mining_y_stop_words)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ex_de_text_mining_y_stop_words main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h)
