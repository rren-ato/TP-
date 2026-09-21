void imprimirResumenJSON(ofstream& archivoJSON, int nReservas, int reservasInvalidas, double total,
                         double mayor, long long fechaHoraMayor, int idMayor,
                         double menor, long long fechaHoraMenor, int idMenor) {
    archivoJSON << "{\"reservas\": " << nReservas
         << ", \"reservasInvalidas\": " << reservasInvalidas
         << ", \"total\": " << fixed << setprecision(2) << total
         << ", \"mayorImporte\": " << mayor
         << ", \"mayorId\": " << idMayor
         << ", \"mayorFechaHora\": \"";
    imprimirFechaHoraISO(archivoJSON, fechaHoraMayor);
    archivoJSON << "\", \"menorImporte\": " << menor
         << ", \"menorId\": " << idMenor
         << ", \"menorFechaHora\": \"";
    imprimirFechaHoraISO(archivoJSON, fechaHoraMenor);
    archivoJSON << "\"}" << endl;
}

void read_and_print_name_whithout_arr(ifstream &input, ofstream &output) {
    char c; int contador_char = 0;
    //! contreras/chang/johana-cinthia,
    input.get(c);
    while (c != ',') {
        if (c == '/') c = ' ';
        if ('a' <= c && c <= 'z') c = c - 'a' + 'A';
        output.put(c);
        contador_char++;
        input.get(c);
    }
}


bool openFiles(ifstream &input_empresas, ifstream &input_infracciones, ifstream &input_tablas, ofstream &output) {
    input_empresas.open("ArchivosDeDatos/EmpresasRegistradas.csv", ios::in);
    input_infracciones.open("ArchivosDeDatos/InfraccionesCometidas.jsonl", ios::in);
    input_tablas.open("ArchivosDeDatos/TablaDeInfracciones.txt", ios::in);
    output.open("ArchivosDeReporte/reporte.json", ios::out);
    return input_empresas.is_open() and input_infracciones.is_open() and input_tablas.is_open() and output.is_open();
}

void closeFiles(ifstream &input_empresas, ifstream &input_infracciones, ifstream &input_tablas, ofstream &output) {
    input_empresas.close();
    input_infracciones.close();
    input_tablas.close();
    output.close();
}

// BUSQUEDA EN JSON
void get_data_pacientes(ifstream &input, ofstream &output, int dni, char &sexo_paciente, int &edad_paciente,
                        int &contador_paciente) {
    //* PERO search_pacientes(ifstream &input, int &dni) SOLO SE LEE HASTA ID - SI NO, NO PUEDES LEER LO DEMAS
    //! {"id": 1, "dni": "469-84-4163", "nombre": "Dunston/Rossoni-P.", "sexo": "F", "edad": 47}
    input.clear();
    input.seekg(0, ios::beg); //*   input.seekg(0)
    int dni_pacientes =0;
    while (true) {
        if (input.peek()=='{') {
            input.ignore(1000, ':'); //? {"id":
            input.ignore(1000, ':'); //?  1, "dni":
            input.ignore(10000, '"'); //* 469-84-4163
        }
        dni_pacientes = read_DNI(input);
        if (input.eof()) break;                     //* <--- BANDERA QUE NECESITA RESETEARSE
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
            break;                                               //! <--- continue
        }
        input.ignore(10000, '\n');
    }

}

// BUQUEDA EN CSV
void get_data_triaje(ifstream &input, int &fecha_registro, int dni, int &frecuencia_cardiaca_triaje,
                     int &presion_sistolica_triaje, int &presion_diastolica_triaje, double &temperatura_triaje,
                     int &saturacion_oxigeno_triaje, bool &paciente_valido) {
    //* PERO SOLO SE LEE HASTA ID - SI NO, NO PUEDES LEER LO DEMAS
    //! 6/04/2023,635-96-2790,86,120,62,39.2,98
    int dia_triaje=0, dni_triaje=0;
    input.clear();
    input.seekg(0, ios::beg);
    while (true) {
        // paciente_valido = false;
        if (input.peek()=='#') {
            input.ignore(10000, '\n');
        }
        dia_triaje = read_date(input);
        if (input.eof()) break;                      //* <--- BANDERA QUE NECESITA RESETEARSE
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
            break;                                           //! <--- continue
        }
        input.ignore(10000, '\n');
    }
}





