#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    //? ARCHIVOS DE LECTURA
    ifstream input_clinica;
    ifstream input_pacientes;
    ifstream input_triaje;
    //? REPORTE
    ofstream reporte;


    //! Validacion de apertura
    if (not openFiles(input_clinica, input_pacientes, input_triaje, reporte)) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1); //return(1);
    }

    //* GENERAR EL REPORTE
    leer_clinica_Y_Generar_reporte(input_clinica, input_pacientes, input_triaje,
                                        reporte);

    closeFiles(input_clinica, input_pacientes, input_triaje, reporte);


    return 0;
}
