//? Con las funciones ya definidas de la biblioteca cstring se pueden realizar diversas acciones

char mensaje[50] = "Hola Mundo";

cout << "/" << mensaje << "/" << endl; 

//* Longitud de cadena (se detiene en '\0')
cout << "Longitud: " << strlen(mensaje) << endl;

//* Agregar algo a la cadena al final
strcat(mensaje, ", a todos");
cout << "/" << mensaje << "/" << endl; 
cout << "Longitud: " << strlen(mensaje) << endl;


//* Comparar cadenas
char mensaje2[50] = "Hola Mundo";

if(strcmp(mensaje, mensaje2) ==0){
  cout << "Son iguales" << endl;
}


//* Busqueda de cadenas
char *ptr = strstr(mensaje, "Mundo");
if(ptr != nullptr){
  //! Imprime desde donde encontro la coincidencia hasta el final
  cout << ptr << endl;
}

//* Remplazar cadena




//! Donde se encuentras mundo se remplaza con galaxia
remplazar(mensaje, "Mundo", "Galaxia);
cout << mensaje << endl;

