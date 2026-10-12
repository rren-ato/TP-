//
// Created by Renato on 12/10/2026.
//

#ifndef RESOLUCION_EX2_2026_1_P2_FUNCIONESAUXILIARES_H
#define RESOLUCION_EX2_2026_1_P2_FUNCIONESAUXILIARES_H

//Utils

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define MAX_ATENCIONES 100
#define ANCHO_REPORTE 210
#define N_COLUMNS 7
#define NOT_FOUND -1

//Funciones

//? Apertura (DEBUG)
void open_read_file(ifstream &input, const char* fileName);
void open_write_file(ofstream &output, const char* fileName);

//? Snipets
void printLine (ofstream &output, int width, char character);
int readTime (ifstream &input);
void printTime (ofstream &output, int time);


//? Odenamiento (swaps o shifts)
void swapInt(int &a, int &b);
void swapDouble(double &a, double &b);
int busquedaNormal (int dato, int *arrDato, int cantAtenciones);
int busquedaBinaria(double dato, double *arrdato, int cantAtenciones);
bool eliminarDato(int *codigosAtencionMed, int *codigosEspecialidad, double *tarifasPorHora,
                    int *numeroAtenciones, int *tiempoTotal, int *tiempoPromedio, double *pagoRecibido,
                    int &cantSmth, int pos);

void insertionSort(int *codigosAtencionMed, int *codigosEspecialidad, double *tarifasPorHora,
                    int *numeroAtenciones, int *tiempoTotal, int *tiempoPromedio, double *pagoRecibido,
                    int cantAntenciones);


//? Lectura
bool insertarDesordenado (ifstream &inputAtenciones, int *tiempoTotal, int duracionAtencion, int *codigosAtencionMed, int codigoMedico,
                          int *numeroAtenciones, int &cantAntenciones, int capacidad);
void llenar_Atenciones(const char *fileNameA, int *tiempoTotal, int *codigosAtencionMed,
                        int *numerosAtenciones, int &cantAntenciones, int capacidad);

void llenar_Medicos(const char *fileNameM, double *tarifasPorHora, int *codigosAtencionMed, int *codigosEspecialidad,
                    int cantAtenciones);

void calcularPagoYtiempoPromedio(int *tiempoTotal, double *tarifaPorHora, double *pagoRecibido, int *numeroAtenciones,
                                 int *tiemposPromedio, int cantAtenciones);

void headerReporteFinal(ofstream &output);
void generarReporte(const char *fileNameReporte,int *codigosAtencionMed, int *codigosEspecialidad, double *tarifasPorHora,
                    int *numeroAtenciones, int *tiempoTotal, int *tiempoPromedio, double *pagoRecibido,
                    int cantAntenciones);

#endif //RESOLUCION_EX2_2026_1_P2_FUNCIONESAUXILIARES_H
