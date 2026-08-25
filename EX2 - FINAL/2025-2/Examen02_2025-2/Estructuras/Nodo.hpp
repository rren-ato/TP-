//
// Created by Renato on 6/07/2026.
//

#ifndef EXAMEN02_2025_2_NODO_HPP
#define EXAMEN02_2025_2_NODO_HPP

#include "../Estructuras/Palabra.hpp"
#include "Palabra.hpp"
struct Nodo {
    struct Palabra palabra;
    Nodo *siguiente;
};
#endif //EXAMEN02_2025_2_NODO_HPP