
#include <iostream>;
#include <fstream>;
#include <cstring>;
#include <cctype>;
#include <iomanip>;

using namespace std;


void crearLista(const char* fileName, struct Nodo *& lista);
void imprimirLista(struct Nodo *lista);
void insertarAlInicio( struct Nodo *& lista, int dato);
void insertarAlFinal( struct Nodo *& lista, int dato);
void insercionOrdenada(struct Nodo *& lista, int dato);
void eliminarDeLaLista(int dato, struct Nodo *& lista);
void eliminarLista(struct Nodo *& lista);
