//? INSERCION DE DATOS EN LOS ARREGLOS DE FORMA ORDENADA
  bool insertarOrdenado(int* arrNumero, int capacidad, int& longitud, int numero) {
    if (longitud >= capacidad) {
        return false;
    }

    int i = longitud - 1;
    while (i >= 0 && arrNumero[i] > numero) {
        arrNumero[i + 1] = arrNumero[i]; // desplazamos a la derecha
        i--;
    }

    numeros[i + 1] = numero; // insertamos el nuevo número
    longitud++;
    return true
}

//! PERO CON BUSQUEDA

int buscarPosicionOrdenada(int* arrCodigos, int longitud, int nuevo) {
  for (int i = 0; i < tamanio; i++) {
    if (codigos[i] > nuevo) {
      return i;
    }
  }
  return tamanio;
}
//-----------------------------------------
bool insertarOrdenado(int* arrCodigos, double* arrCiclos, int& longitud,
  int capacidad, int codigo, double ciclo) {
  
  if (tamanio >= capacidad) return false;
  
  int pos = buscarPosicionOrdenada(codigos, longitud, codigo);
  
  for (int i = tamanio; i > pos; i--) { // de atras hacia adelante
    arrCodigos[i] = arrCodigos[i - 1];
    arrCiclos[i] = arrCiclos[i - 1]; // los DOS arreglos
  }
  
  arrCodigos[pos] = codigo;
  arrCiclos[pos] = ciclo;
  longitud++;
  return true;
  }


//? ORDENAMIENTO
//* El ordenamiento funciona para cuando los datos ya se encuentran leidos en los arreglos
//! CHEQUEAR SI SE NECESITA ASCENDENTEMENTE O DESCENDENTEMENTE
int swapInt (int &a, int &b){  // 1 y 5
  int aux;
  aux = a;  // aux = 1
  a = b;    // a = 5
  b = aux   // b = 1
}                                //Resultado: 5 y 1

char swapChar (char &a, char &b){
  char aux;
  aux = a;  // aux = 1
  a = b;    // a = 5
  b = aux   // b = 1
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

    for(int j = i+1; i<n; j++){
      if(arrNota[j] > arrNota[posMenor]){
        posMenor = j;
      }
      if (posMenor =! i){
        swap(posMenor[i], posMenor[posMenor]) // posMenor en este momento es j
      }
    }
  }
}

//? Ordenamiento TIPO BURBUJA (DUALES)
//* Funcionamiento de pares comparativos hasta el limite de valores

void bubble_sort(int *arr, int n){
  for(int i=0; i < num -1; i++){
    for(int j= i+1; i< num -1 -j; j++){
      if(arr[j] > arr[j+1]){
        swapInt(arr[j], arr[j+1]);
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

  while(inicio <= fin){
    int medio = izquierda + (derecha - izquierda)/2;
      //* |1|2|*3|4|5| ==> |3|*4|5|
    if(datos[medio] == valorAbuscar){
      return medio; // la posicion i
        } else if (datos[medio] < valorAbuscar){
            inicio = medio + 1;
        } else {
            fin = medio + 1;
        }
  }
  return NOT_FOUND; // esto es -1; ==> definido en el .h (Utils)
}




