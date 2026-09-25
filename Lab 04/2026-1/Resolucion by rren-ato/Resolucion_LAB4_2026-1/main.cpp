#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    //? LECTURA Y LLENADO DE ARREGLOS (REVISAR TEORIA DE ESTO)
    //Segun erasmo esto era informalidad y debia ir en el UTILS
    // #define MAX_PACIENTE 100

    int arrCodigoPaciente[MAX_PACIENTES];
    int arrEdadPaciente[MAX_PACIENTES];
    char arrSexoPaciente[MAX_PACIENTES];
    int cantPacientes = 0; // <--- ESTO ES LA LONGITUD QUE SE LLENA EN EL ARREGLO
    //* RECORDAR QUE ES CLAVE DIFERENCIAR ENTRE LA CAPACIDAD Y LONGITUD DE UN ARREGLO (TEORIA)
    llenar_pacientes("ArchivosDeDatos/Pacientes_TP_L4.json", arrCodigoPaciente, arrEdadPaciente, arrSexoPaciente,
                      cantPacientes);

    int arrCodigoEspecialidad[MAX_ESPECIALIDADES];
    double arrCostoEspecialidad[MAX_ESPECIALIDADES];
    int cantEspecialidades = 0;
    llenar_especialidades("ArchivosDeDatos/Especialidades_TP_L4.json", arrCodigoEspecialidad, arrCostoEspecialidad,
                          cantEspecialidades);

    int arrFechaTriaje[MAX_TRIAJES];
    int arrfrecuenciaTriaje[MAX_TRIAJES];
    int arrpresionSisTriaje[MAX_TRIAJES];
    int arrpresionDiasTriaje[MAX_TRIAJES];
    double arrtemperaturaMaxTriaje[MAX_TRIAJES];
    double arrCostoTotal[MAX_TRIAJES];

    llenar_triaje("ArchivosDeDatos/Triaje_TP_L4.csv", arrCodigoPaciente, arrCodigoEspecialidad, arrCostoEspecialidad,
                   arrFechaTriaje, arrfrecuenciaTriaje, arrpresionSisTriaje, arrpresionDiasTriaje,
                   arrtemperaturaMaxTriaje, arrCostoTotal);

    //? IMPRESION
    imprimirReporte("ArchivosDeReporte/reporte_final.txt", arrCodigoPaciente, arrEdadPaciente, arrSexoPaciente,
                     arrFechaTriaje, arrfrecuenciaTriaje, arrpresionSisTriaje, arrpresionDiasTriaje,
                     arrtemperaturaMaxTriaje, arrCostoTotal);



    return 0;
}
