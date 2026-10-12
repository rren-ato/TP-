//
// Created by Renato on 12/10/2026.
//

#include "FuncionesAuxiliares.h"

void open_read_file(ifstream &input, const char* fileName) {
    input.open(fileName, ios:: in);
    if (not input.is_open()) {
        cerr << "El archivo " << fileName << " no se pudo leer" << endl;
        exit(1);
    }
}

void open_write_file(ofstream &output, const char* fileName) {
    output.open(fileName, ios:: out);
    if (not output.is_open()) {
        cerr << "El archivo " << fileName << " no se pudo leer" << endl;
        exit(1);
    }
}

void printLine (ofstream &output, int width, char character) {
    for (int i=0; i<width; i++) output.put(character);
    output << endl;
}

int readTime (ifstream &input) {
    int hh,mm,ss; char c;
    input >> hh >> c >> mm >> c >> ss;
    int time = hh*3600 + mm*60 + ss;
    return time;
}

void printTime (ofstream &output, int time) {
    int hour, min, sec;
    hour = time/3600;
    min = (time%3600)/60;
    sec = time%60;
    output << setw(2) << setfill('0') << hour << ":" <<
        setw(2) << setfill('0') << min << ":" <<
            setw(2) << setfill ('0') << sec << setfill(' ');
}

void swapInt(int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

void swapDouble(double &a, double &b) {
    double aux = a;
    a = b;
    b = aux;
}


bool insertarDesordenado (ifstream &inputAtenciones, int *tiempoTotal, int duracionAtencion, int *codigosAtencionMed, int codigoMedico,
                          int *numeroAtenciones, int &cantAntenciones, int capacidad) {
    if (cantAntenciones >= capacidad) return false;

    for (int i=0; i<cantAntenciones; i++) {
        if (codigosAtencionMed[i] == codigoMedico) {
            numeroAtenciones[i]++;
            tiempoTotal[i] += duracionAtencion;
            return true;
        }
    }

    tiempoTotal[cantAntenciones] = duracionAtencion;
    codigosAtencionMed[cantAntenciones] = codigoMedico;
    numeroAtenciones[cantAntenciones] = 1; //* PRIMERA ATENCION
    cantAntenciones++;
    return true;
}

void llenar_Atenciones(const char *fileNameA, int *tiempoTotal, int *codigosAtencionMed,
                        int *numerosAtenciones, int &cantAntenciones, int capacidad) {
    //* insertar desordenado (sin repeticiones)
    //! 1/04/2023    895    01:21:00    691-12-9990    03:13:54    4393
    ifstream inputAtenciones; open_read_file(inputAtenciones,fileNameA);
    int codigoMedico=0, horaEntrada=0, horaSalida=0, duracionAtencion=0;
    int sedeAtencion=0; //* valor dummy
    while (true) {
        if (inputAtenciones.peek() == EOF) break;
        inputAtenciones >> ws;      inputAtenciones.ignore(1000, ' ');
        while (inputAtenciones >> sedeAtencion) {
            horaEntrada = readTime(inputAtenciones);
            inputAtenciones >> ws;  inputAtenciones.ignore(1000, ' ');
            horaSalida = readTime(inputAtenciones);
            inputAtenciones >> codigoMedico;
            if (horaSalida < horaEntrada) {
                duracionAtencion = horaSalida+(24*60*60) - horaEntrada;
            } else {
                duracionAtencion = horaSalida - horaEntrada;
            }
            insertarDesordenado(inputAtenciones, tiempoTotal, duracionAtencion, codigosAtencionMed, codigoMedico,
                          numerosAtenciones, cantAntenciones, capacidad);
            if (inputAtenciones.peek() == '\n') break; //* Al saltar de linea debes comerte a fecha
        }
    }
    inputAtenciones.close();
}

int busquedaNormal (int dato, int *arrDato, int cantAtenciones) {
    for (int i=0; i<cantAtenciones; i++) {
        if (arrDato[i] == dato) return i;
    }
    return NOT_FOUND;
}

int busquedaBinaria(double dato, double *arrdato, int cantAtenciones) {
    int izquierda = 0; //* En este caso la izquierda no debe moverse (en teoria el dato ahi es 0) - por ordenamiento
    int derecha = cantAtenciones-1;

    while (izquierda <= derecha) {
        int medio = izquierda +(derecha-izquierda)/2;

        if (arrdato[medio] < dato) {
            return medio;
        } else {
            derecha = medio -1;
        }
    }
    return NOT_FOUND;
}

void llenar_Medicos(const char *fileNameM, double *tarifasPorHora, int *codigosAtencionMed, int *codigosEspecialidad,
                    int cantAtenciones) {
    //! 576    Pediatria    9846    AMEZQUITA/EPIQUEN/EVERT_ROBERTO    418.17
    int codigoEspecialidad=0, codigoDoctor=0; double tarifaPorHora=0.0;
    ifstream inputMedicos; open_read_file(inputMedicos, fileNameM);
    while (inputMedicos >> codigoEspecialidad) {
        //! 576    Pediatria
        inputMedicos >> ws;     inputMedicos.ignore(1000, ' ');
        while (inputMedicos >> codigoDoctor) {
            //! 9846    AMEZQUITA/EPIQUEN/EVERT_ROBERTO
            inputMedicos >> ws; inputMedicos.ignore(1000, ' ');
            //*los datos estan desordenado por lo que se debe usar la busqueda normal
            int posMedico = busquedaNormal(codigoDoctor, codigosAtencionMed, cantAtenciones);
            if (posMedico != NOT_FOUND) {
                //! 418.17
                inputMedicos >> tarifasPorHora[posMedico];
                codigosEspecialidad[posMedico] = codigoEspecialidad;
            }
            else {
                //* ES COMO UN VALOR DUMMY
                inputMedicos >> tarifaPorHora;
            }
            if (inputMedicos.peek() == '\n') break; //* Para leer otra especialidad
        }
    }
    inputMedicos.close();
}

bool eliminarDato(int *codigosAtencionMed, int *codigosEspecialidad, double *tarifasPorHora,
                    int *numeroAtenciones, int *tiempoTotal, int *tiempoPromedio, double *pagoRecibido,
                    int &cantSmth, int pos) {
    if (pos <0 or pos >= cantSmth) return false;
    for (int i= pos; i<cantSmth-1; i++) {
        codigosAtencionMed[i] = codigosAtencionMed[i+1]; //* SHIFT
        codigosEspecialidad[i] = codigosEspecialidad[i+1]; //* SHIFT
        tarifasPorHora[i] = tarifasPorHora[i+1]; //* SHIFT
        numeroAtenciones[i] = numeroAtenciones[i+1]; //* SHIFT
        tiempoTotal[i] = tiempoTotal[i+1]; //* SHIFT
        tiempoPromedio[i] = tiempoPromedio[i+1]; //* SHIFT
        pagoRecibido[i] = pagoRecibido[i+1]; //* SHIFT
        }
    cantSmth--;
    return true;
}

void calcularPagoYtiempoPromedio(int *tiempoTotal, double *tarifaPorHora, double *pagoRecibido, int *numeroAtenciones,
                                 int *tiemposPromedio, int cantAtenciones) {
    for (int i=0; i<cantAtenciones; i++) {
        if (tiempoTotal[i] > 0 and numeroAtenciones[i] > 0) {
            tiemposPromedio[i] = tiempoTotal[i] / numeroAtenciones[i];
        } else {
            tiemposPromedio[i] = 0;
        }
        pagoRecibido[i] = tiempoTotal[i] * (tarifaPorHora[i] /3600.0);
    }
}

void insertionSort(int *codigosAtencionMed, int *codigosEspecialidad, double *tarifasPorHora,
                    int *numeroAtenciones, int *tiempoTotal, int *tiempoPromedio, double *pagoRecibido,
                    int cantAntenciones) {
    for (int i=0; i<cantAntenciones-1; i++) {
        for (int j=i+1; j<cantAntenciones; j++) {
            if (pagoRecibido[j] > pagoRecibido[i]) {
                swapInt(codigosAtencionMed[i], codigosAtencionMed[j]);
                swapInt(codigosEspecialidad[i], codigosEspecialidad[j]);
                swapDouble(tarifasPorHora[i], tarifasPorHora[j]);
                swapInt(numeroAtenciones[i], numeroAtenciones[j]);
                swapInt(tiempoTotal[i], tiempoTotal[j]);
                swapInt(tiempoPromedio[i], tiempoPromedio[j]);
                swapDouble(pagoRecibido[i], pagoRecibido[j]);
            }
        }
    }
}

void headerReporteFinal(ofstream &output) {
    printLine(output, ANCHO_REPORTE, '=');
    output << setw(90) << " " << "CLINICA DE URGENCIAS TP-SALUD" << endl;
    output << setw(94) << " " << "ATENCIONES POR MEDICO" << endl;
    printLine(output, ANCHO_REPORTE, '=');
    output << left << setw(ANCHO_REPORTE/N_COLUMNS) << "MEDICO" <<
        setw(ANCHO_REPORTE/N_COLUMNS) << "ESPECIALIDAD" <<
            setw(ANCHO_REPORTE/N_COLUMNS) << "TARIFA" <<
                setw(ANCHO_REPORTE/N_COLUMNS) << "CANT.ATENCIONES" <<
                    setw(ANCHO_REPORTE/N_COLUMNS) << "TIEMPO.TOTAL.ATENCIONES" <<
                        setw(ANCHO_REPORTE/N_COLUMNS) << "TIEMPO.PROM.ATENCIONES" <<
                            setw(ANCHO_REPORTE/N_COLUMNS) << "PAGO_RECIBIDO" << endl;
    printLine(output, ANCHO_REPORTE, '=');
}

void generarReporte(const char *fileNameReporte,int *codigosAtencionMed, int *codigosEspecialidad, double *tarifasPorHora,
                    int *numeroAtenciones, int *tiempoTotal, int *tiempoPromedio, double *pagoRecibido,
                    int cantAntenciones) {
    ofstream outputReporte; open_write_file(outputReporte, fileNameReporte);
    double pagoTotalFinal = 0.0;
    headerReporteFinal(outputReporte);
    for (int i=0; i<cantAntenciones; i++) {
        outputReporte << setw(ANCHO_REPORTE/N_COLUMNS) << codigosAtencionMed[i] <<
            setw(ANCHO_REPORTE/N_COLUMNS) << codigosEspecialidad[i] <<
                setw(ANCHO_REPORTE/N_COLUMNS) << tarifasPorHora[i] <<
                    setw(ANCHO_REPORTE/N_COLUMNS) << numeroAtenciones[i] <<
                        setw(ANCHO_REPORTE/N_COLUMNS) << tiempoTotal[i] <<
                            setw(ANCHO_REPORTE/N_COLUMNS) << tiempoPromedio[i] <<
                                setw(ANCHO_REPORTE/N_COLUMNS) << pagoRecibido[i] << endl;
        pagoTotalFinal += pagoRecibido[i];
    }
    printLine(outputReporte, ANCHO_REPORTE, '-');
    outputReporte << "RESUMEN:" << endl;
    outputReporte << "TOTAL DE MEDICOS: " << cantAntenciones << endl;
    outputReporte << "PAGO TOTAL RECIBIDO:  S/. " << pagoTotalFinal << endl;
    printLine(outputReporte, ANCHO_REPORTE, '=');






}