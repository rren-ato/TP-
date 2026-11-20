//
// Created by aml on 19/11/2026.
//

#ifndef EX_CORRIER_ENVIO_H
#define EX_CORRIER_ENVIO_H

#include "Fecha.h"
#include "Entrega.h"
struct Envio {
    int codigoEnvio;
    struct Fecha fechaRegistro;
    char* remitente;
    char* destinatario;
    char* destino;
    double peso;
    double costo;
    struct Entrega entrega;
};

#endif //EX_CORRIER_ENVIO_H
