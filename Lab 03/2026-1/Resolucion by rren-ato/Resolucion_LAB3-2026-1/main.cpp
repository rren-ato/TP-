#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    //? ARCHIVOS DE LECTURA
    ifstream input_clinica;
    ifstream input_pacientes;
    ifstream input_triaje;
    //? REPORTE
    ofstream reporte;

    openFiles(input_clinica, input_pacientes, input_triaje, reporte);

    //* GENERAR EL REPORTE
    leer_clinica_Y_Generar_reporte(input_clinica, input_pacientes, input_triaje,
                                        reporte);

    closeFiles(input_clinica, input_pacientes, input_triaje, reporte);


    return 0;
}
