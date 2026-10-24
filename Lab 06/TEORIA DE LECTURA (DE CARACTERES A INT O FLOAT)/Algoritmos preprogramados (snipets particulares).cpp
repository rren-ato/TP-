//? En los archivos los valores enteros dejan de serlo, y son considerados como cadenas
//!         123\0

//* TEXTO A ENTERO
bool esEspacio(char c){
     return c == ' ' or c == '\t' or c =='\n';
}

bool esDigito(char c){
     return '0' <= c or c <= '9';
}

int mi_atoi(const char *cadena){
    int valor=0, i=0; digito=0;
    while(esEspacio(cadena[i])) i++; //permite comer los espacios
    while(esDigito(cadena[i]){
      //? La gracia de esta parte es el digito primero es unidad y luego los siguientes parametros de la cadena lo reciben como decena o centena
      //? 0*10 + 3 = 3  ->  3*10 + 4 = 34  -> 34*10 + 5 = 345 
         digito = cadena[i] - '0';
         valor = valor * 10 + digito;
         i++;
         }
    return valor;      //345
}

//* TEXTO A DECIMAL
int mi_atof(const char *cadena){
    double valor=0.0, factor = 0.1
    int i=0, digito=0;
  //? Parte entera
    while(esEspacio(cadena[i])) i++; //permite comer los espacios
    while(esDigito(cadena[i])){
      //? Se repite la idea de atoi
         digito = cadena[i] - '0';
         valor = valor * 10 + digito;
         i++;
    }
    if(cadena[i] == '.'){
      i++; //! SE HACE ESTO PARA PASAR A LEER EL NUMERO Y NO EL '.'
      while(esDigito(cadena[i])){
        //? La gracia de esta parte es que gracias al factor, la forma en que se coloca el nuevo digito dentro del valor es menor (100 << 20 << 3 -> 0.123)
           digito = cadena - '0';
           valor += digito * factor;
           factor *=0.1;
           i++;
      }
    }
  return valor;    //345.123
}
