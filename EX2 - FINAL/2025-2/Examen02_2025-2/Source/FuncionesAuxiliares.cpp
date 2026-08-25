//
// Created by Renato on 6/07/2026.
//

#include "FuncionesAuxiliares.hpp"

#include <cstring>

#include "../Estructuras/Nodo.hpp"

void open_read_file(const char* file_name, ifstream &input){
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo" << file_name << endl;
        exit(1);
    }
}

void open_write_file(const char* file_name, ofstream &output){
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al imprimir" << file_name << endl;
        exit(1);
    }
}

int leer_entero (ifstream &input) {
    int entero;
    input >> entero;
    return entero;
}

double leer_double (ifstream &input) {
    double decimal;
    input >> decimal;
    return decimal;
}

char* leer_cadena(ifstream &input, char delim, int n) {
    char *str, buffer[n];
    input.getline(buffer, delim);
    str = new char[strlen(buffer)+1];
    strcpy (str, buffer);
    return str;
}

void leer_stopword(const char *file_name, struct Nodo *lista) {
    ifstream input; open_read_file(file_name, input);

    struct Palabra palabra{};
    while (not input.eof()) {
        palabra.preproc = leer_cadena(input, ',', 20);

        //insertarlo

    }
}

// void insertar_ordenado(struct Nodo *lista, const struct Palabra &palabra) {
//
//     struct Nodo *ptr = lista;
//     struct Nodo *anterior = nullptr;
//     struct Nodo *siguiente;
//
//     siguiente->palabra = palabra;
//     while (ptr != nullptr) {
//         if (strmpy(siguiente->palabra.preproc, palabra.preproc) > 0) break;
//         anterior = ptr;
//         ptr = ptr->siguiente;
//     }
//     siguiente->siguiente = ptr;
//     if (anterior == nullptr) lista = siguiente;
//     else anterior -> siguiente = siguiente;

void insertar_ordenado(struct Nodo *lista, const struct Palabra &palabra) {
    struct Nodo *ptr = lista;
    struct Nodo *anterior = nullptr;
    struct Nodo *next;
    
    next->palabra = palabra;
    while ( ptr != nullptr ) {
        if (strcmp(next->palabra.preproc, palabra.preproc) > 0) break;
        anterior = ptr;
        ptr = ptr->siguiente;
    }
    next->siguiente = ptr;
    if (anterior == nullptr) lista = next;
    else anterior->siguiente = next;
}