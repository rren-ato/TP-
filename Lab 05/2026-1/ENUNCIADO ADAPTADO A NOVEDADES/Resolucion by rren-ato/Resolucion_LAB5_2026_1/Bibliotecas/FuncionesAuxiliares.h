//
// Created by Renato on 1/10/2026.
//

#ifndef RESOLUCION_LAB5_2026_1_FUNCIONESAUXILIARES_H
#define RESOLUCION_LAB5_2026_1_FUNCIONESAUXILIARES_H


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

//? Busquedas
int busquedaBinaria(int *arrdato, int valorAbuscar, int n);

//? Ordenamiento
bool insertarOrdenadoEsp(int *codigosEspecialidades, int *costosEspecialidades, int capacidad, int &longitud,
                      int codigo, int costo);
bool insertarOrdenadoPac(int *codigosPacientes, char *sexosPacientes, int *arrEdadPacientes,double *maxMontoPacientes,
                         int capacidad, int &longitud, int dni, char sexo, int edad, double montoMaximo);

//? Llenado
void llenar_especialidades(const char* file_name, int *codigosEspecialidades, int *costosEspecialidades,
                           int capacidad, int &longitud);
void llenar_pacientes(const char* file_name, int *codigosPacientes, char *sexosPacientes, int *arrEdadPacientes,
                      double *maxMontoPacientes, int capacidad, int &longitud);
#endif //RESOLUCION_LAB5_2026_1_FUNCIONESAUXILIARES_H
