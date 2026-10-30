#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    char *nombres[TAMAÑO_ARREGLO] = {};
    char *apellidos[TAMAÑO_ARREGLO] = {};
    int edades[TAMAÑO_ARREGLO]{};

    leerDatos("ArchivosDeDatos/personas.csv", nombres, apellidos, edades);
    ordenar(nombres, apellidos, edades);
    generarReporte("ArchivosDeReporte/reporte.txt", nombres, apellidos, edades);


    liberarMemoria(nombres, apellidos);

    return 0;
}
