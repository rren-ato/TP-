//
// Created by Renato on 23/08/2026.
//

#include "FuncionesAuxiliares.h"



void print_line(char character) {
    for (int i=0; i< ANCHO_REPORTE; i++) cout << character;
    cout << endl;
}

void print_title() {
    cout <<setw(ANCHO_TITULO) << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    cout <<setw(ANCHO_TITULO) << "REGISTRO DE LAS ATENCIONES" << endl;
    cout <<setw(ANCHO_TITULO) << "ATENCIONES REALIZADAS ENTRE EL 05/04/2023 Y EL 27/04/2023" << endl;
}

void print_header() {
    //PARTE DE ARRIBA
    generate_whitespaces(ANCHO_REPORTE*4/N_COLUMMNS);
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << "DURACION DE LA" << setfill(' ');
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) <<"COSTO DE LA" << setfill(' ');
    generate_whitespaces(ANCHO_REPORTE/N_COLUMMNS);
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << "PRESION ARTERIAL" << setfill(' ');
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << "NIVEL DE LA" << setfill(' ') << endl;
    //PARTE DE ABAJO
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << "ID" << setfill(' ');
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << "NOMBRE" << setfill(' ');
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << "INGRESO" << setfill(' ');
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << "ALTA" << setfill(' ');
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << "ATENCION" << setfill(' ');
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << "TEMPERATURA" << setfill(' ');
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << "MEDIA" << setfill(' ');
    cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << "PRESION ARTERIAL" << setfill(' ') << endl;;
}

void generate_whitespaces(int width) {
    for (int i=0; i<=width; i++) cout << ' ';
}


int read_date() {
    // 1/04/2023
    int dd, mm, yyyy, date;
    char c;
    cin >> dd >> c >> mm >> c >> yyyy;
    date = yyyy*10000 + mm*100 + dd; //20230401
    return date;
}

void print_date(int date) {
    int day, month, year;
    year = date / 10000;
    month = (date/100) % 100;
    day = date % 100;
    cout << setw(2) << setfill('0') << day << '/';
    cout << setw(2) << setfill('0') << month;
    cout << "/" << year << setfill(' ') << endl; //01/04/2023
}

int read_ID() {
    //766-20-3662
    int p1, p2, p3, DNI;
    char c;
    cin >> p1 >> c >> p2 >> c >> p3;
    DNI = p1*1000000 + p2*10000 + p3; //766203662
    return DNI;
}

void print_ID(int DNI) {
    int P_1, P_2, P_3;
    P_1 = DNI /1000000;
    P_2 = (DNI/ 10000)%100;
    P_3 = DNI%10000;
    cout << setw(3) << setfill('0') << P_1 << "-" <<
        setw(2) << setfill('0') << P_2 << "-" <<
            setw(4) << setfill('0') << P_3;
}

void read_and_print_name_without_arr_cad() {
    //N_Sparsholt
    int i =1;
    char c;
    cin >> c; //1 = PRIMERA LETRA EN MAYUSCULA
    cout << left << c;
    cin.get(c); //
    while (c != ' ') { // 2 = '_' y 3 es otra letra en mayuscula

       if (c == '_') {
           cout << ' ';
       }
       else {
           if (c >= 'a' and c <= 'z'){
               c = c - 'a' + 'A'; // guia del ASCII (suma para mayusculas)
           }
           cout << c;
       }

        cin.get(c); //Obtencion del caracter dentro del bucle
        i++;
    }
    while (i < ANCHO_REPORTE/N_COLUMMNS) {
        cout << ' ';
        i++;
    }
    cin.clear();
}

int read_time() {
    //01:13:00
    int hh, mm, ss, time;
    char c;
    cin >> hh >> c >> mm >> c >> ss;
    time = hh*3600 + mm*60 + ss; // El tiempo pero en segundos
    return time;
}

void print_time(int time) {
    int sec, min, hour;
    hour = time / 3600;
    min = (time / 60) % 60;
    sec = time % 60;

    cout  << right << setfill('0') << setw(2) << hour <<
        ':' << setw(2) << min <<
             ':' << setw(2) << sec << setfill(' ');
    for (int i=8; i< ANCHO_REPORTE/N_COLUMMNS; i++) {
        cout << ' ';
    }
}

void filter_of_lvl_pressure(double sistolic_pressure, double diastolic_pressure, int *cant_pac_normal_prs,
                            int *cant_pac_HP2_prs) {

    bool valid_interval_1;
    valid_interval_1 = (sistolic_pressure < 120 and 80 < diastolic_pressure)
                        or  120 <= sistolic_pressure and sistolic_pressure <= 129 and diastolic_pressure < 80;

    if ( sistolic_pressure < 120 and diastolic_pressure < 80 ) {
        (*cant_pac_normal_prs)++;
        cout << "(Normal)" << endl;
    }
    if (valid_interval_1 == true) {
        cout << "(Elevada)" << endl;
    }
    if ((130 <= sistolic_pressure and sistolic_pressure <= 139) or 80 <= diastolic_pressure and diastolic_pressure<=89){
        cout << "(Hipertensión Nivel 1)" << endl;
    }
    if ((140 <= sistolic_pressure) or 90 <= diastolic_pressure) {
        (*cant_pac_HP2_prs)++;
        cout << "(Hipertensión Nivel 2)" << endl;
    }
}

void reporte_parcial(int *cant_pac_normal_prs, int *cant_pac_HP2_prs, int *duracion_total,
                    double *low_ranked_prs_ammount, int *low_ranked_prs_pac) {
    int fecha = 0, DNI = 0, hora_entrada = 0, hora_salida = 0, duracion = 0;
    double temperature = 0.0, sistolic_pressure =0.0,diastolic_pressure =0.0,middle_pressure =0.0, costo_atencion=0.0; // 1/04/2023
    double last_middle_pressure = 0.0;
    char c;
    fecha = read_date();
    cout << "FECHA: ";
    print_date(fecha);
    cout << "REGISTRO DE ATENCIONES:" << endl;
    print_line('-');
    print_header();
    //  LECTURA DE DATOS POR DIA
    while (true) {
        if (c == '\n') break;
        cin >> ws; // esto permite asegurarse de no leer espacios en blanco (whitespaces)
        //766-20-3662
        DNI = read_ID();
        if (cin.eof())break; //Se puede usar siempre y cuando leas algo antes
        cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << DNI << setfill(' ');

        cin >> ws;
        //N_Sparsholt
        read_and_print_name_without_arr_cad();

        cin >> ws;
        //01:13:00
        hora_entrada = read_time(); // -> print_time(hora_entrada);

        //LECTURA DE DATOS DOUBLE
        //39.5
        cin >> temperature;
        cin >> ws;
        //104
        cin >> sistolic_pressure;
        cin >> ws;
        //61
        cin >> diastolic_pressure;

        cin >> ws;
        //01:50:47
        hora_salida = read_time(); // -> print_time(hora_salida);

        //Impresion
        print_time(hora_entrada);
        print_time(hora_salida);
        if (hora_entrada > hora_salida) {
            duracion = hora_salida + (12*60*60) - hora_entrada;
        }
        else {
            duracion = hora_salida - hora_entrada;
        }
        print_time(duracion);
        costo_atencion = duracion * (575.00/3600); //Consiguiendo el tiempo de duracion total, sirve mas que trabajar asi ( -> reporte final)
        middle_pressure = (sistolic_pressure + 2*diastolic_pressure)/3;
        //Si encuentra uno mas pequeño se actualiza
        if (middle_pressure < last_middle_pressure) {
            *low_ranked_prs_ammount = middle_pressure;
            *low_ranked_prs_pac = DNI;
        }
        last_middle_pressure = middle_pressure; //actualizacion de valores
        cout << setprecision(3);
        cout << left << setw(ANCHO_REPORTE/N_COLUMMNS) << costo_atencion << setfill(' '); //para arreglar justificado (LEFT)
        cout << setw(ANCHO_REPORTE/N_COLUMMNS) << temperature << setfill(' ');
        cout << setw(ANCHO_REPORTE/N_COLUMMNS) << middle_pressure << setfill(' ');
        cout  << sistolic_pressure << '/' << diastolic_pressure << ' '; // No es necesario colocar setw (ya es lo final)

        //AYUDA PARA LA ESTADISTICA
        filter_of_lvl_pressure(sistolic_pressure, diastolic_pressure, cant_pac_normal_prs,
                                cant_pac_HP2_prs);
        *duracion_total = duracion + *duracion_total;
        cin.get(c);
    }
    cin.clear();
    print_line('-');
}


void reporte_final() {
    int cant_atenciones =0, cant_pac_normal_prs=0, cant_pac_HP2_prs=0, at_total_ammount_of_time=0;
    double low_ranked_prs_ammount = 0;
    int low_ranked_prs_pac = 0;
    double total_price_of_at=0;
    total_price_of_at = at_total_ammount_of_time * 575.00 / 3600;

    print_title();
    while (not cin.eof()) {
        at_total_ammount_of_time=0;
        //Aseguramos que lea solo hasta el fin de archivo
        if (cin.eof()) break;
        print_line('=');

        //internamente es por dia
        reporte_parcial(&cant_pac_normal_prs, &cant_pac_HP2_prs,&at_total_ammount_of_time,
                    &low_ranked_prs_ammount, &low_ranked_prs_pac);

        total_price_of_at = at_total_ammount_of_time * 575.00 / 3600;


        cant_atenciones++;
        //Estadistica
        generate_whitespaces(WHITESPACES_WIDTH);
        cout << "RESUMEN DEL CANAL: " << endl;
        generate_whitespaces(WHITESPACES_WIDTH);
        cout << "CANTIDAD DE ATENCIONES: " << cant_atenciones << endl;
        generate_whitespaces(WHITESPACES_WIDTH);
        cout << "CANTIDAD DE PACIENTES CON NIVEL DE LA PRESION ARTERIAL EN NORMAL: " << cant_pac_normal_prs << endl;
        generate_whitespaces(WHITESPACES_WIDTH);
        cout<<"CANTIDAD DE PACIENTES CON NIVEL DE LA PRESION ARTERIAL EN HIPERTENSION NIVEL 2: " <<cant_pac_HP2_prs << endl;
        generate_whitespaces(WHITESPACES_WIDTH);
        cout << "PACIENTE CON MENOR PRESION ARTERIAL MEDIA: ";
        print_ID(low_ranked_prs_pac);
        cout << " con " << low_ranked_prs_ammount << endl;
        generate_whitespaces(WHITESPACES_WIDTH);
        cout << "TIEMPO TOTAL DESTINADO A LAS ATENCIONES: ";
        print_time(at_total_ammount_of_time);
        cout << endl;
        generate_whitespaces(WHITESPACES_WIDTH);
        cout << "COSTO TOTAL POR LAS ATENCIONES: ";
        generate_whitespaces(9);
        cout << setprecision(4) << total_price_of_at << endl;
    }
}

// 1/04/2023    766-20-3662    N_Sparsholt    01:13:00    39.5    104    61    01:50:47













