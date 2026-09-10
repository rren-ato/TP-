
#include "FuncionesAuxiliares.h"


// DNI,NOMBRE,INFRACCION,FECHA,CODIGO
// 79672079,CONTRERAS/CHANG/JOHANA-CINTHIA,P599-629,12/12/2023,2036

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
//AHORA UNO DEBE DE IDENTIFICAR QUE FUNCIONES LEEN O CUALES IMPRIMEN
void print_line(ofstream &output,int width, char character) {
    output << setw(ANCHO_REPORTE) << setfill( ' ') << endl;
}

void ignorar_coma(ifstream &input) {
    char c;
    input.get(c);
}

//Esta funcion se come la coma ',' (la que va luego de leer el nombre)
void read_and_print_name_without_arr(ifstream &input,ofstream &output, int width) {
    //CONTRERAS/CHANG/JOHANA-CINTHIA,
    char c;
    bool minus_letter = false;
    int contador_character = 0;
    input.get(c); //Entra el primer character
    while (c != ',') {

        if (c == '/' or c == '-') {
            c = ' ';
            minus_letter = false;
        }
        if (minus_letter == true) {
            c = c + 'a' - 'A';
        }
        output.put(c);
        contador_character++;
        minus_letter = true;
        input.get(c);
    }
    output << setw(width - contador_character) << setfill( ' ');
}

void read_and_categorize_plate(ifstream &input,ofstream &output) {
    //P599-629,
    char type_plate, c;
    int p1_plate = 0, p2_plate = 0, plate = 0;
    input >> type_plate >> p1_plate >> c >> p2_plate;
    plate = p1_plate * 1000 + p2_plate;
    output << plate << type_plate;
    //ESPACIDO
    output << setw((ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS) - 7) << setfill( ' ');
    //ANALISIS
    if (type_plate == 'P') {
        output << setw(ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS) << "PEQUEÑO" << setfill( ' ');
    }
    else if (type_plate == 'M') {
        output << setw(ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS) << "MEDIANO" << setfill( ' ');
    }
    else if (type_plate == 'G') {
        output << setw(ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS) << "GRANDE" << setfill( ' ');
    }
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
    //GENERAR ESPACIADO
    cout << setw((ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS)-10) << setfill( ' ');
}

void read_and_print_description(ifstream &input, ofstream &output) {
    int cant_character = 0;
    while (true) {
        char c;
        if (input.peek() == '\r') break;
        input.get(c);
        output.put(c);
        cant_character++;
        //! en un archivo siempre esta '\r\n'
    }
    input.ignore(1000, '\n'); //* me como todo hasta pasar el salto de linea

    //ESPACIADO FINAL
    output << setw(ANCHO_REPORTE - (ANCHO_REPORTE_HASTA_MULTA+3 + cant_character)) << setfill( ' ') << endl;
}

//Del segundo archivo...
// L1001   158.33   Circular en las vias publicas urbanas sin portar la licencia de conducir.

//! ESTO ES BUSQUEDAS...
//* Se compara con el codigo de infraccion leido en el anterior archivo
void search_infraction_code(ifstream &input_inf_de_transito, int code_infraccion_leido, int &code_validado,
                            int &falta_leve, int &falta_grave, int &falta_muy_grave) {
    input_inf_de_transito.clear();
    input_inf_de_transito.seekg (0, ios::beg);

    // L1001   158.33   Circular en las vias publicas urbanas sin portar la licencia de conducir.
    while (true) {
        //* Valores que se leen, comparan, abren puertas y luego se pierden
        int code_read; // <---- OJO
        char letter_of_infraccion;

        input_inf_de_transito >> letter_of_infraccion;
        input_inf_de_transito >> code_read;
        if (input_inf_de_transito.eof()) break;
        if (code_read == code_infraccion_leido) code_validado = FOUND; // FOUND = 1 (ENCONTRADO)
        //* DESARROLLAR ESTA FORMA DE PENSAR RECOMENDADA
        //! ESTO MAS ADELANTE TE SIRVE CUANDO HACES BUSQUEDAS DENTRO DE BUSQUEDAS xd
        //! RECORDAR QUE LA FUNION BUSQUEDA SOLO PUEDE BUSCAR, NO IMPRIMIR
        if (code_validado != NOT_FOUND) { //osea si se encuentra
            code_validado = 1;
        //* Si entramos quiere decir que si se encontro (code_read == code_infraccion_leido)
            //ANALISIS
            if (letter_of_infraccion == 'L') falta_leve=1;
            if (letter_of_infraccion == 'G') falta_grave=1;
            if (letter_of_infraccion == 'M') falta_muy_grave=1;
            break;
        }
        double monto_basura=0.0; //no se encuentran coincidencias pero se debe eliminar la data residual
        input_inf_de_transito >> monto_basura;
        input_inf_de_transito.ignore(10000, '\n');
    }
}

void print_header (ofstream &output, int width) {
    output << "VEHIVULOS INFRACCIONADOS: " << endl;
    output << setw(3) << setfill(' ') <<
        setw(width) << "PLACA" << setfill(' ') <<
            setw(width) << "TIPO" <<
                setw(width) << "FECHA" <<
                    setw(width) << "INFRACCION" <<
                        setw(width) << "GRAVEDAD" <<
                            setw(width) << "MULTA" <<
                                setw(80) << "DESCRIPCION" << endl;
}


void procesar_informacion(ifstream &input_inf_cometidas, ifstream &input_inf_de_transito, ofstream &output,
                        int &faltas_leves_per_client, int &faltas_graves_per_client, int &faltas_muy_graves_per_client,
                        double &monto_leve, double &monto_grave, double &monto_muy_grave) {
    int fecha_infraccion=0, code_inf_cometidas=0;
    double multa = 0.0;
    int falta_leve = NOT_FOUND, falta_grave = NOT_FOUND, falta_muy_grave = NOT_FOUND, code_valido = NOT_FOUND;
    output << setw(3) << "-" << setfill(' ');
    read_and_categorize_plate(input_inf_cometidas,output);
    ignorar_coma(input_inf_cometidas);

    fecha_infraccion = read_date (input_inf_cometidas);
    print_date(fecha_infraccion, output);
    ignorar_coma(input_inf_cometidas);

    input_inf_cometidas >> code_inf_cometidas;
    search_infraction_code(input_inf_de_transito, code_inf_cometidas, code_valido,
                        falta_leve, falta_grave, falta_muy_grave);
    //SEGUN EL ENUNCIADO DA IGUAL QUE ESTE VALIDADO
    output << setw(ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS) << code_inf_cometidas << setfill( ' ');
    if (code_valido != NOT_FOUND) {
        //? Si entramos quiere decir que si se encontro (code_read == code_infraccion_leido)
        //ANALISIS
        if (falta_leve != NOT_FOUND) {
            output << setw(ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS) << "LEVE" << setfill( ' ');
            faltas_leves_per_client++;
        }
        else if (falta_grave != NOT_FOUND) {
            output << setw(ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS) << "GRAVE" << setfill( ' ');
            faltas_graves_per_client++;
        }
        else if (falta_muy_grave != NOT_FOUND) {
            output << setw(ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS) << "MUY GRAVE" << setfill( ' ');
            faltas_muy_graves_per_client++;
        }

        input_inf_de_transito >> multa;
        output << setw(ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS) << fixed << setprecision(2) << multa <<
                    setfill(' ');

        //! ACUMULACION DE MULTAS POR LECTURA (SEGUN LA BUSQUEDA - CATEGORIA)
        if (falta_leve != NOT_FOUND) monto_leve += multa;
        else if (falta_grave != NOT_FOUND) monto_grave += multa;
        else if (falta_muy_grave != NOT_FOUND) monto_muy_grave += multa;

        read_and_print_description(input_inf_de_transito, output);
    }
    else {
        output << setw(ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS) << "---" << setfill( ' ');
        output << setw(ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS) << "---" << setfill( ' ');
        output << "NO SE ENCONTRO LA ITERACION." << endl;
    }
}

void print_company_header(ifstream &input, ofstream &output, int n_compania, int DNI,  int width) {
    print_line(output, width, '=');
    output << "COMPANIA No. " << n_compania << endl;
    output << "REPRESENTANTE LEGAL: ";
    read_and_print_name_without_arr(input,output, ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS);
    output << "DNI: " << DNI << endl;
    print_line(output, width, '=');
    print_header(output, ANCHO_REPORTE_HASTA_MULTA/N_COLUMNS);
}

void print_totals_per_company(ofstream &output, int faltas_leves_per_client, int faltas_graves_per_client,
                                int faltas_muy_graves_per_client,
                                double monto_leves, double monto_graves, double monto_muy_graves) {
    print_line(output, ANCHO_REPORTE, '-');
    output << setw(20) << setfill(' ') << "CANTIDAD" <<
        setw(15) << "MONTO PAGADO" << endl;
    output << "FALTAS LEVES: " << setw(8) << setfill(' ') << faltas_leves_per_client <<
        setw(7) << setfill(' ') << monto_leves << endl;
    output << "FALTAS GRAVES: " << setw(7) << setfill(' ') << faltas_graves_per_client <<
        setw(7) << setfill(' ') << monto_graves << endl;
    output << "FALTAS MUY GRAVES: " << setw(4) << setfill(' ') << faltas_muy_graves_per_client <<
        setw(7) << setfill(' ') << monto_muy_graves << endl;
    print_line(output, ANCHO_REPORTE, '-');

    double pago_total = monto_leves + monto_graves + monto_muy_graves;
    output << "PAGO TOTAL: " << fixed << setprecision(2) << pago_total << endl;
}

void generate_report(const char *file_name_cometidas, const char *file_name_inf_transtito,
                    const char *file_name_output) {
    ifstream input_infCometidas; open_read_file(input_infCometidas, file_name_cometidas);
    ifstream input_inf_de_transito; open_read_file(input_inf_de_transito,file_name_inf_transtito);
    ofstream output; open_write_file(output,file_name_output);
    int DNI = 0, dni_leido=0;
    int faltas_leves_per_client=0, faltas_graves_per_client=0, faltas_muy_graves_per_client=0, n_compania=0;
    double montos_leves=0.0, montos_graves=0.0, montos_muy_graves=0.0;
    while (true){
        if (input_inf_de_transito.peek() ==  EOF) break;
        n_compania++;
        //* LECTURA POR DNI
        if (input_infCometidas >> DNI) {
            //! Nos saltamos la coma pos lectura del DNI
            ignorar_coma(input_infCometidas);
            print_company_header(input_infCometidas, output, n_compania, DNI, ANCHO_REPORTE);

            //? Procesar solo lee a partir de las placas
            procesar_informacion(input_infCometidas, input_inf_de_transito, output,
                                 faltas_leves_per_client, faltas_graves_per_client, faltas_muy_graves_per_client,
                                 montos_leves, montos_graves, montos_muy_graves);
        }

        while (input_infCometidas >> dni_leido) {
            ignorar_coma(input_infCometidas);
            if (dni_leido == DNI) {
                //* SI SE LEE EL MISMO DNI SE PROCESA LA INFORMACION - CLIENTE
                //! SE IGNORA EL NOMBRE SI ES EL MISMO DNI
                input_infCometidas.ignore(10000, ',');
                //? VOLVEMOS A LEER DESDE PLACAS
                procesar_informacion(input_infCometidas, input_inf_de_transito, output,
                                 faltas_leves_per_client, faltas_graves_per_client, faltas_muy_graves_per_client,
                                 montos_leves, montos_graves, montos_muy_graves);
            }
            else {
                //* SI SE LEE OTRO DNI, SE TERMINA EL PROCESAMIENTO DE DATOS POR CLIENTE
                print_totals_per_company(output, faltas_leves_per_client, faltas_graves_per_client,
                faltas_muy_graves_per_client,montos_leves, montos_graves, montos_muy_graves);
                print_line(output, ANCHO_REPORTE, '=');
            }
        }

    }
}