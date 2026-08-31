#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 135
#define NO_ENCONTRADO -1

void llenarAtenciones(int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int dd, horaInicio, horaFin, doctor, indice, i = 0;
    while (true) {
        arch >> dd;
        if (arch.eof()) {
            arrMedico[i] = 0;
            break;
        }
        ignorarHasta(' ', arch);
        while (true) {
            ignorarHasta(' ', arch);
            horaInicio = leerHora(arch);
            ignorarHasta(' ', arch);
            horaFin = leerHora(arch);
            arch >> doctor;
            int posDoctor = buscarDoctor(doctor, arrMedico);
            if (posDoctor == NO_ENCONTRADO) {
                indice = i;
                arrMedico[indice] = doctor;
                i++;
            } else indice = posDoctor;
            arrAtencionesMedico[indice]++;
            arrTiempoMedico[indice] += (horaFin - horaInicio);
            if (arch.get() == '\n') break;
        }
    }
}

void generarReportePrueba(int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    imprimirLinea('=', arch);
    arch << "REPORTE DE PRUEBA - MEDICO_ATENCIONES" << endl;
    arch << "CODIGO" << setw(14) << "ATENCIONES" << setw(12) << "TIEMPO" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrMedico[i] != 0; i++) {
        arch << setw(5) << arrMedico[i] << setw(10) << arrAtencionesMedico[i] << setw(10) << "";
        imprimirHora(arrTiempoMedico[i], arch);
        arch << endl;
    }
}

void llenarArreglosAuxiliares(int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, int *arrEspecialidad,
                              double *arrTarifa, double *arrPagoRecibido, double *arrTiempoPromedio,
                              const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int especialidad, doctor;
    double tarifa;
    while (true) {
        arch >> especialidad;
        if (arch.eof()) break;
        ignorarHasta(' ', arch);
        while (true) {
            arch >> doctor;
            ignorarHasta(' ', arch);
            arch >> tarifa;
            int posMedico = buscarDoctor(doctor, arrMedico);
            if (posMedico != NO_ENCONTRADO) {
                arrEspecialidad[posMedico] = especialidad;
                arrTarifa[posMedico] = tarifa;
                arrPagoRecibido[posMedico] = tarifa * (arrTiempoMedico[posMedico] / 3600.00);
                arrTiempoPromedio[posMedico] = arrTiempoMedico[posMedico] / arrAtencionesMedico[posMedico];
            }
            if (arch.get() == '\n') break;
        }
    }
}

void generarReporte(int tipo, int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, int *arrEspecialidad,
                    double *arrTarifa, double *arrPagoRecibido, double *arrTiempoPromedio, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    imprimirLinea('=', arch);
    arch << setw(78) << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    if (tipo == 1) arch << setw(74) << "ATENCIONES POR MEDICO" << endl;
    else if (tipo == 2) arch << setw(65) << "ATENCIONES MEJOR PAGADOS" << endl;
    imprimirLinea('=', arch);
    arch << "MEDICO" << setw(18) << "ESPECIALIDAD" << setw(12) << "TARIFA" << setw(20) << "CANT.ATENCIONES" << setw(30)
            << "TIEMPO.TOTAL.ATENCIONES" << setw(29) << "TIEMPO.PROM.ATENCION" << setw(20) << "PAGO RECIBIDO" << endl;
    imprimirLinea('-', arch);
    double pagoTotal = 0.00;
    for (int i = 0; arrMedico[i] != 0; i++) {
        arch << setw(5) << arrMedico[i] << setw(14) << arrEspecialidad[i] << setw(17) << arrTarifa[i] << setw(12) <<
                arrAtencionesMedico[i] << setw(22) << "";
        imprimirHora(arrTiempoMedico[i], arch);
        arch << setw(24) << "";
        imprimirHora(arrTiempoPromedio[i], arch);
        arch << setw(22) << arrPagoRecibido[i] << endl;
        pagoTotal += arrPagoRecibido[i];
    }
    int n = contar(arrMedico);
    imprimirLinea('-', arch);
    arch << "RESUMEN" << endl;
    arch << "TOTAL DE MEDICOS:" << setw(10) << n << endl;
    arch << "PAGO TOTAL RECIBIDO:" << setw(5) << "$/." << setw(11) << pagoTotal << endl;
    imprimirLinea('=', arch);
}

void eliminarArreglos(int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, int *arrEspecialidad,
                      double *arrTarifa, double *arrPagoRecibido, double *arrTiempoPromedio) {
    int n = contar(arrMedico);
    for (int i = 0; arrMedico[i] != 0; i++) {
        if (arrPagoRecibido[i] < 5000.00) {
            eliminar(i, arrMedico, arrAtencionesMedico, arrTiempoMedico, arrEspecialidad, arrTarifa, arrPagoRecibido,
                     arrTiempoPromedio, n);
            i--;
        }
    }
}

void eliminar(int indice, int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, int *arrEspecialidad,
              double *arrTarifa, double *arrPagoRecibido, double *arrTiempoPromedio, int &numDatos) {
    for (int i = indice; i < numDatos; i++) {
        arrMedico[i] = arrMedico[i + 1];
        arrAtencionesMedico[i] = arrAtencionesMedico[i + 1];
        arrTiempoMedico[i] = arrTiempoMedico[i + 1];
        arrEspecialidad[i] = arrEspecialidad[i + 1];
        arrTarifa[i] = arrTarifa[i + 1];
        arrPagoRecibido[i] = arrPagoRecibido[i + 1];
        arrTiempoPromedio[i] = arrTiempoPromedio[i + 1];
    }
    numDatos--;
}

int contar(int *arr) {
    int i = 0;
    while (arr[i] != 0) i++;
    return i;
}

int buscarDoctor(int doctor, int *arrMedico) {
    for (int i = 0; arrMedico[i]; i++) {
        if (doctor == arrMedico[i]) return i;
    }
    return NO_ENCONTRADO;
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
