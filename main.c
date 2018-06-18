#include <stdio.h>
#include <stdlib.h>
#include "analizador_sintactico.h"
#include "entrada.h"
#include "simbolos.h"

/*
 * 
 */
int main(int argc, char** argv) {

    initEntrada();
    initSimbolos();
    analizadorSintactico();
    
    
    return (EXIT_SUCCESS);
}

