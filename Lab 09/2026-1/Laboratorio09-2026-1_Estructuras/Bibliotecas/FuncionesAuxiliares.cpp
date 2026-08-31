#include <iostream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"

void leerMedicos(Medico *arrMedicos, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int codigo, i = 0;
    double tarifa;
    char car, *nombre, *especialidad;
    while (true) {
        arch >> codigo;
        if (arch.eof()) break;
        arch >> car;
        nombre = leerCadena(',', arch);
        arch >> tarifa >> car;
        especialidad = leerCadena('\n', arch);
        Medico medico{};
        medico.codigo = codigo;
        medico.nombre = new char [strlen(nombre) + 1];
        strcpy(medico.nombre, nombre);
        medico.especialidad = new char [strlen(especialidad) + 1];
        strcpy(medico.especialidad, especialidad);
        medico.tarifa = tarifa;
        arrMedicos[i] = medico;
        i++;
    }
}

void ordenarMedicos(Medico *arrMedicos) {
    int n = contarMedicos(arrMedicos);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arrMedicos[i].especialidad, arrMedicos[j].especialidad) > 0 or (
                    strcmp(arrMedicos[i].especialidad, arrMedicos[j].especialidad) == 0) and strcmp(
                    arrMedicos[i].nombre, arrMedicos[j].nombre) < 0) {
                intercambiarMedicos(arrMedicos[i], arrMedicos[j]);
            }
        }
    }
}

int contarMedicos(Medico *arrMedicos) {
    int i = 0;
    while (arrMedicos[i].codigo) i++;
    return i;
}

void intercambiarMedicos(Medico &datoI, Medico &datoJ) {
    Medico aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

void leerAtenciones(Atencion *arrAtenciones, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int dd, mm, aa, codigoMedico, hhI, minI, ssI, hhF, minF, ssF, num1, num2, num3, i = 0;
    char car;
    while (true) {
        arch >> dd;
        if (arch.eof()) break;
        arch >> car >> mm >> car >> aa >> car;
        while (true) {
            arch >> hhI >> car >> minI >> car >> ssI >> car >> num1 >> car >> num2 >> car >> num3 >> car >> hhF
                    >> car >> minF >> car >> ssF >> car >> codigoMedico;
            int duracion = (hhF * 3600 + minF * 60 + ssF) - (hhI * 3600 + minI * 60 + ssI);
            int hhD = duracion / 3600;
            duracion -= hhD * 3600;
            int minD = duracion / 60;
            duracion -= minD * 60;
            int ssD = duracion;
            Fecha fecha{};
            fecha.año = aa;
            fecha.mes = mm;
            fecha.dia = dd;
            fecha.fecha_AAAAMMDD = aa * 10000 + mm * 100 + dd;
            Hora hora{};
            hora.horas = hhD;
            hora.minutos = minD;
            hora.segundos = ssD;
            hora.segundos_HHHHMMSS = hhD * 3600 + minD * 60 + ssD;
            Codigo codigo{};
            codigo.valor1 = num1;
            codigo.valor2 = num2;
            codigo.valor3 = num3;
            Atencion atencion{};
            atencion.codigoMedico = codigoMedico;
            atencion.fecha = fecha;
            atencion.duracion = hora;
            atencion.paciente = codigo;
            arrAtenciones[i] = atencion;
            i++;
            if (arch.get() == '\n') break;
        }
    }
}

void reporteMedicos(Medico *arrMedicos, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    for (int i = 0; arrMedicos[i].codigo; i++) {
        arch << i + 1 << ") " << "MEDICO:" << endl;
        arch << "CODIGO: " << arrMedicos[i].codigo << endl;
        arch << "NOMBRE: " << arrMedicos[i].nombre << endl;
        arch << "TARIFA: " << arrMedicos[i].tarifa << endl;
        arch << "ESPECIALIDAD: " << arrMedicos[i].especialidad << endl;
    }
}

void reporteAtenciones(Atencion *arrAtenciones, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    arch << "ATENCIONES HECHAS" << endl;
    arch << "No." << setw(7) << "FECHA" << setw(28) << "CODIGO DEL PACIENTE" << setw(14) << "DURACION" << setw(18) <<
            "CODIGO MEDICO" << endl;
    for (int i = 0; arrAtenciones[i].codigoMedico; i++) {
        arch << setfill('0') << setw(3) << i + 1 << ") " << setw(2) << arrAtenciones[i].fecha.dia << "/" << setw(2) <<
                arrAtenciones[i].fecha.mes << "/" << setfill(' ') << arrAtenciones[i].fecha.año << setw(11) <<
                arrAtenciones[i].paciente.valor1 << "-" << arrAtenciones[i].paciente.valor2 << "-" << left << setw(14)
                << arrAtenciones[i].paciente.valor3 << right << setfill('0') << setw(2) << arrAtenciones[i].duracion.
                horas << ":" << setw(2) << arrAtenciones[i].duracion.minutos << ":" << setw(2) << arrAtenciones[i].
                duracion.segundos << setfill(' ') << setw(13) << arrAtenciones[i].codigoMedico << endl;
    }
}

void elaborarInforme(Medico *arrMedicos, Atencion *arrAtenciones, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    for (int i = 0; arrMedicos[i].codigo; i++) {
        arch << i + 1 << ") " << "MEDICO:" << endl;
        arch << "CODIGO: " << arrMedicos[i].codigo << endl;
        arch << "NOMBRE: " << arrMedicos[i].nombre << endl;
        arch << "TARIFA: " << arrMedicos[i].tarifa << endl;
        arch << "ESPECIALIDAD: " << arrMedicos[i].especialidad << endl;
        imprimirLinea('=', arch);
        arch << "ATENCIONES HECHAS" << endl;
        arch << "No." << setw(7) << "FECHA" << setw(28) << "CODIGO DEL PACIENTE" << setw(14) << "DURACION" << setw(10)
                << "PAGO" << endl;
        int cantAtenciones = 0, mayorDuracion = -1, hh, min, ss;
        double totalIngresos = 0.00;
        for (int j = 0; arrAtenciones[j].codigoMedico; j++) {
            if (arrMedicos[i].codigo == arrAtenciones[j].codigoMedico) {
                double pago = (arrAtenciones[j].duracion.segundos_HHHHMMSS * arrMedicos[i].tarifa / 3600.00);
                arch << setfill('0') << setw(3) << cantAtenciones + 1 << ") " << setw(2) << arrAtenciones[j].fecha.dia
                        << "/" << setw(2) << arrAtenciones[j].fecha.mes << "/" << setfill(' ') << arrAtenciones[j].fecha
                        .año << setw(11) << arrAtenciones[j].paciente.valor1 << "-" << arrAtenciones[j].paciente.valor2
                        << "-" << left << setw(14) << arrAtenciones[j].paciente.valor3 << right << setfill('0') <<
                        setw(2) << arrAtenciones[j].duracion.horas << ":" << setw(2) << arrAtenciones[j].duracion.
                        minutos << ":" << setw(2) << arrAtenciones[j].duracion.segundos << setfill(' ') << setw(11) <<
                        pago << endl;
                if (arrAtenciones[j].duracion.segundos_HHHHMMSS > mayorDuracion)
                    mayorDuracion = arrAtenciones[j].duracion.segundos_HHHHMMSS;
                totalIngresos += pago;
                cantAtenciones++;
            }
        }
        imprimirLinea('=', arch);
        arch << "NUMERO DE ATENCIONES" << left << setw(6) << ":" << cantAtenciones << endl;
        arch << "TOTAL DE INGRESOS" << setw(6) << ":" << totalIngresos << endl;
        hh = mayorDuracion / 3600;
        mayorDuracion -= hh * 3600;
        min = mayorDuracion / 60;
        mayorDuracion -= min * 60;
        ss = mayorDuracion;
        arch << "ATENCIÓN CON MAYOR DURACIÓN" << setw(4) << ":" << right << setfill('0') << setw(2) << hh << ":" <<
                setw(2) << min << ":" << setw(2) << ss << setfill(' ') << endl;
        imprimirLinea('=', arch);
    }
}

void imprimirLinea(char car, ofstream &arch) {
    for (int i = 0; i < 80; i++) arch.put(car);
    arch.put('\n');
}

char *leerCadena(char delim, ifstream &arch) {
    char cadena[600], *pcadena;
    arch.getline(cadena, 600, delim);
    if (arch.eof()) return nullptr;
    modificarCadena(cadena);
    pcadena = new char[strlen(cadena) + 1];
    strcpy(pcadena, cadena);
    return pcadena;
}

void modificarCadena(char *cadena) {
    for (int i = 0; cadena[i]; i++) {
        cadena[i] = tolower(cadena[i]);
        if (cadena[i - 1] == ' ' or cadena[i - 1] == '\0') cadena[i] = toupper(cadena[i]);
    }
}

ifstream abrirArchivosEntrada(const char *nombArch) {
    ifstream arch(nombArch, ios::in);
    if (not arch) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << nombArch << endl;
        exit(1);
    }
    return arch;
}

ofstream abrirArchivosSalida(const char *nombArch) {
    ofstream arch(nombArch, ios::out);
    if (not arch) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << nombArch << endl;
        exit(1);
    }
    return arch;
}
