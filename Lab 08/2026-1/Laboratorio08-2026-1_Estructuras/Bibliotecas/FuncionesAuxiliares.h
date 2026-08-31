#ifndef LABORATORIO08_2026_1_ESTRUCTURAS_FUNCIONESAUXILIARES_H
#define LABORATORIO08_2026_1_ESTRUCTURAS_FUNCIONESAUXILIARES_H

#include "Medico.h"
#include "Atencion.h"

void leerEspecialidadesMedicos(Medico *arrMedicos, const char *nombArch);

void reportePruebaMedico(Medico *arrMedicos, const char *nombArch);

void ordenarMedico(Medico *arrMedicos);

int contarMedicos(Medico *arrMedicos);

void intercambiarMedicos(Medico &medicoI, Medico &medicoJ);

void leerAtenciones(Atencion *arrAtenciones, const char *nombArch);

void reportePruebaAtencion(Atencion *arrAtenciones, const char *nombArch);;

void ordenarAtencion(Atencion *arrAtenciones);

int contarAtenciones(Atencion *arrAtenciones);

void intercambiarAtenciones(Atencion &atencionI, Atencion &atencionJ);

void generarReporte(Medico *arrMedicos, Atencion *arrAtenciones, const char *nombArch);

void imprimirEncabezado(int i, Medico *arrMedicos, ofstream &arch);

void imprimirLinea(char car, ofstream &arch);

ifstream abrirArchivosEntrada(const char *nombArch);

ofstream abrirArchivosSalida(const char *nombArch);

#endif //LABORATORIO08_2026_1_ESTRUCTURAS_FUNCIONESAUXILIARES_H
