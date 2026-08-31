//
// Created by aml on 11/05/2026.
//

#ifndef INC_2026_1_LAB05_ARREGLOSORDENADOS_FUNCIONESAUXILIARES_H
#define INC_2026_1_LAB05_ARREGLOSORDENADOS_FUNCIONESAUXILIARES_H

void leerPacientes(int *arrCodigoPaciente, char *arrSexoPaciente, int *arrEdadPaciente, double *arrMontoPaciente,
                   const char *nombArch);

int leerCodigo(ifstream &arch);

void leerEspecialidades(int *arrCodigoEspecialidad, double *arrCostoEspecialidad, const char *nombArch);

void generarReportePrueba(int *arrCodigoPaciente, char *arrSexoPaciente, int *arrEdadPaciente, double *arrMontoPaciente,
                          int *arrCodigoEspecialidad, double *arrCostoEspecialidad, const char *nombArch);

void llenarArreglosAuxiliares(int *arrCodigoPaciente, char *arrSexoPaciente, int *arrEdadPaciente,
                              double *arrMontoPaciente, int *arrCodigoEspecialidad, double *arrCostoEspecialidad,
                              int *arrAtencionPagada, double *arrMontoPagado, int *arrAtencionPendiente,
                              double *arrMontoPendiente, const char *nombArch);

void ordenarPorPacienteYMonto(int *arrCodigoPaciente, char *arrSexoPaciente, int *arrEdadPaciente,
                              double *arrMontoPaciente, int *arrCodigoEspecialidad, double *arrCostoEspecialidad,
                              int *arrAtencionPagada, double *arrMontoPagado, int *arrAtencionPendiente,
                              double *arrMontoPendiente);

void intercambiarInt(int &valorI, int &valorJ);

void intercambiarDouble(double &valorI, double &valorJ);

void intercambiarChar(char &valorI, char &valorJ);

int contar(int *arr);

void generarInforme(int *arrCodigoPaciente, char *arrSexoPaciente, int *arrEdadPaciente,
                    double *arrMontoPaciente, int *arrCodigoEspecialidad, double *arrCostoEspecialidad,
                    int *arrAtencionPagada, double *arrMontoPagado, int *arrAtencionPendiente,
                    double *arrMontoPendiente, const char *nombArch);

int buscarPaciente(int codigoPaciente, int *arrCodigoPaciente);

int buscarEspecialida(int codigoEspecialidad, int *arrCodigoEspecialidad);

int leerDuracion(ifstream &arch);

void imprimirLinea(char car, ofstream &arch);

void ignorarHasta(char car, ifstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

ofstream abrirArchivosSalida(const char *archSalida);

#endif //INC_2026_1_LAB05_ARREGLOSORDENADOS_FUNCIONESAUXILIARES_H
