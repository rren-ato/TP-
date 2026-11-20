//
// Created by aml on 19/11/2026.
//

#ifndef EX_CORRIER_ENTREGA_H
#define EX_CORRIER_ENTREGA_H

#include "Fecha.h"

struct Entrega {
    char characterEstado;
    struct Fecha fechaEntrega;
    int diasDemora;
};

#endif //EX_CORRIER_ENTREGA_H
