//? Ordenamiento segun dos parametros sin uso de matrices

//* Primero ordeno segun un parametro (el primero)
void ordenarAlumnosPorCiclos(int* arrCodigos, int* arrCiclos, double* arrPromedios, int num) {
  //! Esta funcion solo ordena ciclos y los guarda
    for (int i = 0; i < num - 1; i++) {
      //! m es como una bandera, pues al termino del ultimo dato, m = i + 1
        int m = i;
        for (int j = i + 1; j < num; j++) {
            if (arrCiclos[j] > arrCiclos[m]) {
                m = j;
            }
        }
        //! En este momento el m = i+1 entonces entra
        if (m != i) {
            swap(arrCodigos[i], arrCodigos[m]);
            swap(arrCiclos[i], arrCiclos[m]);
            swap(arrPromedios[i], arrPromedios[m]);
        }
    }
}



void ordenarAlumnosPorCicloYPromedio(int* arrCodigos, int* arrCiclos, double* arrPromedios, int num) {
    ordenarAlumnosPorCiclos(codigos, ciclos, promedios, num);
  //! Se define un inicio y un fin pues es para delimitar el intervalo donde ciclos se repite, de esta forma se ordena por intervalos
  //! Internamente se van a tener que ordenar tambien mediante un segundo parametro
    int ini = 0;
    while (ini < num) {
        int fin = ini;
        while (fin + 1 < num or arrCiclos[fin + 1] == arrCiclos[ini]) {
            fin++;
        }
      //! Se recibe el inicio y el fin del intervalo (para el primer dato == mayorDato , se define el inicio = 0 y el fin por ejemplo 5)
      //! Pero para el 3er ciclo que se ordena, el inicio y el fin seran otros numeros (esto esta linkeado a la posicion de los arreglos)
        ordenarAlumnosPorPromedio(codigos, ciclos, promedios, ini, fin);
        ini = fin + 1;
    }
}

//* Usamos meramente el parametro de cantidad de intervalos donde el primer dato es el mismo (osea estamos en un unico ciclo)
void ordenarAlumnosPorPromedio(int* arrCodigos, int* arrCiclos, double* arrPromedios, int ini, int fin) {
    for (int i = ini; i < fin; i++) {
        for (int j = ini; j < fin - (i - ini); j++) {
            if (arrPromedios[j] < arrPromedios[j + 1]) {
                swap(arrCodigos[j], arrCodigos[j + 1]);
                swap(arrCiclos[j], arrCiclos[j + 1]);
                swap(arrPromedios[j], arrPromedios[j + 1]);
            }
        }
    }
}

