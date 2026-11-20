//
// Created by aml on 19/11/2026.
//

#ifndef EX_CORRIER_NODO_H
#define EX_CORRIER_NODO_H

#include "Envio.h"

struct Nodo {
    struct Envio envios;
    struct Nodo *siguiente;
};

#endif //EX_CORRIER_NODO_H
