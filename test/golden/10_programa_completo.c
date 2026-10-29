/* ============================================================ */
/* Generado por tharsis_gen desde: 10_programa_completo.t
   NO EDITAR: modificar el .t y volver a transpilar            */
/* ============================================================ */

#include "tharsis_host.h"

#include <math.h>

#define MAX_ITEMS 5

// programa integrador: combina tipos, control de flujo, operadores,
// strings, chars y comentarios

int principal() {
    int contador = 0;
    int suma = 0;
    float promedio = 0.0;
    bool activo = true;
    char marca = 'X';

    /* bucle principal */
    while (contador < MAX_ITEMS) {
        if (contador && activo) {
            suma = suma + contador;
        }
        contador = contador + 1;
    }

    if (suma > 0) {
        promedio = suma / 5.0;
        imprimir("suma: %d, promedio: %f\n", suma, promedio);
    } else {
        imprimir("suma cero\n");
    }

    switch (contador) {
        case 5:
            imprimir("contador es 5, marca=%c\n", marca);
            break;
        default:
            imprimir("contador raro\n");
            break;
    }

    return 0;
}
