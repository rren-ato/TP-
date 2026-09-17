//
// Created by Renato on 17/09/2026.
//

#ifndef RESOLUCION_LAB3_2026_1_FUNCIONESAUXILIARES_H
#define RESOLUCION_LAB3_2026_1_FUNCIONESAUXILIARES_H

//Utils
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define ANCHO_REPORTE 210
#define ANCHO_REPORTE_JUSTIFICADO 194
#define ANCHO_REPRODUCCION 140
#define N_COLUMNS_POR_CANAL 6
#define N_COLUMNS_POR_REPRODUCCION 4
#define FOUND 1
#define NOT_FOUND -1

//Funciones

//? APERTURA DE ARCHIVOS (DEBUG)
////void open_read_file(ifstream &input, const char* file_name); [NO SE PUEDE USAR EN ESTE LAB]
////void open_write_file(ofstream &output, const char* file_name); [NO SE PUEDE USAR EN ESTE LAB]
bool openFiles(ifstream &input_clinica, ifstream &input_pacientes, ifstream &input_triaje, ofstream &output);
void closeFiles(ifstream &input_clinica, ifstream &input_pacientes, ifstream &input_triaje, ofstream &output);

//? SNIPETS
void generate_whitespaces(ofstream &output, int width);
void print_line(ofstream &output,int width, char character);
void ignorar_coma(ifstream &input);
int read_date (ifstream &input);
void print_date(ofstream &output, int date, int width);
int read_time(ifstream &input);
void print_time(ofstream &output, int width, int time);
int read_DNI(ifstream &input);
void read_and_print_name_without_arr(ifstream &input,ofstream &output, int width);


//? BUSQUEDAS
void get_data_pacientes(ifstream &input, ofstream &output, int &dni, char &sexo_paciente, int &edad_paciente);
void get_data_triaje(ifstream &input, int &fecha_registro, int &dni);

#endif //RESOLUCION_LAB3_2026_1_FUNCIONESAUXILIARES_H
