//
// Created by Renato on 10/09/2026.
//

#ifndef RESOLUCION_LAB2_2025_2_FUNCIONESAUXILIARES_H
#define RESOLUCION_LAB2_2025_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define ANCHO_REPORTE 200
#define ANCHO_REPORTE_JUSTIFICADO 194
#define ANCHO_REPRODUCCION 140
#define N_COLUMNS_POR_CANAL 6
#define N_COLUMNS_POR_REPRODUCCION 4

//Funciones

//? APERTURA DE ARCHIVOS (DEBUG)
void open_read_file(ifstream &input, const char* file_name);
void open_write_file(ofstream &output, const char* file_name);

//? SNIPETS
void generate_whitespaces(ofstream &output, int width);
void print_line(ofstream &output,int width, char character);
void ignorar_coma(ifstream &input);
int read_date (ifstream &input);
void print_date(ofstream &output, int date, int width);
int read_time(ifstream &input);
void print_time(ofstream &output, int width, int time);


void read_and_print_name_without_arr(ifstream &input,ofstream &output, int width);

//?HEADERS
void print_info_canal(ofstream &output, int n_canal);
void print_tittle_of_report(ofstream &output, int date_limite_inf, int date_limite_sup,
                        double tarifax1k_reproducciones, double tarifaxminuto_duracion);
void print_header_reproducciones(ofstream &output);
void print_resumen_por_canal(ofstream &output, int duracion_total_reproduccion, int total_reproducciones,
                             long long ingresos_por_publidad, double ingresos_por_duracion,
                             long long new_follows_of_month,
                             long long new_views_of_month,
                             long long max_ammount_of_chat);


//? FLUJO DE DATOS
void procesar_informacion(ifstream &input, ofstream &output, long long new_visits_of_month,
    double tarifax1k_reproducciones, double tarifaxminuto_duracion,
    int &duracion_total_reproduccion, int &total_reproducciones,
    long long &ingresos_por_publidad, double &ingresos_por_duracion);
void read_and_print_registros_validos(ifstream &input, ofstream &output, int date_of_account,
                                        char char_code_stream, int int_code_stream, long long new_follows_of_month,
                                        long long new_views_of_month, long long max_ammount_of_chat,
                                        double tarifax1k_reproducciones, double tarifaxminuto_duracion,
                                        int duracion_total_reproduccion, int total_reproducciones,
                                        long long &ingresos_por_publidad, double &ingresos_por_duracion);
void registro_por_canal(ifstream &input, ofstream &output, int date_limite_inf, int date_limite_sup,
                        double tarifax1k_reproducciones, double tarifaxminuto_duracion);

void generar_reporte(const char *archivo_lectura_streams, const char *archivo_reporte);

//? LECTURA EN CONSOLA (SOLICITUD DEL ENUNCIADO)
int read_date_with_cin ();
#endif //RESOLUCION_LAB2_2025_2_FUNCIONESAUXILIARES_H


