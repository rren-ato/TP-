#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

#define MAX_PACIENTES 100
#define MAX_ESPECIALIDADES 50
#define MAX_ATENCIONES 400

//20236332 - André Mauricio Fernández Jiménez
int main() {
    //COMENTARIO RESPECTO AL PROYECTO
    //SE LLENAR LOS ARREGLOS RESPECTO A PACIENTES Y ESPECIALIDADES PARA POSTERIORMENTE HACER FUNCIONES DE BUSQUEDAS QUE ME PUEDAN AYUDAR A CONSEGUIR EL TEMA DE COSTOS Y CANTIDAD DE ATENCIONES PAGADAS Y PENDIENTES. CON ESOS DATOS SE GENERA UN REGISTRO DE PACIENTES Y AL FINAL UN RESUMEN

    int arrCodigoPaciente[MAX_PACIENTES], arrEdadPaciente[MAX_PACIENTES];
    double arrMontoPaciente[MAX_PACIENTES];
    char arrSexoPaciente[MAX_PACIENTES];
    leerPacientes(arrCodigoPaciente, arrSexoPaciente, arrEdadPaciente, arrMontoPaciente,
                  "ArchivosDeDatos/Pacientes_TP_L5.txt");

    int arrCodigoEspecialidad[MAX_ESPECIALIDADES];
    double arrCostoEspecialidad[MAX_ESPECIALIDADES];
    leerEspecialidades(arrCodigoEspecialidad, arrCostoEspecialidad, "ArchivosDeDatos/Especialidades_TP_L5.txt");

    generarReportePrueba(arrCodigoPaciente, arrSexoPaciente, arrEdadPaciente, arrMontoPaciente, arrCodigoEspecialidad,
                         arrCostoEspecialidad, "ArchivosDeReporte/Reporte_Prueba");

    int arrAtencionPagada[MAX_ATENCIONES]{}, arrAtencionPendiente[MAX_ATENCIONES]{};
    double arrMontoPagado[MAX_ATENCIONES]{}, arrMontoPendiente[MAX_ATENCIONES]{};
    llenarArreglosAuxiliares(arrCodigoPaciente, arrSexoPaciente, arrEdadPaciente, arrMontoPaciente,
                             arrCodigoEspecialidad, arrCostoEspecialidad, arrAtencionPagada, arrMontoPagado,
                             arrAtencionPendiente, arrMontoPendiente, "ArchivosDeDatos/Atenciones_TP_L5.txt");

    ordenarPorPacienteYMonto(arrCodigoPaciente, arrSexoPaciente, arrEdadPaciente, arrMontoPaciente,
                             arrCodigoEspecialidad, arrCostoEspecialidad, arrAtencionPagada, arrMontoPagado,
                             arrAtencionPendiente, arrMontoPendiente);

    generarInforme(arrCodigoPaciente, arrSexoPaciente, arrEdadPaciente, arrMontoPaciente,
                   arrCodigoEspecialidad, arrCostoEspecialidad, arrAtencionPagada, arrMontoPagado,
                   arrAtencionPendiente, arrMontoPendiente, "ArchivosDeReporte/ReporteDePacientes.txt");

    return 0;
}
