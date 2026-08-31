#ifndef INC_2026_1_LAB04_ARREGLOS_FUNCIONESAUXILIARES_H
#define INC_2026_1_LAB04_ARREGLOS_FUNCIONESAUXILIARES_H
#include <fstream>
using namespace std;

void llenarPacientes(int *arrCodigoPaciente, int *arrEdadPaciente, char *arrSexoPaciente, const char *nombArch);

void llenarEspecialidades(int *arrCodigoEspecialidad, double *arrCostoEspecialidad, const char *nombArch);

void llenarTriaje(int *arrCodigoPaciente, int *arrCodigoEspecialidad, double *arrCostoEspecialidad, int *arrFechaTriaje,
                  int *arrFrecuenciaTriaje, int *arrDiastolicaTriaje, int *arrSistolicaTriaje,
                  double *arrTemperaturaMaximaTriaje, double *arrCostoTotal, const char *nombArch);

void imprimirReporte(int *arrCodigoPaciente, int *arrEdadPaciente, char *arrSexoPaciente, int *arrFechaTriaje,
                     int *arrFrecuenciaTriaje, int *arrDiastolicaTriaje, int *arrSistolicaTriaje,
                     double *arrTemperaturaMaximaTriaje, double *arrCostoTotal, const char *nombArch);

void imprimirCabecera(ofstream &arch);

void imprimirPromedios(int cant, int edadTotal, int sistolicaTotal, int diastolicaTotal, int frecuenciaTotal,
                       double temperaturaTotal,
                       double costoTotal, ofstream &arch);

int buscarPaciente(int codigoPaciente, int *arrCodigoPaciente);

int buscarEspecialidad(int codigoEspecialidad, int *arrCodigoEspecialidad);

void imprimirReportePrueba(int *arrCodigoPaciente, int *arrEdadPaciente, char *arrSexoPaciente,
                           int *arrCodigoEspecialidad, double *arrCostoEspecialidad, const char *nombArch);

void imprimirLinea(char car, ofstream &arch);

int leerCodigo(ifstream &arch);

int leerFecha(ifstream &arch);

void imprimirFecha(int fecha, ofstream &arch);

int leerDuracion(ifstream &arch);

void ignorarHasta(char delim, ifstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

ofstream abrirArchivosSalida(const char *archSalida);
#endif //INC_2026_1_LAB04_ARREGLOS_FUNCIONESAUXILIARES_H
