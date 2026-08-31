#ifndef PREGUNTA1_2026_1_PACIENTE_H
#define PREGUNTA1_2026_1_PACIENTE_H

#include "Hora.h"
#include "SignosVitales.h"
#include "Diagnostico.h"
#include "Tratamiento.h"

struct Paciente {
    int id_paciente;
    char *nombre_completo;
    int fecha_ingreso;
    char sexo;
    int edad;
    int nivel_prioridad;
    Hora tiempo_espera;
    SignosVitales signos_vitales;
    Diagnostico diagnostico;
    Tratamiento *tratamientos;
    int cantidad_tratamientos;
};

#endif //PREGUNTA1_2026_1_PACIENTE_H