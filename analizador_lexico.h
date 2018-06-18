#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char *lexema;
    int id;
    int linea;
}Lexema;

Lexema nextCompLexico();