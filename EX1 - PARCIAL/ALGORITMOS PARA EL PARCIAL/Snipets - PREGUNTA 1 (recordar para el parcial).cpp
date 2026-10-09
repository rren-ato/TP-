
//? PREGUNTA 1 - BUSQUEDAS CON SEEKG (SIN ARREGLOS)

//* APERTURA PUES EN LA RUBRICA SE SOLICITA CREAR UNA FUNCION QUE APERTURE CADA ARCHIVO
void open_read_file(ifstream &input, const char* file_name) {
    input.open(file_name);
    if (not input.is_open()) {
        cerr << "El archivo " << file_name << " no se pudo leer" << endl;
        exit(1);
    }
}

void open_write_file(ofstream &output, const char* file_name) {
    output.open(file_name);
    if (not output.is_open()) {
        cerr << "El archivo " << file_name << " no se pudo leer" << endl;
        exit(1);
    }
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

//*  Se pasa un valor antes leido para la busqueda 
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
            break;                                               //! <--- SI ENCUENTRA LA COINCIDENCIA ROMPE
        }
        input.ignore(10000, '\n');
    }
}

//? Invocando la funcion se veria algo asi
void leer_clinica_Y_Generar_reporte(const char* fileClinica, const char* filePacientes, const char* fileReporte) {
    //* POR UN DIA PODEMOS LEER MAS DE UN PACIENTE
    //! 1/04/2023    01:21:00    463-17-9883    03:13:54    268.65
    //!              02:45:00    332-44-9371    04:57:00    840.51
    ifstream inputClinica; open_read_file(inputClinica, fileClinica);
    ifstream inputPacientes; open_read_file(inputPacientes, filePacientes);
    ofstream outputReporte; open_write_file(outputReporte, fileReporte);
  
    int fecha_registro=0, hora_ingreso=0, dni = 0, hora_salida=0, duracion_atencion=0;
    double costo_atencion_por_hora=0.0, costo_final= 0.0;
    char sexo_paciente; int edad_paciente=0;
    int frecuencia_cardiaca_triaje=0 , presion_sistolica_triaje= 0, presion_diastolica_triaje= 0;
    int saturacion_oxigeno_triaje=0; double temperatura_triaje=0; bool paciente_valido;
    print_header(outputReporte);
    while (true) {
        int contador_paciente=0;
        fecha_registro = read_date(inputClinica);     //* <---- DIA
        if (input_clinica.eof()) break;
        print_header_of_date(outputReporte, fecha_registro);
        //* LECTURA POR DIA DE ATENCION
        while (true) {
            //! LECTURA POR DIA
            if (inputClinica.eof())break;
            if (inputClinica.peek()=='\n') break;
            inputClinica >> ws;
            hora_ingreso = read_time(inputClinica);
            dni = read_DNI(inputClinica);              //* <---- DNI (KEY PARA EL SEEKG)
            inputClinica >> ws;
            hora_salida = read_time(inputClinica);
            inputClinica >> costo_atencion_por_hora;
            //* CALCULO DE LA DURACION
            duracion_atencion = calcular_duracion(hora_ingreso, hora_salida); //? RESULTADO EN SEGUNDOS
            get_data_pacientes(inputPacientes, outputReporte, dni, sexo_paciente, edad_paciente,
                                contador_paciente);
            print_pacientes_info(outputReporte, edad_paciente, sexo_paciente);
        }
    }
}

//* Si se puede encontrar mas de una coincidencia, se necesitaria imprimir en la funcion get_data (usualmente uno se acostumbra
//* a no imprimir nada porque en arreglos la funcion buscar no puede ni debe imprimir nada.)
