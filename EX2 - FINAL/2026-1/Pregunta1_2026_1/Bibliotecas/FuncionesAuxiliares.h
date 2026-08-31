#ifndef PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H
#define PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H

#include "Paciente.h"

void leerTriaje(Paciente *pacientes, const char *nombArch);

void leerSignosVitales(Paciente *pacientes, const char *nombArch);

int buscarIdPaciente(int id_paciente, Paciente *pacientes);

void leerDiagnosticos(Paciente *pacientes, const char *nombArch);

void leerTratamientos(Paciente *pacientes, const char *nombArch);

void generarReporte(const Paciente *pacientes, const char *nombArch);

void imprimirLinea(char car, ofstream &arch);

void ignorarHasta(char car, ifstream &arch);

char *leerCadena(int max, char delim, ifstream &arch);

void formatearCadena(char *cadena);

ifstream abrirArchivosEntrada(const char *nombArch);

ofstream abrirArchivosSalida(const char *nombArch);

#endif //PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H
