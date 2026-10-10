//
// Created by Renato on 9/10/2026.
//

#ifndef RESOLUCION_LAB5_2026_2_FUNCIONESAUXILIARES_H
#define RESOLUCION_LAB5_2026_2_FUNCIONESAUXILIARES_H


//Utils

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#define NOT_FOUND -1
#define MAX_CLIENTES 100
#define MAX_PAGOS 150

//Funciones

//? Aperturas
void open_read_file(ifstream &input, const char *filename);
void open_write_file(ofstream &output, const char *filename);

//? SNIPETS
int readDate(ifstream &input);
void ignorarComa(ifstream &input);

//? MOVIMIENTO DE DATOS (SHIFT O SWAP)
void swapInt (int &a, int &b);
void swapDouble (double &a, double &b);
void swapChar (char &a, char &b);
void ordenarClientes(int *codigosClientes, char *tiposCreditos, double *montosDesembolsados, int &cantClientes);
int busquedaBinaria(int *codigosClientes, int codigoClienteMovimiento, int cantClientes);
bool eliminacionDato(int *codigosClientes, char *tiposCreditos, double *montosDesembolsados,
                            int &cantClientes, int posClienteEliminar);
bool insertarOrdenado(int *codigosClientes, char *tiposCreditos, double *montosDesembolsados,
                            int &cantClientes, int capacidad,
                            int codigoCliente, char tipoCredito, double montoDesembolsado);

//? LLenado
bool insertarDesordenado(ifstream &input, int *codigosClientes, char *tiposCreditos, double *montosDesembolsados,
                      int &cantClientes, int capacidad,
                      int codigoCliente, char tipoCredito, double montoDesembolsado);
void llenarClientes (const char *filename, int *codigosClientes, char *tiposCreditos, double *montosDesembolsados,
                     int &cantClientes, int capacidad);
void updateClientesConMovimientos(const char* fileName, int *codigosClientes, char *tiposCreditos, double *montosDesembolsados,
                                  int &cantClientes, int capacidad);
void updateClientesConPagos(const char* fileName, int *codigosClientes, double *saldosPendientesPagos, int *cantCuotas,
                            int *mayorAtraso, int *fechaMayorAtraso,
                            int cantClientes);



#endif //RESOLUCION_LAB5_2026_2_FUNCIONESAUXILIARES_H
