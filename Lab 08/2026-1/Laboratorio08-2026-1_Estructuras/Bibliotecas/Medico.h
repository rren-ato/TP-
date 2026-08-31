#ifndef LABORATORIO08_2026_1_ESTRUCTURAS_MEDICO_H
#define LABORATORIO08_2026_1_ESTRUCTURAS_MEDICO_H

struct Medico {
    int codigo;
    char nombre[200];
    int especialidadCodigo;
    char especialidad[200];
    double tarifa;
};

#endif //LABORATORIO08_2026_1_ESTRUCTURAS_MEDICO_H