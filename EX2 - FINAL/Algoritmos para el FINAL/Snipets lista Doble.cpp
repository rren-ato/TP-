
void insertarAlFinal(struct Nodo *&lista, struct OtraStruct& valor){
    struct Nodo *p = lista;
    struct Nodo * nuevo;
    nuevo = new struct Nodo;
    nuevo->siguiente = dato
    
}

void eliminarDeLaLista(const char* valorAbuscar, struct Nodo *&lista){
    struct Nodo* p = buscar(codigo, lista);
    if(not p){
        return false;
    }
    if(not p->anterior){
        lista = p->siguiente;
    }else{
        p->anterior->siguiente = p->siguiente
    }
    if(p ->siguiente){
        p->siguiente->anterior = p->anterior
    }
    //Liberar memoria
    
}
