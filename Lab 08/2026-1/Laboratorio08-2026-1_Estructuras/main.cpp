#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

//20236332 - André Mauricio Fernández Jiménez

int main() {
    //Descripción del programa:
    //Se realiza las estructuras principales de Medico y Atencion, a ello se comienza a llenar sus respectivos valores desde codigos, nombres, tarifas, duracion, etc. Se ordenan según lo estipulado para al final realizar un reporte de todas las atenciones realizadas por cada médico, generando un mini resumen respecto al numero de atenciones, total de ingresos y la atención más duradera

    Medico arrMedicos[800]{};
    leerEspecialidadesMedicos(arrMedicos, "ArchivosDeDatos/Especialidades_Medicos_TP_Lab8.csv");

    reportePruebaMedico(arrMedicos, "ArchivosDeReporte/ReporteDePrueba_Medico.txt");

    ordenarMedico(arrMedicos);

    reportePruebaMedico(arrMedicos, "ArchivosDeReporte/ReporteDePruebaOrdenado_Medico.txt");

    Atencion arrAtenciones[800]{};
    leerAtenciones(arrAtenciones, "ArchivosDeDatos/Atenciones_TP_Lab8.csv");

    reportePruebaAtencion(arrAtenciones, "ArchivosDeReporte/ReporteDePrueba_Atencion.txt");

    ordenarAtencion(arrAtenciones);

    reportePruebaAtencion(arrAtenciones, "ArchivosDeReporte/ReporteDePruebaOrdenado_Atencion.txt");

    generarReporte(arrMedicos, arrAtenciones, "ArchivosDeReporte/ReporteDeAtencionesPorMedico.txt");
    return 0;
}