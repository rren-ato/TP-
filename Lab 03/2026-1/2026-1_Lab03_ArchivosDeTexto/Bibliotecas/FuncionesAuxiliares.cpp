#include <iostream>
#include <fstream>
#include <iomanip>

#define MAX_LINES 135

using namespace std;

#include "FuncionesAuxiliares.h"

void elaborarInforme(const char *nombArchClinica, const char *nombArchPacientes,
                     const char *nombArchTriaje, const char *nombArchReporte) {
    ifstream archClinica = abrirArchivoEntrada(nombArchClinica);
    ifstream archPacientes = abrirArchivoEntrada(nombArchPacientes);
    ifstream archTriaje = abrirArchivoEntrada(nombArchTriaje);
    ofstream arch = abrirArchivoSalida(nombArchReporte);
    arch << right << fixed << setprecision(2);
    generarInforme(archClinica, archPacientes, archTriaje, arch);
}

void generarInforme(ifstream &archClinica, ifstream &archPacientes, ifstream &archTriaje, ofstream &arch) {
    int dd, mm, aa, hhI, minI, ssI, num1, num2, num3, hhF, minF, ssF, contador, duracion;
    double costoXHora;
    char car;
    imprimirCabecera(arch);
    while (true) {
        contador = 1;
        archClinica >> dd;
        if (archClinica.eof()) break;
        archClinica >> car >> mm >> car >> aa;
        imprimirCabeceraAtenciones(dd, mm, aa, arch);
        while (true) {
            archClinica >> hhI >> car >> minI >> car >> ssI >> num1 >> car >> num2 >> car >> num3 >> hhF >> car >> minF
                    >> car >> ssF >> costoXHora;
            duracion = calcularDuracion(hhI, minI, ssI, hhF, minF, ssF);
            leerPacientes(duracion, costoXHora, dd, mm, aa, num1, num2, num3, contador, archPacientes, archTriaje,
                          arch);
            if (archClinica.get() == '\n') break;
        }
    }
}

void leerPacientes(int duracion, double costoXHora, int dd, int mm, int aa, int num1, int num2, int num3, int &contador,
                   ifstream &archPacientes,
                   ifstream &archTriaje, ofstream &arch) {
    int num1Paciente, num2Paciente, num3Paciente, edad;
    char car, sexo;
    archPacientes.clear();
    archPacientes.seekg(0, ios::beg);
    while (true) {
        archPacientes >> num1Paciente;
        if (archPacientes.eof()) break;
        archPacientes >> car >> num2Paciente >> car >> num3Paciente;
        if (num1 == num1Paciente and num2 == num2Paciente and num3 == num3Paciente) {
            imprimirDatosPaciente(num1, num2, num3, edad, sexo, contador, archPacientes, arch);
            leerTriaje(dd, mm, aa, num1, num2, num3, archTriaje, arch);
            imprimirDatosAtencion(duracion, costoXHora, edad, arch);
        } else while (archPacientes.get() != '\n');
    }
}

void leerTriaje(int dd, int mm, int aa, int num1, int num2, int num3, ifstream &archTriaje, ofstream &arch) {
    int ddTriaje, mmTriaje, aaTriaje, num1Triaje, num2Triaje, num3Triaje, fecha, fechaTriaje, frecuenciaCardiaca,
            sistolica, diastolica;
    double temperatura, saturacion;
    char car;
    archTriaje.clear();
    archTriaje.seekg(0, ios::beg);
    while (true) {
        archTriaje >> ddTriaje;
        if (archTriaje.eof()) break;
        archTriaje >> car >> mmTriaje >> car >> aaTriaje >> num1Triaje >> car >> num2Triaje >> car >> num3Triaje;
        fecha = convertirFecha(dd, mm, aa);
        fechaTriaje = convertirFecha(ddTriaje, mmTriaje, aaTriaje);
        if (fecha == fechaTriaje and num1 == num1Triaje and num2 == num2Triaje and num3 == num3Triaje) {
            archTriaje >> frecuenciaCardiaca >> sistolica >> diastolica >> temperatura >> saturacion;
            imprimirSignosVitales(temperatura, sistolica, diastolica, arch);
        } else while (archTriaje.get() != '\n');
    }
}

void imprimirSignosVitales(double temperatura, int sistolica, int diastolica, ofstream &arch) {
    arch << setw(19) << "SIGNOS VITALES:" << endl;
    arch << setw(17) << "TEMPERATURA: " << temperatura << setw(24) << "PRESION SISTOLICA: " << sistolica << setw(25) <<
            "PRESION DIASTOLICA: " << diastolica << endl;;
}

void imprimirDatosPaciente(int num1, int num2, int num3, int &edad, char &sexo, int &contador, ifstream &archPacientes,
                           ofstream &arch) {
    int cantCaracteres;
    imprimirLinea('-', arch);
    arch << setfill('0') << setw(2) << contador << ") " << setfill(' ') << "DATOS DEL PACIENTE:" << endl;
    arch << setw(8) << "ID: " << setfill('0') << setw(3) << num1 << setw(2) << num2 << setw(4) << num3 << setfill(' ')
            << setw(18) << "NOMBRE: ";
    imprimirTexto(cantCaracteres, archPacientes, arch);
    archPacientes >> sexo >> edad;
    arch << setw(35 - cantCaracteres) << "EDAD: " << setfill('0') << setw(2) << edad << setfill(' ') << setw(15) <<
            "SEXO: ";
    if (sexo == 'M') arch << "MASCULINO" << endl;
    if (sexo == 'F') arch << "FEMENINO" << endl;
    contador++;
}

void imprimirDatosAtencion(int duracion, double costoXHora, int edad, ofstream &arch) {
    double costo;
    costo = costoXHora * duracion / 3600.00;
    if (edad < 18) costo -= 0.05 * costo;
    else if (edad > 64) costo -= 0.18 * costo;
    arch << setw(13) << "ATENCION:" << endl;
    arch << setw(42) << "COSTO POR HORA SEGUN LA ESPECIALIDAD: " << costoXHora << setw(15) << "DURACION: ";
    imprimirHora(duracion, arch);
    arch << setw(17) << "COSTO TOTAL: " << costo  << endl;
}

void imprimirCabecera(ofstream &arch) {
    arch << setw(75) << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    arch << setw(72) << "REGISTRO DE ATENCIONES" << endl;
}

void imprimirCabeceraAtenciones(int dd, int mm, int aa, ofstream &arch) {
    imprimirLinea('=', arch);
    arch << "FECHA: ";
    imprimirFecha(dd, mm, aa, arch);
    arch << endl;
    arch << "PACIENTES ATENDIDOS:" << endl;
}

void imprimirTexto(int &cantCaracteres, ifstream &archEntrada, ofstream &arch) {
    char car;
    cantCaracteres = 0;
    archEntrada >> ws;
    while (true) {
        archEntrada.get(car);
        if (car == ' ') break;
        if (car == '/' or car == '-') car = ' ';
        car = toupper(car);
        arch.put(car);
        cantCaracteres++;
    }
}

int calcularDuracion(int hhI, int minI, int ssI, int hhF, int minF, int ssF) {
    int fechaInicio, fechaFin, duracion;
    fechaInicio = convertirHora(hhI, minI, ssI);
    fechaFin = convertirHora(hhF, minF, ssF);
    duracion = fechaFin - fechaInicio;
    if (duracion < 0) duracion += 24 * 3600;
    return duracion;
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

void imprimirHora(int duracion, ofstream &arch) {
    int hh, min, ss;
    revertirHora(duracion, hh, min, ss);
    arch << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) << ss << setfill(' ');
}

int convertirFecha(int dd, int mm, int aa) {
    return aa * 10000 + mm * 100 + dd;
}

void imprimirFecha(int dd, int mm, int aa, ofstream &arch) {
    arch << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << aa << setfill(' ');
}

void imprimirLinea(char car, ofstream &arch) {
    for (int i = 0; i < MAX_LINES; i++) arch.put(car);
    arch.put('\n');
}

ifstream abrirArchivoEntrada(const char *archEntrada) {
    ifstream arch(archEntrada, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << archEntrada;
        exit(1);
    }
    return arch;
}

ofstream abrirArchivoSalida(const char *archSalida) {
    ofstream arch(archSalida, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << archSalida;
        exit(1);
    }
    return arch;
}
