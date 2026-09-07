//
// Created by Renato on 3/09/2026.
//

#ifndef RESOLUCION_LAB1_2025_1_FUNCIONESAUXILIARES_H
#define RESOLUCION_LAB1_2025_1_FUNCIONESAUXILIARES_H

//Uso Utils para la apertura de bibliotecas y definir parametros generales
#include "Utils.h"

void print_line(int width, char character);
int read_date();
void print_date(int date);
int read_time();
void print_time(int time);
void generate_whitespaces(int width);

void print_header();
void read_and_print_name_without_arr_cad();
void print_datta_header();

void read_plate(char &type_vehicle, int &plate);
void print_info_plate(char type_vehicle, int plate);

void print_lvl_of_urgency(char character_of_lvl, double &multa);
void analyse_and_print_price_increase_per_type(double multa, char type_vehicle , double &type_increase);
void analyse_and_print_price_increase_per_date(double multa, int ticket_day , double &date_increase);
void analyse_and_print_price_increase_per_time(double multa, int time_of_ticket , double &time_increase);


void reporte_per_client(double &pago_total, double &pago_total_con_dni, int DNI);
void reporte_parcial(double &mayor_pago_con_dni, double &menor_pago_con_dni);



#endif //RESOLUCION_LAB1_2025_1_FUNCIONESAUXILIARES_H
