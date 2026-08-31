#include <iostream>
#include "Bibliotecas/Atencion.h"
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

//20236332 - André Mauricio Fernández Jiménez

int main() {
    //Descripción del programa
    //Se realiza el llenado de Medicos y Atenciones como estructuras principales, donde se encontrará información de codigos del medico, duracion de atenciones, codigos de pacientes, fechas de registro, nombre, especialidad y tarifa del médico entre otros. Para posteriormente realizar una búsqueda e imprimir un informe donde aparezca todas las atenciones que tuvo cada médico detallando los datos anteriormente mencionados

    Medico *arrMedicos;
    arrMedicos = new Medico[50]{};
    leerMedicos(arrMedicos, "ArchivosDeDatos/Medicos_TP_Lab9.csv");

    reporteMedicos(arrMedicos, "ArchivosDeReporte/ReportePrueba_Medicos.txt");

    ordenarMedicos(arrMedicos);

    reporteMedicos(arrMedicos, "ArchivosDeReporte/ReportePrueba_MedicosOrdenados.txt");

    Atencion *arrAtenciones;
    arrAtenciones = new Atencion[300]{};
    leerAtenciones(arrAtenciones, "ArchivosDeDatos/Atenciones_TP_Lab9.csv");

    reporteAtenciones(arrAtenciones, "ArchivosDeReporte/ReportePrueba_Atenciones.txt");

    elaborarInforme(arrMedicos, arrAtenciones, "ArchivosDeReporte/ReporteAtencionesPorMedico.txt");
    return 0;
}
