cmake_minimum_required(VERSION 4.3)
project(Alumnos)

set(CMAKE_CXX_STANDARD 20)

add_executable(Alumnos main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Alumno.h)
