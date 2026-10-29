/* ============================================================ */
/* Generado por tharsis_gen desde: 04_operadores.t
   NO EDITAR: modificar el .t y volver a transpilar            */
/* ============================================================ */

#include "tharsis_host.h"

int principal() {
    int a = 1;
    int b = 0;
    int nota = 5;
    int yacimiento = 7;

    if (a && b) {
        imprimir("a y b\n");
    }

    if (a || b) {
        imprimir("a o b\n");
    }

    if (! b) {
        imprimir("no b\n");
    }

    if ((a > 0) && (b < 1)) {
        imprimir("compuesto\n");
    }

    if (nota > 3 && yacimiento < 10) {
        imprimir("sin parentesis\n");
    }

    return 0;
}
