#include <stdio.h>

void printError(int id, int linea, char *erro, char *lexema) {
    if (linea == -1)
        printf("Erro!!: Código do erro: %d || Liña: %d || Mensaxe de erro: %s\n", id, linea, erro);
    else
        printf("Erro!!: Código do erro: %d || Liña: %d || Mensaxe de erro: %s ||Lexema que o produciu: %s\n", id, linea, erro, lexema);
}