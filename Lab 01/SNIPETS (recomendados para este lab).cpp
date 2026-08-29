
//FUNCIONES RECOMENDADAS PARA ESTE LAB (PRIMERO ENTIENDANLAS)

void print_line(char character){ //character pues pueden haber diferenes tipos de line '=' o '-'
  for(int i=0; i <= ANCHO_REPORTE; i++) cout.put(character); // puede ser meramente cout tambien btw 
  cout << endl;
}

void generate_whitespaces(int width) { //Se usa mas que todo en arreglo de caracteres o para un tabulador (extraño que pase - pero sucede)
    for (int i=0; i<=width; i++) cout << ' ';
}

//En esta parte se hacen arreglos de valores pues pueden pedir evaluar e imprimir de mayor a menos mas adelante
//Es bueno ir mecanisandose de esta forma (al fin y al cabo son SNIPETS)

//Considerar esta parte para fechas (se pasa todo a dias para trabajar btw)
int read_date() {
    // 1/04/2023
    int dd, mm, yyyy, date;
    char c;
    cin >> dd >> c >> mm >> c >> yyyy;
    date = yyyy*10000 + mm*100 + dd; //20230401
    return date;
}

void print_date(int date) {
    int day, month, year;
    year = date / 10000;
    month = (date/100) % 100;
    day = date % 100;
    cout << setw(2) << setfill('0') << day << '/';
    cout << setw(2) << setfill('0') << month;
    cout << "/" << year << setfill(' ') << endl; //01/04/2023
}

//Considerar esta parte para tiempos - (se pasa todo a segundos para imprimir btw)

int read_time() {
    //01:13:00
    int hh, mm, ss, time;
    char c;
    cin >> hh >> c >> mm >> c >> ss;
    time = hh*3600 + mm*60 + ss; // El tiempo pero en segundos
    return time;
}

void print_time(int time) {
    int sec, min, hour;
    hour = time / 3600;
    min = (time / 60) % 60;
    sec = time % 60;

    cout  << right << setfill('0') << setw(2) << hour <<
        ':' << setw(2) << min <<
             ':' << setw(2) << sec << setfill(' ');
    for (int i=8; i< ANCHO_REPORTE/N_COLUMMNS; i++) {
        cout << ' ';
    }
}


//Puede que esto no sirva pues usualmente los nombres se obian (no lo solicitan), pues realmente son una cadena de caracteres
//Sin embargo hay un truco si es que lo pidiesen
//Se necesita tener control en que momento imprimir esto osea necesitas lectura e impresion dinamica (no tener una seccion lectura -> impresion)
void read_and_print_name_without_arr_cad() {
    //N_Sparsholt
    int i =1;
    char c;
    cin >> c; //1 = PRIMERA LETRA EN MAYUSCULA
    cout << left << c;
    cin.get(c); //
    while (c != ' ') { // 2 = '_' y 3 es otra letra en mayuscula

       if (c == '_') {
           cout << ' ';
       }
       else {
           if (c >= 'a' and c <= 'z'){
               c = c - 'a' + 'A'; // guia del ASCII (suma para mayusculas)
           }
           cout << c;
       }

        cin.get(c); //Obtencion del caracter dentro del bucle
        i++;
    }
    while (i < ANCHO_REPORTE/N_COLUMMNS) {
        cout << ' ';
        i++;
    }
    cin.clear();
}
