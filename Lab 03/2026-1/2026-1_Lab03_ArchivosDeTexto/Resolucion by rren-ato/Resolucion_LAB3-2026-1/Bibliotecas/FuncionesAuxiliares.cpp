//
// Created by Renato on 17/09/2026.
//

#include "FuncionesAuxiliares.h"


// * ESTAS SON LAS LECTURAS CORRECTAS DE LECTURA PARA LAB3
//! EN ESTAS FUNCIONES SE PEGA DIRECTAMENTE EL PATH DEL ARCHIVO
bool openFiles(ifstream &input_clinica, ifstream &input_pacientes, ifstream &input_triaje, ofstream &output) {
    input_clinica.open("ArchivosDeDatos/ClinicaDeUrgencias_TP_L3.txt", ios::in);
    input_pacientes.open("ArchivosDeDatos/Pacientes_TP_L3_registros.json", ios::in);
    input_triaje.open("ArchivosDeDatos/Triaje_TP_L3.csv", ios::in);
    output.open("ArchivosDeReporte/reporte.txt", ios::out);
    return input_clinica.is_open() and input_pacientes.is_open() and input_triaje.is_open() and output.is_open();
}

void closeFiles(ifstream &input_clinica, ifstream &input_pacientes, ifstream &input_triaje, ofstream &output) {
    input_clinica.close();
    input_pacientes.close();
    input_triaje.close();
    output.close();
}

//
//! AHORA UNO DEBE DE IDENTIFICAR QUE FUNCIONES LEEN O CUALES IMPRIMEN
//* SIN ESO NO SABES DONDE VERIDICAMENTE USAR INPUT O OUTPUT (EXPLICAR)
void generate_whitespaces(ofstream &output, int width) {
    for (int i=0; i<=width; i++) output.put(' '); //? archivo << setw(ancho) << ' ' << setfill(' ')
}

void print_line(ofstream &output,int width, char character) { //? '-' / '_' / '='
    for (int i=0; i<=width; i++) output.put(character);
    output << endl;
}

void ignorar_coma(ifstream &input) { //? input << sep << dato
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

void print_date(ofstream &output, int date, int width) {
    int day, month, year;
    year = date /10000;
    month = (date/100) % 100;
    day = date %100;
    //TODO ESTO ABARCA 10 CARACTERES
    output << setw(2) << setfill( '0') << day << '/' <<
        setw(2) << setfill( '0') << month << '/' <<
            setw(4) << setfill( '0') << year << setfill(' ');
    //* GENERAR ESPACIADO
    int espacios_en_blanco = width - 10;
    generate_whitespaces(output, espacios_en_blanco);
}

int read_time(ifstream &input) {
    int mm, ss, hh, time;
    char c;
    input >> hh >> c >> mm >> c >> ss;
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
            setw(2) << setfill( '0') << sec << setfill(' ');
    //* GENERAR ESPACIADO
    int espacios_en_blanco = width - 8;
    generate_whitespaces(output, espacios_en_blanco);
}

int read_DNI(ifstream &input) {
    //! 298-10-7060 <--- tener cuidado de como te dan el DNI (vino diferente a lo usual [xxx-xxx-xxx])
    int p1, p2, p3, DNI;
    char c;
    input >> p1 >> c >> p2 >> c >> p3;
    DNI = p1*1000000 + p2*10000 + p3;
    return DNI;
}

void read_and_print_name_without_arr(ifstream &input,ofstream &output, int width) {
    //Dunston/Rossoni-P."
    char c;
    int contador_character = 0;
    input.get(c); //Entra el primer character
    while (c != '.') {
        output.put(c);
        contador_character++;
        input.get(c);
    }
    //* GENERAR ESPACIADO
    output << setw(width - contador_character) << setfill( ' ');
}

void leer_clinica(ifstream &input, ifstream &input_pacientes, ifstream &input_triaje, ofstream &output) {
    //* POR UN DIA PODEMOS LEER MAS DE UN PACIENTE
    //! 1/04/2023    01:21:00    463-17-9883    03:13:54    268.65
    //!              02:45:00    332-44-9371    04:57:00    840.51
    int fecha_registro=0, hora_ingreso=0, dni = 0, hora_salida=0;
    double costo_atencion_por_hora=0.0;
    char sexo_paciente; int edad_paciente=0;
    fecha_registro = read_date(input);
    //* LECTURA POR DIA DE ATENCION
    while (true) {
        if (input.eof())break;
        if (input.peek()=='\n') break;
        hora_ingreso = read_time(input);
        dni = read_DNI(input);
        hora_salida = read_date(input);
        input >> costo_atencion_por_hora;
        get_data_pacientes(input_pacientes, output, dni, sexo_paciente, edad_paciente);
        get_data_triaje(input_triaje, fecha_registro, dni);
    }

}
//* NO CONFUNDIR CON EL SEARCH QUE SE VERA EN ARREGLOS
void get_data_pacientes(ifstream &input, ofstream &output, int &dni, char &sexo_paciente, int &edad_paciente) {
    //* PEsearch_pacientes(ifstream &input, int &dni)RO SOLO SE LEE HASTA ID - SI NO, NO PUEDES LEER LO DEMAS
    //! {"id": 1, "dni": "469-84-4163", "nombre": "Dunston/Rossoni-P.", "sexo": "F", "edad": 47}
    input.clear();
    input.seekg(0, ios::beg);
    int dni_pacientes =0;
    while (true) {
        if (input.peek()=='{') {
            input.ignore(1000, ':'); //? {"id":
            input.ignore(1000, ':'); //?  1, "dni":
            input.ignore(10000, '"');
        }
        input >> dni_pacientes;
        if (dni_pacientes==dni) {
            input.ignore(10000, ':');
            input.ignore(10000, '"');
            read_and_print_name_without_arr(input, output, dni);
            input.ignore(10000, ':');
            input.ignore(1000,'"');
            input >> sexo_paciente;
            input.ignore(10000, ':');
            input >> edad_paciente;
            break;
        }
        input.ignore(10000, '\n');
    }

}

void get_data_triaje(ifstream &input, int &fecha_registro, int &dni) {
    //* PERO SOLO SE LEE HASTA ID - SI NO, NO PUEDES LEER LO DEMAS
    //! 6/04/2023,635-96-2790,86,120,62,39.2,98
    int dia_triaje=0, dni_triaje=0;
    int dni_pacientes =0;
    if (input.peek()=='#') {
        input.ignore(10000, '\n'); //? {"id":
    }
    dia_triaje = read_date(input);
    ignorar_coma(input);
    dni_triaje = read_DNI(input);
    ignorar_coma(input);
    if (dia_triaje==fecha_registro and dni_pacientes==dni) {


    }
}

