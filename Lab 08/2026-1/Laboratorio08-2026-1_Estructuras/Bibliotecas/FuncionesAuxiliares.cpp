#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 135
#define NO_ENCONTRADO -1

void leerEspecialidadesMedicos(Medico *arrMedicos, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int codigo, especialidadCodigo, i = 0;
    double tarifa;
    char car, nombre[200], especialidad[200];
    while (true) {
        arch >> especialidadCodigo;
        if (arch.eof()) break;
        arch >> car;
        arch.getline(especialidad, 200, ',');
        while (true) {
            arch >> codigo >> car;
            arch.getline(nombre, 200, ',');
            arch >> tarifa;
            Medico medico{};
            medico.codigo = codigo;
            strcpy(medico.nombre, nombre);
            medico.especialidadCodigo = especialidadCodigo;
            strcpy(medico.especialidad, especialidad);
            medico.tarifa = tarifa;
            arrMedicos[i] = medico;
            i++;
            if (arch.get() == '\n') break;
        }
    }
}

void reportePruebaMedico(Medico *arrMedicos, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    imprimirLinea('=', arch);
    arch << "REPORTE DE PRUEBA - MEDICOS" << endl;
    arch << "CODIGO" << setw(12) << "NOMBRE" << setw(28) << "ESPECIALIDAD" << setw(9) << "NOMBRE" << setw(14) <<
            "TARIFA" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrMedicos[i].codigo != 0; i++) {
        arch << left << setw(6) << arrMedicos[i].codigo << setw(34) << arrMedicos[i].nombre << setw(5) << arrMedicos[i]
                .especialidadCodigo << setw(19) << arrMedicos[i].especialidad << arrMedicos[i].tarifa << endl;;
    }
}

void ordenarMedico(Medico *arrMedicos) {
    int n = contarMedicos(arrMedicos);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arrMedicos[i].nombre, arrMedicos[j].nombre) > 0) {
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

void intercambiarMedicos(Medico &medicoI, Medico &medicoJ) {
    Medico aux;
    aux = medicoI;
    medicoI = medicoJ;
    medicoJ = aux;
}

void leerAtenciones(Atencion *arrAtenciones, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int sede, dd, mm, aa, codigoMedico, hhI, minI, ssI, hhF, minF, ssF, num1, num2, num3, i = 0;
    char car;
    while (true) {
        arch >> dd;
        if (arch.eof()) break;
        arch >> car >> mm >> car >> aa >> car;
        while (true) {
            arch >> sede >> car >> hhI >> car >> minI >> car >> ssI >> car >> num1 >> car >> num2 >> car >> num3 >> car
                    >> hhF >> car >> minF >> car >> ssF >> car >> codigoMedico;
            int duracion = (hhF * 3600 + minF * 60 + ssF) - (hhI * 3600 + minI * 60 + ssI);
            Atencion atencion{};
            atencion.fecha.dia = dd;
            atencion.fecha.mes = mm;
            atencion.fecha.año = aa;
            atencion.fecha.fecha_AAAAMMDD = aa * 10000 + mm * 100 + dd;
            atencion.codigoMedico = codigoMedico;
            atencion.duracion.segundos_HHHHMMSS = duracion;
            atencion.duracion.horas = duracion / 3600;
            duracion -= atencion.duracion.horas * 3600;
            atencion.duracion.minutos = duracion / 60;
            duracion -= atencion.duracion.minutos * 60;
            atencion.duracion.segundos = duracion;
            atencion.paciente.valor1 = num1;
            atencion.paciente.valor2 = num2;
            atencion.paciente.valor3 = num3;
            arrAtenciones[i] = atencion;
            i++;
            if (arch.get() == '\n') break;
        }
    }
}

void reportePruebaAtencion(Atencion *arrAtenciones, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    imprimirLinea('=', arch);
    arch << "REPORTE DE PRUEBA - ATENCIONES" << endl;
    arch << "FECHA" << setw(11) << "CODIGO" << setw(10) << "DURACION" << setw(10) << "PACIENTE" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrAtenciones[i].codigoMedico != 0; i++) {
        arch << setfill('0') << setw(2) << arrAtenciones[i].fecha.dia << "/" << setw(2) << arrAtenciones[i].fecha.mes <<
                "/" << setfill(' ') << arrAtenciones[i].fecha.año << setw(6) << arrAtenciones[i].codigoMedico <<
                setw(7) << arrAtenciones[i].duracion.segundos_HHHHMMSS << setw(5) << arrAtenciones[i].paciente.valor1
                << "-" << arrAtenciones[i].paciente.valor2 << "-" << arrAtenciones[i].paciente.valor3 << endl;
    }
}

void ordenarAtencion(Atencion *arrAtenciones) {
    int n = contarAtenciones(arrAtenciones);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrAtenciones[i].codigoMedico > arrAtenciones[j].codigoMedico or (
                    arrAtenciones[i].codigoMedico == arrAtenciones[j].codigoMedico and arrAtenciones[i].paciente.valor1
                    * 1000000 + arrAtenciones[i].paciente.valor2 * 10000 + arrAtenciones[i].paciente.valor3 <
                    arrAtenciones[j].paciente.valor1 * 1000000 + arrAtenciones[j].paciente.valor2 * 10000 +
                    arrAtenciones[j].paciente.valor3) or (
                    arrAtenciones[i].codigoMedico == arrAtenciones[j].codigoMedico and arrAtenciones[i].paciente.valor1
                    * 1000000 + arrAtenciones[i].paciente.valor2 * 10000 + arrAtenciones[i].paciente.valor3 ==
                    arrAtenciones[j].paciente.valor1 * 1000000 + arrAtenciones[j].paciente.valor2 * 10000 +
                    arrAtenciones[j].paciente.valor3 and arrAtenciones[i].fecha.fecha_AAAAMMDD > arrAtenciones[j].fecha.
                    fecha_AAAAMMDD)) {
                intercambiarAtenciones(arrAtenciones[i], arrAtenciones[j]);
            }
        }
    }
}

int contarAtenciones(Atencion *arrAtenciones) {
    int i = 0;
    while (arrAtenciones[i].codigoMedico) i++;
    return i;
}

void intercambiarAtenciones(Atencion &atencionI, Atencion &atencionJ) {
    Atencion aux;
    aux = atencionI;
    atencionI = atencionJ;
    atencionJ = aux;
}

void generarReporte(Medico *arrMedicos, Atencion *arrAtenciones, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    for (int i = 0; arrMedicos[i].codigo; i++) {
        imprimirEncabezado(i, arrMedicos, arch);
        int contador = 0, mayorDuracion = 0, hhMayor, minMayor, ssMayor;
        double totalIngresos = 0.00;
        for (int j = 0; arrAtenciones[j].codigoMedico; j++) {
            if (arrMedicos[i].codigo == arrAtenciones[j].codigoMedico) {
                arch << " " << setfill('0') << setw(2) << contador + 1 << setfill(' ') << left << setw(2) << ")" <<
                        right << setfill('0') << setw(2) << arrAtenciones[j].fecha.dia << "/" << setw(2) <<
                        arrAtenciones[j].fecha.mes << "/" << setfill(' ') << arrAtenciones[j].fecha.año << setw(10) <<
                        arrAtenciones[j].paciente.valor1 << "-" << arrAtenciones[j].paciente.valor2 << "-" << left <<
                        setw(12) << arrAtenciones[j].paciente.valor3 << right << setfill('0') << setw(2) <<
                        arrAtenciones
                        [j].duracion.horas << ":" << setw(2) << arrAtenciones[j].duracion.minutos << ":" << setw(2) <<
                        arrAtenciones[j].duracion.segundos << setfill(' ') << setw(12) << (
                            arrMedicos[i].tarifa * arrAtenciones[j].duracion.segundos_HHHHMMSS / 3600.00) << endl;
                if (arrAtenciones[j].duracion.segundos_HHHHMMSS > mayorDuracion) {
                    mayorDuracion = arrAtenciones[j].duracion.segundos_HHHHMMSS;
                    hhMayor = arrAtenciones[j].duracion.horas;
                    minMayor = arrAtenciones[j].duracion.minutos;
                    ssMayor = arrAtenciones[j].duracion.segundos;
                }
                totalIngresos += (arrMedicos[i].tarifa * arrAtenciones[j].duracion.segundos_HHHHMMSS / 3600.00);
                contador++;
            }
        }
        imprimirLinea('=', arch);
        arch << setw(23) << "NUMERO DE ATENCIONES: " << contador << endl;
        arch << setw(20) << "TOTAL DE INGRESOS: " << totalIngresos << endl;
        arch << setw(30) << "ATENCION CON MAYOR DURACION: " << setfill('0') << setw(2) << hhMayor << ":" << setw(2) <<
                minMayor << ":" << setw(2) << ssMayor << setfill(' ') << endl;
    }
}

void imprimirEncabezado(int i, Medico *arrMedicos, ofstream &arch) {
    imprimirLinea('=', arch);
    arch << setw(2) << i + 1 << ")" << setw(8) << "MEDICO:" << endl;
    arch << setw(9) << "CODIGO: " << arrMedicos[i].codigo << endl;
    arch << setw(9) << "NOMBRE: " << arrMedicos[i].nombre << endl;
    arch << setw(9) << "TARIFA: " << arrMedicos[i].tarifa << endl;
    imprimirLinea('-', arch);
    arch << setw(14) << "ESPECIALIDAD:" << endl;
    arch << setw(9) << "CODIGO: " << arrMedicos[i].especialidadCodigo << endl;
    arch << setw(9) << "NOMBRE: " << arrMedicos[i].especialidad << endl;
    imprimirLinea('=', arch);
    arch << setw(19) << "ATENCIONES HECHAS:" << endl;
    arch << setw(4) << "No." << setw(6) << "FECHA" << setw(27) << "CODIGO DEL PACIENTE" << setw(12) << "DURACION"
            << setw(11) << "PAGO" << endl;
}

void imprimirLinea(char car, ofstream &arch) {
    for (int i = 0; i < MAX_LINES; i++) arch.put(car);
    arch.put('\n');
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
