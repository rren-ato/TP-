//
// Created by Renato on 23/09/2026.
//

#include "FuncionesAuxiliares.h"

//? Ya se permite la apertura con estas funciones (son muy utiles y reusables)
void open_read_file(ifstream &input, const char* file_name) {
    input.open(file_name);
    if (not input.is_open()) {
        cerr << "El archivo " << file_name << " no se pudo leer" << endl;
        exit(1);
    }
}

void open_write_file(ofstream &output, const char* file_name) {
    output.open(file_name);
    if (not output.is_open()) {
        cerr << "El archivo " << file_name << " no se pudo leer" << endl;
        exit(1);
    }
}

//? Recordar que imprime y que lee

void print_line(ofstream &output,int width, char character) { //? '-' / '_' / '='
    for (int i=0; i<=width; i++) output.put(character);
    output << endl;
}

void ignorar_coma(ifstream &input) { //? input << sep << dato
    char c;
    input.get(c);
}

int read_ID(ifstream &input) {
    int p1, p2, p3;
    char c;
    input >> p1 >> c >> p2 >> c >> p3;
    return p1 * 1000000 + p2 * 10000 + p3;
}

int read_date (ifstream &input) {
    //12/12/2023
    int dd, mm, yyyy;
    char c;
    input >> dd >> c >> mm >> c >> yyyy;
    return yyyy*10000 + mm*100 + dd;
}

void print_date(ofstream &output, int width, int fechasTriajes) {
    int day, month, year;
    year = fechasTriajes / 1000;
    month = (fechasTriajes/100) % 100;
    day = fechasTriajes % 100;
    output << setfill('0') << setw(2) << day << "/" << setw(2) << month << setfill(' ') << "/" << year;
    //* GENERAR ESPACIADO
    for (int i=10; i<=width; i++) output.put(' ');
}

int read_time(ifstream &input) {
    int mm, ss, hh;
    char c;
    input >> hh >> c >> mm >> c >> ss;
    return hh*3600 + mm*60 + ss;

}


//! PARA ARREGLOS ESTA ES LA FORMA QUE NO ES RECOMENDADA - TRATAR DE EVITAR PENSAR ASI EN ESTE LAB Y PARCIAL
//?
// void generar_reportes(const char* fileEspecialidades, const char* filePacientes, const char* fileTriaje,
//                      const char* reporte) {
//     ifstream inputEspecialidades; open_read_file(inputEspecialidades, fileEspecialidades);
//     ifstream inputPacientes; open_read_file(inputPacientes, filePacientes);
//     ifstream inputTriaje; open_read_file(inputTriaje, fileTriaje);
//     ofstream outputReporte; open_write_file(outputReporte, reporte);
//
//     leer_pacientes(inputPacientes, odigosPacientes, edadesPacientes, sexosPacientes)
// }

//! PENSAR UNICAMENTE QUE LA LECTURA SE DA POR FUNCIONES - SE LLENAN LOS ARREGLOS Y LUEGO SE PUEDE IMPRIMIR
void llenar_pacientes(const char* filePacientes, int *codigosPacientes, int *edadesPacientes, char *sexosPacientes,
                      int &cantPacientes) {
    //! {"id": 1, "dni": "469-84-4163", "nombre": "Dunston/Rossoni-P.", "sexo": "F", "edad": 47}
    ifstream inputPacientes; open_read_file(inputPacientes, filePacientes);
    int i =0;
    while (true) {
        if (inputPacientes.peek() == '{') {
            inputPacientes.ignore(10000,',');               //*   {"id": 1,
            inputPacientes.ignore(10000,':');               //*    "dni":
            inputPacientes.ignore(10000,'"');               //*    "
        }
        codigosPacientes[i] = read_ID(inputPacientes);
        if (codigosPacientes[i] == 0) break; //!             osea el arreglo no lee nada
        //* NO SE GUARDA EL NOMBRE XQ AUN NO ENSEÑAN ARREGLO DE CARACTERES
        inputPacientes.ignore(10000,':');                   //*     ", "nombre":
        inputPacientes.ignore(10000,',');                   //*      "Dunston/Rossoni-P.",
        inputPacientes.ignore(10000,':');                   //*      "sexo":
        inputPacientes.ignore(10000,'"');                   //*      "
        inputPacientes >> sexosPacientes[i];
        inputPacientes.ignore(10000,':');                   //*    ", "edad":
        inputPacientes >> edadesPacientes[i];
    }
    cantPacientes = i; //*COLOCAR "CANT" EN CADA ARREGLO ME PARECE ENGORROSO
}

void llenar_especialidades(const char* fileEspecialidades, int *codigosEspecialidades, double *costosEspecialidades,
                           int &cantEspecialidades) {
    //! {"id": 1, "codigo": 576, "nombre": "Pediatria", "costo": 268.65}
    ifstream inputEspecialidades; open_read_file(inputEspecialidades, fileEspecialidades);
    int i =0;
    while (true) {
        if (inputEspecialidades.peek() == '{') {
            inputEspecialidades.ignore(10000,',');               //*   {"id": 1,
            inputEspecialidades.ignore(10000,':');               //*    "codigo":
            inputEspecialidades.ignore(10000,'"');               //*    "
        }
        inputEspecialidades >> codigosEspecialidades[i];
        if (codigosEspecialidades[i] == 0) break;
        //* NO SE GUARDA EL NOMBRE XQ AUN NO ENSEÑAN ARREGLO DE CARACTERES
        inputEspecialidades.ignore(10000,':');                   //*     ", "nombre":
        inputEspecialidades.ignore(10000,',');                   //*       "Pediatria",
        inputEspecialidades.ignore(10000,':');                   //*      "sexo":
        inputEspecialidades.ignore(10000,'"');                   //*       "costo":
        inputEspecialidades >> costosEspecialidades[i];
    }
    cantEspecialidades = i; //*COLOCAR "CANT" EN CADA ARREGLO ME PARECE ENGORROSO
}


//? BUSQUEDAS (RETORNAN EN QUE POSICION (i) ENCONTRARON EL VALOR)
int buscarPaciente(int codigoPaciente, int *arrCodigosPacientes) {
    for (int i=0; arrCodigosPacientes[i] != 0; i++) {
        if (codigoPaciente == arrCodigosPacientes[i]) return i;
    }
    //* SI SALES Y NO HAY COINCIENCIAS - SE RETORNA NO ENCONTRADO (-1) <-- Yo defino esto en el .h
    return NOT_FOUND;
}

int buscarEspecialidad(int codigoEspecialidad, int *arrCodigosEspecialidades) {
    for (int i=0; arrCodigosEspecialidades[i] != 0; i++) {
        if (codigoEspecialidad == arrCodigosEspecialidades[i]) return i;
    }
    //* SI SALES Y NO HAY COINCIENCIAS - SE RETORNA NO ENCONTRADO (-1) <-- Yo defino esto en el .h
    return NOT_FOUND;
}

void llenar_triaje(const char* fileTriaje,int *CodigosPacientes,int *CodigosEspecialidades,double *costosEspecialidades,
                   int *fechasTriajes, int *frecuenciasTriajes, int *presionesSisTriajes, int *presionesDiasTriajes,
                   double *temperaturaMaxTriajes, double *CostoTotal) {
    //! Fecha,ID,FC,PAS,PAD,Temperatura,SpO2,Codigo_Especialidad,Hora       <--- OJO CON EL ENCABEZADO
    //! 12/04/2023,698-47-1909,101,154,93,36.7,94,716,03:25:07
    int fecha=0, codigoPacienteTriaje=0, frecuenciaC, presionSistolica=0, presionDiastolica=0, duracion=0;
    int codigoEspecialidadTriaje=0; double temperatura=0.0, costo=0.0;
    double oxigenacion=0.0; //* <---- VALOR DUMMY (SE PUEDE IGNORAR)
    int posPaciente=0, posEspecialidad=0;
    ifstream inputTriaje; open_read_file(inputTriaje, fileTriaje);
    while (true) {
        if (inputTriaje.peek() == '#') inputTriaje.ignore(10000,'\n');      //* Encabezado
        fecha = read_date(inputTriaje);
        if (inputTriaje.eof()) break;
        codigoPacienteTriaje = read_ID(inputTriaje);
        inputTriaje >> frecuenciaC;                 ignorar_coma(inputTriaje);
        inputTriaje >> presionSistolica;            ignorar_coma(inputTriaje);
        inputTriaje >> presionDiastolica;           ignorar_coma(inputTriaje);
        inputTriaje >> temperatura;                 ignorar_coma(inputTriaje);
        inputTriaje >> oxigenacion;                 ignorar_coma(inputTriaje);  //* <--- Aqui se lee valor Dummy
        //? Pudo ser tambien inputTriaje.ignore(10000, ',')
        inputTriaje >> codigoEspecialidadTriaje;    ignorar_coma(inputTriaje);
        //* BUSQUEDA DE COINCIDENCIA (NO SE PUEDE IMPRIMIR AQUI)
        posPaciente = buscarPaciente(codigoPacienteTriaje, CodigosPacientes);
        posEspecialidad = buscarEspecialidad(codigoEspecialidadTriaje, CodigosEspecialidades);
        //? ETAPA DE GUARDADOS
        if (posPaciente != NOT_FOUND and posEspecialidad != NOT_FOUND) {
            duracion = read_time(inputTriaje);
            //! se remplaza el i por la posicion encontrada (MATCH)
            costo = costosEspecialidades[posEspecialidad]; //* SE BUSCA PASAR EL DATO DE UN ARREGLO A OTRO (LINKEO)
            if (temperaturaMaxTriajes[posPaciente] < temperatura) {
                fechasTriajes[posPaciente] = fecha;
                frecuenciasTriajes[posPaciente] = frecuenciaC;
                presionesSisTriajes[posPaciente] = presionSistolica;
                presionesDiasTriajes[posPaciente] = presionDiastolica;
            }
            //* SE GUARDA EL COSTO EN FUNCION A LAS POSICIONES DEL PACIENTE - LINKEO COMPLETO DE INFORMACION
            CostoTotal[posPaciente] += (costo/3600) * duracion;

        }
        else {
            //* NO SE ENCUENTRA LOS VALORES POR ENDE IGNORAS TODA LA LINEA
            inputTriaje.ignore(10000,'\n');
        }
    }

}

//? EN UN REPORTE LA BUENA PRACTICA REALMENTE SERIA
//* PERO UNO NO ESTA OBLIGADO A HACERLO (PROF HUIZA)
// void imprimirReporte(const char *fileReporte,const int *CodigosPacientes,const int *EdadesPacientes,const char *SexosPacientes,
//                      const int *fechasTriajes,const int *frecuenciasTriajes,const int *presionesSisTriajes,
//                      const int *presionesDiasTriajes,const double *temperaturaMaxTriajes,const double *CostoTotal);

void imprimirReporte(const char *fileReporte, int *CodigosPacientes, int *EdadesPacientes, char *SexosPacientes,
                     int *fechasTriajes, int *frecuenciasTriajes, int *presionesSisTriajes, int *presionesDiasTriajes,
                     double *temperaturaMaxTriajes, double *CostoTotal) {
    ofstream outputReporte; open_write_file(outputReporte, fileReporte);
    int cant = 0, edadTotal = 0, sistolicaTotal = 0, diastolicaTotal = 0, frecuenciaTotal = 0;
    double temperaturaTotal = 0.00, costoTotal = 0.00;
    //* Imprimir el Header

    for (int i = 0; CodigosPacientes[i] != 0; i++) {
        //* Descuentos circunstanciales por edad
        print_date(outputReporte, 16, fechasTriajes[i]);
        if (EdadesPacientes[i] < 18) CostoTotal[i] *= 0.95;
        else if (EdadesPacientes[i] > 64) CostoTotal[i] *= 0.82;
         outputReporte << setfill('0') << setw(2) << i + 1 << setfill(' ') << ")" <<
             setw(12) << CodigosPacientes[i] << setw(6) << SexosPacientes[i] << setw(6) << "" <<
                 setfill('0') <<setw(2) << EdadesPacientes[i] << setfill(' ') <<
                     setw(15) << temperaturaMaxTriajes[i] << setw(17) << presionesSisTriajes[i] <<
                         setw(17) << presionesDiasTriajes[i] << setw(20) << frecuenciasTriajes[i] << setw(8) << "";
        //* IMPRIMIR FECHA
        outputReporte << setw(14) << CostoTotal[i] << endl;
        //* GUARDADO DE VALORES PARA PROMEDIO
        edadTotal += EdadesPacientes[i];
        sistolicaTotal += frecuenciasTriajes[i];
        diastolicaTotal += presionesSisTriajes[i];
        frecuenciaTotal += presionesDiasTriajes[i];
        temperaturaTotal += temperaturaMaxTriajes[i];
        costoTotal += CostoTotal[i];
        cant++;
    }
    print_line(outputReporte,ANCHO_REPORTE, '-');
    //* IMPRIMIR PROMEDIOS
    
}

