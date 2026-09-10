#include "Bibliotecas/FuncionesAuxiliares.h"

//ESTE LAB CONCIERNES MAS A BUSQUEDAS
//PRACTICAR PARA LAB3
//En este lab se uso un archivo csv y uno txt (BUSQUEDAS)
int main() {
    generate_report("ArchivosDeDatos/InfraccionesCometidas_Lab02.csv", "ArchivosDeDatos/Infracciones_de_transito_Lab02.txt",
                    "ArchivosDeReporte/reporte.txt");
    return 0;
}
