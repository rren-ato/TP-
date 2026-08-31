#ifndef PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H
#define PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H

void llenarAtenciones(int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, const char *nombArch);

void generarReportePrueba(int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, const char *nombArch);

void llenarArreglosAuxiliares(int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, int *arrEspecialidad,
                              double *arrTarifa, double *arrPagoRecibido, double *arrTiempoPromedio,
                              const char *nombArch);

void generarReporte(int tipo, int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, int *arrEspecialidad,
                    double *arrTarifa, double *arrPagoRecibido, double *arrTiempoPromedio, const char *nombArch);

void eliminarArreglos(int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, int *arrEspecialidad,
                      double *arrTarifa, double *arrPagoRecibido, double *arrTiempoPromedio);

void eliminar(int indice, int *arrMedico, int *arrAtencionesMedico, int *arrTiempoMedico, int *arrEspecialidad,
              double *arrTarifa, double *arrPagoRecibido, double *arrTiempoPromedio, int &numDatos);

int contar(int *arr);

int buscarDoctor(int doctor, int *arrMedico);

int leerHora(ifstream &arch);

void imprimirHora(int hora, ofstream &arch);

void imprimirLinea(char car, ofstream &arch);

void ignorarHasta(char delim, ifstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

ofstream abrirArchivosSalida(const char *archSalida);

#endif //PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H
