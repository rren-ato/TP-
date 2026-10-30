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
//! Verificar con lo que hizo huiza (creo que hay un error)
void remplazar (char* textoOrigen, const char* cadenaBuscar, const char* cadenaRemplazar){
     char aux[200], *pt;
     *ptr = strstr(textoOrigen, cadenaBuscar);                
     if(pt == nullptr) return;                       
     *pt = 0;                                        
     strcpy(aux, texto);                          
     strcat(aux, cadenaRemplazar);                
    
   
     strcat(aux, &pt[mi_strlen(cadenaBuscar)]);   
    //! ACTUALIZACION DE CADENA
     strcpy(textoOrigen, aux);                    


//! Donde se encuentras mundo se remplaza con galaxia
remplazar(mensaje, "Mundo", "Galaxia);
cout << mensaje << endl;

