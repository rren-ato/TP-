#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

#define MAX_ATENCIONES 150
#define MAX_ESPECIALIDADES 150

//20236332 - André Mauricio Fernández Jiménez
int main() {
    //Descripción del programa
    //Se realiza el llenado de arreglos para los médicos, comenzando a llenar sin repetir; posteriormente al leer el archivo de especialidad hallamos sus arreglos auxiliares como la tarifa, especialidad o pago que junto a mis arreglos principales, del archivo Atenciones_TP_Ex1.txt, me ayudará para hallar el tiempo promedio, pago recibido y entre otros. Se realiza un resumen respecto a la cantidad total de doctores y el pago recibido para finalmente, en otro reporte, realizar la eliminación de cuyos doctores reciban un pago menor a 5000.00 soles y se vuelve a imprimir dicho reporte
    int arrMedico[MAX_ATENCIONES]{}, arrAtencionesMedico[MAX_ATENCIONES]{}, arrTiempoMedico[MAX_ATENCIONES]{};
    llenarAtenciones(arrMedico, arrAtencionesMedico, arrTiempoMedico, "ArchivosDeDatos/Atenciones_TP_Ex1.txt");

    generarReportePrueba(arrMedico, arrAtencionesMedico, arrTiempoMedico, "ArchivosDeReporte/Reporte_Prueba.txt");

    int arrEspecialidad[MAX_ESPECIALIDADES];
    double arrTarifa[MAX_ESPECIALIDADES], arrPagoRecibido[MAX_ESPECIALIDADES], arrTiempoPromedio[MAX_ESPECIALIDADES];
    llenarArreglosAuxiliares(arrMedico, arrAtencionesMedico, arrTiempoMedico, arrEspecialidad, arrTarifa,
                             arrPagoRecibido, arrTiempoPromedio, "ArchivosDeDatos/Especialidades_Medicos_TP_Ex1.txt");

    generarReporte(1, arrMedico, arrAtencionesMedico, arrTiempoMedico, arrEspecialidad, arrTarifa, arrPagoRecibido,
                   arrTiempoPromedio, "ArchivosDeReporte/Reporte_Atenciones_Medicos.txt");

    eliminarArreglos(arrMedico, arrAtencionesMedico, arrTiempoMedico, arrEspecialidad, arrTarifa, arrPagoRecibido,
                     arrTiempoPromedio);

    generarReporte(2, arrMedico, arrAtencionesMedico, arrTiempoMedico, arrEspecialidad, arrTarifa, arrPagoRecibido,
                   arrTiempoPromedio, "ArchivosDeReporte/Reporte_Atenciones_Medicos_MejorPagados.txt");
    return 0;
}
