#include <iostream>
#include <iomanip>
#include <fstream>

#define MAX_LINES 130

using namespace std;

#include "FuncionesAuxiliares.h"

void elaborarInforme(const char *nombArch, const char *nombArchReporte) {
    int di = 5, mi = 4, ai = 2023, df = 27, mf = 4, af = 2023;
    int fechaInicio, fechaFin;
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo " << nombArch << endl;
        exit(1);
    }
    ofstream archReporte(nombArchReporte, ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir el archivo " << nombArchReporte << endl;
        exit(1);
    }
    imprimirCabecera(di, mi, ai, df, mf, af, archReporte);
    fechaInicio = convertirFecha(di, mi, ai);
    fechaFin = convertirFecha(df, mf, af);
    generarInforme(fechaInicio, fechaFin, arch, archReporte);
}

void generarInforme(int fechaInicio, int fechaFin, ifstream &arch, ofstream &archReporte) {
    int dd, mm, aa, fechaAtencion, num1, num2, num3, hi, mini, si, edad, sistolica, diastolica, hf, minf, sf,
            cantCaracteres, duracion, cantAtenciones, cantPacientesMenoresFiebre, tiempoAtenciones, cantTotalAtenciones
                    = 0, tiempoTotalAtenciones = 0;
    double temperatura, precioXhora, costo, costoAtenciones, costoTotalAtenciones = 0.00;
    char car;
    while (true) {
        arch >> dd;
        if (arch.eof()) break;
        arch >> car >> mm >> car >> aa;
        fechaAtencion = convertirFecha(dd, mm, aa);
        if (fechaAtencion >= fechaInicio and fechaAtencion <= fechaFin) {
            imprimirCabeceraAtenciones(dd, mm, aa, archReporte);
            cantAtenciones = cantPacientesMenoresFiebre = tiempoAtenciones = 0;
            costoAtenciones = 0.00;
            while (true) {
                arch >> num1 >> car >> num2 >> car >> num3;
                archReporte << setfill('0') << setw(3) << num1 << setw(2) << num2 << setw(4) << num3 << setfill(' ') <<
                        setw(2) << "";
                imprimirNombre(cantCaracteres, arch, archReporte);
                arch >> hi >> car >> mini >> car >> si >> edad >> temperatura >> sistolica >> diastolica >> hf >> car >>
                        minf >> car >> sf >> precioXhora;
                imprimirDatosAtenciones(cantCaracteres, edad, hi, mini, si, hf, minf, sf, precioXhora, temperatura,
                                        sistolica, diastolica, duracion, costo, archReporte);
                if (edad < 18 and temperatura > 37.5) cantPacientesMenoresFiebre++;
                cantAtenciones++;
                tiempoAtenciones += duracion;
                costoAtenciones += costo;
                if (arch.get() == '\n') break;
            }
            imprimirResumenFecha(cantAtenciones, cantPacientesMenoresFiebre, tiempoAtenciones, costoAtenciones,
                                 archReporte);
            cantTotalAtenciones += cantAtenciones;
            tiempoTotalAtenciones += tiempoAtenciones;
            costoTotalAtenciones += costoAtenciones;
        } else while (arch.get() != '\n');
    }
    imprimirResumenFinal(cantTotalAtenciones, tiempoTotalAtenciones, costoTotalAtenciones, archReporte);
}

void imprimirCabecera(int di, int mi, int ai, int df, int mf, int af, ofstream &archReporte) {
    archReporte << right << setw(80) << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    archReporte << setw(79) << "REGISTRO DE LAS ATENCIONES" << endl;
    archReporte << setw(70) << "ATENCIONES REALIZADAS ENTRE EL ";
    imprimirFecha(di, mi, ai, archReporte);
    archReporte << " Y EL ";
    imprimirFecha(df, mf, af, archReporte);
    archReporte << endl;
    imprimirLinea('=', archReporte);
}

void imprimirCabeceraAtenciones(int dd, int mm, int aa, ofstream &archReporte) {
    archReporte << "FECHA: ";
    imprimirFecha(dd, mm, aa, archReporte);
    archReporte << endl;
    archReporte << "REGISTRO DE ATENCIONES:" << endl;
    imprimirLinea('-', archReporte);
    archReporte << "ID" << setw(15) << "NOMBRE" << setw(14) << "EDAD" << setw(13) << "INGRESO" << setw(11) << "ALTA" <<
            setw(17) << "DURACION" << setw(12) << "COSTO" << setw(19) << "TEMPERATURA" << setw(22) << "PRESION ARTERIAL"
            << endl;
}

void imprimirDatosAtenciones(int cantCaracteres, int edad, int hi, int mini, int si, int hf, int minf, int sf,
                             double precioXhora, double temperatura, int sistolica, int diastolica, int &duracion,
                             double &costo, ofstream &archReporte) {
    archReporte << setw(19 - cantCaracteres) << edad << setw(6) << "";
    imprimirHora(hi, mini, si, archReporte);
    archReporte << setw(6) << "";
    imprimirHora(hf, minf, sf, archReporte);
    duracion = calcularDuracion(hi, mini, si, hf, minf, sf);
    if (duracion < 0) duracion += 24 * 3600;
    archReporte << setw(6) << "";
    imprimirDuracion(duracion, archReporte);
    costo = calcularCostoXhora(duracion, precioXhora);
    if (edad < 18) costo -= costo * 0.05;
    if (edad > 64) costo -= costo * 0.18;
    archReporte << setw(14) << fixed << setprecision(2) << costo << setw(14) << temperatura;
    calcularPresionArterial(sistolica, diastolica, archReporte);
}

void imprimirResumenFecha(int cantAtenciones, int cantPacientesMenoresFiebre, int tiempoAtenciones,
                          double costoAtenciones, ofstream &archReporte) {
    imprimirLinea('-', archReporte);
    archReporte << left << setw(5) << "" << "RESUMEN DE LA FECHA" << endl;
    archReporte << setw(5) << "" << "CANTIDAD DE ATENCIONES: " << cantAtenciones << endl;
    archReporte << setw(5) << "" << "CANTIDAD DE PACIENTES MENORES DE EDAD QUE PRESENTARON FIEBRE: " <<
            cantPacientesMenoresFiebre << endl;
    archReporte << setw(5) << "" << "TIEMPO TOTAL DESTINADO A LAS ATENCIONES: ";
    imprimirDuracion(tiempoAtenciones, archReporte);
    archReporte << endl;
    archReporte << setw(5) << "" << "COSTO TOTAL POR LAS ATENCIONES:" << right << setw(17) << fixed << setprecision(2)
            << costoAtenciones << endl;
    imprimirLinea('=', archReporte);
}

void imprimirResumenFinal(int cantTotalAtenciones, int tiempoTotalAtenciones, double costoTotalAtenciones,
                          ofstream &archReporte) {
    archReporte << "RESUMEN FINAL:" << endl;
    archReporte << left << setw(5) << "" << "CANTIDAD DE ATENCIONES: " << cantTotalAtenciones << endl;
    archReporte << setw(5) << "" << "TIEMPO TOTAL DESTINADO A LAS ATENCIONES: ";
    imprimirDuracion(tiempoTotalAtenciones, archReporte);
    archReporte << endl;
    archReporte << setw(5) << "" << "COSTO TOTAL POR LAS ATENCIONES:" << right << setw(19) << fixed << setprecision(2)
            << costoTotalAtenciones << endl;
}

void imprimirNombre(int &cantCaracteres, ifstream &arch, ofstream &archReporte) {
    cantCaracteres = 0;
    char car;
    arch >> ws;
    while (true) {
        arch.get(car);
        if (car == ' ') break;
        if (car == '_') car = ' ';
        car = toupper(car);
        archReporte.put(car);
        cantCaracteres++;
    }
}

int calcularDuracion(int hi, int mini, int si, int hf, int minf, int sf) {
    int horaInicio, horaFin;
    horaInicio = convertirHora(hi, mini, si);
    horaFin = convertirHora(hf, minf, sf);
    return horaFin - horaInicio;
}

double calcularCostoXhora(double duracion, double precioXhora) {
    return (duracion / 3600.00) * precioXhora;
}

void calcularPresionArterial(int sistolica, int diastolica, ofstream &archReporte) {
    archReporte << setw(12) << sistolica << "/" << left << setw(3) << diastolica << right;
    if (sistolica < 120 and diastolica < 80) {
        archReporte << " (Normal)" << endl;
    } else {
        if ((sistolica < 120 and diastolica > 80) or (sistolica >= 120 and sistolica <= 129 and diastolica < 80)) {
            archReporte << " (Elevada)" << endl;
        } else {
            if ((sistolica >= 130 and sistolica <= 139) or (diastolica >= 80 and diastolica <= 89)) {
                archReporte << " (Hipertension Nivel 1)" << endl;
            } else {
                if (sistolica >= 140 or diastolica >= 90) {
                    archReporte << " (Hipertension Nivel 2)" << endl;
                }
            }
        }
    }
}

int convertirFecha(int dd, int mm, int aa) {
    return aa * 10000 + mm * 100 + dd;
}

int convertirHora(int hh, int min, int ss) {
    return hh * 3600 + min * 60 + ss;
}

void revertirHora(int duracion, int &hh, int &min, int &ss) {
    hh = duracion / 3600;
    duracion -= hh * 3600;
    min = duracion / 60;
    duracion -= min * 60;
    ss = duracion;
}

void imprimirFecha(int dd, int mm, int aa, ofstream &archReporte) {
    archReporte << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << aa << setfill(' ');
}

void imprimirHora(int hh, int min, int ss, ofstream &archReporte) {
    archReporte << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) << ss << setfill(' ');
}

void imprimirDuracion(int duracion, ofstream &archReporte) {
    int hh, min, ss;
    revertirHora(duracion, hh, min, ss);
    imprimirHora(hh, min, ss, archReporte);
}

void imprimirLinea(char car, ofstream &archReporte) {
    for (int i = 0; i < MAX_LINES; i++) archReporte.put(car);
    archReporte << endl;
}
