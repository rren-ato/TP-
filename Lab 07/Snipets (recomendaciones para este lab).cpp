// CADENAS

//? Lectura de una cadena
char *leer_cadena(ifstream &input, char until) {
    char buffer[MAX_TAM_CADENA];
    char *cadena; //Arr Dinamico
    input.getline(buffer, MAX_TAM_CADENA, until);
    if(input.eof()) return nullptr; //! Permite dar validaciones por si leemos en un bucle (la cadena como primer dato a leer)
    //DESIGNAR MEMORIA (asignar)
    cadena = new char[strlen(buffer) +1];
    strcpy(cadena, buffer);
    return cadena;
}

//Asignacion de cadena debido a algun filtro (por ejemplo un caracter de genero) 
char *asignar_cadena(char* cadena) {
    char* str;
    str = new char[strlen(cadena) + 1];
    strcpy(str, cadena);
    return str;

//Es como una busqueda normal (la que no es binaria) pero con cadena
int buscar_cadena(char* genero, char** genero_sin_repeticion, int n_generos) {
    for (int i=0; i< n_generos; i++) {
        if (strcmp(genero,genero_sin_repeticion[i]) == 0) return i;
    }
    return -1;
}


void insertar_genero(char* genero, char** genero_sin_repeticion, int* frecuencias, int &n_generos) {
    int pos;
    pos = buscar_cadena(genero, genero_sin_repeticion, n_generos);
    if (pos == -1) {
        //* Debido a que es un arreglo de cadenas, es por ello que es doble puntero  (es un arreglo de char*) 
        genero_sin_repeticion[n_generos] = asignar_cadena(genero);
        frecuencias[n_generos] = 1;
        n_generos++;
    }
    else {
        frecuencias[pos]++;
    }
}


void calcular_frecuencias(char** arr_generos_totales, int cant_datos, int* frecuencias,
                          char** genero_sin_repeticion, int &n_generos) {
    char genero[40]{};
    int k=0;

    cout << cant_datos << endl;
    for (int i=0; i < cant_datos; i++) {
        char* generos;
        generos = asignar_cadena(arr_generos_totales[i]);
        //hiphop-pop-R&B
        for (int j=0; j<strlen(generos)+1; j++) {
            if (generos[j] == '-' or generos[j] == '\0') {
                //hiphop
                genero[k] = '\0';
                insertar_genero(genero, genero_sin_repeticion, frecuencias, n_generos);
                k=0; //reseteo por palabra (genero)
            }
            else {
                genero[k] = generos[j];
                k++;
            }
        }
    }
}
