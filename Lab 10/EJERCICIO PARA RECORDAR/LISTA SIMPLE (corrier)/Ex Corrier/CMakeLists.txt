cmake_minimum_required(VERSION 4.4)
project(Ex_Corrier)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ex_Corrier main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Estructuras/Fecha.h
        Bibliotecas/Estructuras/Persona.h
        Bibliotecas/Estructuras/Tarifa.h
        Bibliotecas/Estructuras/Destino.h
        Bibliotecas/Estructuras/Entrega.h
        Bibliotecas/Estructuras/Envio.h
        Bibliotecas/Estructuras/Nodo.h
        Bibliotecas/Estructuras/TotalPorZona.h
        Bibliotecas/Estructuras/Resumen.h)
