#include <iostream>

#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

//André Mauricio Fernández Jiménez - 20236332

int main() {
    //Se genera un informe respecto a un registro de atencion de una clínica, en el cual se va a ir mostrando paciente por paciente cada vez que se atienda con sus respectivos datos como fecha, edad, sexo y se calculará sus signos vitales para poder calcular el costo por atención de cada uno, adicionando su descuento respectivo por ser menor de edad o adulto mayor. Se van leyendo diferentes archivos de textos para así enlazarlos y poder hallar los datos que le corresponde a cada paciente.
    elaborarInforme("ArchivosDeDatos/ClinicaDeUrgencias_TP_L3.txt", "ArchivosDeDatos/Pacientes_TP_L3.txt",
                    "ArchivosDeDatos/Triaje_TP_L3.txt", "ArchivosDeReporte/Reporte.txt");
    return 0;
}
