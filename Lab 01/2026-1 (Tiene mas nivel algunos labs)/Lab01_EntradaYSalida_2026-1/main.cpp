#include <iostream>

using namespace std;

#include "Bibliotecas/FuncionesAuxiliares.h"

//André Mauricio Fernández Jiménez - 202363332

int main() {
    //Se realiza un informe detallado sobre las atenciones que se realizan dentro de un rango de fechas, mostrando la información del paciente como la información entregada por el médico como el ingreso, temperatura, presion arterial y demás datos variados
    int di = 5, mi = 4, ai = 2023, df = 27, mf = 4, af = 2023;
    generarInforme(di, mi, ai, df, mf, af);
    return 0;
}
