//
// Created by Renato on 11/10/2026.
//

#ifndef RESOLUCION_EX1_2026_1_P1_FUNCIONESAUXILIARES_H
#define RESOLUCION_EX1_2026_1_P1_FUNCIONESAUXILIARES_H


//Utils
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ANCHO_REPORTE 240
#define NOT_FOUND -1

//Funciones

//? Apertura (DEBUG)
void open_read_file(ifstream &input, const char *fileName);
void open_write_file(ofstream &output, const char *fileName);

//? Snipets
int readDate(ifstream &input, int dd);
void printDate(ofstream &output, int date);
int readTime(ifstream &input);
void printDuracion(ofstream &output, int duracion);
int readID(ifstream &input);
void printLine(ofstream &output, int width, char character);
void readAndPrintWhitoutArr(ifstream &input, ofstream &output);

//? Headers
void printGeneralHeader(ofstream &output);


void leerSedes(ifstream &inputSede, ofstream &outputReporte, int sedeAtencion);

//? Busquedas
void getDattaFromAtenciones (ifstream &inputAtenciones, ofstream &outputReporte, int &fechaAtencion, int sedeAtencion,
                             ifstream &inputPacientes, ifstream &inputEspecialidades);
void getDattaFromPacientes (ifstream &inputPacientes, ofstream &outputReporte, int IdAtencion, int fechaAtencion,
                            int duracionAtencion, int cantAtenciones);
void getDattaFromEspecialidades(ifstream &inputEspecialidades, ofstream &outputReporte, int codigoDocAtencion,
                                int duracionAtencion);

//? Reporte
void GenerarReporte (const char *fileNameA, const char *fileNameS, const char *fileNameP,
                     const char *fileNameE, const char *fileName);


#endif //RESOLUCION_EX1_2026_1_P1_FUNCIONESAUXILIARES_H
