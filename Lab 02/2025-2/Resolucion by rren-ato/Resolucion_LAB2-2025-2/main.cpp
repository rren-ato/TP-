#include "Bibliotecas/FuncionesAuxiliares.h"

//* RECORDAR DESCARGAR EN PLUGLINS BETTER COMMENTS PARA VER MEJOR LOS COMENTARIOS (COLORES Y ESO)
int main() {
    ifstream input_twitchData;
    ofstream reporte;

    openFiles(input_twitchData, reporte);

    //! Validacion de apertura
    if (not openFiles(input_twitchData, reporte)) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    generar_reporte(input_twitchData, reporte);

    closeFiles(input_twitchData, reporte);

    return 0;
}
