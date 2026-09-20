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

#define ANCHO_REPORTE 100



//* UNO NO DEBE CONFUNDIR COMO SE ESTA ENSEÑANDO EN EL CURSO
//! ESTAS BUSQUEDAS (SIN ARREGLOS) NO REQUIEREN UN FOUND O NOT_FOUND
//* LAS BUSQUEDAS DE ESTE LAB3 CONCIERNES SOLO A BUSCAR LOS VALORES Y LITERALMENTE LEER LO QUE QUEDA O FALTA
//? #define FOUND 1
//? #define NOT_FOUND -1

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
int calcular_duracion(int hora_ingreso, int hora_salida);
double calculo_monto_final(double costo_atencion_por_hora, double duracion_atencion, int edad_paciente);

//? BUSQUEDAS
void get_data_pacientes(ifstream &input, ofstream &output, int dni, char &sexo_paciente, int &edad_paciente,
                        int &contador_paciente);
void get_data_triaje(ifstream &input, int &fecha_registro, int dni, int &frecuencia_cardiaca_triaje,
                     int &presion_sistolica_triaje, int &presion_diastolica_triaje, double &temperatura_triaje,
                     int &saturacion_oxigeno_triaje, bool &paciente_valido);


//? IMPRESIONES
void print_header(ofstream &output);
void print_header_of_date(ofstream &output, int fecha_registro);
void print_pacientes_info(ofstream &output, int edad_paciente, char sexo_paciente);
void print_triaje_info(ofstream &output, double temperatura_triaje, int presion_sistolica_triaje,
                       int presion_diastolica_triaje, double costo_atencion_por_hora, int duracion_atencion,
                       double costo_final);


void leer_clinica_Y_Generar_reporte(ifstream &input_clinica, ifstream &input_pacientes, ifstream &input_triaje,
                                    ofstream &output);
#endif //RESOLUCION_LAB3_2026_1_FUNCIONESAUXILIARES_H
