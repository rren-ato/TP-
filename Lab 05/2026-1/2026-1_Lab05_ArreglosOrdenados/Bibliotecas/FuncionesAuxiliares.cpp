#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 140
#define NO_ENCONTRADO -1

void leerPacientes(int *arrCodigoPaciente, char *arrSexoPaciente, int *arrEdadPaciente, double *arrMontoPaciente,
                   const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int i = 0;
    while (true) {
        arrCodigoPaciente[i] = leerCodigo(arch);
        if (arrCodigoPaciente[i] == 0) break;
        arch >> ws;
        ignorarHasta(' ', arch);
        arch >> arrSexoPaciente[i] >> arrEdadPaciente[i] >> arrMontoPaciente[i];
        i++;
    }
}

int leerCodigo(ifstream &arch) {
    int num1, num2, num3;
    char car;
    arch >> num1;
    if (arch.eof()) return 0;
    arch >> car >> num2 >> car >> num3;
    return num1 * 1000000 + num2 * 10000 + num3;
}

void leerEspecialidades(int *arrCodigoEspecialidad, double *arrCostoEspecialidad, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int i = 0;
    while (true) {
        arch >> arrCodigoEspecialidad[i];
        if (arch.eof()) {
            arrCodigoEspecialidad[i] = 0;
            break;
        }
        arch >> ws;
        ignorarHasta(' ', arch);
        arch >> arrCostoEspecialidad[i] >> ws;
        i++;
    }
}

void generarReportePrueba(int *arrCodigoPaciente, char *arrSexoPaciente, int *arrEdadPaciente, double *arrMontoPaciente,
                          int *arrCodigoEspecialidad, double *arrCostoEspecialidad, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    imprimirLinea('=', arch);
    arch << "CODIGO PACIENTE" << setw(20) << "SEXO PACIENTE" << setw(20) << "EDAD PACIENTE" << setw(20) <<
            "MONTO LIMITE" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrCodigoPaciente[i] != 0; i++) {
        arch << setw(12) << arrCodigoPaciente[i] << setw(17) << arrSexoPaciente[i] << setw(18) << "" << setfill('0') <<
                setw(2) << arrEdadPaciente[i] << setfill(' ') << setw(24) << arrMontoPaciente[i] << endl;
    }
    imprimirLinea('=', arch);
    arch << "CODIGO ESPECIALIDAD" << setw(20) << "COSTO ESPECIALIDAD" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrCodigoEspecialidad[i] != 0; i++) {
        arch << setw(10) << arrCodigoEspecialidad[i] << setw(23) << arrCostoEspecialidad[i] << endl;
    }
}

void llenarArreglosAuxiliares(int *arrCodigoPaciente, char *arrSexoPaciente, int *arrEdadPaciente,
                              double *arrMontoPaciente, int *arrCodigoEspecialidad, double *arrCostoEspecialidad,
                              int *arrAtencionPagada, double *arrMontoPagado, int *arrAtencionPendiente,
                              double *arrMontoPendiente, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int dd, codigoPaciente, codigoEspecialidad;
    while (true) {
        arch >> dd;
        if (arch.eof()) break;
        ignorarHasta(' ', arch);
        codigoPaciente = leerCodigo(arch);
        arch >> codigoEspecialidad;
        int posPaciente = buscarPaciente(codigoPaciente, arrCodigoPaciente);
        int posEspecialidad = buscarEspecialida(codigoEspecialidad, arrCodigoEspecialidad);

        if (posPaciente != NO_ENCONTRADO and posEspecialidad != NO_ENCONTRADO) {
            double duracion = leerDuracion(arch);
            double costoAtencion = duracion / 3600.00 * arrCostoEspecialidad[posEspecialidad];
            if ((costoAtencion + arrMontoPagado[posPaciente]) <= arrMontoPaciente[posPaciente]) {
                arrMontoPagado[posPaciente] += costoAtencion;
                arrAtencionPagada[posPaciente]++;
            } else {
                arrMontoPendiente[posPaciente] += costoAtencion;
                arrAtencionPendiente[posPaciente]++;
            }
        } else ignorarHasta('\n', arch);
    }
}

void ordenarPorPacienteYMonto(int *arrCodigoPaciente, char *arrSexoPaciente, int *arrEdadPaciente,
                              double *arrMontoPaciente, int *arrCodigoEspecialidad, double *arrCostoEspecialidad,
                              int *arrAtencionPagada, double *arrMontoPagado, int *arrAtencionPendiente,
                              double *arrMontoPendiente) {
    int n = contar(arrCodigoPaciente);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((arrCodigoPaciente[i] > arrCodigoPaciente[j]) or (
                    arrCodigoPaciente[i] == arrCodigoPaciente[j] and arrMontoPendiente[i] < arrMontoPendiente[j])) {
                intercambiarInt(arrCodigoPaciente[i], arrCodigoPaciente[j]);
                intercambiarChar(arrSexoPaciente[i], arrSexoPaciente[j]);
                intercambiarInt(arrEdadPaciente[i], arrEdadPaciente[j]);
                intercambiarDouble(arrMontoPaciente[i], arrMontoPaciente[j]);
                intercambiarDouble(arrCostoEspecialidad[i], arrCostoEspecialidad[j]);
                intercambiarInt(arrAtencionPagada[i], arrAtencionPagada[j]);
                intercambiarDouble(arrMontoPagado[i], arrMontoPagado[j]);
                intercambiarInt(arrAtencionPendiente[i], arrAtencionPendiente[j]);
                intercambiarDouble(arrMontoPendiente[i], arrMontoPendiente[j]);
            }
        }
    }
}


void intercambiarInt(int &valorI, int &valorJ) {
    int aux = valorI;
    valorI = valorJ;
    valorJ = aux;
}

void intercambiarDouble(double &valorI, double &valorJ) {
    double aux = valorI;
    valorI = valorJ;
    valorJ = aux;
}

void intercambiarChar(char &valorI, char &valorJ) {
    char aux = valorI;
    valorI = valorJ;
    valorJ = aux;
}

int contar(int *arr) {
    int i = 0;
    while (arr[i] != 0) i++;
    return i;
}

void generarInforme(int *arrCodigoPaciente, char *arrSexoPaciente, int *arrEdadPaciente,
                    double *arrMontoPaciente, int *arrCodigoEspecialidad, double *arrCostoEspecialidad,
                    int *arrAtencionPagada, double *arrMontoPagado, int *arrAtencionPendiente,
                    double *arrMontoPendiente, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    int cantMontosPendientes = 0;
    double totalMontosPendientes = 0.00;
    arch << right << fixed << setprecision(2);
    arch << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    arch << "REGISTRO DE PACIENTES (SV2.1)" << endl;
    imprimirLinea('=', arch);
    arch << "CODIGO" << setw(10) << "SEXO" << setw(7) << "EDAD" << setw(13) << "MONTO_MAX" << setw(17) <<
            "MONTO_PAGADO" << setw(28) << "CANT_ATENCIONES_PAGADAS" << setw(27) << "MONTO_PENDIENTE_PAGO" << setw(32) <<
            "CANT_ATENCIONES_POR_PAGAR" << endl;
    for (int i = 0; arrCodigoPaciente[i] != 0; i++) {
        arch << arrCodigoPaciente[i] << setw(5) << arrSexoPaciente[i] << setw(6) << "" << setfill('0') << setw(2) <<
                arrEdadPaciente[i] << setfill(' ') << setw(13) << arrMontoPaciente[i] << setw(15) << arrMontoPagado[i]
                << setw(17) << "" << setfill('0') << setw(2) << arrAtencionPagada[i] << setfill(' ') << setw(31) <<
                arrMontoPendiente[i] << setw(28) << "" << setfill('0') << setw(2) << arrAtencionPendiente[i] <<
                setfill(' ') << endl;
        cantMontosPendientes += arrAtencionPendiente[i];
        totalMontosPendientes += arrMontoPendiente[i];
    }
    imprimirLinea('=', arch);
    arch << "RESUMEN" << endl;
    arch << endl;
    arch << "CANTIDAD DE PACIENTES CON MONTOS PENDIENTES DE PAGO: " << cantMontosPendientes << endl;
    arch << "TOTAL MONTOS PENDIENTES DE PAGO: " << totalMontosPendientes << endl;
    imprimirLinea('=', arch);
}

int buscarPaciente(int codigoPaciente, int *arrCodigoPaciente) {
    for (int i = 0; arrCodigoPaciente[i] != 0; i++) {
        if (codigoPaciente == arrCodigoPaciente[i]) return i;
    }
    return NO_ENCONTRADO;
}

int buscarEspecialida(int codigoEspecialidad, int *arrCodigoEspecialidad) {
    for (int i = 0; arrCodigoEspecialidad[i] != 0; i++) {
        if (codigoEspecialidad == arrCodigoEspecialidad[i]) return i;
    }
    return NO_ENCONTRADO;
}

int leerDuracion(ifstream &arch) {
    int hh, min, ss;
    char car;
    arch >> hh >> car >> min >> car >> ss;
    return hh * 3600 + min * 60 + ss;
}

void imprimirLinea(char car, ofstream &arch) {
    for (int i = 0; i < MAX_LINES; i++) arch.put(car);
    arch.put('\n');
}

void ignorarHasta(char delim, ifstream &arch) {
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
