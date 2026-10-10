//
// Created by Renato on 9/10/2026.
//

#include "FuncionesAuxiliares.h"


void open_read_file(ifstream &input, const char *filename) {
    input.open(filename, ios::in);
    if (not input.is_open()) {
        cerr << "Error al leer el archivo: " << filename << endl;
        exit(1);
    }
}

void open_write_file(ofstream &output, const char *filename) {
    output.open(filename, ios::out);
    if (not output.is_open()) {
        cerr << "Error al leer el archivo: " << filename << endl;
        exit(1);
    }
}

int readDate(ifstream &input) {
    int dd, mm ,yyyy; char c;
    input >> dd >> c >> mm >> c >> yyyy;
    int date = yyyy*10000 + mm*100 + dd;
    return date;
}

//* Incluye endl asi que solo es invocar
void printDate(ofstream &output, int date) {
    int day, month, year;
    year = date /10000;
    month = (date/100)%100;
    day = date %100;

    output << setw(2) << day << setfill('0') << "/" <<
        setw(2) << month << setfill('0') << "/" <<
            setw(4) << year << setfill(' ') << endl;
}

void ignorarComa(ifstream &input) {
    char c;
    input.get(c);
}

void swapInt (int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

void swapDouble (double &a, double &b) {
    double aux = a;
    a = b;
    b = aux;
}

void swapChar (char &a, char &b) {
    char aux = a;
    a = b;
    b = aux;
}

void llenarClientes (const char *filename, int *codigosClientes, char *tiposCreditos, double *montosDesembolsados,
                     int &cantClientes, int capacidad) {
//!     1030   Anastasio  C 29743.91
//!     1006   Milagros  M  86302.71
    ifstream inputClientes; open_read_file(inputClientes, filename);
    while (true) {
        int codigoCliente = 0; char tipoCredito; double montoDesembolsado=0.0;
        inputClientes >> codigoCliente;
        if (inputClientes.eof())break;
        inputClientes.ignore();//* <--- NOMBRE NO ES NECESARIO
        inputClientes >> tipoCredito;
        inputClientes >> montoDesembolsado;
        insertarDesordenado(inputClientes, codigosClientes, tiposCreditos, montosDesembolsados,
                      cantClientes, capacidad,
                      codigoCliente, tipoCredito, montoDesembolsado);
        //* Se frena cuando no hay mas clientes (osea se llega al fin de archivo)
    }
}

bool insertarDesordenado(ifstream &input, int *codigosClientes, char *tiposCreditos, double *montosDesembolsados,
                      int &cantClientes, int capacidad,
                      int codigoCliente, char tipoCredito, double montoDesembolsado) {
    if (cantClientes >= capacidad) return false;

    //! Se necesita solo considerar la primera aparicion por codigo
    for (int i=0; i< cantClientes; i++) {
        if (codigosClientes[i] == codigoCliente) return false;
        }

    codigosClientes[cantClientes] = codigoCliente;
    tiposCreditos[cantClientes] = tipoCredito;
    montosDesembolsados[cantClientes] = montoDesembolsado;
    cantClientes++;
    return true;
}

void ordenarClientes(int *codigosClientes, char *tiposCreditos, double *montosDesembolsados, int &cantClientes) {
    //? ME GUSTA HACERLO POR SELECTION SORT
    for (int i=0; i< cantClientes-1; i++) {
        int posMenor = i;
        for (int j=i+1; j<cantClientes; j++) {
            if (codigosClientes[j] < codigosClientes[posMenor]) posMenor = j;
        }
        if (posMenor != i) {
            swapInt(codigosClientes[i], codigosClientes[posMenor]);
            swapChar(tiposCreditos[i], tiposCreditos[posMenor]);
            swapDouble(montosDesembolsados[i], montosDesembolsados[posMenor]);
        }
    }
}

int busquedaBinaria(int *codigosClientes, int codigoClienteMovimiento, int cantClientes) {
    int izquierda = 0;
    int derecha = cantClientes -1;
    while(izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda)/2;
        if (codigosClientes[medio] == codigoClienteMovimiento) {
            return medio;
        } else if (codigosClientes[medio] < codigoClienteMovimiento) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    return NOT_FOUND;
}

void updateClientesConMovimientos(const char* fileName, int *codigosClientes, char *tiposCreditos, double *montosDesembolsados,
                                  int &cantClientes, int capacidad) {
    ifstream inputMovimientos; open_read_file(inputMovimientos, fileName);
//!     E 1001
//!     A  9007  Ximena  T  4200.00
//!     A 1017 Hugo C 5000.00
    while (true) {
        int posClienteEliminar = 0, posClienteInsertar =0;
        char typeMovimiento; int codigoClienteMovimiento =0.0; char tipoCreditoMovimiento; double montoDesebolsadoMovimiento =0.0;
        inputMovimientos >> typeMovimiento;
        if (inputMovimientos.eof()) break;
        if (typeMovimiento == 'E') {
            inputMovimientos >> codigoClienteMovimiento;
            posClienteEliminar = busquedaBinaria(codigosClientes, codigoClienteMovimiento, cantClientes);
            eliminacionDato(codigosClientes, tiposCreditos, montosDesembolsados,
                            cantClientes, posClienteEliminar);
        }
        else if (typeMovimiento == 'A') {
            inputMovimientos >> codigoClienteMovimiento;
            inputMovimientos >> tipoCreditoMovimiento;
            inputMovimientos >> montoDesebolsadoMovimiento;
            //* Insertar ordenado pero sin repetir informacion del cliente
            posClienteInsertar = busquedaBinaria(codigosClientes, codigoClienteMovimiento, cantClientes);
            if (posClienteInsertar == NOT_FOUND) {
                insertarOrdenado(codigosClientes, tiposCreditos, montosDesembolsados,
                            cantClientes, capacidad,
                            codigoClienteMovimiento, tipoCreditoMovimiento, montoDesebolsadoMovimiento);
            }
            inputMovimientos.ignore(1000, '\n');
        }
    }
}

bool eliminacionDato(int *codigosClientes, char *tiposCreditos, double *montosDesembolsados,
                            int &cantClientes, int posClienteEliminar){
    if (posClienteEliminar < 0 or posClienteEliminar >= cantClientes) {
        return false;
    }

    for (int i = posClienteEliminar; i < cantClientes; i++) {
        codigosClientes[i] = codigosClientes[i+1]; //* SE IMPLEMENTA SHIFT
        tiposCreditos[i] = tiposCreditos[i+1];
        montosDesembolsados[i] = montosDesembolsados[i+1];
    }
    cantClientes--; //* Se resta la longitud del arreglo pues elimino un dato
    return true;
}

bool insertarOrdenado(int *codigosClientes, char *tiposCreditos, double *montosDesembolsados,
                            int &cantClientes, int capacidad,
                            int codigoCliente, char tipoCredito, double montoDesembolsado) {
    if (cantClientes >= capacidad) return false;

    int i = cantClientes -1;
    while (i <= 0 and codigosClientes[i] > codigoCliente) {
        //* Se implementan shifts pues insertamos un dato que es menor al del 'i' en ese momento (array)
        //* La idea es hacer un espacio dentro de los datos ya leidos para agregarlo (pues es menor al max)
        codigosClientes[i+1] = codigosClientes[i];
        tiposCreditos[i+1] = tiposCreditos[i];
        montosDesembolsados[i+1] = montosDesembolsados[i];
        i--;
    }
    codigosClientes[i+1] = codigoCliente;
    tiposCreditos[i+1] = tipoCredito;
    montosDesembolsados[i+1] = montoDesembolsado;
    cantClientes++;
    return true;

}



void updateClientesConPagos(const char* fileName, int *codigosClientes, double *saldosPendientesPagos, int *cantCuotas,
                            int *mayorAtraso, int *fechaMayorAtraso,
                            int cantClientes) {
    //!     1029,11249.98,11249.98,1,05/06/2026
    ifstream inputPagos; open_read_file(inputPagos, fileName);
    while (true) {
        int posPagos=0;
        int codigoClientePago=0, diasAtraso=0, fechaVencimiento=0;
        double montoCuota=0.0, montoPagado=0.0;
        inputPagos >> codigoClientePago;
        if (inputPagos.eof()) break;                    ignorarComa(inputPagos);
        inputPagos >> montoCuota;                       ignorarComa(inputPagos);
        inputPagos >> montoPagado;                      ignorarComa(inputPagos);
        inputPagos >> diasAtraso;                       ignorarComa(inputPagos);
        fechaVencimiento = readDate(inputPagos);

        posPagos = busquedaBinaria(codigosClientes, codigoClientePago, cantClientes);
        if ( posPagos != NOT_FOUND) {
            saldosPendientesPagos[posPagos] += (montoCuota - montoPagado);
            cantCuotas[posPagos]++;

            if (diasAtraso > mayorAtraso[posPagos] or
                diasAtraso == mayorAtraso[posPagos] and fechaVencimiento < fechaMayorAtraso[posPagos]) {
                mayorAtraso[posPagos] = diasAtraso;
                fechaMayorAtraso[posPagos] = fechaVencimiento;
            }
        }
    }
}
