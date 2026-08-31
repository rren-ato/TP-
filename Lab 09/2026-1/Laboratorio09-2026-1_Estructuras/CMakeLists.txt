cmake_minimum_required(VERSION 4.1)
project(Laboratorio09_2026_1_Estructuras)

set(CMAKE_CXX_STANDARD 20)

add_executable(Laboratorio09_2026_1_Estructuras main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Medico.h
        Bibliotecas/Fecha.h
        Bibliotecas/Hora.h
        Bibliotecas/Codigo.h
        Bibliotecas/Atencion.h)
