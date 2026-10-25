#include <math.h>

#define MAX_ITEMS 5

// programa integrador: combina tipos, control de flujo, operadores,
// strings, chars y comentarios

principal() {
    entero contador = 0;
    entero suma = 0;
    decimal promedio = 0.0;
    booleano activo = verdadero;
    caracter marca = 'X';

    /* bucle principal */
    mientras (contador < MAX_ITEMS) {
        si (contador Y activo) {
            suma = suma + contador;
        }
        contador = contador + 1;
    }

    si (suma > 0) {
        promedio = suma / 5.0;
        imprimir("suma: %d, promedio: %f\n", suma, promedio);
    } sino {
        imprimir("suma cero\n");
    }

    segun (contador) {
        caso 5:
            imprimir("contador es 5, marca=%c\n", marca);
            romper;
        por_defecto:
            imprimir("contador raro\n");
            romper;
    }

    retornar 0;
}
