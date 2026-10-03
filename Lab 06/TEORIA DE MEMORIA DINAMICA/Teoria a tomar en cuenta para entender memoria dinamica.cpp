
//? En el heap nada tiene nombre, solo se trabaja con direcciones de memoria. Por ende si la memoria se pierde o se leakea no se va a econtrar el valor
void sumar(int a, int b, int *&s){
  int *c = new int;    //! Se reserva un espacio de memoria en el heap (memoria dinamica)
  *c = a + b;          //! Se actualiza su valor ('*') en la direccion de memoria
  s = c                //! S linkea el espacio de memoria de C para extraerlo
    //! c se pierde pues esta declarado de forma local pero al extraerlo con S se guarda su valor pues se tiene su direccion de memoria
}
