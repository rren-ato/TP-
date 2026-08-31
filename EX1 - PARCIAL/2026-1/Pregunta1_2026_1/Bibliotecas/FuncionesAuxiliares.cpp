#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 135

void elaborarInforme(const char *nombArchSedes, const char *nombArchPacientes, const char *nombArchEspecialidad,
                     const char *nombArchAtenciones, const char *nombArchReporte) {
    ifstream archSedes = abrirArchivosEntrada(nombArchSedes);
    ifstream archPacientes = abrirArchivosEntrada(nombArchPacientes);
    ifstream archEspecialidad = abrirArchivosEntrada(nombArchEspecialidad);
    ifstream archAtenciones = abrirArchivosEntrada(nombArchAtenciones);
    ofstream arch = abrirArchivosSalida(nombArchReporte);
    arch << right << fixed << setprecision(2);
    imprimirLinea('=', arch);
    arch << setw(78) << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    arch << setw(73) << "ATENCIONES POR SEDE" << endl;
    generarInforme(archSedes, archPacientes, archEspecialidad, archAtenciones, arch);
}

void generarInforme(ifstream &archSedes, ifstream &archPacientes, ifstream &archEspecialidad, ifstream &archAtenciones,
                    ofstream &arch) {
    int sede, cantCaracteres, totalSedes = 0, sedeMayor;
    double totalPago = 0.00, pagoMayor = 0.00;
    while (true) {
        archSedes >> sede;
        if (archSedes.eof()) break;
        imprimirLinea('=', arch);
        arch << "SEDE: " << sede << " - ";
        imprimirTexto('\n', cantCaracteres, archSedes, arch);
        arch << endl;
        leerAtenciones(sede, totalSedes, totalPago, sedeMayor, pagoMayor, archAtenciones, archPacientes,
                       archEspecialidad, arch);
    }
    imprimirLinea('=', arch);
    arch << "RESUMEN TOTAL" << endl;
    imprimirLinea('-', arch);
    arch << "CANTIDAD DE SEDES QUE ATENDIERON: " << totalSedes << endl;
    arch << "PAGO TOTAL: $/. " << totalPago << endl;
    arch << "SEDE CON MAYOR PAGO: " << sedeMayor << " - " << pagoMayor << endl;
    imprimirLinea('=', arch);
}

void leerAtenciones(int sede, int &totalSedes, double &totalPago, int &sedeMayor, double &pagoMayor,
                    ifstream &archAtenciones, ifstream &archPacientes, ifstream &archEspecialidad, ofstream &arch) {
    archAtenciones.clear();
    archAtenciones.seekg(0, ios::beg);
    int fecha, sedeAtencion, doctorAtencion, cantAtenciones = 0, duracion, totalDuracionSede = 0;
    double pago, totalPagoSede = 0.00;
    while (true) {
        fecha = leerFecha(archAtenciones);
        if (fecha == 0) break;
        while (true) {
            archAtenciones >> sedeAtencion;
            int horaInicio = leerHora(archAtenciones);
            int pacienteAtencion = leerPaciente(archAtenciones);
            int horaFin = leerHora(archAtenciones);
            duracion = horaFin - horaInicio;
            archAtenciones >> doctorAtencion;
            if (sede == sedeAtencion) {
                imprimirCabeceraAtenciones(cantAtenciones, fecha, arch);
                leerPacientes(doctorAtencion, pacienteAtencion, duracion, pago, archPacientes,
                              archEspecialidad, arch);
                totalPagoSede += pago;
                totalDuracionSede += duracion;
                cantAtenciones++;
            }
            if (archAtenciones.get() == '\n') break;
        }
    }
    imprimirResumenSede(sede, cantAtenciones, totalPagoSede, totalDuracionSede, totalSedes, totalPago, sedeMayor,
                        pagoMayor, arch);
}

void imprimirResumenSede(int sede, int cantAtenciones, double totalPagoSede, int totalDuracionSede,
                         int &totalSedes, double &totalPago, int &sedeMayor, double &pagoMayor, ofstream &arch) {
    imprimirLinea('-', arch);
    arch << "TOTAL ATENCIONES: " << cantAtenciones << endl;
    arch << "TOTAL PAGO SEDE: $/. " << totalPagoSede << endl;
    arch << "TIEMPO TOTAL ATENCIONES: ";
    imprimirHora(totalDuracionSede, arch);
    arch << endl;
    if (cantAtenciones > 0) totalSedes++;
    totalPago += totalPagoSede;
    if (pagoMayor == 0.00 or totalPagoSede > pagoMayor) {
        pagoMayor = totalPagoSede;
        sedeMayor = sede;
    }
}

void imprimirCabeceraAtenciones(int cantAtenciones, int fecha, ofstream &arch) {
    if (cantAtenciones == 0) {
        arch << "ATENCIONES" << endl;
        arch << setw(12) << "FECHA" << setw(23) << "PACIENTE" << setw(32) << "DURACION" << setw(20) <<
                "MEDICO" << setw(40) << "ESPECIALIDAD" << setw(7) << "PAGO" << endl;
    }
    arch << setfill('0') << setw(2) << cantAtenciones + 1 << setfill(' ') << ") ";
    imprimirFecha(fecha, arch);
}

void leerPacientes(int doctorAtencion, int pacienteAtencion, int duracion, double &pago, ifstream &archPacientes,
                   ifstream &archEspecialidad, ofstream &arch) {
    archPacientes.clear();
    archPacientes.seekg(0, ios::beg);
    int paciente, cantCaracteres;
    while (true) {
        paciente = leerPaciente(archPacientes);
        if (paciente == 0) break;
        if (paciente == pacienteAtencion) {
            arch << setw(12) << pacienteAtencion << " - ";
            imprimirTexto(' ', cantCaracteres, archPacientes, arch);
            arch << setw(30 - cantCaracteres) << "";
            imprimirHora(duracion, arch);
            ignorarHasta('\n', archPacientes);
            leerEspecialidades(doctorAtencion, duracion, pago, archEspecialidad, arch);
        } else ignorarHasta('\n', archPacientes);
    }
}

void leerEspecialidades(int doctorAtencion, int duracion, double &pago, ifstream &archEspecialidad, ofstream &arch) {
    archEspecialidad.clear();
    archEspecialidad.seekg(0, ios::beg);
    int especialidad, doctor, cantCaracteres;
    double tarifa;
    while (true) {
        archEspecialidad >> especialidad;
        if (archEspecialidad.eof()) break;
        ignorarHasta(' ', archEspecialidad);
        while (true) {
            archEspecialidad >> doctor;
            if (doctor == doctorAtencion) {
                arch << setw(10) << doctor << " - ";
                imprimirTexto(' ', cantCaracteres, archEspecialidad, arch);
                archEspecialidad >> tarifa;
                pago = tarifa * (duracion / 3600.00);
                arch << setw(42 - cantCaracteres) << especialidad << setw(13) << pago << endl;;
            } else {
                ignorarHasta(' ', archEspecialidad);
                archEspecialidad >> tarifa;
            }
            if (archEspecialidad.get() == '\n') break;
        }
    }
}

int leerPaciente(ifstream &arch) {
    int num1, num2, num3;
    char car;
    arch >> num1;
    if (arch.eof()) return 0;
    arch >> car >> num2 >> car >> num3;
    return num1 * 1000000 + num2 * 10000 + num3;
}

int leerHora(ifstream &arch) {
    int hh, min, ss;
    char car;
    arch >> hh >> car >> min >> car >> ss;
    return hh * 3600 + min * 60 + ss;
}

void imprimirHora(int hora, ofstream &arch) {
    int hh, min, ss;
    hh = hora / 3600;
    hora -= hh * 3600;
    min = hora / 60;
    hora -= min * 60;
    ss = hora;
    arch << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) << ss << setfill(' ');
}

int leerFecha(ifstream &arch) {
    int dd, mm, aa;
    char car;
    arch >> dd;
    if (arch.eof()) return 0;
    arch >> car >> mm >> car >> aa;
    return aa * 10000 + mm * 100 + dd;
}

void imprimirFecha(int fecha, ofstream &arch) {
    int dd, mm, aa;
    aa = fecha / 10000;
    fecha -= aa * 10000;
    mm = fecha / 100;
    fecha -= mm * 100;
    dd = fecha;
    arch << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << aa << setfill(' ');
}

void imprimirTexto(char delim, int &cantCaracteres, ifstream &archEntrada, ofstream &archSalida) {
    char car;
    cantCaracteres = 0;
    archEntrada >> ws;
    while (true) {
        archEntrada.get(car);
        if (car == delim) break;
        if (car == '_' or car == '/' or car == '-') car = ' ';
        archSalida.put(toupper(car));
        cantCaracteres++;
    }
}

void imprimirLinea(char car, ofstream &arch) {
    for (int i = 0; i < MAX_LINES; i++) arch.put(car);
    arch.put('\n');
}

void ignorarHasta(char delim, ifstream &arch) {
    arch >> ws;
    while (arch.get() != delim);
}

ifstream abrirArchivosEntrada(const char *archEntrada) {
    ifstream arch(archEntrada, ios::in);
    if (not arch) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << archEntrada << endl;
        exit(1);
    }
    return arch;
}

ofstream abrirArchivosSalida(const char *archSalida) {
    ofstream arch(archSalida, ios::out);
    if (not arch) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << archSalida << endl;
        exit(1);
    }
    return arch;
}
