#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"
#include "Bibliotecas/Paciente.h"

//20236332 - Fernández Jiménez André Mauricio

int main() {
    //Descripción del programa
    //Se realiza un llenado principal de arreglo dinámico de pacientes, en el cual se llenarán datos como sus ids, nombres completos, fechas ingresos y demás datos personales; además se tendrá acceso a sus signos vitales, diagnostico y sus múltiples tratamientos dependiendo de cada uno. Finalmente se imprime un reporte donde aparece el reporte de todos los pacientes tomando en caso que algunos no tienen tratamiento preescrito
    Paciente *pacientes = new Paciente [120]{};
    leerTriaje(pacientes, "ArchivosDeDatos/triaje.csv");

    generarReporte(pacientes, "ArchivosDeReporte/reporte_inicial_pacientes.txt");

    leerSignosVitales(pacientes, "ArchivosDeDatos/signos_vitales.csv");

    leerDiagnosticos(pacientes, "ArchivosDeDatos/diagnosticos.csv");

    generarReporte(pacientes, "ArchivosDeReporte/reporte_actualizado_sv_diagnosticos.txt");

    leerTratamientos(pacientes, "ArchivosDeDatos/tratamientos.csv");

    generarReporte(pacientes, "ArchivosDeReporte/reporte_pacientes_tratamientos.txt");

    generarReporte(pacientes, "ArchivosDeReporte/reporte_pacientes.txt");

    return 0;
}
