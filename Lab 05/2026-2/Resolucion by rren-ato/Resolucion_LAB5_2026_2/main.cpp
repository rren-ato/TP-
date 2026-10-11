#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    int arrCodigoCliente[MAX_CLIENTES] = {};
    char arrTipoCredito[MAX_CLIENTES] = {};
    double arrMontoDesembolsado[MAX_CLIENTES] = {};
    int cantClientes = 0;

    llenarClientes ("ArchivosDeDatos/clientes_registrados.txt", arrCodigoCliente, arrTipoCredito, arrMontoDesembolsado,
                     cantClientes, MAX_CLIENTES) ;

    //* REPORTE PARCIAL
    reporteClientes("ArchivosDeReporte/ReporteClientes.txt", arrCodigoCliente, arrTipoCredito, arrMontoDesembolsado,
                     cantClientes);
    //? ----------------------------------------------------------------------------------------------------------------
    ordenarClientes( arrCodigoCliente, arrTipoCredito, arrMontoDesembolsado, cantClientes);
    updateClientesConMovimientos("ArchivosDeDatos/movimientos_clientes.txt", arrCodigoCliente, arrTipoCredito, arrMontoDesembolsado,
                     cantClientes, MAX_CLIENTES);

    //* REPORTE PARCIAL
    reporteMovimiento("ArchivosDeReporte/ReporteClientesMov.txt", arrCodigoCliente, arrTipoCredito, arrMontoDesembolsado,
                                  cantClientes);
    //? ----------------------------------------------------------------------------------------------------------------

    double arrSaldoPendientePago[MAX_PAGOS] = {};
    int arrCantCuotas[MAX_PAGOS] = {};
    int arrMayorAtraso[MAX_PAGOS] = {};
    int arrFechaMayorAtraso[MAX_PAGOS] = {};

    updateClientesConPagos("ArchivosDeDatos/pagos_cuotas.csv", arrCodigoCliente, arrSaldoPendientePago, arrCantCuotas,
                            arrMayorAtraso, arrFechaMayorAtraso,
                            cantClientes);

    ordenarPagos(arrCodigoCliente, arrTipoCredito, arrSaldoPendientePago, arrCantCuotas,
                            arrMayorAtraso, arrFechaMayorAtraso,
                            cantClientes);

    //* REPORTE FINAL
    reporteClasificacion("ArchivosDeReporte/ReporteClasificacionCartera.txt", arrCodigoCliente, arrTipoCredito, arrSaldoPendientePago, arrCantCuotas,
                            arrMayorAtraso, arrFechaMayorAtraso,
                            cantClientes);

    return 0;
}
