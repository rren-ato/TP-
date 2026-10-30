//
// Created by aml on 29/10/2026.
//

#include "FuncionesAuxiliares.h"

void openReadFile(ifstream &input, const char *fileName) {
    input.open(fileName, ios::in);
    if (not input.is_open()) {
        cerr << "El archivo " << fileName << " no se pudo leer";
        exit(1);
    }
}

void openWriteFile(ofstream &output, const char *fileName) {
    output.open(fileName, ios::out);
    if (not output.is_open()) {
        cerr << "El archivo " << fileName << " no se pudo abrir";
        exit(1);
    }
}


char *leerCadena(ifstream &input, char until) {
    char buffer[200],*cadena;
    input.getline(buffer, TAMAÑO_ARREGLO, until);
    if (input.eof()) return nullptr;
    cadena = new char[strlen(buffer) +1];
    strcpy(cadena,buffer);
    return cadena;
}


void leerDatos(const char* fileName, char** nombres, char **apellidos, int* edades) {
    ifstream inputDatos; openReadFile(inputDatos, fileName);

    int num=0;
    while (true) {
        char *nombre = leerCadena(inputDatos, ',');
        if (nombre == nullptr or inputDatos.eof()) break;
        char *apellido = leerCadena(inputDatos, ',');
        //? Asignacion (introducir el valor dentro del arreglo de cadenas)
        nombres[num] = nombre;

        apellidos[num] = apellido;

        inputDatos >> edades[num];      inputDatos.ignore();
        num++;
    }
}

//* Esto es opcional btw
void liberarMemoria(char **nombres, char **apellidos, int* edades) {
    for (int i=0; nombres[i]; i++) {
        delete[] nombres[i];
    }

    for (int i=0; apellidos[i]; i++) {
        delete[] apellidos[i];
    }

    for (int i=0; edades[i]; i++) {
        delete[] edades[i];
    }
}

void generarReporte(const char *fileName, char **nombres, char **apellidos, int* edades) {
    ofstream outputReporte; openWriteFile(outputReporte, fileName);
    outputReporte << setw(30) << "NOMBRES: " << setw(30) << "APELLIDOS: " << setw(20) << "EDAD: " << endl;
    for (int i=0; nombres[i]; i++) {
        outputReporte << setw(30) << nombres[i];
        outputReporte << setw(30) << apellidos[i];
        outputReporte << setw(20) << edades[i];
    }
}

int numPersonas(char** nombres) {
    int i=0;
    for (i=0; nombres[i]; i++) {}
    return i;
}

//* Esto es como un swap pero de cadenas
void intercambio(char *&a, char *&b) {
    char* aux= a;
    a = b;
    b= aux;
}

void ordenar(char **nombres, char **apellidos, int* edades) {
    int n= numPersonas(nombres);
    for (int i=0; i < n -1; i++) {
        for (int j=i+1; j < n; j++) {
            if (strcmp(nombres[i], nombres[j]) >0       or
                strcmp(nombres[i],nombres[j]) ==0 and strcmp(apellidos[i], apellidos[j]) >0 or
                strcmp(nombres[i],nombres[j]) ==0 and strcmp(apellidos[i], apellidos[j]) == 0 and edades[i]>edades[j]) {
                intercambio(nombres[i], nombres[j]);
                intercambio(apellidos[i], apellidos[j]);
                intercambio(edades[i], edades[j]);
            }
        }
    }
}