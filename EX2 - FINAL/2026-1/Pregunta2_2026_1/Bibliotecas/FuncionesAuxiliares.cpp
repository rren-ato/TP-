#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "FuncionesAuxiliares.h"

void inicializarLista(ListaPaciente &lista) {
    lista.inicio = nullptr;
}

void crearListaPacientes(ListaPaciente &listaPaciente, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    inicializarLista(listaPaciente);
    PacienteTriaje paciente{};
    while (true) {
        leerPaciente(paciente, arch);
        if (arch.eof()) break;
        insertarListaOrdenada(paciente, listaPaciente);
    }
}

void leerPaciente(PacienteTriaje &paciente, ifstream &arch) {
    int id_paciente, edad, prioridad;
    char sexo, *nombre_completo;
    arch >> id_paciente;
    if (arch.eof()) return;
    arch.get();
    nombre_completo = leerCadena(150, ',', arch);
    ignorarHasta(',', arch);
    arch >> sexo;
    arch.get();
    arch >> edad;
    arch.get();
    arch >> prioridad;
    ignorarHasta('\n', arch);
    paciente.id_paciente = id_paciente;
    paciente.nombre_completo = nombre_completo;
    paciente.sexo = sexo;
    paciente.edad = edad;
    paciente.prioridad = prioridad;
}

void insertarListaOrdenada(const PacienteTriaje &paciente, ListaPaciente &listaPaciente) {
    NodoListaPaciente *panterior, *pactual, *nuevo;
    nuevo = new NodoListaPaciente();
    nuevo->paciente = paciente;
    panterior = nullptr;
    pactual = listaPaciente.inicio;
    while (pactual and pactual->paciente.prioridad < paciente.prioridad) {
        panterior = pactual;
        pactual = pactual->siguiente;
    }
    nuevo->siguiente = pactual;
    if (panterior == nullptr) listaPaciente.inicio = nuevo;
    else panterior->siguiente = nuevo;
}

void eliminarPrioridad3y5(ListaPaciente &listaPaciente) {
    NodoListaPaciente *panterior, *pactual;
    panterior = nullptr;
    pactual = listaPaciente.inicio;
    while (pactual) {
        if (pactual->paciente.prioridad == 3 or pactual->paciente.prioridad == 5) {
            panterior->siguiente = pactual->siguiente;
            NodoListaPaciente *aEliminar = pactual;
            pactual = pactual->siguiente;
            delete [] aEliminar->paciente.nombre_completo;
            delete [] aEliminar;
        } else {
            panterior = pactual;
            pactual = pactual->siguiente;
        }
    }
}


void generarReporte(int caso, const ListaPaciente &listaPaciente, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    arch << setw(50) << "REPORTE DE ATENCIÓN PRIORITARIA EN EMERGENCIAS" << endl;
    imprimirLinea('-', arch);
    if (caso == 1) {
        for (int i = 1; i <= 5; i++) {
            imprimirPrioridad(i, listaPaciente, arch);
        }
    } else {
        if (caso == 2) {
            for (int i = 1; i <= 2; i++) {
                imprimirPrioridad(i, listaPaciente, arch);
            }
            for (int i = 4; i <= 4; i++) {
                imprimirPrioridad(i, listaPaciente, arch);
            }
            imprimirLinea('-', arch);
            arch << "Observación: Prioridades 3 y 5 se atenderán en sala de admisión." << endl;
        }
    }
}

void imprimirPrioridad(int i, const ListaPaciente &listaPaciente, ofstream &arch) {
    NodoListaPaciente *pactual = listaPaciente.inicio;
    arch << "PRIORIDAD CLÍNICA: " << i << endl;
    arch << "ID" << setw(19) << "NOMBRE COMPLETO" << setw(27) << "EDAD" << setw(8) << "SEXO" << endl;
    while (pactual) {
        if (pactual->paciente.prioridad == i) {
            arch << left << setw(6) << pactual->paciente.id_paciente << setw(35) << pactual->paciente.nombre_completo <<
                    right << setw(5) << pactual->paciente.edad;
            if (pactual->paciente.sexo == 'F') arch << setw(14) << "FEMENINO" << endl;
            else arch << setw(15) << "MASCULINO" << endl;
        }
        pactual = pactual->siguiente;
    }
}

void ignorarHasta(char car, ifstream &arch) {
    while (arch.get() != car);
}

void imprimirLinea(char car, ofstream &arch) {
    for (int i = 0; i < 80; i++) arch.put(car);
    arch.put('\n');
}

char *leerCadena(int max, char delim, ifstream &arch) {
    char cadena[max], *pcadena;
    arch.getline(cadena, max, delim);
    if (arch.eof()) return nullptr;
    formatearCadena(cadena);
    pcadena = new char [strlen(cadena) + 1];
    strcpy(pcadena, cadena);
    return pcadena;
}

void formatearCadena(char *cadena) {
    for (int i = 0; cadena[i]; i++) {
        if (i == 0 or cadena[i - 1] == '_') {
            cadena[i - 1] = ' ';
            cadena[i] = toupper(cadena[i]);
        }
    }
}

ifstream abrirArchivosEntrada(const char *nombArch) {
    ifstream arch(nombArch, ios::in);
    if (not arch) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << nombArch << endl;
        exit(1);
    }
    return arch;
}

ofstream abrirArchivosSalida(const char *nombArch) {
    ofstream arch(nombArch, ios::out);
    if (not arch) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << nombArch << endl;
        exit(1);
    }
    return arch;
}
