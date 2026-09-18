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
    //! Dunston/Rossoni-P."
    char c;
    int contador_character = 0;
    input.get(c); //Entra el primer character
    while (c != '.') {
        if (c == '/' or c == '-') c = ' ';
        if ('a' <= c or c >= 'z') c = c - 'a' +'A';
        output.put(c);
        contador_character++;
        input.get(c);
    }
    //* GENERAR ESPACIADO
    output << setw(width - contador_character) << setfill( ' ');
}

int calcular_duracion(int hora_ingreso, int hora_salida) {
    int duracion=0;
    if (hora_ingreso > hora_salida) {
        duracion = (hora_salida+24*60*60) - hora_ingreso;
    }
    else {
        duracion = hora_salida - hora_ingreso;
    }
    return duracion;
}

double calculo_monto_final(double costo_atencion_por_hora, double duracion_atencion, int edad_paciente) {
    double costo_parcial= 0.0, descuento = 0.0, costo_final= 0.0;
    costo_parcial = (costo_atencion_por_hora/3600) * duracion_atencion;
    if (edad_paciente <= 18) descuento = costo_parcial * 5/100;
    else if (edad_paciente >= 64) descuento = costo_parcial * 18/100;
    costo_final = costo_parcial - descuento;
    return costo_final;
}

void print_header(ofstream &output) {
    output << right << setw((ANCHO_REPORTE+30)/2) << "CLINICA DE URGENCIAS TP_SALUD" << setfill(' ') << endl;
    output << right << setw((ANCHO_REPORTE+22)/2) << "REGISTRO DE ATENCIONES" << setfill(' ') << endl;
}

void print_header_of_date(ofstream &output, int fecha_registro) {
    print_line(output, ANCHO_REPORTE, '=');
    output << left << "FECHA:  ";
    print_date(output, fecha_registro, 10);
    output << endl;
    output << "PACIENTES ATENDIDOS:" << right << endl;
    print_line(output, ANCHO_REPORTE, '-');
}

void print_pacientes_info(ofstream &output, int edad_paciente, char sexo_paciente) {
    //*IMPRESION
    generate_whitespaces(output, 4); output << "EDAD: " << edad_paciente;
    generate_whitespaces(output,8); output << "SEXO: ";
    if (sexo_paciente == 'F') output << "FEMENINO" << endl;
    else if (sexo_paciente == 'M') output << "MASCULINO" << endl;
}

void print_triaje_info(ofstream &output, double temperatura_triaje, int presion_sistolica_triaje,
                       int presion_diastolica_triaje, double costo_atencion_por_hora, int duracion_atencion,
                       double costo_final) {
    generate_whitespaces(output, 5); output << "SIGNOS VITALES: " << endl;
    generate_whitespaces(output, 5);output << "TEMPERATURA: " << fixed << setprecision(2) << temperatura_triaje;
    generate_whitespaces(output, 5); output << "PRESION SISTOLICA: " << presion_sistolica_triaje;
    generate_whitespaces(output, 5); output << "PRESION DIASTOLICA: " << presion_diastolica_triaje << endl;
    output << "ATENCION: " << endl;
    output << "COSTO POR HORA SEGUN LA ESPECIALIDAD: " << fixed << setprecision(2) << costo_atencion_por_hora;
    generate_whitespaces(output, 5); output << "DURACION: "; print_time(output, 13,duracion_atencion);
    output << "COSTO TOTAL: " << costo_final << endl;
}

void leer_clinica_Y_Generar_reporte(ifstream &input_clinica, ifstream &input_pacientes, ifstream &input_triaje,
                                    ofstream &output) {
    //* POR UN DIA PODEMOS LEER MAS DE UN PACIENTE
    //! 1/04/2023    01:21:00    463-17-9883    03:13:54    268.65
    //!              02:45:00    332-44-9371    04:57:00    840.51
    int fecha_registro=0, hora_ingreso=0, dni = 0, hora_salida=0, duracion_atencion=0;
    double costo_atencion_por_hora=0.0, costo_final= 0.0;
    char sexo_paciente; int edad_paciente=0;
    int frecuencia_cardiaca_triaje=0 , presion_sistolica_triaje= 0, presion_diastolica_triaje= 0;
    int saturacion_oxigeno_triaje=0; double temperatura_triaje=0; bool paciente_valido;
    print_header(output);
    while (true) {
        int contador_paciente=0;
        fecha_registro = read_date(input_clinica);
        if (input_clinica.eof()) break;
        print_header_of_date(output, fecha_registro);
        //* LECTURA POR DIA DE ATENCION
        while (true) {
            if (input_clinica.eof())break;
            if (input_clinica.peek()=='\n') break;
            input_clinica >> ws;
            hora_ingreso = read_time(input_clinica);
            dni = read_DNI(input_clinica);
            input_clinica >> ws;
            hora_salida = read_time(input_clinica);
            input_clinica >> costo_atencion_por_hora;
            //* CALCULO DE LA DURACION
            duracion_atencion = calcular_duracion(hora_ingreso, hora_salida); //? RESULTADO EN SEGUNDOS
            get_data_pacientes(input_pacientes, output, dni, sexo_paciente, edad_paciente,
                                contador_paciente);
            print_pacientes_info(output, edad_paciente, sexo_paciente);
            get_data_triaje(input_triaje, fecha_registro, dni, frecuencia_cardiaca_triaje,
                         presion_sistolica_triaje, presion_diastolica_triaje, temperatura_triaje,
                         saturacion_oxigeno_triaje, paciente_valido);
            //* CALCULO DEL COSTO FINAL
            costo_final = calculo_monto_final(costo_atencion_por_hora, duracion_atencion, edad_paciente);
            print_triaje_info(output, temperatura_triaje, presion_sistolica_triaje,
                       presion_diastolica_triaje, costo_atencion_por_hora, duracion_atencion,
                        costo_final);

        }
    }
}
//* NO CONFUNDIR CON EL SEARCH QUE SE VERA EN ARREGLOS
void get_data_pacientes(ifstream &input, ofstream &output, int &dni, char &sexo_paciente, int &edad_paciente,
                        int &contador_paciente) {
    //* PERO search_pacientes(ifstream &input, int &dni) SOLO SE LEE HASTA ID - SI NO, NO PUEDES LEER LO DEMAS
    //! {"id": 1, "dni": "469-84-4163", "nombre": "Dunston/Rossoni-P.", "sexo": "F", "edad": 47}
    input.clear();
    input.seekg(0, ios::beg);
    int dni_pacientes =0;
    while (true) {
        if (input.peek()=='{') {
            input.ignore(1000, ':'); //? {"id":
            input.ignore(1000, ':'); //?  1, "dni":
            input.ignore(10000, '"'); //* 469-84-4163
        }
        dni_pacientes = read_DNI(input);
        if (dni_pacientes==dni) {
            contador_paciente++;
            output << setw(2) << contador_paciente; generate_whitespaces(output, 3);
            output << "DATOS DEL PACIENTE: " << endl;
            generate_whitespaces(output, 5); output << "ID: " << dni;
            generate_whitespaces(output,8); output << "NOMBRE: ";
            input.ignore(10000, ':');                           //? ", "nombre":
            input.ignore(10000, '"');                           //?  "
            read_and_print_name_without_arr(input, output, 20); //* Dunston/Rossoni-P.
            input.ignore(10000, ':');                           //? ", "sexo":
            input.ignore(1000,'"');                             //?  "
            input >> sexo_paciente;                                    //* F
            input.ignore(10000, ':');                           //? ", "edad":
            input >> edad_paciente;                                    //* 47
            break;
        }
        input.ignore(10000, '\n');
    }

}

void get_data_triaje(ifstream &input, int &fecha_registro, int &dni, int &frecuencia_cardiaca_triaje,
                     int &presion_sistolica_triaje, int &presion_diastolica_triaje, double &temperatura_triaje,
                     int &saturacion_oxigeno_triaje, bool &paciente_valido) {
    //* PERO SOLO SE LEE HASTA ID - SI NO, NO PUEDES LEER LO DEMAS
    //! 6/04/2023,635-96-2790,86,120,62,39.2,98
    int dia_triaje=0, dni_triaje=0;
    input.clear();
    input.seekg(0, ios::beg);
    while (true) {
        paciente_valido = false;
        if (input.peek()=='#') {
            input.ignore(10000, '\n'); //? {"id":
        }
        dia_triaje = read_date(input);
        ignorar_coma(input);
        dni_triaje = read_DNI(input);
        ignorar_coma(input);
        if (dia_triaje==fecha_registro and dni_triaje==dni) {
            paciente_valido = true;
            input >> frecuencia_cardiaca_triaje;
            ignorar_coma(input);
            input >> presion_sistolica_triaje;
            ignorar_coma(input);
            input >> presion_diastolica_triaje;
            ignorar_coma(input);
            input >> temperatura_triaje;
            ignorar_coma(input);
            input >> saturacion_oxigeno_triaje;
            break;
        }
        input.ignore(10000, '\n');
    }
}

