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
//* SIN ESO NO SABES DONDE VERIDICAMENTE USAR INPUT O OUTPUT (EXPLICAR)
void generate_whitespaces(ofstream &output, int width) {
    output << setw(width) << setfill( ' ');
}

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

void print_date(ofstream &output, int date, int width) {
    int day, month, year;
    year = date /10000;
    month = (date/100) % 100;
    day = date %100;
    //TODO ESTO ABARCA 10 CARACTERES
    output << setw(2) << setfill( '0') << day <<
        setw(2) << setfill( '0') << month <<
            setw(4) << setfill( '0') << year;
    //* GENERAR ESPACIADO
    output << setw((width)-10) << setfill( ' ');
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

void print_info_canal(ofstream &output, int n_canal) {
    print_line(output, ANCHO_REPORTE, '=');
    output << "CANAL No. " << n_canal;
    generate_whitespaces(output, 6);
    output << setw(ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS_POR_CANAL) << "NOMBRE" << setfill(' ');
    output << setw(ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS_POR_CANAL) << "CODIGO" << setfill(' ');
    output << setw(ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS_POR_CANAL) << "CREADO EL" << setfill(' ');
    output << setw(ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS_POR_CANAL) << "SEGUIDORES NUEVOS POR MES" << setfill(' ');
    output << setw(ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS_POR_CANAL) << "VISIAS NUEVAS POR MES" << setfill(' ');
    output << setw(ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS_POR_CANAL) << "MAXIMO DE ESPECTADORES" << setfill(' ')<<endl;
}

void print_header_reproducciones(ofstream &output) {
    print_line(output, ANCHO_REPORTE, '-');
    generate_whitespaces(output, 5); output << "ULTIMAS REPRODUCCIONES" << endl;
    generate_whitespaces(output,10);
    output << setw(ANCHO_REPRODUCCION/N_COLUMNS_POR_REPRODUCCION) << "FECHA DE PUBLICACION" << setfill(' ');
    output << setw(ANCHO_REPRODUCCION/N_COLUMNS_POR_REPRODUCCION) << "TIEMPO DE DURACION" << setfill(' ');
    output << setw(ANCHO_REPRODUCCION/N_COLUMNS_POR_REPRODUCCION) << "INGRESOS POR DURACION" << setfill(' ');
    output << setw(ANCHO_REPRODUCCION/N_COLUMNS_POR_REPRODUCCION) << "NUMERO DE REPRODUCCIONES" << setfill(' ');
    output << endl;
}

void print_resumen_por_canal(ofstream &output, int duracion_total_reproduccion, int total_reproducciones,
                             long long ingresos_por_publidad, double ingresos_por_duracion,
                             long long new_follows_of_month,
                             long long new_views_of_month,
                             long long max_ammount_of_chat) {
    long long atraccion_del_publico = 0.0;
    generate_whitespaces(output,5); output << "RESUMEN DEL CANAL: " << endl;
    generate_whitespaces(output, 5); output << "DURACION TOTAL DE LAS REPRODUCCIONES: ";
    print_time(output, 12 , duracion_total_reproduccion); output << endl;
    generate_whitespaces(output, 5); output << "INGRESOS POR DURACION: " <<
        setw(16) << '$' << right << setw(7) << fixed << setprecision(2) << ingresos_por_duracion << endl;
    generate_whitespaces(output, 5); output << "TOTAL DE REPRODUCCIONES: " <<
        setw(19) << total_reproducciones << endl;
    generate_whitespaces(output, 5); output << "INGRESOS POR PUBLICIDAD" <<
        setw(14) << '$' << right << setw(7) << fixed << setprecision(2) << ingresos_por_publidad << endl;
    //! CALCULO DEL ENGAGEMENT INDEX
    atraccion_del_publico = ((new_follows_of_month + (new_views_of_month/1000))/max_ammount_of_chat);
    generate_whitespaces(output, 5); output << "ENGAGEMENT INDEX: " <<
        setw(23) << atraccion_del_publico << endl;
    output << endl;
}

void procesar_informacion(ifstream &input, ofstream &output, long long new_visits_of_month,
    double tarifax1k_reproducciones, double tarifaxminuto_duracion,
    int &duracion_total_reproduccion, int &total_reproducciones,
    long long &ingresos_por_publidad, double &ingresos_por_duracion) {
    // 16/07/2025,00:25:55,1396
    int release_date = 0, duration_time=0, number_of_plays=0;
    double ingresos_por_tiempo_stream=0.0;
    long long ingresos_por_reproducciones = 0.0;
    while (true) {
        if (input.peek() ==  '\r' or input.peek() == '\n') {
            input.ignore(10000, '\n');
            break;
        }
        release_date = read_date(input);
        ignorar_coma(input);
        duration_time = read_time(input);
        ignorar_coma(input);
        input >> number_of_plays;

        //? CALCULAR INGRESOS POR DURACION
        ingresos_por_reproducciones = ((long long)tarifax1k_reproducciones * new_visits_of_month); //* ingreso x publicidad
        ingresos_por_tiempo_stream = tarifaxminuto_duracion * ((double)duration_time/60); //* ingreso x duracion

        //! IMPRESION
        generate_whitespaces(output,10);
        print_date(output, release_date, ANCHO_REPRODUCCION/N_COLUMNS_POR_REPRODUCCION);
        print_time(output,  ANCHO_REPRODUCCION/N_COLUMNS_POR_REPRODUCCION, duration_time);
        output << setw(ANCHO_REPRODUCCION/N_COLUMNS_POR_REPRODUCCION) << ingresos_por_tiempo_stream;
        output << setw(ANCHO_REPRODUCCION/N_COLUMNS_POR_REPRODUCCION) << number_of_plays << endl;

        //? GUARDADO
        duracion_total_reproduccion += duration_time;
        ingresos_por_duracion += ingresos_por_tiempo_stream;
        total_reproducciones += number_of_plays;
        ingresos_por_publidad += ingresos_por_reproducciones;

    }
}

void read_and_print_registros_validos(ifstream &input, ofstream &output, int date_of_account,
                                        char char_code_stream, int int_code_stream, long long new_follows_of_month,
                                        long long new_views_of_month, long long max_ammount_of_chat,
                                        double tarifax1k_reproducciones, double tarifaxminuto_duracion,
                                        int duracion_total_reproduccion, int total_reproducciones,
                                        long long &ingresos_por_publidad, double &ingresos_por_duracion) {
    char char_code_leido; int int_code_leido=0, date_of_account_leido=0;
    long long follows_leido=0.0, views_leido=0.0, chat_leido=0.0;
    while (true) {
        date_of_account_leido = read_date(input);
        if (input.eof())break;
        ignorar_coma(input);
        input >> char_code_leido >> int_code_leido;
        ignorar_coma(input);
        //! SE IGNORA EL CANAL
        input.ignore(10000,',');
        ignorar_coma(input);
        input >> follows_leido;
        ignorar_coma(input);
        input >> views_leido;
        ignorar_coma(input);
        input >> chat_leido;
        //! BUSQUEDA SIMPLE A TRAVES DE UNA PASADA EN LA INFORMACION DEL ARCHIVO (DE MOMENTO A MOMENTO)
        if (date_of_account_leido == date_of_account and char_code_leido == char_code_stream
            and int_code_leido == int_code_stream and follows_leido == new_follows_of_month
            and views_leido == new_views_of_month and chat_leido == max_ammount_of_chat) {
            procesar_informacion(input, output, new_follows_of_month,
            tarifax1k_reproducciones, tarifaxminuto_duracion,
            duracion_total_reproduccion, total_reproducciones,
            ingresos_por_publidad, ingresos_por_duracion);
            }
        else {
            input.ignore(10000,'\n');
        }
        //* IMPRIMIR EL RESUMEN DE LAS REPRODUCCIONES POR CANAL
        print_line(output, ANCHO_REPORTE, '-');
        print_resumen_por_canal(output, duracion_total_reproduccion, total_reproducciones,
                             ingresos_por_publidad, ingresos_por_duracion,
                             new_follows_of_month,
                             new_views_of_month,
                             max_ammount_of_chat);
    }
}

void registro_por_canal(ifstream &input, ofstream &output, int date_limite_inf, int date_limite_sup,
                        double tarifax1k_reproducciones, double tarifaxminuto_duracion) {
    //  01/04/2021,F3765,Fextralife,1734810,93036735,222720,16/07/2025,00:25:55,1396
    char char_code_stream;
    int int_code_stream, date_of_account=0;
    long long new_follows_of_month=0.0, new_views_of_month=0.0, max_ammount_of_chat=0.0;
    long long ingresos_por_publidad= 0.0; double ingresos_por_duracion= 0.0;
    int n_canal = 0;
    //! IGNORAR LA PRIMERA FILA QUE ESTA EN COMMITS
    if (input.peek() == '#') input.ignore(10000,'\n');
    while (true){
        print_line(output, ANCHO_REPORTE, '=');
        int duracion_total_reproduccion= 0, total_reproducciones = 0;
        //! BREAK SI SE CONSIGUE EL FIN DE ARCHIVO
        if (input.eof()) break;
        date_of_account = read_date(input);
        //! FECHAS DELIMITADAS EN LA CONSOLA - PRECISAMENTE POR ESO HAGO UNA FUNCION QUE DEVUELVE UN ENTERO
        //* 20221009 <= date_of_account and date_of_account <= 20230101
        if (date_limite_inf <= date_of_account and date_of_account <= date_limite_sup) {
            n_canal++; print_info_canal(output, n_canal);
            ignorar_coma(input);
            input >> char_code_stream >> int_code_stream;
            ignorar_coma(input);
            read_and_print_name_without_arr(input, output, ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS_POR_CANAL);
            output << char_code_stream << int_code_stream <<
                setw((ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS_POR_CANAL)-5) << setfill( ' ');
            ignorar_coma(input);
            print_date(output, date_of_account, ANCHO_REPORTE_JUSTIFICADO/N_COLUMNS_POR_CANAL);
            ignorar_coma(input);
            input >> new_follows_of_month;
            ignorar_coma(input);
            input >> new_views_of_month;
            ignorar_coma(input);
            input >> max_ammount_of_chat; //* me refiero a la cantidad de personas en el chat - livestream
            //! SE PROCESA LA INFORMACION POR PRIMERA VEZ PARA LUEGO COMPARAR
            print_header_reproducciones(output);
            procesar_informacion(input, output, new_follows_of_month,
            tarifax1k_reproducciones, tarifaxminuto_duracion,
            duracion_total_reproduccion, total_reproducciones,
            ingresos_por_publidad, ingresos_por_duracion);

            //! INGRESO DE DATOS VARIOS COMO BUSQUEDA DE PASO
            //* SI SE PASA EL FILTRO, TAMBIEN SE PROCESA LA INFORMACION
            //! SI NO SE TIENEN COINCIDENCIAS PUES SE IMPRIME LA ESTADISTICA
            //? TENER EN CUENTA QUE ESTE ARCHIVO TIENE LA DATA ORDENADA (SIMILAR A LO QUE SERA LAB 2)
            read_and_print_registros_validos(input, output, date_of_account,
                                        char_code_stream, int_code_stream, new_follows_of_month,
                                        new_views_of_month, max_ammount_of_chat,
                                        tarifax1k_reproducciones, tarifaxminuto_duracion,
                                        duracion_total_reproduccion, total_reproducciones,
                                        ingresos_por_publidad, ingresos_por_duracion);
        }
        else {
            input.ignore(10000,'\n');
        }
    }
}

void generar_reporte(const char *archivo_lectura_streams, const char *archivo_reporte) {
    ifstream input_twitchData; open_read_file(input_twitchData, archivo_lectura_streams);
    ofstream output; open_write_file(output, archivo_reporte);

    int date_limite_inf =0, date_limite_sup=0;
    double tarifax1k_reproducciones=0.0, tarifaxminuto_duracion=0.0;
    //! LECTURA EN CONSOLA (EL ENUNCIADO LO INDICA)
    cout << "INGRESE EL LIMITE INFERIOR Y EL SUPERIOR PARA EL REGISTRO";
    date_limite_inf = read_date_with_cin();
    date_limite_sup = read_date_with_cin();

    cout << "INGRESE LA TARIDA POR NUMERO DE REPORDUCCIONES: ";
    cin >> tarifax1k_reproducciones;
    cout << "INGRESE LA TARIFA POR DURACION DEL STREAM: ";
    cin >> tarifaxminuto_duracion;
    //! IMPRESION DEL REPORTE COMO TAL
    print_tittle_of_report(output, date_limite_inf, date_limite_sup,
                           tarifax1k_reproducciones, tarifaxminuto_duracion);

    registro_por_canal(input_twitchData, output, date_limite_inf, date_limite_sup,
                        tarifax1k_reproducciones, tarifaxminuto_duracion);
}

void print_tittle_of_report(ofstream &output, int date_limite_inf, int date_limite_sup,
                        double tarifax1k_reproducciones, double tarifaxminuto_duracion) {
    output << setw((ANCHO_REPORTE+20)/2) << setfill(' ') << "PLATAFORMA TP_Twitch" << endl;
    output << setw((ANCHO_REPORTE+10)/34) << setfill(' ') << "REGISTRO DE LOS CANALES AFILIADOS " << endl;
    generate_whitespaces(output , 42);
    output << "FECHA DE CREACION ENTRE EL ";
    print_date(output, date_limite_inf, 11); output << " Y EL ";
    print_date(output, date_limite_sup, 11); output << endl;
    generate_whitespaces(output , 28);
    output << "TARIFA POR NUMERO DE REPORDUCCIONES: " << tarifax1k_reproducciones <<
        "POR CADA 1,000 REPRODUCCIONES Y FRACCION" << endl;
    generate_whitespaces(output , 28);
    output << "TARIFA POR DURACION DEL STREAM: " << tarifaxminuto_duracion <<
        "POR CADA 1,000 REPRODUCCIONES Y FRACCION" << endl;
}

int read_date_with_cin () {
    //12/12/2023
    int dd, mm, yyyy, date;
    char c;
    cin >> dd >> c >> mm >> c >> yyyy;
    date = yyyy*10000 + mm*100 + dd;
    return date;
}