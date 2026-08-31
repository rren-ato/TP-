#ifndef LABORATORIO08_2026_1_ESTRUCTURAS_ATENCION_H
#define LABORATORIO08_2026_1_ESTRUCTURAS_ATENCION_H

#include "Fecha.h"
#include "Hora.h"
#include "Codigo.h"

struct Atencion {
    Fecha fecha;
    int codigoMedico;
    Hora duracion;
    Codigo paciente;
};

#endif //LABORATORIO08_2026_1_ESTRUCTURAS_ATENCION_H
