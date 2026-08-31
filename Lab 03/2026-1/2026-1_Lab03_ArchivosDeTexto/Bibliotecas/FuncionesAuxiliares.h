#ifndef INC_2026_1_LAB03_ARCHIVOSDETEXTO_FUNCIONESAUXILIARES_H
#define INC_2026_1_LAB03_ARCHIVOSDETEXTO_FUNCIONESAUXILIARES_H

#include <fstream>

using namespace std;

void elaborarInforme(const char *nombArchClinica, const char *nombArchPacientes,
                     const char *nombArchTriaje, const char *nombArchReporte);

void generarInforme(ifstream &archClinica, ifstream &archPacientes, ifstream &archTriaje, ofstream &arch);

void leerPacientes(int duracion, double costoXHora, int dd, int mm, int aa, int num1, int num2, int num3, int &contador,
                   ifstream &archPacientes,
                   ifstream &archTriaje, ofstream &arch);

void leerTriaje(int dd, int mm, int aa, int num1, int num2, int num3, ifstream &archTriaje, ofstream &arch);

void imprimirSignosVitales(double temperatura, int sistolica, int diastolica, ofstream &arch);

void imprimirDatosPaciente(int num1, int num2, int num3, int &edad, char &sexo, int &contador, ifstream &archPacientes,
                           ofstream &arch);

void imprimirDatosAtencion(int duracion, double costoXHora, int edad, ofstream &arch);

void imprimirCabecera(ofstream &arch);

void imprimirCabeceraAtenciones(int dd, int mm, int aa, ofstream &arch);

void imprimirTexto(int &cantCaracteres, ifstream &archEntrada, ofstream &arch);

int calcularDuracion(int hhI, int minI, int ssI, int hhF, int minF, int ssF);

int convertirHora(int hh, int min, int ss);

void revertirHora(int duracion, int &hh, int &min, int &ss);

void imprimirHora(int duracion, ofstream &arch);

int convertirFecha(int dd, int mm, int aa);

void imprimirFecha(int dd, int mm, int aa, ofstream &arch);

void imprimirLinea(char car, ofstream &arch);

ifstream abrirArchivoEntrada(const char *archEntrada);

ofstream abrirArchivoSalida(const char *archSalida);
#endif //INC_2026_1_LAB03_ARCHIVOSDETEXTO_FUNCIONESAUXILIARES_H
