
void open_read_file(ifstream &input, const char* file_name) {
    input.open(file_name);
    if (not input.is_open()) {
        cerr << "El archivo " << file_name << " no se pudo leer" << endl;
        exit(1);
    }
}

void cargarNumeros(const char* fileName, int* numeros, int& longitud) {
    ifstream inputNumeros; open_read_file(inputNumeros, fileName);
  
    longitud = 0;
    int numero;
    while (archivo >> numero) {
        insertarOrdenado(numeros, CAPACIDAD, longitud, numero);

        // numeros[longitud] = numero;
        // longitud++;
    }
}

bool insertarOrdenado(int* arrNumero, int capacidad, int& longitud, int numero) {
    if (longitud >= capacidad) {
        return false;
    }

    int i = longitud - 1;
    while (i >= 0 && arrNumero[i] > numero) {
        arrNumero[i + 1] = arrNumero[i]; // desplazamos a la derecha
        i--;
    }
    arrNumero[i + 1] = numero; // insertamos el nuevo número
    longitud++;

    return true;
}

  //? Extras Utiles
bool agregar(int* arrNumero, int capacidad, int& longitud, int numero) { //agregar al final sin orden
    if (longitud >= capacidad) {
        return false;
    }

    arrNumero[longitud] = numero;
    longitud++;

    return true;
}

bool insertar(int* arrNumero, int capacidad, int& longitud, int pos, int numero) { //tu indicas en que posicion se agrega y pues tienes que desplazar datos
    if (longitud >= capacidad or pos < 0 or pos > longitud) {
        return false;
    }

    for (int i = longitud; i > pos; i--) {
        arrNumero[i] = arrNumero[i - 1];
    }
    arrNumero[pos] = numero;
    longitud++;

    return true;
}

bool eliminar(int* arrNumero, int& longitud, int pos) { //Eliminas un valor (segun la posicion de numero dentro del arreglo)
    if (pos < 0 or pos >= longitud) {
        return false;
    }

    for (int i = pos; i < longitud -1; i++) {
        arrNumero[i] = arrNumero[i + 1];
    }
    longitud--;

    return true;
}
