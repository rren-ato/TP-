#ifndef PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H
#define PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H

void elaborarInforme(const char *nombArchSedes, const char *nombArchPacientes, const char *nombArchEspecialidad,
                     const char *nombArchAtenciones, const char *nombArchReporte);

void generarInforme(ifstream &archSedes, ifstream &archPacientes, ifstream &archEspecialidad, ifstream &archAtenciones,
                    ofstream &arch);

void leerAtenciones(int sede, int &totalSedes, double &totalPago, int &sedeMayor, double &pagoMayor,
                    ifstream &archAtenciones, ifstream &archPacientes, ifstream &archEspecialidad, ofstream &arch);

void imprimirResumenSede(int sede, int cantAtenciones, double totalPagoSede, int totalDuracionSede,
                         int &totalSedes, double &totalPago, int &sedeMayor, double &pagoMayor, ofstream &arch);

void imprimirCabeceraAtenciones(int cantAtenciones, int fecha, ofstream &arch);

void leerPacientes(int doctorAtencion, int pacienteAtencion, int duracion, double &pago, ifstream &archPacientes,
                   ifstream &archEspecialidad, ofstream &arch);

void leerEspecialidades(int doctorAtencion, int duracion, double &pago, ifstream &archEspecialidad, ofstream &arch);

int leerPaciente(ifstream &arch);

int leerHora(ifstream &arch);

void imprimirHora(int hora, ofstream &arch);

int leerFecha(ifstream &arch);

void imprimirFecha(int fecha, ofstream &arch);

void imprimirTexto(char delim, int &cantCaracteres, ifstream &archEntrada, ofstream &archSalida);

void imprimirLinea(char car, ofstream &arch);

void ignorarHasta(char delim, ifstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

ofstream abrirArchivosSalida(const char *archSalida);

#endif //PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H
