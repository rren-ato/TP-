//
// Created by Renato on 23/08/2026.
//

#ifndef RESOLUCION_LAB1_2026_1_FUNCIONESAUXILIARES_H
#define RESOLUCION_LAB1_2026_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>

#define ANCHO_REPORTE 220
#define ANCHO_TITULO (ANCHO_REPORTE/2)
#define WHITESPACES_WIDTH 6
#define N_COLUMMNS 9

using namespace std;


//FUNCIONES BASICAS
void print_line(char character);
void print_title();
void generate_whitespaces(int width);
void print_header();

//FECHAS
int read_date();
void print_date(int date);

int read_ID();
void print_ID(int DNI);
void read_and_print_name_without_arr_cad() ;
int read_time();
void print_time(int time);

void filter_of_lvl_pressure(double sistolic_pressure, double diastolic_pressure, int *cant_pac_normal_prs,
                            int *cant_pac_HP2_prs);

void reporte_parcial(int *cant_pac_normal_prs, int *cant_pac_HP2_prs, int *duracion_total,
                    double *low_ranked_prs_ammount, int *low_ranked_prs_pac);

void reporte_final();
#endif //RESOLUCION_LAB1_2026_1_FUNCIONESAUXILIARES_H