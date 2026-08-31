#ifndef LAB01_ENTRADAYSALIDA_2026_1_FUNCIONESAUXILIARES_H
#define LAB01_ENTRADAYSALIDA_2026_1_FUNCIONESAUXILIARES_H

void generarInforme(int di, int mi, int ai, int df, int mf, int af);

void imprimirCabecera(int di, int mi, int ai, int df, int mf, int af);

void imprimirCabeceraAtenciones(int dd, int mm, int aa);

void imprimirDatosAtenciones(int hi, int mini, int si, double temperatura, int presionArterialSistolica,
                             int presionArterialDiastolica, int hf, int minf, int sf, double &costoAtencion,
                             double &presionArterialMedia, double &nivelPresionArterial, int numIdentificacion1,
                             int numIdentificacion2, int numIdentificacion3, int &numMayorIdentificacion1,
                             int &numMayorIdentificacion2, int &numMayorIdentificacion3,
                             double &presionMediaMayor, int &cantAtenciones, int &cantPacientesPresionNormal,
                             int &cantPacientesPresionHipertensionNivel2, int &tiempoTotalAtenciones,
                             double &costoTotalAtenciones);

void imprimirResumenCanal(int numMayorIdentificacion1, int numMayorIdentificacion2, int numMayorIdentificacion3,
                          double presionMediaMayor, int cantAtenciones, int cantPacientesPresionNormal,
                          int cantPacientesPresionHipertensionNivel2, int tiempoTotalAtenciones,
                          double costoTotalAtenciones);

void impresionFinal(int cantFinalAtenciones, int tiempoFinalAtenciones, double costoFinalAtenciones);

void calcularNivelPresionArterial(int presionArterialSistolica, int presionArterialDiastolica,
                                  int &cantPacientesPresionNormal,
                                  int &cantPacientesPresionHipertensionNivel2);

void imprimirNombrePaciente();

int convertirFecha(int dd, int mm, int aa);

int convertirHora(int hh, int min, int ss);

void revertirHora(int duracion, int &hh, int &min, int &ss);

void imprimirLinea(char car, int cantLineas);

#endif //LAB01_ENTRADAYSALIDA_2026_1_FUNCIONESAUXILIARES_H
