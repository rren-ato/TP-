//
// Created by Renato on 3/09/2026.
//

#include "FuncionesAuxiliares.h"

void print_line(int width, char character) {
    cout << setw(width) << setfill(character);
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

void print_info_plate(char type_vehicle, int plate) {
    if (type_vehicle == 'P') {
        cout << setw(ANCHO_PARCIAL_REPORTE/N_COLUMMNS) << setw(' ')<< "PEQUEÑO";
    }
    else if (type_vehicle == 'M') {
        cout << setw(ANCHO_PARCIAL_REPORTE/N_COLUMMNS) << setw(' ')<< "MEDIANO";
    }
    else if (type_vehicle == 'G') {
        cout << setw(ANCHO_PARCIAL_REPORTE/N_COLUMMNS) << setw(' ')<< "GRANDE";
    }
    cout << type_vehicle << plate;
    generate_whitespaces((ANCHO_PARCIAL_REPORTE/N_COLUMMNS)-7);
}

void generate_whitespaces(int width) {
    cout << setw(width) << setfill(' ');
}

void print_lvl_of_urgency(char character_of_lvl, double &multa) {
    if (character_of_lvl == 'L') {
        cout << setw(ANCHO_PARCIAL_REPORTE/N_COLUMMNS) << "LEVE";
        multa = 158.33;
    }
    else if (character_of_lvl == 'G') {
        cout << setw(ANCHO_PARCIAL_REPORTE/N_COLUMMNS) << "GRAVE";
        multa = 516.75;
    }
    else if (character_of_lvl == 'M') {
        cout << setw(ANCHO_PARCIAL_REPORTE/N_COLUMMNS) << "MUY GRAVE";
        multa = 3920.25;
    }
    cout << setw(ANCHO_PARCIAL_REPORTE/N_COLUMMNS) << multa;
}

void analyse_and_print_price_increase_per_type(double multa, char type_vehicle , double &type_increase) {
    if (type_vehicle == 'P') {
        type_increase = multa * 27/1000;
    }
    else if (type_vehicle == 'M') {
        type_increase = multa * 117/1000;
    }
    else if (type_vehicle == 'G') {
        type_increase = multa * 153/1000;
    }
    cout << setw(ANCHO_PARCIAL_REPORTE/N_COLUMMNS) << setfill(' ') << type_increase;
}

void analyse_and_print_price_increase_per_date(double multa, int ticket_day , double &date_increase) {
    
}

void analyse_and_print_price_increase_per_time(double multa, int time_of_ticket , double &time_increase) {
    if (((4*60*60)+30*60) <= time_of_ticket or time_of_ticket < (11*60*60)+25*60) {
        time_increase = multa * 85/1000;
    }
    else if (((11*60*60)+25*60) <= time_of_ticket or time_of_ticket < ((20*60*60)+40*60)) {
        time_increase = multa * 58/1000;
    }
    else if ((20*60*60)+40*60 <= time_of_ticket or time_of_ticket < ((4*60*60)+30*60)) {
    time_increase = multa * 37/1000;
    }
    cout << setw(ANCHO_PARCIAL_REPORTE/N_COLUMMNS) << setfill(' ') << time_increase;
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
    print_line(ANCHO_REPORTE, '=');
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
    // cout << right<< setw((((int) 1.5*ANCHO_REPORTE)+11)/2) << "INCREMENTOS" << endl;
    cout << setw(ANCHO_REPORTE/2) << setfill(' ');
    cout << setw(ANCHO_REPORTE/4) << "INCREMENTOS" << endl;
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

void read_plate(char &type_vehicle, int &plate) {
    int p1_plate = 0, p2_plate = 0;
    char c;
    cin.get(type_vehicle);
    cout << type_vehicle;
    cin >> p1_plate >> c >> p2_plate;
    plate = p1_plate*100 + p2_plate;
}

void reporte_per_client(double &pago_total, double &pago_total_con_dni, int DNI) { //P599-629    12/12/2023  10:42:26      L
    // int cant_infracciones = 1; no se usa pero la mayoria de veces lo piden
    int ticket_day = 0, time_of_ticket = 0;
    char lvl_of_urgency, c;
    while (true) {
        int plate=0; //Valores que se resetean por placa
        double multa=0;
        double type_increase=0, date_increase=0, time_increase = 0, total_a_pagar_per_plate= 0;
        char type_vehicle;
        cin >> ws;
        read_plate(type_vehicle, plate);
        if (c =='\n' or c == '\r')break;  // \r es salto de un caracter de MAC
        cin >> ws;
        ticket_day = read_date();
        if (26022024 > ticket_day or ticket_day > 300125) continue; //seguimos en la iteracion pero saltamos
        cin >> ws;                                                      //lectura e impresion demás
        time_of_ticket = read_time();
        cin >> ws;
        cin >> lvl_of_urgency;
        cin.get(c);

        print_info_plate(type_vehicle, plate);
        print_date(ticket_day);
        generate_whitespaces(ANCHO_REPORTE/N_COLUMMNS - 10);
        print_time(time_of_ticket);
        // generate_whitespaces(); [lo tiene la funcion]
        print_lvl_of_urgency(lvl_of_urgency, multa);
        analyse_and_print_price_increase_per_type(multa, type_vehicle , type_increase);
        analyse_and_print_price_increase_per_date(multa, ticket_day , date_increase); //no lo entiendo
        analyse_and_print_price_increase_per_time(multa, time_of_ticket , time_increase);
        total_a_pagar_per_plate = multa + type_increase + date_increase + time_increase;
        cout << setw(ANCHO_PARCIAL_REPORTE/N_COLUMMNS) << setfill(' ') << total_a_pagar_per_plate << endl;
        pago_total = total_a_pagar_per_plate;
        pago_total_con_dni = total_a_pagar_per_plate*100000000 + DNI;
    }


}

void reporte_parcial(double &mayor_pago_con_dni, double &menor_pago_con_dni) { //Guardo el dni junto al monto :D
    int i =1, DNI = 0;
    char c;
    int contador_de_enterprise = 1; // enterprise = empresa por las dudas
    while (not cin.eof()) {
        cout << "COMPAÑIA No. " << i << endl;
        cout << "REPRESENTANTE LEGAL: ";
        cin >> DNI;
        read_and_print_name_without_arr_cad();

        cout << "DNI: " << DNI << endl; //88167677
        print_line(ANCHO_REPORTE, '-');
        cout << "VEHICULOS INFRACCIONADOS: ";
        print_datta_header();
        while (c != '\0'){ //este caracter es el fin de archivo (mismo a eof())
            double pago_total = 0, pago_total_con_dni = 0;
            //P599-629    12/12/2023  10:42:26      L
            reporte_per_client(pago_total, pago_total_con_dni, DNI);
            if (contador_de_enterprise == 1) {
                menor_pago_con_dni = pago_total_con_dni;
            }
            else if (pago_total_con_dni < menor_pago_con_dni) {
                menor_pago_con_dni = pago_total_con_dni;
            }
            else if (mayor_pago_con_dni < pago_total_con_dni) {
                mayor_pago_con_dni = pago_total_con_dni;
            }
            contador_de_enterprise++ ;
            print_line(ANCHO_REPORTE, '_');
            cout << "PAGO TOTAL: " << pago_total << endl; //Hubo una aclaracion en el mismo  lab / era muy largo

            cin.get(c); //espaciado luego del nivel
        }
        i++;
    }

}

void reporte_final() {
    double mayor_pago_con_dni = 0.0, menor_pago_con_dni= 0.0;
    double mayor_pago = 0.0, menor_pago=0.0;
    double DNI_mayor_pago = 0, DNI_menor_pago =0;
    print_header();
    reporte_parcial(mayor_pago_con_dni, menor_pago_con_dni);
    mayor_pago = mayor_pago_con_dni /100000000;
    DNI_mayor_pago = (mayor_pago_con_dni - mayor_pago*100000000)*10000000000;
    menor_pago = mayor_pago_con_dni /100000000;
    DNI_menor_pago = (menor_pago_con_dni - menor_pago*100000000)*10000000000;
    //ESTADISTICA
    cout << endl;
    cout << "COMPAÑIA CON MAYOR PAGO POR INFRACCIONES: " << endl;
    cout << left << "DNI: " << right << setw(12) << fixed << setprecision(1) << DNI_mayor_pago << endl;
    cout << left << "TOTAL PAGADO: " << right << setw(3) << mayor_pago << endl;
    print_line(50, '/');
    cout << "COMPAÑIA CON MENOR PAGO POR INFRACCIONES: " << endl;
    cout << left << "DNI: " << right << setw(12) << fixed << setprecision(1) << DNI_menor_pago << endl;
    cout << left << "TOTAL PAGADO: " << right << setw(3) << menor_pago << endl;
    print_line(50,'/');
}