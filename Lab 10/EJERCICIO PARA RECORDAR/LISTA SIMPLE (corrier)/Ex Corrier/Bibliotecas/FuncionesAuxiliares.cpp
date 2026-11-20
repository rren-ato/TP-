//
// Created by aml on 19/11/2026.
//

#include "FuncionesAuxiliares.h"

void openReadFile (ifstream &input, const char* fileName) {
    input.open(fileName);
    if (not input.is_open()) {
        cerr << "El archivo " << fileName << " no se pudo leer" << endl;
        exit(1);
    }
}

void openWriteFile (ofstream &output, const char* fileName) {
    output.open(fileName);
    if (not output.is_open()) {
        cerr << "El archivo " << fileName << " no se pudo abrir" << endl;
        exit(1);
    }
}