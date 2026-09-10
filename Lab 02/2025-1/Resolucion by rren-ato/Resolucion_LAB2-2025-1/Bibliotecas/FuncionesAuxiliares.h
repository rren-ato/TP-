//
// Created by Renato on 9/09/2026.
//

#ifndef RESOLUCION_LAB2_2025_1_FUNCIONESAUXILIARES_H
#define RESOLUCION_LAB2_2025_1_FUNCIONESAUXILIARES_H

#endif //RESOLUCION_LAB2_2025_1_FUNCIONESAUXILIARES_H

//UTILS
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define ANCHO_REPORTE 200
#define ANCHO_REPORTE_HASTA_MULTA 84
#define N_COLUMNS 6
#define FOUND 1
#define NOT_FOUND -1 // para busquedas a futuro (mecanisar)

//FUNCIONES
void open_read_file(ifstream &input, const char* file_name);
void open_write_file(ofstream &output, const char* file_name);


void print_line(ofstream &output,int width, char character);
void read_and_print_name_without_arr(ifstream &input,ofstream &output, int width);
void read_and_categorize_plate(ifstream &input,ofstream &output);
int read_date (ifstream &input);
void print_date(int date, ofstream &output);
void read_and_print_description(ifstream &input, ofstream &output);

void search_infraction_code(ifstream &input_inf_de_transito, int code_infraccion_leido, int &code_validado,
                            int &falta_leve, int &falta_grave, int &falta_muy_grave);

void print_header (ofstream &output, int width);

void procesar_informacion(ifstream &input_inf_cometidas, ifstream &input_inf_de_transito, ofstream &output,
                        int &faltas_leves_per_client, int &faltas_graves_per_client, int &faltas_muy_graves_per_client,
                        double &monto_leve, double &monto_grave, double &monto_muy_grave);

void print_company_header(ifstream &input, ofstream &output, int n_compania, int DNI,  int width);

void print_totals_per_company(ofstream &output, int faltas_leves_per_client, int faltas_graves_per_client,
                                int faltas_muy_graves_per_client,
                                double monto_leves, double monto_graves, double monto_muy_graves);

void generate_report(const char *file_name_cometidas, const char *file_name_inf_transtito,
                    const char *file_name_output);




