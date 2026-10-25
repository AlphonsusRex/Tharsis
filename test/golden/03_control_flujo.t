principal() {
    entero x = 10;

    si (x > 5) {
        imprimir("mayor\n");
    } sino {
        imprimir("menor\n");
    }

    mientras (x > 0) {
        x = x - 1;
    }

    para (entero i = 0; i < 3; i = i + 1) {
        si (i == 1) {
            continuar;
        }
        si (i == 2) {
            romper;
        }
    }

    segun (x) {
        caso 0:
            imprimir("cero\n");
            romper;
        caso 1:
            imprimir("uno\n");
            romper;
        por_defecto:
            imprimir("otro\n");
            romper;
    }

    retornar 0;
}
