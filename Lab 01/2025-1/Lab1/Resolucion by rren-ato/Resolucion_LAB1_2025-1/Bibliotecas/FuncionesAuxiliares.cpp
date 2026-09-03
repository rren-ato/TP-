//
// Created by Renato on 3/09/2026.
//

#include "FuncionesAuxiliares.h"

void print_line(int width) {
    cout << setw(width) << setfill(' ');
    cout << endl;
}

int read_date() {
    // 1/04/2023
    int dd, mm, yyyy, date;
    char c;
    cin >> dd >> c >> mm >> c >> yyyy;
    date = yyyy*10000 + mm*100 + dd; //20240128
    return date;
}

void print_date(int date) {
    int day, month, year;
    year = date / 10000;
    month = (date/100) % 100;
    day = date % 100;
    cout << setw(2) << setfill('0') << day << '/';
    cout << setw(2) << setfill('0') << month;
    cout << "/" << year << setfill(' ') << endl; //28/01/2024    25/02/2025
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



void print_header() {
    int dia_limite_inf =0, dia_limite_sup =0;
    cout << setw((ANCHO_REPORTE + 24)/2) << "MINISTERIO DE TRANSPORTE" << endl;
    cout << setw((ANCHO_REPORTE + 24)/2) << "MULTAS IMPUESTAS A LAS COMPANIAS" << endl;
    dia_limite_inf = read_date();
    dia_limite_sup = read_date();
    cout << setw((ANCHO_REPORTE + 24)/2) << "RANGO DE FECHAS A CONSIDERAR: DEL ";
    print_date(dia_limite_inf);
    cout << " AL ";
    print_date(dia_limite_sup);
    cout << endl;
    print_line(ANCHO_REPORTE);
}

void read_and_print_name_without_arr_cad() { //Paso todo a mayusculas btw
    //Contreras/Chang/Johana-Cinthia
    int i =1;
    char c;
    cin >> c; //1 = PRIMERA LETRA EN MAYUSCULA
    cout << left << c;
    while (c != ' ') { //Fin de la cadena (entre comillas)
        if (c == '/') { //Espaciado
            cout << ' ';
        }
        else {
            if (c >= 'a' and c <= 'z'){
                c = c - 'a' + 'A'; // guia del ASCII (resta para mayusculas)
            }
            cout << c;
        }

        cin.get(c); //Obtencion del caracter dentro del bucle
        i++;
    }
    while (i < ANCHO_NOMBRE) {
        cout << ' ';
        i++;
    }
    cin.clear();
}

void print_datta_header() {
    cout << setw(2) << setfill(' '); // generate whitespaces
    cout << setw(ANCHO_PARCIAL_REPORTE) << "TIPO";
    cout << setw(ANCHO_PARCIAL_REPORTE) << "PLACA";
    cout << setw(ANCHO_PARCIAL_REPORTE) << "FECHA";
    cout << setw(ANCHO_PARCIAL_REPORTE) << "HORA";
    cout << setw(ANCHO_PARCIAL_REPORTE) << "GRAVEDAD";
    cout << setw(ANCHO_PARCIAL_REPORTE) << "MULTA";
    cout << setw(ANCHO_PARCIAL_REPORTE) << "POR TIPO";
    cout << setw(ANCHO_PARCIAL_REPORTE) << "POR FECHA";
    cout << setw(ANCHO_PARCIAL_REPORTE) << "POR HORA";
    cout << setw(ANCHO_PARCIAL_REPORTE) << "TOTAL A PAGAR" << endl;
}

void read_plate() {
    char c;
    cin.get(c);
    cout << c;
    while (c != ' ') {
        cin.get(c);
        if (c == '-') cout << ' ';
        else cout << c;
    }
}

void reporte_per_client() { //P599-629    12/12/2023  10:42:26      L
    int cant_infracciones = 1;
    int ticket_day = 0, time_of_ticket = 0;
    while (true) {
        cin >> ws;
        read_plate();
        if (cin.eof())break;
        cin >> ws;
        ticket_day = read_date();
        time_of_ticket = read_time();

        print_date(ticket_day);
        generate_whitespaces(ANCHO_REPORTE/N_COLUMMNS - 10);
        print_time(time_of_ticket);
        // generate_whitespaces(); [lo tiene la funcion]
    }


}

void reporte_parcial() {
    int i =1, DNI = 0;
    char c;
    while (not cin.eof()) {
        cout << "COMPAÑIA No. " << i << endl;
        cout << "REPRESENTANTE LEGAL: ";
        read_and_print_name_without_arr_cad();
        cin >> DNI;
        cout << "DNI: " << DNI << endl;
        print_line(ANCHO_REPORTE);
        cout << "VEHICULOS INFRACCIONADOS: ";

        cout << right<< setw((((int) 1.5*ANCHO_REPORTE)+11)/2) << "INCREMENTOS" << endl;
        print_datta_header();
        while (c == '\n' or c == '\r'){
            //P599-629    12/12/2023  10:42:26      L
            reporte_per_client();
            cin.get(c); //espaciado luego del nivel
        }


        i++;
    }

}