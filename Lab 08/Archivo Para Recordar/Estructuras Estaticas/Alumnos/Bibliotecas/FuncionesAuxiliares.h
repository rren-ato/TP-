//
// Created by aml on 5/11/2026.
//

#ifndef ALUMNOS_FUNCIONESAUXILIARES_H
#define ALUMNOS_FUNCIONESAUXILIARES_H

#include "Alumno.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <iomanip>
using namespace std;

#define NUM_ALUMNO 10
#define NOT_FOUND -1

//? Debug
void openReadFile (ifstream &input, const char* fileName);
void openWriteFile (ofstream &output, const char* fileName);


//? Lectura
char* leerCadena(ifstream &input);
void cargarDatos(const char* fileName, struct Alumno* alumnos, int &numAlumno);

//? Ordenamiento
void intercambiar(struct Alumno& a, struct Alumno& b);
void ordenarPorPormedio(struct Alumno* alumnos, int numAlumno);
void ordenarPorNombre(struct Alumno* alumnos, int numAlumno);

//? Impresion
void printEncabezado(ofstream &output);
// void generarReporte(const struct Alumno&);
void generarReporteGeneral(const char* fileName, const struct Alumno& a, int numAlumno);

//? Liberar Memoria
void liberarEstructuras(struct Alumno& alumno);
#endif //ALUMNOS_FUNCIONESAUXILIARES_H
