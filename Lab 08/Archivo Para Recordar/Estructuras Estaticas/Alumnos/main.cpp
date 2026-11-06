#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    //* Esta es otra forma de inicializar la estructura (si los datos son hardcode)
    // struct Alumno a {20249999, 19.5, "Juan Perez", true};

    // struct Alumno a;
    // a.codigo = 20249999;
    // a.promedio = 19.5;
    // a.matriculado = true;
    // strcpy(a.nombre, "Juan Perez");

    //? Formato de estructura dinamica
    //?     struct Alumno *alumnos = new struct Alumno[NUM_ALUMNO];

    struct Alumno alumnos[NUM_ALUMNO]{};
    int num =0;
    cargarDatos("AlumnosDeDatos/alumnos.csv", alumnos, num);
    ordenarPorPormedio(alumnos, num);
    ordenarPorNombre(alumnos, num);
    generarReporteGeneral("ArchivosDeReporte/reporteAlumnos.txt", alumnos, num);

    for (int i = 0; i < num; i++) {
        liberarEstructuras(alumnos[i]);
    }
    //! Esto va si fuera dinamico
    //?     delete[] alumnos;

    return 0;
}
