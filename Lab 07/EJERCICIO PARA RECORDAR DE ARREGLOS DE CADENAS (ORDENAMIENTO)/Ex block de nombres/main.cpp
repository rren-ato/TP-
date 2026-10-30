#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    char *nombres[TAMAÑO_ARREGLO] = {};
    char *apellidos[TAMAÑO_ARREGLO] = {};
    int *edades = new int[num];

    leerDatos("ArchivosDeDatos/personas.csv", nombres, apellidos);
    ordenar(nombres, apellidos);
    generarReporte("ArchivosDeReporte/reporte.txt", nombres, apellidos);


    liberarMemoria(nombres, apellidos);

    return 0;
}
