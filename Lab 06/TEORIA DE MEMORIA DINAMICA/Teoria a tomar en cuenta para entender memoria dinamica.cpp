
//? En el heap nada tiene nombre, solo se trabaja con direcciones de memoria. Por ende si la memoria se pierde o se leakea no se va a econtrar el valor
void sumar(int a, int b, int *&s){
  int *c = new int;    //! Se reserva un espacio de memoria en el heap (memoria dinamica)
  *c = a + b;          //! Se actualiza su valor ('*') en la direccion de memoria
  s = c                //! S linkea el espacio de memoria de C para extraerlo
    //! c se pierde pues esta declarado de forma local pero al extraerlo con S se guarda su valor pues se tiene su direccion de memoria

    //* Aca no puede aparecer el delete, si no seria un danglin' pointer; la maquina obtendria un dato basura.
}


//!      En el main seria algo asi

int main(){
  int *s;
  sumar(3,5,s);
  cout << *s << endl;
  delete s;            //* Para prevenir un leakeo de memoria uno debe borrar el dato que se guardo en el heap; pues si no se hace ahora, este persistira.
                      
  return 0;
}
