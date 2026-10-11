//? Cargar en arreglo dinamico
void cargarPacientes(const char* fileName,
    int*& codigosPacientes,
    char*& generosPacientes,
    int*& edadesPacientes,
    double*& montosLimitesPacientes,
    int& cantPacientes) {

    ifstream inputPacientes; open_read_file(inputPacientes, fileName);

    //* cantPacientes = 0; <--- tener en cuenta que esto se inicializa en el main
    int bufferCodigos[CAP_PACIENTES];
    char bufferGeneros[CAP_PACIENTES];
    int bufferEdades[CAP_PACIENTES];
    double bufferMontosLimites[CAP_PACIENTES];

    int cod1, cod2, cod3, edad;
    char c, genero;
    double monto;
    while (true) {
        //* La primera lectura es un dni
        inputPacientes >> cod1;
        if(inputPacientes.eof())break;
        inputPacientes >> c >> cod2 >> c >> cod3
        inputPacientes >> ws;
        inputPacientes.ignore(TAM_LINEA, ' ');
        inputPacientes >> genero >> edad >> monto;

        int codigo = cod1 * 1000000 + cod2 * 10000 + cod3;
        bufferCodigos[cantPacientes] = codigo;
        bufferGeneros[cantPacientes] = genero;
        bufferEdades[cantPacientes] = edad;
        bufferMontosLimites[cantPacientes] = monto;
        cantPacientes++;
    }
    //* Se le da memoria a los arreglos
    codigosPacientes = new int[num];
    generosPacientes = new char[num];
    edadesPacientes = new int[num];
    montosLimitesPacientes = new double[num];

    //? Aqui se podria hacer una insercion ordenada xd
    for (int i = 0; i < num; i++) {
        //* Se "dereferencia (dereference) el buffer y por el puntero te quedas apuntando a la direccion de memoria del valor
        codigosPacientes[i] = bufferCodigos[i];
        generosPacientes[i] = bufferGeneros[i];
        edadesPacientes[i] = bufferEdades[i];
        montosLimitesPacientes[i] = bufferMontosLimites[i];
    }
}

//? En el main se veria algo asi
    int* codigosPacientes;
    char* generosPacientes;
    int* edadesPacientes;
    double* montosLimitesPacientes;
    int cantPacientes =0;
    cargarPacientes("ArchivosDeDatos/Pacientes.txt", codigosPacientes, generosPacientes, edadesPacientes, montosLimitesPacientes, cantPacientes);
    delete[] codigosPacientes;
    delete[] generosPacientes;
    delete[] edadesPacientes;
    delete[] montosLimitesPacientes;

