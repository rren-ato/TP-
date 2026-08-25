cmake_minimum_required(VERSION 4.1)
project(Examen02_2025_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Examen02_2025_2 main.cpp
        Source/FuncionesAuxiliares.cpp
        Source/FuncionesAuxiliares.hpp
        Estructuras/Nodo.hpp
        Estructuras/Palabra.hpp
        Source/Utils.hpp)
