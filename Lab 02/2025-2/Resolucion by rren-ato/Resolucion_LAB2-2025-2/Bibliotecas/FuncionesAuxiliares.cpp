//
// Created by Renato on 10/09/2026.
//

#include "FuncionesAuxiliares.h"
// # registration_date,channel_id,channel_name,metric1,metric2,metric3,stream_date,stream_duration,peak_viewers
// 01/04/2021,F3765,Fextralife,1734810,93036735,222720,16/07/2025,00:25:55,1396

void open_read_file(ifstream &input, const char* file_name) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "El archivo " << file_name << " no se pudo leer" << endl;
        exit(1);
    }
}

void open_write_file(ofstream &output, const char* file_name) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        output << "El archivo " << file_name << " no se pudo abrir" << endl;
        exit(1);
    }
}
//! AHORA UNO DEBE DE IDENTIFICAR QUE FUNCIONES LEEN O CUALES IMPRIMEN
void print_line(ofstream &output,int width, char character) {
    output << setw(ANCHO_REPORTE) << setfill( ' ') << endl;
}

void ignorar_coma(ifstream &input) {
    char c;
    input.get(c);
}

int read_date (ifstream &input) {
    //12/12/2023
    int dd, mm, yyyy, date;
    char c;
    input >> dd >> c >> mm >> c >> yyyy;
    date = yyyy*10000 + mm*100 + dd;
    return date;
}

void print_date(int date, ofstream &output) {
    int day, month, year;
    year = date /10000;
    month = (date/100) % 100;
    day = date %100;
    //TODO ESTO ABARCA 10 CARACTERES
    output << setw(2) << setfill( '0') << date <<
        setw(2) << setfill( '0') << month <<
            setw(4) << setfill( '0') << year;
    //* GENERAR ESPACIADO
    cout << setw((ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS)-10) << setfill( ' ');
}

int read_time(ifstream &input) {
    int mm, ss, hh, time;
    char c;
    input >> mm >> c >> ss >> c >> hh;
    time = hh*3600 + mm*60 + ss;
    return time;
}

void print_time(ofstream &output, int width, int time) {
    int hour, min, sec;
    hour = time / 3600;
    min = (time / 60) % 60;
    sec = time % 60;
    output << setw(2) << setfill( '0') << hour << ':' <<
        setw(2) << setfill( '0') << min << ':' <<
            setw(2) << setfill( '0') << sec;
    //* GENERAR ESPACIADO
    output << setw(width - 8) << setfill( ' ');
}

//! Se debe leer la coma antes de invocar a esta funcion
void read_and_print_name_without_arr(ifstream &input,ofstream &output, int width) {
    //CONTRERAS/CHANG/JOHANA-CINTHIA,
    char c;
    int contador_character = 0;
    input.get(c); //Entra el primer character
    while (c != ',') {
        output.put(c);
        contador_character++;
        input.get(c);
    }
    output << setw(width - contador_character) << setfill( ' ');
}

void registro_por_canal(ifstream &input, ofstream &output) {
//  01/04/2021,F3765,Fextralife,1734810,93036735,222720,16/07/2025,00:25:55,1396
    char char_code_stream;
    int int_code_stream, date_of_account=0, new_follows_of_month=0, new_views_of_month=0, max_ammount_of_chat=0;
    char char_code_leido; int int_code_leido=0, date_of_account_leido=0;
    while (true) {
        //! IGNORAR LA PRIMERA FILA QUE ESTA EN COMMITS
        if (input.peek() == '#') input.ignore(10000,'\n');
        //! BREAK SI SE CONSIGUE EL FIN DE ARCHIVO
        if (input.peek() ==  EOF) break;
        date_of_account = read_date(input);
        if (20221009 < date_of_account and date_of_account < 20230101) {
            ignorar_coma(input);
            input >> char_code_stream >> int_code_stream;
            ignorar_coma(input);
            read_and_print_name_without_arr(input, output, ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS);
            output << char_code_stream << int_code_stream <<
                setw((ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS)-5) << setfill( ' ');
            ignorar_coma(input);
            print_date(date_of_account, output);
            ignorar_coma(input);
            input >> new_follows_of_month;
            ignorar_coma(input);
            input >> new_views_of_month;
            ignorar_coma(input);
            input >> max_ammount_of_chat; //me refiero a la cantidad de personas en el chat - livestream
            procesar_informacion(input, output);

            //Se necesita comparar la fecha para comparar el codigo, luego ignorar todo lo demás
            while (true) {
                if (input.peek() ==  EOF) break;
                ignorar_coma(input);
                if (char_code_leido == char_code_stream and int_code_leido == int_code_stream) {}


            }

        }
        else {
            input.ignore(10000,'\n');
        }
    }
}
