//
// Created by aml on 19/11/2026.
//

#ifndef EX_CORRIER_TOTALPORZONA_H
#define EX_CORRIER_TOTALPORZONA_H

#include "Destino.h"
#include "Envio.h"

struct TotalPorzona {
    struct Destino destinos; //zona
    struct Envio envios; //peso++ y costo++ (contador por referencia)
    char characterZona;
};

#endif //EX_CORRIER_TOTALPORZONA_H
