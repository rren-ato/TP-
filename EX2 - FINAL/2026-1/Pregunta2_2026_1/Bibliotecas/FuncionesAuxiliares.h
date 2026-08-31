#ifndef PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H
#define PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H

#include "ListaPaciente.h"

void inicializarLista(ListaPaciente &lista);

void leerPaciente(PacienteTriaje &paciente, ifstream &arch);

void insertarListaOrdenada(const PacienteTriaje &paciente, ListaPaciente &listaPaciente);

void crearListaPacientes(ListaPaciente &listaPaciente, const char *nombArch);

void eliminarPrioridad3y5(ListaPaciente &listaPaciente);

void generarReporte(int caso, const ListaPaciente &listaPaciente, const char *nombArch);

void imprimirPrioridad(int i, const ListaPaciente &listaPaciente, ofstream &arch);

void ignorarHasta(char car, ifstream &arch);

void imprimirLinea(char car, ofstream &arch);

char *leerCadena(int max, char delim, ifstream &arch);

void formatearCadena(char *cadena);

ifstream abrirArchivosEntrada(const char *nombArch);

ofstream abrirArchivosSalida(const char *nombArch);

#endif //PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H
