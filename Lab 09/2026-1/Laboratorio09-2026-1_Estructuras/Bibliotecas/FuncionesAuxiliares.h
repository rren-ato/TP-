#ifndef LABORATORIO09_2026_1_ESTRUCTURAS_FUNCIONESAUXILIARES_H
#define LABORATORIO09_2026_1_ESTRUCTURAS_FUNCIONESAUXILIARES_H

#include "Medico.h"
#include "Atencion.h"

void leerMedicos(Medico *arrMedicos, const char *nombArch);

void ordenarMedicos(Medico *arrMedicos);

int contarMedicos(Medico *arrMedicos);

void intercambiarMedicos(Medico &datoI, Medico &datoJ);

void leerAtenciones(Atencion *arrAtenciones, const char *nombArch);

void reporteMedicos(Medico *arrMedicos, const char *nombArch);

void reporteAtenciones(Atencion *arrAtenciones, const char *nombArch);

void elaborarInforme(Medico *arrMedicos, Atencion *arrAtenciones, const char *nombArch);

void imprimirLinea(char car, ofstream &arch);

char *leerCadena(char delim, ifstream &arch);

void modificarCadena(char *cadena);

ifstream abrirArchivosEntrada(const char *nombArch);

ofstream abrirArchivosSalida(const char *nombArch);

#endif //LABORATORIO09_2026_1_ESTRUCTURAS_FUNCIONESAUXILIARES_H
