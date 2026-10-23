//?  Cadenas Estaticas (stack)
char cadenaEstatica[20];
//?Lectura de la cadena
input.getline(cadenaEstatica, cantidadReferencial, delim); //* el delimitador puede ser una coma, un espacio en blanco o fin de archivo
input.getline(cadenaEstatica, cantidadReferencial); //* De esta forma meramente el sistema asume que el delim es \n

//*  Al llegar al fin de la cantidad Referencial... (LA RECOMENDACION POR ELLO ES USAR UNA CANTIDAD REFERENCIAL GRANDE)
input.clear()  //?  Necesitas levantar la bandera pues si usas getline al final levantas un failbit (.fail)


//! NOVEDADES (APARTIR DE AHORA)
//?  Creacion de funciones (en este lab esta prohibido usar cstring)


//* Longitud de la cadena (strlen)
//? ESTO ES SUMAMENTE IMPORTANTE PARA COPIAR
int mi_strlen(const char* Cadena){
    for(int nCaracteres =0; Cadena[i]; nCaracteres++) //? Se lee todo hasta el '\0'
    return nCaracteres;
}

//* Comparacion (strcmp)
int mi_strcmp(const char* cadena1, const char* cadena2){
    int i=0;
    while(cadena1[i] == cadena2[i]){
        if(cadena1[i] == 0) return 0;    //? Se llega al fin de cadena '\0'
        i++;
    }
    return cadena1[i] - cadena2[i];
  //? Si el resultado es 0 <-- Ambas cadenas son iguales
  //* Considerando un ordenamiento ascendente (de menor a mayor)
  //? Si el resultado es > 0 <-- Cadena 1 va despues de Cadena 2
  //? Si el resultado es < 0 <-- Cadena 2 va despues de Cadena 1
}

//* Compia (strcpy)
char arrNombre[20] = "Marco";  //? En la declaracion tambien puedes leer (pero esto seria hard code)
char arrApellido[20];
mi_strcpy(arrApellido, "Garcia");

int mi_strcpy(char* arr, const char* CadenaACopiar){    //? Cadena a copiar pasa como "Hola\0"
    for(int i=0; palabraACopiar != 0; i++){
        arr[i] = palabraACopiar[i];
    }
  
}

//* Concatenar (strcat)  - Concatenar quiere decir que añades un extra en la parte final
char nombre[40] = "Juana";
mi_strcat(nombre, "Perez");

void mi_strcat(const char* cadena1, const char* cadena2){
     int pos = mi_strlen(cadena1);      //? llegas al "Hola| |\0"
     mi_strcpy(&cadena1[pos], cadena2[i]);
}

//* Busquedas (strstr) 
bool corresponde (const char* cadena1, const char* cadena2){
     for(int i=0; cad[i]; i++){
         if(cad[i] != cad[i]) return false;
     }
     return true;
}

char mi_strstr(char* cadena1, const char* cadena2){    //? Llamenlo doble if (asi les cuadra mas rapido)
     for (int i=0; cad1[i];i++){
       if(cadena1[i] == cadena2[i]){
         if(corresponde(&cadena1[i], cadena2[i])) return &cadena[i];     
     }
     return nullptr;
}
