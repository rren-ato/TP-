#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    int arrTiempoTotalAtencion[MAX_ATENCIONES]={};
    int arrCodigoMedico[MAX_ATENCIONES]={};
    int arrNumeroAtenciones[MAX_ATENCIONES]={};
    int cantAtenciones=0;
    llenar_Atenciones("ArchivosDeDatos/Atenciones_TP_Ex1.txt", arrTiempoTotalAtencion, arrCodigoMedico,
                            arrNumeroAtenciones, cantAtenciones, MAX_ATENCIONES);

    double arrTarifaMedico [MAX_ATENCIONES]={};
    int arrCodigoEspecialidad[MAX_ATENCIONES]={};
    llenar_Medicos("ArchivosDeDatos/Especialidades_Medicos_TP_Ex1.txt", arrTarifaMedico, arrCodigoMedico, arrCodigoEspecialidad,
        cantAtenciones);
    double arrPagoRecibido[MAX_ATENCIONES]={};
    int arrTiempoPromedio[MAX_ATENCIONES]={};
    calcularPagoYtiempoPromedio(arrTiempoTotalAtencion, arrTarifaMedico, arrPagoRecibido, arrNumeroAtenciones,
                                 arrTiempoPromedio, cantAtenciones);

    //* Ordeno por Pagos  para meterle un poco mas de dificultad
    insertionSort(arrCodigoMedico, arrCodigoEspecialidad, arrTarifaMedico,
                        arrNumeroAtenciones, arrTiempoTotalAtencion, arrTiempoPromedio, arrPagoRecibido,
                        cantAtenciones);
    //? Si no ordenaba por pagos no podia hacer busqueda binaria pero si busqueda normal
    int posEliminacion = busquedaBinaria(5000.0, arrPagoRecibido, cantAtenciones);
    eliminarDato(arrCodigoMedico, arrCodigoEspecialidad, arrTarifaMedico,
                        arrNumeroAtenciones, arrTiempoTotalAtencion, arrTiempoPromedio, arrPagoRecibido,
                    cantAtenciones, posEliminacion);
    generarReporte("ArchivosDeReporte/Reporte_Atenciones_Medicos,txt",arrCodigoMedico, arrCodigoEspecialidad, arrTarifaMedico,
                        arrNumeroAtenciones, arrTiempoTotalAtencion, arrTiempoPromedio, arrPagoRecibido,
                        cantAtenciones);
    return 0;
}
