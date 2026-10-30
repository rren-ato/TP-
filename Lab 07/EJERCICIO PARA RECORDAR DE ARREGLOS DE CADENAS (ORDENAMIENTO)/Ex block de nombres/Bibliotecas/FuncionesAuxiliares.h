//
// Created by aml on 29/10/2026.
//

#ifndef EX_BLOCK_DE_NOMBRES_FUNCIONESAUXILIARES_H
#define EX_BLOCK_DE_NOMBRES_FUNCIONESAUXILIARES_H


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

#define TAMAÑO_ARREGLO 200

void openReadFile(ifstream &input, const char *fileName);
void openWriteFile(ofstream &output, const char *fileName);

char *leerCadena(ifstream &input, char until);

void leerDatos(const char* fileName, char** nombres, char **apellidos, int* edades) ;
void generarReporte(const char *fileName, char **nombres, char **apellidos, int* edades);

int numPersonas(char** nombres);
void ordenar(char **nombres, char **apellidos, int* edades);
void intercambio(char *&a, char *&b);
void swapInt(int &a, int &b);

void liberarMemoria(char **nombres, char **apellidos);

#endif //EX_BLOCK_DE_NOMBRES_FUNCIONESAUXILIARES_H
