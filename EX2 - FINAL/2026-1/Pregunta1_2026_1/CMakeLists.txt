cmake_minimum_required(VERSION 4.1)
project(Pregunta1_2026_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pregunta1_2026_1 main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Hora.h
        Bibliotecas/Tratamiento.h
        Bibliotecas/SignosVitales.h
        Bibliotecas/Diagnostico.h
        Bibliotecas/Paciente.h)
