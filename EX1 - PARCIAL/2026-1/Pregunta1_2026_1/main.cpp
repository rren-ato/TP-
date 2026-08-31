#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

//20236332 - André Mauricio Fernández Jiménez
int main() {
    //Descripción del programa
    //Se realizan multiples lecturas de archivos, empezando desde las sedes hasta las especialidades médicas, en el transcurso de esta lectura voy encontrando y calculando valores respecto a atenciones por sede. Con ello, muestro las multiples atenciones que se realizan en cada sede, calculando el total de pago y de atenciones por sede, para finalmente realizar un resumen final mostrando la cantidad de sedes que sí atendieron, el pago total de todas las sedes y el pago mayor junto con su sede respectiva
    elaborarInforme("ArchivosDeDatos/Sedes_TP_Ex1.txt", "ArchivosDeDatos/Pacientes_TP_Ex1.txt",
                    "ArchivosDeDatos/Especialidades_Medicos_TP_Ex1.txt", "ArchivosDeDatos/Atenciones_TP_Ex1.txt",
                    "ArchivosDeReporte/Reporte.txt");
    return 0;
}