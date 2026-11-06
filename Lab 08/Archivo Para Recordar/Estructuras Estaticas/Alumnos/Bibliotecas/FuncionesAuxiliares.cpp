//
// Created by aml on 5/11/2026.
//

#include "FuncionesAuxiliares.h"

#include <bits/unicode.h>

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

char* leerCadena(ifstream &input) {
    char buffer[100];
    char* str;
    input.getline(buffer, 100);
    if (not input.eof()) return nullptr;
    str = new char[strlen(buffer) + 1];
    strcpy(str, buffer);
    return str;
}

void cargarDatos(const char* fileName, struct Alumno* alumnos, int &numAlumno) {
    ifstream inputDatos; openReadFile (inputDatos, fileName);
    struct Alumno alumno;
    numAlumno = 0;
    int codigo;
    while (inputDatos >> codigo) {
        inputDatos.ignore(); // para la coma
        //? Inicializacion
        alumno.codigo = codigo;
        inputDatos >> alumno.promedio;                  inputDatos.ignore();
        alumno.nombre = leerCadena(inputDatos);      inputDatos.ignore();
        inputDatos >> alumno.matriculado;               inputDatos.ignore();
        //* Se copia toda la estructura
        alumnos[numAlumno++] = alumno;
    }

}

void intercambiar(struct Alumno& a, struct Alumno& b) {
    struct Alumno aux = a;
    a = b;
    b = aux;
}

void ordenarPorPormedio(struct Alumno* alumnos, int numAlumno) {
    for (int i = 0; i < numAlumno-1; i++) {
        for (int j=i+1; j<numAlumno; j++) {
            if (alumnos[i].promedio < alumnos[j].promedio) {
                //* se intercambia la estructura completa
                intercambiar(alumnos[i], alumnos[j]);
            }
        }
    }
}

void ordenarPorNombre(struct Alumno* alumnos, int numAlumno) {
    for (int i = 0; i < numAlumno-1; i++) {
        for (int j=i+1; j<numAlumno; j++) {
            if (strcmp(alumnos[i].nombre, alumnos[j].nombre) < 0) {
                //* se intercambia la estructura completa
                intercambiar(alumnos[i], alumnos[j]);
            }
        }
    }
}


void printEncabezado(ofstream &output) {
    output << left << setw(20) << "CODIGO" <<
    setw(15) << "PROMEDIO" <<
        setw(18) << "MAT." <<
            setw(30) << "NOMBRE" << endl;
}

// void generarReporte(ofstream &output, const struct Alumno& a) {
//     printEncabezado();
//     output << left << setw(20) << a.codigo <<
//         setw(15) << fixed << setprecision(2) << a.promedio <<
//             left << setw(18) << (a.matriculado ? "SI" : "NO") <<
//                 setw(30) << a.nombre;
// }

void generarReporteGeneral(const char* fileName, const struct Alumno &a, int numAlumno) {
    ofstream outputReporte; openWriteFile(outputReporte, fileName);
    printEncabezado(outputReporte);
    cout << left << setw(20) << a.codigo <<
        setw(15) << fixed << setprecision(2) << a.promedio <<
            left << setw(18) << (a.matriculado ? "SI" : "NO") <<
                setw(30) << a.nombre;
}


void liberarEstructuras(struct Alumno& alumno) {
    delete[] alumno.nombre;
}