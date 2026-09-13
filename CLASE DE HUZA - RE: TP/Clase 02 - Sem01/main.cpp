#include <iostream>
#include <fstream>
#include "funciones.h"

using namespace std;

int main() {
    int a, b;
    cout << "Ingrese el primer número: ";
    cin >> a;
    cout << "Ingrese el segundo número: ";
    cin >> b;
    int c;
    sumar(a, b, c);

    cout
        << "La suma del número "
        << a
        << " y "
        << b
        << " es: "
        << c
        << endl;

    return 0;
}
