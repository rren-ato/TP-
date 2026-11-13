
#include "Nodo.h"

#include "Bibliotecas/FuncionesAuxiliares.h"

void crearLista(const char* fileName, struct Nodo *& lista){
    ifstream input; openReadFile(input, fileName);
    int dato=0;
    lista = nullptr;
    while(true){
        input >> dato;
        if(input.eof())break;
        //* Inicio de lectura
        insercionOrdenada(lista, dato);
    }
}

void imprimirLista(struct Nodo *lista) {
    struct Nodo *recorrido;
    recorrido = lista;
    while (recorrido) {
        cout << setw(5) << recorrido->dato;
        recorrido = recorrido->siguiente;
    }
}



void insertarAlInicio( struct Nodo *& lista, int dato){
    struct Nodo *nuevo;
    nuevo = new struct Nodo;
  //* Insersion natural de informacion
    nuevo->dato = dato;
  //* Cambio de puntero
    nuevo->siguiente = lista
    lista = nuevo;
}

void insertarAlFinal( struct Nodo *& lista, int dato){
  //* Recorrido (tambien llamado p) es el que se desplaza realmente
  //? Tomar en cuenta que es como una mira telescopica - si recorrido o p cambia, lo hace tambien la lista
    struct Nodo *recorrido = lista;
    struct Nodo *nuevo;
    nuevo = new struct Nodo;
  //* Nuevo lo usamos como un borrador para evaluar (un auxiliar)
    nuevo->dato = dato;
  //* Cambio de puntero (dato por dato)
    nuevo->siguiente = nullptr;
    if(lista == nullptr){    //* si la lista esta vacia simplemente se llena (recordar que lista no es puntero - p si lo es)
        lista = nuevo;
    }else{ 
        while( recorrido->siguiente != nullptr){ //* Aqui entramos si la lista no esta vacia y recorrido que es el puntero a desplazar detecta que hay otrs datos...
              recorrido = recorrido->siguiente;  //* 
        }
      //* Recorrido queda abierto a mas enganches
        recorrido->siguiente = nuevo;
    }
}

void insercionOrdenada(struct Nodo *& lista, int dato){
    //* Doble puntero...
    struct Nodo* recorrido = lista;
    struct Nodo* anterior = nullptr;
    struct Nodo* nuevo;
    nuevo = new struct Nodo;
    nuevo->dato = dato;
    while(recorrido != nullptr and recorrido->dato < dato){
      //* Aqui es donde se presentan los cambios en el anterior y el recorrido (o p) se desplaza
        anterior = dato;
        recorrido = recorrido->siguiente;
      }
      nuevo->siguiente = recorrido;
    if(anterior == nullptr){
      lista = nuevo;
    }else{
      anterior->siguiente = nuevo;
}


void eliminarDeLaLista(int dato, struct Nodo *& lista){
    struct Nodo* recorrido;
    struct Nodo* anterior = nullptr;
    while(recorrido and recorrido->dato < dato){
        anterior = recorrido;
        recorrido = recorrido->siguiente;
      }
    if(recorrido and recorrido->dato == dato){
        if(anterior == nullptr){
          lista = lista->siguiente;
        }else{ 
          anterior->siguiente = recorrido->siguiente;
        }
        delete recorrido;
    }
}

void eliminarLista(struct Nodo *& lista){
    struct Nodo* salida;
    while(lista){
        salida = lista;
        lista = lista->siguiente;
        delete salida;
    }
}


