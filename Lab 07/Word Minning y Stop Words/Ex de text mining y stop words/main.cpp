#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    char** diccOtros;
    char** diccPalabras;
    int* arrContaOtros;
    int* arrContaPalabras;
    int tamOtros =0, tamPalabras = 0;

    cargarDatos(diccOtros, arrContaOtros, tamOtros,
              diccPalabras, arrContaPalabras, tamPalabras);

    reporteParciales(diccOtros,tamOtros, diccPalabras, tamPalabras);

    char* diccDesconocido[MAX_DESCONOCIDO];
    int frecuenciaDesconocido[MAX_DESCONOCIDO] {};
    int tamDesconocido=0;
    int cantDesconocido=0;
    int cantOtros=0, cantPalabras=0;
    procesarTexto(arrContaOtros, arrContaPalabras,
                     diccDesconocido, frecuenciaDesconocido, tamDesconocido, cantDesconocido,
                     diccOtros, tamOtros, cantOtros,
                     diccPalabras, tamPalabras, cantPalabras);


    generarReportes(diccDesconocido, frecuenciaDesconocido, tamDesconocido,
                         cantOtros, cantPalabras, cantDesconocido, tamOtros, tamPalabras,
                         arrContaOtros, arrContaPalabras,
                         diccPalabras, diccOtros);

    liberarMemoria(diccDesconocido,
                     arrContaOtros, arrContaPalabras,
                     diccPalabras, diccOtros,
                     tamOtros, tamPalabras, tamDesconocido);
    return 0;
}
