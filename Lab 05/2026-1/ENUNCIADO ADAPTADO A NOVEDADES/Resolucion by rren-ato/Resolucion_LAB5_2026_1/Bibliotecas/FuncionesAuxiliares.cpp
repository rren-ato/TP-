//
// Created by Renato on 1/10/2026.
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
    year = fechasTriajes / 10000;
    month = (fechasTriajes/100) % 100;
    day = fechasTriajes % 100;
    output << setfill('0') << setw(2) << day << "/" <<
        setw(2) << month << setfill('0') << "/" <<
            setw(4) << year << setfill(' ');
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

bool insertarOrdenadoEsp(int *codigosEspecialidades, int *costosEspecialidades, int capacidad, int &longitud,
                      int codigo, int costo) {
    //! La longitud en el main esta definida como 0
    if (longitud >= capacidad) return false;

    int i = longitud - 1;
    while (0 <= i or codigosEspecialidades[i] > codigo) {
        codigosEspecialidades[i+1] = codigosEspecialidades[i];
        costosEspecialidades[i+1] = costosEspecialidades[i];
        i--;
    }
    codigosEspecialidades[i+1] = codigo;
    costosEspecialidades[i+1] = costo;
    longitud++;
    return true;
}

void llenar_especialidades(const char* file_name, int *codigosEspecialidades, int *costosEspecialidades,
                           int capacidad, int &longitud) {
    //! {"id": 1, "codigo": 576, "nombre": "Pediatria", "costo": 268.65}
    ifstream inputEspecialidades; open_read_file(inputEspecialidades, file_name);
    int codigo =0, costo =0;
    while (true) {
        if (inputEspecialidades.peek() == '{') {
            inputEspecialidades.ignore(10000, ',');
            inputEspecialidades.ignore(10000, ':');
            inputEspecialidades >> codigo;
            if (inputEspecialidades.eof())break;
            inputEspecialidades.ignore(10000, ':');
            inputEspecialidades.ignore(10000, ',');
            inputEspecialidades.ignore(10000, ':');
            inputEspecialidades >> costo;
            //? Insertar ordenado por codigo de especialidad ascendentemente
            if (not insertarOrdenadoEsp(codigosEspecialidades, costosEspecialidades, capacidad, longitud,
                                  codigo, costo)) break;
            //* Se insertara ordenado hasta que la funcion devuelva falso osea se llene
        }
    }
}


bool insertarOrdenadoPac(int *codigosPacientes, char *sexosPacientes, int *arrEdadPacientes,double *maxMontoPacientes,
                         int capacidad, int &longitud, int dni, char sexo, int edad, double montoMaximo) {
    //! La longitud en el main esta definida como 0
    if (longitud >= capacidad) return false;

    int i = longitud - 1;
    while (0 <= i or codigosPacientes[i] > dni) {
        codigosPacientes[i+1] = codigosPacientes[i];
        sexosPacientes[i+1] = sexosPacientes[i];
        arrEdadPacientes[i+1] = arrEdadPacientes[i];
        maxMontoPacientes[i+1] = maxMontoPacientes[i];
        i--;
    }
    codigosPacientes[i+1] = dni;
    sexosPacientes[i+1] = sexo;
    arrEdadPacientes[i+1] = edad;
    maxMontoPacientes[i+1] = montoMaximo;
    longitud++;
    return true;
}

void llenar_pacientes(const char* file_name, int *codigosPacientes, char *sexosPacientes, int *arrEdadPacientes,
                      double *maxMontoPacientes, int capacidad, int &longitud) {
    //!                         691-12-9990    Harbertson/Abrahim-H.    F    33    3757.55
    //! DATO INVALIDO ==>       198-35-6734      Goneau/Eykel-U.        M    49    0
    ifstream inputPacientes; open_read_file(inputPacientes, file_name);
    int dni =0, edad =0;        char sexo;      double montoMaximo = 0.0;
    while (true) {
        dni = read_ID(inputPacientes);
        if (inputPacientes.eof())break;
        inputPacientes.ignore(10000, '.');
        inputPacientes >> sexo;
        inputPacientes >> edad;
        inputPacientes >> montoMaximo;

        //? Insertar ordenado por codigo de especialidad ascendentemente
        if (not insertarOrdenadoPac(codigosPacientes, sexosPacientes, arrEdadPacientes,maxMontoPacientes,
                         capacidad, longitud, dni, sexo, edad, montoMaximo)) break;
    }
}

int busquedaBinaria(int *arrdato, int valorAbuscar, int n) {
    int izquierda = 0;
    int derecha = n-1;      //* no deberia ser sencillamente n ?

    while(izquierda <= derecha){
        int medio = izquierda + (derecha - izquierda)/2;
        //* |1|2|*3|4|5| ==> |3|*4|5|
        if(arrdato[medio] == valorAbuscar){
            return medio; // la posicion i
        } else if (arrdato[medio] < valorAbuscar){
            izquierda = medio + 1;
        } else {
            derecha = medio + 1;
        }
    }
    return NOT_FOUND; // esto es -1; ==> definido en el .h (Utils)
}

void llenar_atenciones(const char *file_name, int *fechasAtenciones, int *dnisAtenciones, int *especialidadesAtenciones,
                       int *horasAtenciones, int capacidad, int &longitud,
                       int *arrCodigoPaciente, int n_pacientes, int* arrCodigoEspecialidad, int n_especialidades) {
    //! Fecha,ID,Codigo_Especialidad,Hora
    //! 12/04/2023,698-47-1909,716,03:25:07
    ifstream inputAtenciones; open_read_file(inputAtenciones, file_name);
    int fecha =0, dniAtenciones =0, especialidadAtenciones =0, hora =0;
    while (true) {
        int posPacientes =0, posEspecialidades =0;
        if (inputAtenciones.peek() == '#') inputAtenciones.ignore(10000, '\n');
        fecha = read_date(inputAtenciones);
        if (inputAtenciones.eof()) break;
        ignorar_coma(inputAtenciones);
        dniAtenciones = read_ID(inputAtenciones);       ignorar_coma(inputAtenciones); //* <-- KEY (PACIENTES)
        inputAtenciones >> especialidadAtenciones;         ignorar_coma(inputAtenciones); //* <-- KEY (ESPECIALIDAD)
        hora = read_time(inputAtenciones);
        posPacientes = busquedaBinaria(arrCodigoPaciente, dniAtenciones, n_pacientes);
        posEspecialidades = busquedaBinaria(arrCodigoEspecialidad, especialidadAtenciones, n_especialidades);
        if (posPacientes != NOT_FOUND and posEspecialidades != NOT_FOUND) {
            
        }
        //* Si no se encuentra pues se imprime en el archivo de invalidos

    }
}














