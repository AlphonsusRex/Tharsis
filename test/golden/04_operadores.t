principal() {
    entero a = 1;
    entero b = 0;
    entero nota = 5;
    entero yacimiento = 7;

    si (a Y b) {
        imprimir("a y b\n");
    }

    si (a O b) {
        imprimir("a o b\n");
    }

    si (NO b) {
        imprimir("no b\n");
    }

    si ((a > 0) Y (b < 1)) {
        imprimir("compuesto\n");
    }

    si (nota > 3 Y yacimiento < 10) {
        imprimir("sin parentesis\n");
    }

    retornar 0;
}
