//? INSERCION DE DATOS EN LOS ARREGLOS DE FORMA ORDENADA
  bool insertarOrdenado(int* arrNumero, int capacidad, int& longitud, int numero) {
    if (longitud >= capacidad) {
        return false;
    }

    int i = longitud - 1;
    while (i >= 0 and arrNumero[i] > numero) {
        arrNumero[i + 1] = arrNumero[i]; // desplazamos a la derecha (SHIFT)
        i--;
    }

    arrNumero[i + 1] = numero; // insertamos el nuevo número
    longitud++;
    return true
}

//! PERO CON BUSQUEDA
//? Esta funcion indica la posicion donde deberia ir el nuevo dato
//Asumir que se sabe que en el tu funcion aparte es donde lees cada codigo (nuevo)
int buscarPosicionOrdenada(int* arrCodigos, int longitud, int nuevo) {
  for (int i = 0; i < longitud; i++) {
    if (arrCodigos[i] > nuevo) {
      return i;
    }
  }
  return longitud;   // si no encontró ninguno mayor, va al final
}

bool insertarOrdenado(int* arrCodigos, double* arrCiclos, int& longitud,      //!Asumir que se sabe que en el tu funcion aparte es donde lees cada codigo (nuevo)
                      int capacidad, int codigo, double ciclo) {    
  
  if (longitud >= capacidad) return false;
  
  int pos = buscarPosicionOrdenada(arrCodigos, longitud, codigo);
  
  // correr los elementos hacia la derecha (de atrás hacia adelante)
  for (int i = longitud; i > pos; i--) {
    arrCodigos[i] = arrCodigos[i - 1]; //aplastas el valor nuevo (y vas moviendo los datos hasta antes de llegar a tu pos)
    arrCiclos[i]  = arrCiclos[i - 1];
  }
  
  arrCodigos[pos] = codigo; //luego añades el valor que querias añadir
  arrCiclos[pos]  = ciclo;
  longitud++;
  return true;
}

//? INSERTAR DESORDENADAMENTE (PERO SIN REPETICION DE UN ELEMENTO)
bool insertarDesordenado(ifstream &input, int *arrClientes, int codigoCliente
                      int &cantClientes, int capacidad) {
    if (cantClientes >= capacidad) return false;

    //! Se necesita solo considerar la primera aparicion por codigo
    for (int i=0; i< cantClientes; i++) {
        if (arrClientes[i] == codigoCliente) return false;
        }
    //* Si se pasa el filtro de comparaciones entra la datta ya rellenada (entonces se coloca como nueva informacion en el arreglo)
    arrClientes[cantClientes] = codigoCliente;
    cantClientes++;
    return true;
}


//? ORDENAMIENTO
//* El ordenamiento funciona para cuando los datos ya se encuentran leidos en los arreglos
//! CHEQUEAR SI SE NECESITA ASCENDENTEMENTE O DESCENDENTEMENTE
void swapInt (int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

void swapDouble (double &a, double &b) {
    double aux = a;
    a = b;
    b = aux;
}

void swapChar (char &a, char &b) {
    char aux = a;
    a = b;
    b = aux;
}


void insertion_sort(int *arr, int n){ //el arr puede cambiar de tipo de dato
  for (int i=0; i< n-1; i++;){        //key = arr[i]  (posicion 0)
    for( int j= i+1; j < n; j++){     // arr[j] (posicion 1) - ESTA POSICION VA VARIANDO
      if(arr[j] > arr[i]){
         // Dependiendo de > o < se ordena de forma ACENDETEMENTE o DESCENDENTEMENTE respectivamente
        swapInt(arr[i], arr[j]); //* si el dato de la posicion 1 es mayor al de la posicion 0, se va ordenando
      }
    }
  }
}



//? Ordenamiento POR SELECCION [Eficiente pero al inicio puede resultar confuso]
//* Funciona a traves de encontrar las POSICIONES (por ello no se hacen intercambios "swap")
void selection_sort(double *arrNota, int n){
  for(int i=0; i<n-1; i++){
    int posMenor = i; // se hace esto pero no es necesario btw es namas para pedagogico
    //? posMenor se usa para orden ascendente - posMayor se usa para orden descentende

    for(int j = i+1; i<n; j++){
      if(arrNota[j] < arrNota[posMenor]){ //En este caso se esta ordenando descendentemente, pero si fuera descendente seria arrNota[j] > arrNota[posMenor]
        posMenor = j;
      }
      if (posMenor =! i){
        swap(arrNota[i], arrNota[posMenor]) // posMenor en este momento es j
      }
    }
  }
}

//? Ordenamiento TIPO BURBUJA (DUALES)
//* Funcionamiento de pares comparativos hasta el limite de valores

void bubble_sort(int *arr, int num){
  for(int i=0; i < num -1; i++){
    for(int j= 0; i< num -1 -i; j++){
      if(arr[j] > arr[j+1]){
        int aux = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = aux;
      }
    }
  }
}

//? BUSQUEDA
//* La busqueda binaria requiere que los datos esten previamente ordenados


int busquedaBinaria(int *arrdato, int n, int valorAbuscar){
  // si busco 4
  int izquierda = 0;
  int derecha = n-1;

  while(izquierda <= derecha){
    int medio = izquierda + (derecha - izquierda)/2;
      //* |1|2|*3|4|5| ==> |3|*4|5|
    if(arrdato[medio] == valorAbuscar){
      return medio; // la posicion i
        } else if (arrdato[medio] < valorAbuscar){
            izquierda = medio + 1;
        } else {
            derecha = medio + 1;
        }
  }
  return NOT_FOUND; // esto es -1; ==> definido en el .h (Utils)
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




