#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

int analizadorSintactico() {

    Lexema L;

    L = nextCompLexico();
    while (L.lexema[0] != EOF) {
        if (L.lexema[0] == '\n')
            printf("Linea: %d || Componente lexico: (salto de linea) || Id: %d\n", L.linea, L.id);
        else
            printf("Linea: %d || Componente lexico: %s || Id: %d\n", L.linea, L.lexema, L.id);
        L = nextCompLexico();
    }
    printf("Fin do arquivo.");

    return EXIT_SUCCESS;
}