//
// Created by Renato on 1/11/2026.
//

#include "FuncionesAuxiliares.h"

void openReadFile(ifstream &input, const char *fileName) {
    input.open(fileName, ios::in);
    if (not input.is_open()) {
        cerr << "El archivo " << fileName << " no se pudo leer" << endl;
        exit(1);
    }
}

void openWriteFile(ofstream &output, const char *fileName) {
    output.open(fileName, ios::out);
    if (not output.is_open()) {
        cerr << "El archivo " << fileName << " no se pudo abrir" << endl;
        exit(1);
    }
}

int contadorLineas (ifstream &input) {
    int n=0;
    while (input.ignore(TAM_BUFFER, '\n')) {
        n++;
    }
    return n;
}

char* leerCadena (ifstream &input, char delim) {
    char buffer[TAM_BUFFER];
    char *str;
    input.getline(buffer, TAM_BUFFER ,delim);
    if (input.eof()) return nullptr;
    str = new char[strlen(buffer)+1];
    strcpy (str, buffer);
    return str;
}

//? --- CARGA DE DATOS (DICCIONARIOS) ---

void llenarDiccionario(ifstream &input, char** diccionario, int &tamañoDiccionario) {
    tamañoDiccionario = 0;
    char* cadena;
    while ((cadena = leerCadena(input, '\n')) != nullptr) {
        diccionario[tamañoDiccionario++] = cadena;
    }
}

void cargarDiccionario(const char* fileName, char**& diccionario, int*& arrContadorApariciones,
                       int &tamañoDiccionario) {
    ifstream input; openReadFile(input, fileName);

    int cantLineas = contadorLineas(input);
    //* Designacion de memoria exacta
    diccionario = new char* [cantLineas];
    arrContadorApariciones = new int [cantLineas] {};
    input.clear();
    input.seekg (0, ios::beg);
    llenarDiccionario(input, diccionario, tamañoDiccionario);
}

void cargarDatos(char**& diccOtros, int*& arrContaOtros, int& tamañoOtros,
                 char**& diccPalabras, int*& arrContaPalabras, int& tamañoPalabras) {
    cargarDiccionario("ArchivosDeDatos/otros.txt", diccOtros, arrContaOtros,
                       tamañoOtros);
    cargarDiccionario("ArchivosDeDatos/palabras.txt", diccPalabras, arrContaPalabras,
                       tamañoPalabras);
}

//? Parte de reporte parcial (ORDENAMIENTO)

void generarReporteParcial(ofstream &output, char** diccionario, int tamañoDiccionario, const char *descripcion) {
    output << descripcion << endl;
    for (int i=0; i < tamañoDiccionario; i++) {
        output << diccionario[i] << endl;
    }
    output << endl;
}

void intercambiar (char*& a, char*& b) {
    char* aux = a;
    a=b;
    b=aux;
}

void ordenarPorNombres(char** listaNombre, int tamaño) {
    //* Ordenamiento ascendente (de menor a mayor)
    for (int i=0; i < tamaño -1; i++) {
        for (int j=i+1; j < tamaño; j++) {
            if (strcmp(listaNombre[i], listaNombre[j]) > 0) {
                intercambiar(listaNombre[i], listaNombre[j]);
            }
        }
    }
}

void reporteParciales(char** diccOtros, int tamOtros, char** diccPalabras, int tamPalabras) {
    ofstream outputOtros; openWriteFile(outputOtros, "ArchivosDeReporte/reporteParcialOtros.txt");
    ofstream outputPalabras; openWriteFile(outputPalabras, "ArchivosDeReporte/reporteParcialPalabras.txt");

    generarReporteParcial(outputOtros, diccOtros, tamOtros, "---Antes de Ordenar---");
    generarReporteParcial(outputPalabras, diccPalabras, tamPalabras, "---Antes de Ordenar---");

    ordenarPorNombres(diccOtros, tamOtros);
    ordenarPorNombres(diccPalabras, tamPalabras);
    generarReporteParcial(outputOtros, diccOtros, tamOtros, "---Despues de Ordenar---");
    generarReporteParcial(outputPalabras, diccPalabras, tamPalabras, "---Despues de Ordenar---");
}

//? Tockenizacion respecto al texto

void pasarAMinusculas(char* cadena) {
    for (int i=0; cadena[i]; i++) {
        //* Implementaciond e tolower (ctype)
        cadena[i] = tolower(cadena[i]);
    }
}

int busquedaBinaria(char** dicc, int tamDicc, char* cadena) {
    int izquierda=0;
    int derecha = tamDicc-1;
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha-izquierda)/2;
        int cmp = strcmp(cadena, dicc[medio]);
        if (cmp == 0) {
            return medio;
        }
        if (cmp < 0) {
            derecha = medio-1;
        } else {
            izquierda = medio+1;
        }
    }
    return NOT_FOUND;
}

//* Esto evalua mas la palabra que la cadena en si, por eso es que a cadena la pasamos a llamar palabra
void registrarDesconocido(char** diccDesconocido, int* frecuenciaDesconocido, int &tamDesconocido, const char* palabra) {
    int pos=0;
    while (pos < tamDesconocido and strcmp(diccDesconocido[pos], palabra) < 0) {
        pos++;
    }
    if (pos < tamDesconocido and strcmp(diccDesconocido[pos], palabra) == 0) {
        frecuenciaDesconocido[pos]++;
        return;
    }

    //* Insertar ordenado (pero sin bool porque le aumentas la complejidad a la funcion y maximo esta permitido 5)
    for (int j = tamDesconocido; j > pos; j--) {
        //* Etapa conocida como shift
        diccDesconocido[j] = diccDesconocido[j - 1];
        frecuenciaDesconocido[j] = frecuenciaDesconocido[j - 1];
    }
    //* Ese proceso se asemeja al asignar cadena (se enseñaba antes con mas detalle esto)
    diccDesconocido[pos] = new char[strlen(palabra) + 1];
    strcpy(diccDesconocido[pos], palabra);
    frecuenciaDesconocido[pos]++;
    tamDesconocido++;
}

void procesarTockens(ifstream &input, int* arrContaOtros, int* arrContaPalabras,
                     char** diccDesconocido, int* frecuenciaDesconocido, int& tamDesconocido, int& cantDesconocido,
                     char** diccOtros, int tamOtros, int &cantOtros,
                     char** diccPalabras, int tamPalabras, int &cantPalabras) {

    char cadena[TAM_BUFFER];
    tamDesconocido = 0;
    while (input >> cadena) {
        pasarAMinusculas(cadena);
        int tam = strlen(cadena);
        //* Con strchr lees la cadena hasta cierto punto (marcas partes como sentences)
        if ( tam > 0 and strchr(".:,!", cadena[tam-1])) {
            cadena[tam - 1] = '\0';
        }
        if (cadena[0] == '\0') {    //* lo que quiere decir esto es que la cadena en si esta vacia
            continue;
        }
        int posOtros = busquedaBinaria(diccOtros, tamOtros, cadena);
        if (posOtros != NOT_FOUND) {
            arrContaOtros[posOtros]++;
            cantOtros++;
            continue;
        }
        int posPalabras = busquedaBinaria(diccPalabras, tamPalabras, cadena);
        if (posPalabras != NOT_FOUND) {
            arrContaPalabras[posPalabras]++;
            cantPalabras++;
            continue;
        }
        registrarDesconocido(diccDesconocido, frecuenciaDesconocido, tamDesconocido, cadena);
        cantDesconocido++;
    }

}

void procesarTexto(int* arrContaOtros, int* arrContaPalabras,
                     char** diccDesconocido, int* frecuenciaDesconocido, int& tamDesconocido, int& cantDesconocido,
                     char** diccOtros, int tamOtros, int &cantOtros,
                     char** diccPalabras, int tamPalabras, int &cantPalabras) {
    ifstream inputTexto; openReadFile(inputTexto, "ArchivosDeDatos/texto.txt");

    procesarTockens(inputTexto, arrContaOtros, arrContaPalabras,
                     diccDesconocido, frecuenciaDesconocido, tamDesconocido, cantDesconocido,
                     diccOtros, tamOtros, cantOtros,
                     diccPalabras, tamPalabras, cantPalabras);

}

//? --- Etapa Final (Impresiones y registros) ---

void escribirDesconocidos(ofstream &output, char** diccDesconocido, int* frecuenciaDesconocido, int tamDesconocido) {
    output << left << setw(15) << "Palabra" << "Frecuencia" << endl;
    for (int i=0; i < tamDesconocido; i++) {
        output << left << setw(15) << diccDesconocido[i] << frecuenciaDesconocido[i] << endl;
    }
}

int contadorPalabrasDistintas(int *arrConta, int tam) {
    int distinto = 0;
    for (int i=0; i < tam; i++) {
        if (arrConta[i] > 0) {
            distinto++;
        }
    }
    return distinto;
}

void creaResumenGeneral(int cantOtros, int cantPalabras, int cantDesconocido, int tamDesconocido,
                        ofstream& output, int tamOtros, int tamPalabras,
                        int* arrContaOtros, int* arrContaPalabras) {

    int total = cantOtros + cantPalabras + cantDesconocido;
    int distContenido = contadorPalabrasDistintas(arrContaPalabras, tamPalabras);
    int distOtro = contadorPalabrasDistintas(arrContaOtros, tamOtros);
    int distDesconocido = tamDesconocido;
    int vocab = distOtro + distContenido + distDesconocido;

    output << "============================================================" << endl;
    output << "REPORTE 1: RESUMEN GENERAL" << endl;
    output << "============================================================" << endl;
    output << fixed << setprecision(2) << left;
    output << setw(15) << "Categoria" << right << setw(10) << "Tokens" << setw(10) << "%"
            << setw(12) << "Distintas" << endl;
    output << left << setw(15) << "CONTENIDO" << right << setw(10) << cantPalabras
            << setw(10) << 100.0 * cantPalabras / total << setw(12) << distContenido << endl;
    output << left << setw(15) << "OTROS" << right << setw(10) << cantOtros
            << setw(10) << 100.0 * cantOtros / total << setw(12) << distOtro << endl;
    output << left << setw(15) << "DESCONOCIDA" << right << setw(10) << cantDesconocido
            << setw(10) << 100.0 * cantDesconocido / total << setw(12) << distDesconocido << endl;
    output << endl;
    output << left;
    output << "Total de palabras (tokens) .........." << total << endl;
    output << "Vocabulario (palabras distintas) ....." << vocab << endl;
    output << "Riqueza lexica (TTR) ................." << (double)vocab / total << endl;
}

void swapInt(int& a, int& b) {
    int aux = a;
    a = b;
    b = aux;
}

//? --- HISTOGRAMA ---

void ordenarFrecuencias(char** dicc, int tam, int* frecuencia) {
    //* Ordenamiento descendente
    for (int i=0; i < tam - 1; i++) {
        for (int j=i+1; j < tam; j++) {
            if (frecuencia[i] < frecuencia[j] or
                (frecuencia[i] == frecuencia[j] and strcmp(dicc[i], dicc[j]) > 0)) {
                intercambiar(dicc[i], dicc[j]);
                swapInt(frecuencia[i], frecuencia[j]);
            }
        }
    }
}

void generarRelleno(ofstream &output, char car, int n) {
    for (int j=0; j < n; j++) {
        output << car;
    }
    output << " (" << n << ")" << endl;
}

void crearHistograma(ofstream &output, char** diccPalabras, int tamPalabras, int* arrContaPalabras) {
    ordenarFrecuencias(diccPalabras, tamPalabras, arrContaPalabras);
    output << "REPORTE 2: HISTOGRAMA" << endl;
    for (int i =0; i < tamPalabras and arrContaPalabras[i] > 0; i++) {
        output << left << setw(12) << diccPalabras[i] << "| ";
        generarRelleno(output, '#', arrContaPalabras[i]);
    }
}

//? --- RANKING ---

void imprimirPorFilaRanking( ofstream &output, int pos, char* palabra, const char* categoria, int frecuencia) {
    output << left << setw(6) << pos << setw(15) << palabra << setw(12) << categoria << frecuencia << endl;
}

void generarRankingGeneral(ofstream &output, char** diccPalabras, int tamPalabras, int* arrContaPalabras,
                           char** diccOtros, int tamOtros, int* arrContaOtros) {
    ordenarFrecuencias(diccPalabras, tamPalabras, arrContaPalabras);
    ordenarFrecuencias(diccOtros, tamOtros, arrContaOtros);

    int indexPalabra = 0, indexOtros = 0, pos =0;
    while (true) {
        bool quedanPalabrasEnElArreglo = indexPalabra < tamPalabras and arrContaPalabras[indexPalabra] > 0;
        bool quedanOtrosEnElArreglo = indexOtros < tamOtros and arrContaOtros[indexOtros] > 0;

        if (not quedanPalabrasEnElArreglo and not quedanOtrosEnElArreglo) break;

        if (quedanPalabrasEnElArreglo and (not quedanOtrosEnElArreglo or
            arrContaPalabras[indexPalabra] > arrContaOtros[indexOtros] or
            (arrContaPalabras[indexPalabra] == arrContaOtros[indexOtros] and strcmp (diccPalabras[indexPalabra], diccOtros[indexOtros]) < 0))) {
            imprimirPorFilaRanking(output, pos, diccPalabras[indexPalabra], "CONTENIDO", arrContaPalabras[indexPalabra]);
            indexPalabra++;
        } else { //* Lo contrario
            imprimirPorFilaRanking(output, pos, diccOtros[indexOtros], "OTROS", arrContaOtros[indexOtros]);
            indexOtros++;
        }
        pos++;
    }
}


//? --- GENERACION DE TODOS LOS REPORTES ---

void generarReportes(char** diccDesconocido, int* frecuenciaDesconocido, int tamDesconocido,
                     int cantOtros, int cantPalabras, int cantDesconocido, int tamOtros, int tamPalabras,
                     int* arrContaOtros, int* arrContaPalabras,
                     char** diccPalabras, char** diccOtros) {
    ofstream outputDesconocidos; openWriteFile(outputDesconocidos, "ArchivosDeReporte/desconocidos.txt");
    ofstream outputResumen; openWriteFile(outputResumen, "ArchivosDeReporte/resumen.txt");
    ofstream outputHistograma; openWriteFile(outputHistograma, "ArchivosDeReporte/histograma.txt");
    ofstream outputRankingGeneral; openWriteFile(outputRankingGeneral, "ArchivosDeReporte/rankingGeneral.txt");

    escribirDesconocidos(outputDesconocidos, diccDesconocido, frecuenciaDesconocido, tamDesconocido);
    creaResumenGeneral(cantOtros, cantPalabras, cantDesconocido, tamDesconocido,
                        outputResumen, tamOtros, tamPalabras,
                        arrContaOtros, arrContaPalabras);
    crearHistograma(outputHistograma, diccPalabras, tamPalabras, arrContaPalabras);
    generarRankingGeneral(outputRankingGeneral, diccPalabras, tamPalabras, arrContaPalabras,
                           diccOtros, tamOtros, arrContaOtros);
}

void liberarMemoria(char** diccDesconocido,
                     int* arrContaOtros, int* arrContaPalabras,
                     char** diccPalabras, char** diccOtros,
                     int tamOtros, int tamPalabras, int tamDesconocido) {
    //* Forma de eliminar los arreglos de cadenas
    for (int i=0; i < tamDesconocido-1; i++) {
        delete[] diccDesconocido[i];
    }
    for (int i=0; i < tamOtros-1; i++) {
        delete[] diccOtros[i];
    }
    for (int i=0; i < tamPalabras-1; i++) {
        delete[] diccPalabras[i];
    }
    //* Eliminacion de memoria de los punteros ( de aquellos arreglos que son de memoria dinamica)
    delete[] diccOtros;
    delete[] diccPalabras;
    delete[] arrContaOtros;
    delete[] arrContaPalabras;
}