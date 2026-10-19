// CADENAS
int buscar_cadena(char* genero, char** genero_sin_repeticion, int n_generos) {
    for (int i=0; i< n_generos; i++) {
        if (strcmp(genero,genero_sin_repeticion[i]) == 0) return i;
    }
    return -1;
}

char* asignar_cadena(char* cadena) {
    char* str;
    str = new char[strlen(cadena) + 1];
    strcpy(str, cadena);
    return str;
