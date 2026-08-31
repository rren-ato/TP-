#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "FuncionesAuxiliares.h"

void leerTriaje(Paciente *pacientes, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int id_paciente, dd, mm, aa, edad, nivel_prioridad, hh, min, ss, i = 0;
    char car, sexo, *nombre_completo;
    while (true) {
        arch >> id_paciente;
        if (arch.eof()) return;
        arch.get();
        nombre_completo = leerCadena(150, ',', arch);
        arch >> dd >> car >> mm >> car >> aa >> car >> sexo >> car >> edad >> car >> nivel_prioridad >> car >> hh >> car
                >> min >> car >> ss;
        Hora hora{};
        hora.horas = hh;
        hora.minutos = mm;
        hora.segundos = ss;
        hora.segundos_totales = hh * 3600 + min * 60 + ss;
        Paciente paciente{};
        paciente.id_paciente = id_paciente;
        paciente.nombre_completo = nombre_completo;
        paciente.fecha_ingreso = aa * 10000 + mm * 100 + dd;
        paciente.sexo = sexo;
        paciente.edad = edad;
        paciente.nivel_prioridad = nivel_prioridad;
        paciente.tiempo_espera = hora;
        paciente.tratamientos = new Tratamiento[10]{};
        pacientes[i] = paciente;
        i++;
    }
}

void leerSignosVitales(Paciente *pacientes, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int id_paciente, frecuencia_cardiaca, presion_sistolica, presion_diastolica;
    double temperatura;
    char car;
    while (true) {
        arch >> id_paciente;
        if (arch.eof()) break;
        int posIdPaciente = buscarIdPaciente(id_paciente, pacientes);
        if (posIdPaciente != -1) {
            arch >> car >> frecuencia_cardiaca >> car >> presion_sistolica >> car >> presion_diastolica >> car >>
                    temperatura;
            pacientes[posIdPaciente].signos_vitales.frecuencia_cardiaca = frecuencia_cardiaca;
            pacientes[posIdPaciente].signos_vitales.presion_sistolica = presion_sistolica;
            pacientes[posIdPaciente].signos_vitales.presion_diastolica = presion_diastolica;
            pacientes[posIdPaciente].signos_vitales.temperatura = temperatura;
        } else ignorarHasta('\n', arch);
    }
}

int buscarIdPaciente(int id_paciente, Paciente *pacientes) {
    for (int i = 0; pacientes[i].id_paciente; i++) {
        if (pacientes[i].id_paciente == id_paciente) return i;
    }
    return -1;
}

void leerDiagnosticos(Paciente *pacientes, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int id_paciente;
    char *nombre, *observacion;
    while (true) {
        arch >> id_paciente;
        if (arch.eof()) break;
        int posIdPaciente = buscarIdPaciente(id_paciente, pacientes);
        if (posIdPaciente != -1) {
            arch.get();
            nombre = leerCadena(50, ',', arch);
            observacion = leerCadena(120, '\n', arch);
            pacientes[posIdPaciente].diagnostico.nombre = nombre;
            pacientes[posIdPaciente].diagnostico.observacion = observacion;
        } else ignorarHasta('\n', arch);
    }
}

void leerTratamientos(Paciente *pacientes, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int id_paciente, codigo_tratamiento;
    double costo;
    char car, *descripcion;
    while (true) {
        arch >> id_paciente;
        if (arch.eof()) break;
        int posIdPaciente = buscarIdPaciente(id_paciente, pacientes);
        if (posIdPaciente != -1) {
            arch >> car >> codigo_tratamiento >> car;
            descripcion = leerCadena(200, ',', arch);
            arch >> costo;
            int cantTratamientos = pacientes[posIdPaciente].cantidad_tratamientos;
            pacientes[posIdPaciente].tratamientos[cantTratamientos].codigo_tratamiento = codigo_tratamiento;
            pacientes[posIdPaciente].tratamientos[cantTratamientos].descripcion = descripcion;
            pacientes[posIdPaciente].tratamientos[cantTratamientos].costo += costo;
            pacientes[posIdPaciente].cantidad_tratamientos++;
        } else ignorarHasta('\n', arch);
    }
}

void generarReporte(const Paciente *pacientes, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    arch << setw(68) << "REPORTE DE PACIENTES EN EMERGENCIA" << endl;
    for (int i = 0; pacientes[i].id_paciente; i++) {
        imprimirLinea('-', arch);
        arch << "ID PACIENTE" << setw(15) << "NOMBRE" << setw(45) << "FECHA INGRESO" << setw(12) << "SEXO" << setw(12)
                << "EDAD" << endl;
        imprimirLinea('-', arch);
        arch << left << setw(20) << pacientes[i].id_paciente << setw(38) << pacientes[i].nombre_completo << right <<
                setfill('0') << setw(2) << pacientes[i].fecha_ingreso % 100 << "-" << setw(2) << (pacientes[i].
                    fecha_ingreso) / 100 % 100 << "-" << setfill(' ') << left << setw(15) << pacientes[i].fecha_ingreso
                / 10000;
        if (pacientes[i].sexo == 'F') arch << setw(12) << "Femenino";
        else arch << setw(12) << "Masculino";
        arch << pacientes[i].edad << right << endl;
        if (pacientes[i].signos_vitales.frecuencia_cardiaca != 0 or pacientes[i].nivel_prioridad != 0) {
            imprimirLinea('=', arch);
            arch << "SIGNOS VITALES" << endl;
            imprimirLinea('=', arch);
            if (pacientes[i].signos_vitales.frecuencia_cardiaca != 0) {
                arch << "FC" << setw(22) << ": " << pacientes[i].signos_vitales.frecuencia_cardiaca << " bpm" << endl;
                arch << "PRESIÓN" << setw(17) << ": " << pacientes[i].signos_vitales.presion_sistolica << "/" << pacientes[
                    i].signos_vitales.presion_diastolica << "mmHg" << endl;
                arch << "TEMPERATURA" << setw(13) << ": " << pacientes[i].signos_vitales.temperatura << " C" << endl;
            }
            arch << "PRIORIDAD" << setw(15) << ": " << pacientes[i].nivel_prioridad << endl;
            if (pacientes[i].signos_vitales.frecuencia_cardiaca != 0) {
                arch << "OBSERVACIONES" << setw(11) << ": " << pacientes[i].diagnostico.observacion << endl;
                arch << "DIAGNOSTICO PROBABLE" << setw(4) << ": " << pacientes[i].diagnostico.nombre << endl;
            }
            imprimirLinea('=', arch);
            if (pacientes[i].cantidad_tratamientos != 0) {
                arch << "TRATAMIENTOS" << setw(15) << ": ";
                double costoTotal = 0.00;
                for (int j = 0; j < pacientes[i].cantidad_tratamientos; j++) {
                    arch << pacientes[i].tratamientos[j].codigo_tratamiento << " ";
                    costoTotal += pacientes[i].tratamientos[j].costo;
                }
                arch << setw(30) << "COSTO TOTAL: " << costoTotal << endl;
            } else arch << "NO TIENE TRATAMIENTOS" << endl;
            imprimirLinea('=', arch);
        }
    }
}


void imprimirLinea(char car, ofstream &arch) {
    for (int i = 0; i < 95; i++) arch.put(car);
    arch.put('\n');
}

void ignorarHasta(char car, ifstream &arch) {
    while (arch.get() != car);
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
