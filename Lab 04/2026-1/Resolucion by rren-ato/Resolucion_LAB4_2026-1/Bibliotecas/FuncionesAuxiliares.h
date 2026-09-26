//
// Created by Renato on 23/09/2026.
//

#ifndef RESOLUCION_LAB4_2026_1_FUNCIONESAUXILIARES_H
#define RESOLUCION_LAB4_2026_1_FUNCIONESAUXILIARES_H

//Utils
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define MAX_PACIENTES 100
#define MAX_ESPECIALIDADES 20
#define MAX_TRIAJES 600
#define ANCHO_REPORTE 240
#define NOT_FOUND -1

//Funciones

//! Evitar pensar asi
//? void generar_reportes(const char* fileEspecialidades, const char* filePacientes, const char* fileTriaje,
//                      const char* reporte);
//* ES UNA ESTRUCTURA DISTINTA A LA DE BUSQUEDAS CON SEEKG (AYUDA A NO CONFUNDIRSE) <-- PARA EL PARCIAL

//? Apertura de archivos
void open_read_file(ifstream &input, const char* file_name);
void open_write_file(ofstream &output, const char* file_name);

//? Snipets
void print_line(ofstream &output,int width, char character);
void ignorar_coma(ifstream &input);
int read_ID(ifstream &input);
int read_date (ifstream &input);
void print_date(ofstream &output, int width, int fechasTriajes);
int read_time(ifstream &input);


//? BUSQUEDAS (DE ARREGLOS)
int buscarPaciente(int codigoPaciente, int *arrCodigosPaciente);
int buscarEspecialidad(int codigoEspecialidad, int *arrCodigosEspecialidades);


//? Lectura (llenado de arreglos)
void llenar_pacientes(const char* filePacientes, int *codigosPacientes, int *edadesPacientes, char *sexosPacientes,
                      int &cantPacientes);
void llenar_especialidades(const char* fileEspecialidades, int *codigosEspecialidades, double *costosEspecialidades,
                           int &cantEspecialidades);
void llenar_triaje(const char* fileTriaje,int *CodigosPacientes,int *CodigosEspecialidades,double *costosEspecialidades,
                   int *fechasTriajes, int *frecuenciasTriajes, int *presionesSisTriajes, int *presionesDiasTriajes,
                   double *temperaturaMaxTriajes, double *CostoTotal);

//? Impresion
void imprimirReporte(const char *fileReporte, int *CodigosPacientes, int *EdadesPacientes, char *SexosPacientes,
                     int *fechasTriajes, int *frecuenciasTriajes, int *presionesSisTriajes, int *presionesDiasTriajes,
                     double *temperaturaMaxTriajes, double *CostoTotal);



#endif //RESOLUCION_LAB4_2026_1_FUNCIONESAUXILIARES_H
