/* ============================================================ */
/* Generado por tharsis_gen desde: 03_control_flujo.t
   NO EDITAR: modificar el .t y volver a transpilar            */
/* ============================================================ */

#include "tharsis_host.h"

int principal() {
    int x = 10;

    if (x > 5) {
        imprimir("mayor\n");
    } else {
        imprimir("menor\n");
    }

    while (x > 0) {
        x = x - 1;
    }

    for (int i = 0; i < 3; i = i + 1) {
        if (i == 1) {
            continue;
        }
        if (i == 2) {
            break;
        }
    }

    switch (x) {
        case 0:
            imprimir("cero\n");
            break;
        case 1:
            imprimir("uno\n");
            break;
        default:
            imprimir("otro\n");
            break;
    }

    return 0;
}
