#include <iostream>
#include <iomanip>

#define MAX_LINES 140

using namespace std;

#include "FuncionesAuxiliares.h"

void generarInforme(int di, int mi, int ai, int df, int mf, int af) {
    int dd, mm, aa, numIdentificacion1, numIdentificacion2, numIdentificacion3, fechaInicio, fechaFinal, fechaRegistro,
            hi, mini, si, presionArterialSistolica, presionArterialDiastolica, hf, minf, sf, numMayorIdentificacion1,
            numMayorIdentificacion2, numMayorIdentificacion3, cantAtenciones,
            cantPacientesPresionNormal, cantPacientesPresionHipertensionNivel2, tiempoTotalAtenciones,
            cantFinalAtenciones = 0, tiempoFinalAtenciones = 0;
    double presionMediaMayor, costoTotalAtenciones, costoFinalAtenciones = 0.00, costoAtencion, presionArterialMedia,
            nivelPresionArterial, temperatura;
    char c;
    imprimirCabecera(di, mi, ai, df, mf, af);
    fechaInicio = convertirFecha(di, mi, ai);
    fechaFinal = convertirFecha(df, mf, af);
    //1/04/2023
    while (true) {
        cin >> dd;
        if (cin.eof()) break;
        cin >> c >> mm >> c >> aa;
        fechaRegistro = convertirFecha(dd, mm, aa);
        if (fechaRegistro >= fechaInicio && fechaRegistro <= fechaFinal) {
            imprimirCabeceraAtenciones(dd, mm, aa);
            //766-20-3662  N_Sparsholt    01:13:00    39.5    104    61    01:50:47    701-64-7880    L_Brothwell    01:21:00    35.5    115    101    02:11:23    259-51-9518    T_Rolingson    02:45:00    39.5    137    106    03:01:15    125-52-4944    N_Sommerscales    04:34:00    35.5    121    86    06:10:29    628-45-6492    L_McCarrison    06:07:00    39    153    105    08:25:48    576-82-1180    X_Bassford    07:16:00    37.5    154    61    09:36:32    874-57-8352    V_Matyushenko    09:49:00    38.4    115    60    11:07:52    170-60-7747    T_Snowdon    13:25:00    38.9    121    85    14:55:16    161-03-2325    Q_Everson    13:31:00    39.4    124    76    13:50:07
            numMayorIdentificacion1 = numMayorIdentificacion2 =
                                      numMayorIdentificacion3 =
                                      cantAtenciones =
                                      cantPacientesPresionNormal =
                                      cantPacientesPresionHipertensionNivel2 = tiempoTotalAtenciones = 0;
            presionMediaMayor = costoTotalAtenciones = 0.00;
            while (true) {
                cin >> numIdentificacion1 >> c >> numIdentificacion2 >> c >> numIdentificacion3;
                cout << right << setfill('0') << setw(3) << numIdentificacion1 << setw(2) << numIdentificacion2 <<
                        setw(4) << numIdentificacion3 << setfill(' ') << setw(4) << "";
                imprimirNombrePaciente();
                cin >> hi >> c >> mini >> c >> si >> temperatura >> presionArterialSistolica >>
                        presionArterialDiastolica >> hf >> c >> minf >> c >> sf;
                imprimirDatosAtenciones(hi, mini, si, temperatura, presionArterialSistolica, presionArterialDiastolica,
                                        hf, minf, sf, costoAtencion, presionArterialMedia, nivelPresionArterial,
                                        numIdentificacion1, numIdentificacion2, numIdentificacion3,
                                        numMayorIdentificacion1, numMayorIdentificacion2, numMayorIdentificacion3,
                                        presionMediaMayor, cantAtenciones, cantPacientesPresionNormal,
                                        cantPacientesPresionHipertensionNivel2, tiempoTotalAtenciones,
                                        costoTotalAtenciones);
                if (cin.get() == '\n') break;
            }
            imprimirLinea('-', MAX_LINES);
            imprimirResumenCanal(numMayorIdentificacion1, numMayorIdentificacion2, numMayorIdentificacion3,
                                 presionMediaMayor, cantAtenciones, cantPacientesPresionNormal,
                                 cantPacientesPresionHipertensionNivel2, tiempoTotalAtenciones, costoTotalAtenciones);
            cantFinalAtenciones += cantAtenciones;
            tiempoFinalAtenciones += tiempoTotalAtenciones;
            costoFinalAtenciones += costoTotalAtenciones;
        } else {
            while (cin.get() != '\n');
        }
    }
    impresionFinal(cantFinalAtenciones, tiempoFinalAtenciones, costoFinalAtenciones);
}

void imprimirCabecera(int di, int mi, int ai, int df, int mf, int af) {
    cout << right << setw(75) << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    cout << setw(73) << "REGISTRO DE LOS ATENCIONES" << endl;
    cout << setw(65) << "ATENCIONES REALIZADAS ENTRE EL " << setfill('0') << setw(2) << di << "/" << setw(2) << mi <<
            "/" << ai << " Y EL " << setw(2) << df << "/" << setw(2) << mf << "/" << af << setfill(' ') << endl;
    imprimirLinea('=', MAX_LINES);
}

void imprimirCabeceraAtenciones(int dd, int mm, int aa) {
    cout << "FECHA:" << setw(4) << "" << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << aa <<
            setfill(' ') << endl;
    cout << "REGISTRO DE ATENCIONES:" << endl;
    imprimirLinea('-', MAX_LINES);
    cout << setw(65) << "DURACION DE LA" << setw(14) << "COSTO DE LA" << setw(35) << "PRESION ARTERIAL" << setw(20) <<
            "NIVEL DE LA" << endl;
    cout << "ID" << setw(16) << "NOMBRE" << setw(18) << "INGRESO" << setw(10) << "ALTA" << setw(15) << "ATENCION" <<
            setw(15) << "ATENCION" << setw(15) << "TEMPERATURA" << setw(15) << "MEDIA" << setw(30) << "PRESION ARTERIAL"
            << endl;
}

void imprimirDatosAtenciones(int hi, int mini, int si, double temperatura, int presionArterialSistolica,
                             int presionArterialDiastolica, int hf, int minf, int sf, double &costoAtencion,
                             double &presionArterialMedia, double &nivelPresionArterial, int numIdentificacion1,
                             int numIdentificacion2, int numIdentificacion3, int &numMayorIdentificacion1,
                             int &numMayorIdentificacion2, int &numMayorIdentificacion3,
                             double &presionMediaMayor, int &cantAtenciones, int &cantPacientesPresionNormal,
                             int &cantPacientesPresionHipertensionNivel2, int &tiempoTotalAtenciones,
                             double &costoTotalAtenciones) {
    int horaIngreso, horaAlta, duracionAtencion, hh, min, ss;
    horaIngreso = convertirHora(hi, mini, si);
    horaAlta = convertirHora(hf, minf, sf);
    duracionAtencion = horaAlta - horaIngreso;
    if (duracionAtencion < 0) duracionAtencion += 3600.00;
    costoAtencion = (duracionAtencion / 3600.00) * 575.00;
    presionArterialMedia = (presionArterialSistolica * presionArterialDiastolica) / 3.00;
    revertirHora(duracionAtencion, hh, min, ss);
    cout << setw(4) << "" << setfill('0') << setw(2) << hi << ":" << setw(2) << mini << ":" << setw(2) << si <<
            setfill(' ') << setw(4) << "" << setfill('0') << setw(2) << hf << ":" << setw(2) << minf << ":" << setw(2)
            << sf << setfill(' ') << setw(4) << "" << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" <<
            setw(2) << ss << setfill(' ') << setw(14) << fixed << setprecision(2) << costoAtencion << setw(15) << fixed
            << setprecision(2) << temperatura << setw(16) << presionArterialMedia;
    calcularNivelPresionArterial(presionArterialSistolica, presionArterialDiastolica, cantPacientesPresionNormal,
                                 cantPacientesPresionHipertensionNivel2);
    if (presionArterialMedia > presionMediaMayor) {
        numMayorIdentificacion1 = numIdentificacion1;
        numMayorIdentificacion2 = numIdentificacion2;
        numMayorIdentificacion3 = numIdentificacion3;
        presionMediaMayor = presionArterialMedia;
    }
    costoTotalAtenciones += costoAtencion;
    tiempoTotalAtenciones += duracionAtencion;
    cantAtenciones++;
}


void imprimirResumenCanal(int numMayorIdentificacion1, int numMayorIdentificacion2, int numMayorIdentificacion3,
                          double presionMediaMayor, int cantAtenciones, int cantPacientesPresionNormal,
                          int cantPacientesPresionHipertensionNivel2, int tiempoTotalAtenciones,
                          double costoTotalAtenciones) {
    int hh, min, ss;
    revertirHora(tiempoTotalAtenciones, hh, min, ss);
    cout << setw(20) << "RESUMEN DEL CANAL:" << endl;
    cout << setw(25) << "CANTIDAD DE ATENCIONES:" << cantAtenciones << endl;
    cout << setw(67) << "CANTIDAD DE PACIENTES CON NIVEL DE LA PRESION ARTERIAL EN NORMAL:" <<
            setw(4) << cantPacientesPresionNormal << endl;
    cout << setw(81) << "CANTIDAD DE PACIENTES CON NIVEL DE LA PRESION ARTERIAL EN HIPERTENSION NIVEL 2:" <<
            setw(4) << cantPacientesPresionHipertensionNivel2 << endl;
    cout << setw(44) << "PACIENTE CON MAYOR PRESION ARTERIAL MEDIA:" << setw(6) << numMayorIdentificacion1 << "-" <<
            numMayorIdentificacion2 << "-" << numMayorIdentificacion3 << " con " << presionMediaMayor << endl;
    cout << setw(42) << "TIEMPO TOTAL DESTINADO A LAS ATENCIONES:" << setw(6) << "" << setfill('0') << setw(2) << hh <<
            ":" << setw(2) <<
            min << ":" << setw(2) << ss << setfill(' ') << endl;
    cout << setw(33) << "COSTO TOTAL POR LAS ATENCIONES:" << setw(10) << fixed << setprecision(2) <<
            costoTotalAtenciones << endl;
    imprimirLinea('=', MAX_LINES);
}

void impresionFinal(int cantFinalAtenciones, int tiempoFinalAtenciones, double costoFinalAtenciones) {
    int hh, min, ss;
    revertirHora(tiempoFinalAtenciones, hh, min, ss);
    cout << "RESUMEN FINAL" << endl;
    cout << left << setw(3) << "" << "CANTIDAD DE ATENCIONES: " << cantFinalAtenciones << endl;
    cout << left << setw(3) << "" << "TIEMPO TOTAL DESTINADO A LAS ATENCIONES: " << right << setw(5) << "" <<
            setfill('0') << setw(2) << hh <<
            ":" << setw(2) <<
            min << ":" << setw(2) << ss << setfill(' ') << endl;
    cout << left << setw(3) << "" << "COSTO TOTAL POR LAS ATENCIONES: " << right << setw(8) << "" << fixed <<
            setprecision(2) << costoFinalAtenciones << endl;
}

void calcularNivelPresionArterial(int presionArterialSistolica, int presionArterialDiastolica,
                                  int &cantPacientesPresionNormal,
                                  int &cantPacientesPresionHipertensionNivel2) {
    //106/83
    if (presionArterialSistolica < 120 and presionArterialDiastolica < 80) {
        cout << setw(10) << presionArterialSistolica << "/" << presionArterialDiastolica << " (Normal)" << endl;
        cantPacientesPresionNormal++;
    } else {
        if ((presionArterialSistolica < 120 and presionArterialDiastolica > 80) or (
                presionArterialSistolica >= 120 and presionArterialSistolica <= 129 and presionArterialDiastolica <
                80)) {
            cout << setw(10) << presionArterialSistolica << "/" << presionArterialDiastolica << " (Elevada)" << endl;
        } else {
            if ((presionArterialSistolica >= 130 and presionArterialSistolica <= 139) or (
                    presionArterialDiastolica >= 80 and presionArterialDiastolica <= 89)) {
                cout << setw(10) << presionArterialSistolica << "/" << presionArterialDiastolica <<
                        " (Hipertension Nivel 1)" << endl;
            } else {
                if (presionArterialSistolica >= 140 or presionArterialDiastolica >= 90) {
                    cout << setw(10) << presionArterialSistolica << "/" << presionArterialDiastolica <<
                            " (Hipertension Nivel 2)" << endl;
                    cantPacientesPresionHipertensionNivel2++;
                }
            }
        }
    }
}

void imprimirNombrePaciente() {
    char c;
    cin >> ws;
    while (true) {
        c = cin.get();
        if (c == ' ') break;
        if (c == '_') c = ' ';
        if (c >= 'a' and c <= 'z') c = toupper(c);
        cout.put(c);
    }
}

int convertirFecha(int dd, int mm, int aa) {
    return aa * 10000 + mm * 100 + dd;
}

int convertirHora(int hh, int min, int ss) {
    return hh * 3600 + min * 60 + ss;
}

void revertirHora(int duracion, int &hh, int &min, int &ss) {
    hh = duracion / 3600;
    duracion -= hh * 3600;
    min = duracion / 60;
    duracion -= min * 60;
    ss = duracion;
}

void imprimirLinea(char car, int cantLineas) {
    for (int i = 0; i < cantLineas; i++) cout.put(car);
    cout << endl;
}
