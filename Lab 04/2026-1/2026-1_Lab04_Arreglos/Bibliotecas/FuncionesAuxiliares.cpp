#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 135
#define NO_ENCONTRADO -1

void llenarPacientes(int *arrCodigoPaciente, int *arrEdadPaciente, char *arrSexoPaciente, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int i = 0;
    while (true) {
        arrCodigoPaciente[i] = leerCodigo(arch);
        if (arrCodigoPaciente[i] == 0) break;
        arch >> ws;
        ignorarHasta(' ', arch);
        arch >> arrSexoPaciente[i] >> arrEdadPaciente[i];
        i++;
    }
}

void llenarEspecialidades(int *arrCodigoEspecialidad, double *arrCostoEspecialidad, const char *nombArch) {
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
        arch >> arrCostoEspecialidad[i];
        i++;
    }
}

void llenarTriaje(int *arrCodigoPaciente, int *arrCodigoEspecialidad, double *arrCostoEspecialidad, int *arrFechaTriaje,
                  int *arrFrecuenciaTriaje, int *arrDiastolicaTriaje, int *arrSistolicaTriaje,
                  double *arrTemperaturaMaximaTriaje, double *arrCostoTotal, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int fecha, codigoPaciente, codigoEspecialidad, frecuencia, sistolica, diastolica, duracion, posPaciente,
            posEspecialidad;
    double temperatura, costo;
    while (true) {
        fecha = leerFecha(arch);
        if (fecha == 0) break;
        codigoPaciente = leerCodigo(arch);
        arch >> frecuencia >> sistolica >> diastolica >> temperatura >> ws;
        ignorarHasta(' ', arch);
        arch >> codigoEspecialidad;
        posPaciente = buscarPaciente(codigoPaciente, arrCodigoPaciente);
        posEspecialidad = buscarEspecialidad(codigoEspecialidad, arrCodigoEspecialidad);
        if (posPaciente != NO_ENCONTRADO and posEspecialidad != NO_ENCONTRADO) {
            duracion = leerDuracion(arch);
            costo = arrCostoEspecialidad[posEspecialidad];
            if (temperatura > arrTemperaturaMaximaTriaje[posPaciente]) {
                arrFechaTriaje[posPaciente] = fecha;
                arrFrecuenciaTriaje[posPaciente] = frecuencia;
                arrSistolicaTriaje[posPaciente] = sistolica;
                arrDiastolicaTriaje[posPaciente] = diastolica;
                arrTemperaturaMaximaTriaje[posPaciente] = temperatura;
            }
            arrCostoTotal[posPaciente] += costo * duracion / 3600.00;
        } else while (arch.get() != '\n');
    }
}

void imprimirReporte(int *arrCodigoPaciente, int *arrEdadPaciente, char *arrSexoPaciente, int *arrFechaTriaje,
                     int *arrFrecuenciaTriaje, int *arrDiastolicaTriaje, int *arrSistolicaTriaje,
                     double *arrTemperaturaMaximaTriaje, double *arrCostoTotal, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    int cant = 0, edadTotal = 0, sistolicaTotal = 0, diastolicaTotal = 0, frecuenciaTotal = 0;
    double temperaturaTotal = 0.00, costoTotal = 0.00;
    imprimirCabecera(arch);
    for (int i = 0; arrCodigoPaciente[i] != 0; i++) {
        if (arrEdadPaciente[i] < 18) arrCostoTotal[i] *= 0.95;
        else if (arrEdadPaciente[i] > 64) arrCostoTotal[i] *= 0.82;
        arch << setfill('0') << setw(2) << i + 1 << setfill(' ') << ")" << setw(12) << arrCodigoPaciente[i] << setw(6)
                << arrSexoPaciente[i] << setw(6) << "" << setfill('0') <<setw(2) << arrEdadPaciente[i] << setfill(' ') <<
                setw(15) << arrTemperaturaMaximaTriaje[i] << setw(17) << arrSistolicaTriaje[i] << setw(17) <<
                arrDiastolicaTriaje[i] << setw(20) << arrFrecuenciaTriaje[i] << setw(8) << "";
        imprimirFecha(arrFechaTriaje[i], arch);
        arch << setw(14) << arrCostoTotal[i] << endl;
        edadTotal += arrEdadPaciente[i];
        sistolicaTotal += arrSistolicaTriaje[i];
        diastolicaTotal += arrDiastolicaTriaje[i];
        frecuenciaTotal += arrFrecuenciaTriaje[i];
        temperaturaTotal += arrTemperaturaMaximaTriaje[i];
        costoTotal += arrCostoTotal[i];
        cant++;
    }
    imprimirLinea('=', arch);
    imprimirPromedios(cant, edadTotal, sistolicaTotal, diastolicaTotal, frecuenciaTotal, temperaturaTotal, costoTotal,
                      arch);
}

void imprimirCabecera(ofstream &arch) {
    arch << right << fixed << setprecision(2);
    arch << setw(75) << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    arch << setw(83) << "REGISTRO DE ATENCIONES CRITICAS DE LOS PACIENTES" << endl;
    imprimirLinea('=', arch);
    arch << "No. " << setw(8) << "CODIGO" << setw(10) << "SEXO" << setw(8) << "EDAD" << setw(20) << "TEMPERATURA MAXIMA"
            << setw(17) << "PRES. SISTOLICA" << setw(18) << "PRES. DIASTOLICA" << setw(21) << "FRECUENCIA CARDIACA" <<
            setw(8) << "FECHA" << setw(21) << "GASTO EN ATENCIONES" << endl;
    imprimirLinea('-', arch);
}

void imprimirPromedios(int cant, int edadTotal, int sistolicaTotal, int diastolicaTotal, int frecuenciaTotal,
                       double temperaturaTotal,
                       double costoTotal, ofstream &arch) {
    arch << "PROMEDIOS" << setw(22) << (double) edadTotal / cant << setw(13) << (double) temperaturaTotal / cant <<
            setw(18) <<
            (double) sistolicaTotal / cant << setw(17) << (double) diastolicaTotal / cant << setw(20) << (double)
            frecuenciaTotal / cant
            << endl;
    arch << "TOTAL DE GASTOS: " << costoTotal << endl;
}

int buscarPaciente(int codigoPaciente, int *arrCodigoPaciente) {
    for (int i = 0; arrCodigoPaciente[i] != 0; i++) {
        if (codigoPaciente == arrCodigoPaciente[i]) return i;
    }
    return NO_ENCONTRADO;
}

int buscarEspecialidad(int codigoEspecialidad, int *arrCodigoEspecialidad) {
    for (int i = 0; arrCodigoEspecialidad[i] != 0; i++) {
        if (codigoEspecialidad == arrCodigoEspecialidad[i]) return i;
    }
    return NO_ENCONTRADO;
}

void imprimirReportePrueba(int *arrCodigoPaciente, int *arrEdadPaciente, char *arrSexoPaciente,
                           int *arrCodigoEspecialidad, double *arrCostoEspecialidad, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    arch << "CODIO PACIENTE" << setw(17) << "SEXO PACIENTE" << setw(19) << "EDAD PACIENTE" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrCodigoPaciente[i] != 0; i++) {
        arch << arrCodigoPaciente[i] << setw(15) << arrSexoPaciente[i] << setw(20) << arrEdadPaciente[i] << endl;
    }
    imprimirLinea('=', arch);
    arch << "CODIGO ESPECIALIDAD" << setw(25) << "COSTO ESPECIALIDAD" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrCodigoEspecialidad[i] != 0; i++) {
        arch << arrCodigoEspecialidad[i] << setw(35) << arrCostoEspecialidad[i] << endl;
    }
}

void imprimirLinea(char car, ofstream &arch) {
    for (int i = 0; i < MAX_LINES; i++) arch.put(car);
    arch.put('\n');
}

int leerCodigo(ifstream &arch) {
    int num1, num2, num3;
    char car;
    arch >> num1;
    if (arch.eof()) return 0;
    arch >> car >> num2 >> car >> num3;
    return num1 * 1000000 + num2 * 10000 + num3;
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
    arch << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << setfill(' ') << "/" << aa;
}

int leerDuracion(ifstream &arch) {
    int hh, min, ss;
    char car;
    arch >> hh >> car >> min >> car >> ss;
    return hh * 3600 + min * 60 + ss;
}

void ignorarHasta(char delim, ifstream &arch) {
    while (arch.get() != delim);
}

ifstream abrirArchivosEntrada(const char *archEntrada) {
    ifstream arch(archEntrada, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << archEntrada << endl;
        exit(1);
    }
    return arch;
}

ofstream abrirArchivosSalida(const char *archSalida) {
    ofstream arch(archSalida, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << archSalida << endl;
        exit(1);
    }
    return arch;
}
