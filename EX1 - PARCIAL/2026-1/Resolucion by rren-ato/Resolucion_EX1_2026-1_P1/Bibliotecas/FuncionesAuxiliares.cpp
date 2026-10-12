//
// Created by Renato on 11/10/2026.
//

#include "FuncionesAuxiliares.h"


void open_read_file(ifstream &input, const char *fileName) {
    input.open(fileName, ios:: in);
    if (not input.is_open()) {
        cerr << "El archivo " << fileName << " no se pudo leer" << endl;
        exit(1);
    }
}

void open_write_file(ofstream &output, const char *fileName) {
    output.open(fileName, ios:: out);
    if (not output.is_open()) {
        cerr << "El archivo " << fileName << " no se pudo abrir" << endl;
        exit(1);
    }
}

void printLine(ofstream &output, int width, char character) {
    for (int i=0; i< width; i++) output.put(character);
    output << endl;
}

int readDate(ifstream &input, int dd) {
    char c; int mm=0, yyyy=0;
    input >> c >> mm >> c >> yyyy;
    int date = yyyy*10000 + mm*100+ dd;
    return date;
}

void printDate(ofstream &output, int date) {
    int day, month, year;
    year = date /10000;
    month = (date/100)%100;
    day = date %100;
    output << setw(2) << setfill('0') << day << '/' <<
        setw(2) << setfill('0') << month << '/' <<
            setw(4) << year << setfill(' ');
}

int readTime(ifstream &input) {
    int hh, mm, ss; char c;
    input >> hh >> c >> mm >> c >> ss;
    int time = hh*3600 + mm*60+ ss;
    return time;
}

void printDuracion(ofstream &output, int duracion) {
    int hour, min, sec;
    hour = duracion / 3600;
    min = (duracion%3600) / 60;
    sec = duracion%60;

    output << setw(2) << setfill('0') << hour << ':' <<
        setw(2) << setfill('0') << min << ':' <<
            setw(2) << setfill('0') << sec << setfill(' ');
}

int readID(ifstream &input) {
    int p1, p2, p3; char c;
    input >> p1 >> c >> p2 >> c >> p3;
    int DNI = p1 * 1000000 + p2 * 10000 + p3;
    return DNI;
}

void readAndPrintWhitoutArr(ifstream &input, ofstream &output) {
    char c;
    input >> ws;
    input.get(c);
    while (true) {
        if (c == ' ' or c == '\n' or c == EOF) break;
        if (c == '/' or c == '_' or c == '-') c= ' ';
        if ('a' <= c and c <= 'z') c = c - 'a' + 'A';
        output.put(c);
        input.get(c);
    }
}

void printGeneralHeader(ofstream &output) {
    printLine(output, ANCHO_REPORTE, '=');
    output << setw(ANCHO_REPORTE/3) << " ";
    output << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    output << setw((ANCHO_REPORTE/3) + 4) << " ";
    output << "ATENCIONES POR SEDE" << endl;
}

void leerSedes(ifstream &inputSede, ofstream &outputReporte, int sedeAtencion) {
     printLine(outputReporte, ANCHO_REPORTE, '=');
     outputReporte << "SEDE: " << sedeAtencion << " - ";
     readAndPrintWhitoutArr(inputSede, outputReporte);
     outputReporte << endl;
     printLine(outputReporte, ANCHO_REPORTE, '-');
}



void getDattaFromAtenciones (ifstream &inputAtenciones, ofstream &outputReporte, int &fechaAtencion, int sedeAtencion,
                             ifstream &inputPacientes, ifstream &inputEspecialidades) {
    int codigoSede=0, horaIngreso=0, horaSalida=0;
    inputAtenciones.clear();
    inputAtenciones.seekg (0, ios::beg);
    int dd; int cantAtenciones=0;
    int IdAtencion=0, duracionAtencion=0, codigoDocAtencion=0;
    while (inputAtenciones >> dd) {
        fechaAtencion = readDate(inputAtenciones, dd);
        while (true) {
            if (inputAtenciones.peek() == '\n' or inputAtenciones.peek() == EOF) break;
            inputAtenciones >> codigoSede;
            if (inputAtenciones.eof())break;
            if (codigoSede == sedeAtencion) {
                horaIngreso = readTime(inputAtenciones);
                IdAtencion = readID(inputAtenciones);
                horaSalida = readTime(inputAtenciones);
                if (horaIngreso > horaSalida) {
                    duracionAtencion = horaSalida+(24*60*60) - horaIngreso;
                }
                else{
                    duracionAtencion = horaSalida - horaIngreso;
                }
                inputAtenciones >> codigoDocAtencion;

                cantAtenciones++;

                getDattaFromPacientes (inputPacientes, outputReporte, IdAtencion, fechaAtencion,
                                duracionAtencion, cantAtenciones);
                getDattaFromEspecialidades(inputEspecialidades, outputReporte, codigoDocAtencion,
                                        duracionAtencion);

            }
            else{
                horaIngreso = readTime(inputAtenciones);
                IdAtencion = readID(inputAtenciones);
                horaSalida = readTime(inputAtenciones);
                inputAtenciones >> codigoDocAtencion;
            }
        }
    }
}

void getDattaFromPacientes (ifstream &inputPacientes, ofstream &outputReporte, int IdAtencion, int fechaAtencion,
                            int duracionAtencion, int cantAtenciones) {
    inputPacientes.clear();
    inputPacientes.seekg (0, ios::beg);
    int IdPaciente;
    while (true) {
        int p1, p2, p3; char c;
        if (inputPacientes.peek() == '\n') break;

        inputPacientes >> p1;
        if (inputPacientes.eof())break;
        inputPacientes >> c >> p2 >> c >> p3;
        IdPaciente = p1 * 1000000 + p2 * 10000 + p3;
        if (IdPaciente == IdAtencion) {
            //* Imprimir header por atenciones por fecha
            outputReporte << setw(2) << setfill('0') << cantAtenciones << ')';
            printDate(outputReporte, fechaAtencion);
            outputReporte << IdAtencion << " - ";
            readAndPrintWhitoutArr(inputPacientes, outputReporte);
            printDuracion(outputReporte, duracionAtencion);
            return;
        }
        else{
            inputPacientes.ignore(1000,'\n');
        }
    }
}

void getDattaFromEspecialidades(ifstream &inputEspecialidades, ofstream &outputReporte, int codigoDocAtencion,
                                int duracionAtencion) {

    inputEspecialidades.clear();
    inputEspecialidades.seekg (0, ios::beg);

    while (true) {
        int codigoEspecialidad =0;
        inputEspecialidades >> codigoEspecialidad;
        if (inputEspecialidades.eof()) break;
        inputEspecialidades >> ws;
        inputEspecialidades.ignore(10000,' ');
        int codigoDoctor =0;
        while (inputEspecialidades >> codigoDoctor) {
            double costoPorHora=0.0, pago =0.0;
            if (codigoDoctor == codigoDocAtencion) {
                outputReporte << codigoDoctor << " - ";
                inputEspecialidades >> ws;
                readAndPrintWhitoutArr(inputEspecialidades, outputReporte);
                outputReporte << codigoEspecialidad;
                inputEspecialidades >> costoPorHora;
                pago = costoPorHora * (duracionAtencion/3600.0);
                outputReporte << pago << endl;
                return;
            }
            else{
                //* Ignoras el nombre y el precio por hora
                inputEspecialidades >> ws;
                inputEspecialidades.ignore(1000,' ');
                inputEspecialidades >> ws;
                inputEspecialidades >> costoPorHora;
                if (inputEspecialidades.get() == '\n') break;
            }
        }
    }
}

void GenerarReporte (const char *fileNameA, const char *fileNameS, const char *fileNameP,
                     const char *fileNameE, const char *fileName) {
    ifstream inputSede; open_read_file(inputSede, fileNameS);
    ifstream inputAtenciones; open_read_file(inputAtenciones, fileNameA);
    ifstream inputPacientes; open_read_file(inputPacientes, fileNameP);
    ifstream inputEspecialidades; open_read_file(inputEspecialidades, fileNameE);
    ofstream outputReporte; open_write_file(outputReporte, fileName);
    int dd=0;
    int fechaAtencion=0;
    //* Imprimir header
    printGeneralHeader(outputReporte);
    while (true) {
        int sedeAtencion=0;
        inputSede >> sedeAtencion;
        if (inputSede.eof()) break;
        leerSedes(inputSede, outputReporte, sedeAtencion);
        int IdAtencion=0, duracionAtencion=0, codigoDocAtencion=0;
        //* Por sede se realiza busquedas
        getDattaFromAtenciones (inputAtenciones, outputReporte, fechaAtencion, sedeAtencion,
                                 inputPacientes, inputEspecialidades);

    }
    printLine(outputReporte, ANCHO_REPORTE, '-');
    outputReporte << "TOTAL DE ATENCIONES: " << "XX" << endl;
    outputReporte << "TOTAL PAGO SEDE: " << "XX" << endl;
    outputReporte << "TIEMPO TOTAL ATENCIONES: " << "XX" << endl;
    printLine(outputReporte, ANCHO_REPORTE, '=');
}



