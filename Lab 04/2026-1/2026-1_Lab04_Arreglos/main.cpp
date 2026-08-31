#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

#define MAX_PACIENTE 100
#define MAX_TRIAJE 600
#define MAX_ESPECIALIDAD 50

//20236332 - André Mauricio Fernández Jiménez
int main() {
    //DESCRIPCIÓN DEL PROGRAMA:
    //Se realizan múltiples arreglos tomando como "llaves" los arreglos de Pacientes y Especialidades para al final ligarlo al principal "Triaje". Luego de hallar los respectivos datos, se comenzará a dar un reporte donde aparezcan los códigos de pacientes, sexo, edad, presiones y entre otros datos; al final se estará colocando el costo de atención por cada paciente y finalmente se hará un resumen donde se calculará el promedio de los datos contables y el costo total de todas las atenciones de todos los pacientes.
    int arrCodigoPaciente[MAX_PACIENTE], arrEdadPaciente[MAX_PACIENTE];
    char arrSexoPaciente[MAX_PACIENTE];
    llenarPacientes(arrCodigoPaciente, arrEdadPaciente, arrSexoPaciente, "ArchivosDeDatos/Pacientes_TP_L4.txt");
    int arrCodigoEspecialidad[MAX_ESPECIALIDAD];
    double arrCostoEspecialidad[MAX_ESPECIALIDAD];
    llenarEspecialidades(arrCodigoEspecialidad, arrCostoEspecialidad, "ArchivosDeDatos/Especialidades_TP_L4.txt");
    imprimirReportePrueba(arrCodigoPaciente, arrEdadPaciente, arrSexoPaciente, arrCodigoEspecialidad,
                          arrCostoEspecialidad, "ArchivosDeReporte/Reporte_Prueba.txt");
    int arrFechaTriaje[MAX_TRIAJE], arrFrecuenciaTriaje[MAX_TRIAJE], arrDiastolicaTriaje[MAX_TRIAJE], arrSistolicaTriaje
            [MAX_TRIAJE];
    double arrTemperaturaMaximaTriaje[MAX_TRIAJE]{}, arrCostoTotal[MAX_TRIAJE]{};
    llenarTriaje(arrCodigoPaciente, arrCodigoEspecialidad, arrCostoEspecialidad, arrFechaTriaje, arrFrecuenciaTriaje,
                 arrDiastolicaTriaje, arrSistolicaTriaje, arrTemperaturaMaximaTriaje, arrCostoTotal,
                 "ArchivosDeDatos/Triaje_TP_L4.txt");
    imprimirReporte(arrCodigoPaciente, arrEdadPaciente, arrSexoPaciente, arrFechaTriaje, arrFrecuenciaTriaje,
                    arrDiastolicaTriaje, arrSistolicaTriaje, arrTemperaturaMaximaTriaje, arrCostoTotal,
                    "ArchivosDeReporte/ReporteDeAtencionesCriticas.txt");
    return 0;
}
