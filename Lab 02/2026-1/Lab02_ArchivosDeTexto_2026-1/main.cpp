#include <iostream>

using namespace std;

#include "Bibliotecas/FuncionesAuxiliares.h"

//André Mauricio Fernández Jiménez - 20236332

int main() {
    //Se elabora un programa donde se imprime atenciones médicas realizadas entre dos fechas fijas, en la cual se dan los datos de cada atencion viniendo a ser nombres, edades, temperaturas y presiones. Además, se calcula cierto tipo de descuento dependiendo la edad del paciente, la cantidad de horas y costo de atencion que se gasta tanto por dia/fecha como en general
    elaborarInforme("ArchivosDeDatos/ClinicaDeUrgencias_TP_L2.txt", "ArchivosDeReporte/Reporte.txt");
    return 0;
}