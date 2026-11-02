//
// Created by Renato on 1/11/2026.
//

#ifndef EX_DE_TEXT_MINING_Y_STOP_WORDS_FUNCIONESAUXILIARES_H
#define EX_DE_TEXT_MINING_Y_STOP_WORDS_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <iomanip>
using namespace std;

#define NOT_FOUND -1
#define TAM_BUFFER 500
#define MAX_DESCONOCIDO 600
// Funciones

//? Debug
void openReadFile(ifstream &input, const char *fileName);
void openWriteFile(ofstream &output, const char *fileName);

//? Snipets
char* leerCadena (ifstream &input, char delim);
int contadorLineas (ifstream &input);
int busquedaBinaria(char** dicc, int tamDicc, char* cadena);
void swapInt(int& a, int& b);

//? Lectura de Datos
void cargarDatos(char**& diccOtros, int*& arrContaOtros, int& tamañoOtros,
                 char**& diccPalabras, int*& arrContaPalabras, int& tamañoPalabras);
void cargarDiccionario(const char* fileName, char**& diccionario, int*& arrContadorApariciones,
                       int &tamañoDiccionario);
void llenarDiccionario(ifstream &input, char** diccionario, int &tamañoDiccionario);
//? --- Tockenisacion --
void procesarTexto(int* arrContaOtros, int* arrContaPalabras,
                     char** diccDesconocido, int* frecuenciaDesconocido, int& tamDesconocido, int& cantDesconocido,
                     char** diccOtros, int tamOtros, int &cantOtros,
                     char** diccPalabras, int tamPalabras, int &cantPalabras);



//? Procesamiento de info
void procesarTockens(ifstream &input, int* arrContaOtros, int* arrContaPalabras,
                     char** diccDesconocido, int* frecuenciaDesconocido, int& tamDesconocido, int& cantDesconocido,
                     char** diccOtros, int tamOtros, int &cantOtros,
                     char** diccPalabras, int tamPalabras, int &cantPalabras);

//? Ordenamiento
void intercambiar (char*& a, char*& b);
void ordenarPorNombres(char** listaNombre, int tamaño);
void ordenarFrecuencias(char** dicc, int tam, int* frecuencia);

//? Reportes
void generarReporteParcial(ofstream &output, char** diccionario, int tamañoDiccionario, const char *descripcion);
void reporteParciales(char** diccOtros, int tamOtros, char** diccPalabras, int tamPalabras);


void escribirDesconocidos(ofstream &output, char** diccDesconocido, int* frecuenciaDesconocido, int tamDesconocido);
void creaResumenGeneral(int cantOtros, int cantPalabras, int cantDesconocido, int tamDesconocido,
                        ofstream& output, int tamOtros, int tamPalabras,
                        int* arrContaOtros, int* arrContaPalabras);
int contadorPalabrasDistintas(int *arrConta, int tam);


void crearHistograma(ofstream &output, char** diccPalabras, int tamPalabras, int* arrContaPalabras);
void generarRelleno(ofstream &output, char car, int n);


void generarRankingGeneral(ofstream &output, char** diccPalabras, int tamPalabras, int* arrContaPalabras,
                           char** diccOtros, int tamOtros, int* arrContaOtros);
void imprimirPorFilaRanking( ofstream &output, int pos, char* palabra, const char* categoria, int frecuencia);


void generarReportes(char** diccDesconocido, int* frecuenciaDesconocido, int tamDesconocido,
                     int cantOtros, int cantPalabras, int cantDesconocido, int tamOtros, int tamPalabras,
                     int* arrContaOtros, int* arrContaPalabras,
                     char** diccPalabras, char** diccOtros);

//? --- Liberacion de memoria ---
void liberarMemoria(char** diccDesconocido,
                     int* arrContaOtros, int* arrContaPalabras,
                     char** diccPalabras, char** diccOtros,
                     int tamOtros, int tamPalabras, int tamDesconocido);
#endif //EX_DE_TEXT_MINING_Y_STOP_WORDS_FUNCIONESAUXILIARES_H

