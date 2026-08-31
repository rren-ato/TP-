#ifndef PREGUNTA2_2026_1_NODOLISTAPACIENTE_H
#define PREGUNTA2_2026_1_NODOLISTAPACIENTE_H

#include "PacienteTriaje.h"

struct NodoListaPaciente {
    PacienteTriaje paciente;
    NodoListaPaciente *siguiente;
};

#endif //PREGUNTA2_2026_1_NODOLISTAPACIENTE_H