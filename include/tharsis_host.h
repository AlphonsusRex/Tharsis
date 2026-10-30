#ifndef THARSIS_HOST_H
#define THARSIS_HOST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Mapeo de la función principal en host
#define principal int main

// Mapeo de imprimir
#define imprimir printf

// Macro de lectura de cadena
#define tomar_cadena(var, tam) fgets((var), (tam), stdin)

#endif // THARSIS_HOST_H
