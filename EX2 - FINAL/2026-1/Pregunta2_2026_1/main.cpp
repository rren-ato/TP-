#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

//20236332 - Fernández Jiménez André Mauricio

int main() {
    //Descripción del programa
    //Se llena una lista de pacientes con su información personal como id del paciente, nombre completo, sexo y demás. Posteriormente se va llenando la información para imprimir un reporte según las prioridades del 1 al 5 para terminar eliminando las prioridades 3 y 5 porque se atenderán en sala de admisión y mostrando sus respectivos reportes.
    ListaPaciente listaPaciente;
    crearListaPacientes(listaPaciente, "ArchivosDeDatos/triaje.csv");

    generarReporte(1, listaPaciente, "ArchivosDeReporte/reporte_prioridades.txt");

    eliminarPrioridad3y5(listaPaciente);

    generarReporte(2, listaPaciente, "ArchivosDeReporte/reporte_prioridades_actualizado.txt");

    return 0;
}