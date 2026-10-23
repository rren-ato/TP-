//Cadenas Estaticas (stack)
char cadenaEstatica[20];

void probarGetline(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("getline consume el delimitador");

    char cadena1[50];
    char cadena2[50];
    archivo.getline(cadena1, 50);   // hasta '\n'
    cout << "Cadena leida: " << cadena1 << endl;
    archivo.getline(cadena1, 50, '/');   // hasta '/'
    cout << "Cadena leida: " << cadena1 << endl;
    archivo.getline(cadena2, 50);   // resto de la linea
    cout << "Cadena restante: " << cadena2 << endl;
}

void probarGetlineConArregloPequenio(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("Arreglo pequenio: getline activa failbit");

    char cadena1[10];
    char cadena2[50];
    archivo.getline(cadena1, 10);   // copia 9 caracteres y el '\0'
    imprimirEstadoFailbit(archivo);
    archivo.clear();   // obligatorio
    archivo.getline(cadena2, 50);
    cout << "cadena1 = " << cadena1 << endl;
    cout << "cadena2 = " << cadena2 << endl;
}

void probarLecturaMixtaLimpiando(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("Lectura mixta limpiando el buffer");

    int numero;
    char cadena[200];
    archivo >> numero;
    while (archivo.get() != '\n');   // vacia el buffer hasta '\n'
    archivo.getline(cadena, 200);
    imprimirNumeroYCadena(numero, cadena);
}
