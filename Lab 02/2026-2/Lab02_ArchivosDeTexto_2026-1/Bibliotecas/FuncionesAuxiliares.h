//
// Created by aml on 20/04/2026.
//

#ifndef LAB02_ARCHIVOSDETEXTO_2026_1_FUNCIONESAUXILIARES_H
#define LAB02_ARCHIVOSDETEXTO_2026_1_FUNCIONESAUXILIARES_H

using namespace std;

void elaborarInforme(const char *nombArch, const char *nombArchReporte);

void generarInforme(int fechaInicio, int fechaFin, ifstream &arch, ofstream &archReporte);

void imprimirCabecera(int di, int mi, int ai, int df, int mf, int af, ofstream &archReporte);

void imprimirCabeceraAtenciones(int dd, int mm, int aa, ofstream &archReporte);

void imprimirDatosAtenciones(int cantCaracteres, int edad, int hi, int mini, int si, int hf, int minf, int sf,
                             double precioXhora, double temperatura, int sistolica, int diastolica, int &duracion,
                             double &costo, ofstream &archReporte);

void imprimirResumenFecha(int cantAtenciones, int cantPacientesMenoresFiebre, int tiempoAtenciones,
                          double costoAtenciones, ofstream &archReporte);

void imprimirResumenFinal(int cantTotalAtenciones, int tiempoTotalAtenciones, double costoTotalAtenciones,
                          ofstream &archReporte);

void imprimirNombre(int &cantCaracteres, ifstream &arch, ofstream &archReporte);

int calcularDuracion(int hi, int mini, int si, int hf, int minf, int sf);

double calcularCostoXhora(double duracion, double precioXhora);

void calcularPresionArterial(int sistolica, int diastolica, ofstream &archReporte);

int convertirFecha(int dd, int mm, int aa);

int convertirHora(int hh, int min, int ss);

void revertirHora(int duracion, int &hh, int &min, int &ss);

void imprimirFecha(int dd, int mm, int aa, ofstream &archReporte);

void imprimirHora(int hh, int min, int ss, ofstream &archReporte);

void imprimirDuracion(int duracion, ofstream &archReporte);

void imprimirLinea(char car, ofstream &archReporte);

#endif //LAB02_ARCHIVOSDETEXTO_2026_1_FUNCIONESAUXILIARES_H
