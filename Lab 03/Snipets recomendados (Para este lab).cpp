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





