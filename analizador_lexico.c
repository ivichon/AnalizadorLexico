#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "definiciones.h"
#include "analizador_lexico.h"
#include "erros.h"
#include "entrada.h"
#include "simbolos.h"
#define MAX_TAM_LEXEMA 128


char* checkLenght(char *palabra);
Lexema comentarios(int estado, Lexema L);
Lexema numeros(int estado, Lexema L);
void automata();
int linea = 1, numchar = 0, flag = 0;
size_t tam_lexema = 8;

Lexema nextCompLexico() {

    int estado = 0, id;
    char c;
    Lexema L;
    L.lexema = (char *) malloc(tam_lexema * sizeof (char));
    L.id = 0;

    while (1) {
        switch (estado) {
            case 0: //Estado inicial
                c = nextChar();
                if (c == ' ' || c == '\t');
                else if (c == '\n') {
                    L.lexema[0] = c;
                    L.lexema[1] = '\0';
                    L.id = c;
                    L.linea = linea;
                    linea++;
                    return L;
                } else if (c == EOF) {
                    L.lexema[0] = c;
                    L.lexema[1] = '\0';
                    L.id = c;
                    L.linea = linea;
                    finLexema();
                    return L;
                } else if (isalpha(c) || c == '_') {
                    L.lexema[0] = c;
                    L.lexema[1] = '\0';
                    estado = 1;
                } else if (isdigit(c)) {
                    L.lexema[0] = c;
                    L.lexema[1] = '\0';
                    estado = 2;
                } else {
                    estado = 3;
                }
                break;

            case 1: //Primeiro caracter do lexema é unha letra.
                c = nextChar();
                if (c == ' ' || c == '\t') {
                    estado = 100;
                } else if (c == '.' || c == ';') {
                    retrocederChar(1);
                    estado = 100;
                } else if (isalnum(c) || c == '_') {
                    checkLenght(L.lexema);
                    strncat(L.lexema, &c, 1);
                } else {
                    id = buscarLexema(L.lexema, &L);
                    if (id == 0) {
                        L.id = IDENTIFICADOR;
                        L.linea = linea;
                        insertarLexema(L);
                        finLexema();
                        retrocederChar(1);
                        return L;
                    }
                    L.linea = linea;
                    finLexema();
                    retrocederChar(1);
                    return L;
                }
                break;

            case 2: //Primeiro caracter do lexema é un número.
                c = nextChar();
                if (c == ' ' || c == '\t' || c == ',' || c == ';' || c == '+' || c == '-'
                        || c == '*' || c == '/' || c == '\n' || c == '}' || c == ']' || c == ':') {
                    L.linea = linea;
                    L.id = INTEGER_LITERAL;
                    finLexema();
                    retrocederChar(1);
                    return L;
                } else if (isdigit(c)) {
                    checkLenght(L.lexema);
                    strncat(L.lexema, &c, 1);
                } else if (c == 'e') {
                    estado = 21;
                } else if (c == '_' || c == 'x') {
                    strncat(L.lexema, &c, 1);
                    estado = 22;
                } else if (c == '.') {
                    estado = 23;
                } else {
                    L.linea = linea;
                    while (!(c == ' ' || c == '\t' || c == ',' || c == ';' || c == '+' || c == '-' || c == '*' || c == '/')) {
                        checkLenght(L.lexema);
                        strncat(L.lexema, &c, 1);
                        c = nextChar();
                    }
                    printError(NUM_NON_VALIDO, L.linea, "Formato de numero non valido", L.lexema);
                    retrocederChar(1);
                    estado = 0;
                }
                break;
            case 3: //O caracter lido é un símbolo
                switch (c) {
                    case '(':
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case ')':
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case '[':
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case ']':
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case '{':
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case '}':
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case '.':
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case '=':
                        c = nextChar();
                        if (c == '=') {
                            L.lexema = "==";
                            //L.id = IGUAL_IGUAL;
                            L.linea = linea;
                            finLexema();
                            return L;
                        } else {
                            L.lexema = "=";
                            L.id = '=';
                            L.linea = linea;
                            finLexema();
                            retrocederChar(1);
                            return L;
                        }
                    case '+':
                        c = nextChar();
                        if (c == '=') {
                            L.lexema = "+=";
                            L.id = MAIS_IGUAL;
                            L.linea = linea;
                            finLexema();
                            return L;
                        } else {
                            L.lexema = "+";
                            L. id = '+';
                            L.linea = linea;
                            finLexema();
                            retrocederChar(1);
                            return L;
                        }
                    case '-':
                        c = nextChar();
                        if (isdigit(c)) {
                            L.lexema[0] = '-';
                            L.lexema[1] = c;
                            estado = 2;
                            break;
                        }
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case '*':
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case ';':
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case',':
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case '/':
                        estado = 30;
                        break;
                    case '"':
                        c = nextChar();
                        while (c != '"') {
                            if (c == '\n')
                                linea++;
                            if (c == '\\')
                                c = nextChar();
                            checkLenght(L.lexema);
                            strncat(L.lexema, &c, 1);
                            c = nextChar();
                        }
                        L.id = '"';
                        L.linea = linea;
                        finLexema();
                        return L;
                    case '<':
                        c = nextChar();
                        if (c == '-') {
                            L.lexema = "<-";
                            L.id = SEND;
                            L.linea = linea;
                            finLexema();
                            return L;
                        } else {
                            L.lexema[0] = c;
                            L.lexema[1] = '\0';
                            L.id = c;
                            L.linea = linea;
                            finLexema();
                            retrocederChar(1);
                            return L;
                        }
                    case '>':
                        L.lexema[0] = c;
                        L.lexema[1] = '\0';
                        L.id = c;
                        L.linea = linea;
                        finLexema();
                        return L;
                    case ':':
                        c = nextChar();
                        if (c == '=') {
                            L.lexema = ":=";
                            L.id = IGUAL;
                            L.linea = linea;
                            finLexema();
                            return L;
                        } else {
                            L.lexema[0] = ':';
                            L.lexema[1] = '\0';
                            L.id = ':';
                            L.linea = linea;
                            finLexema();
                            retrocederChar(1);
                            return L;
                        }
                }
                break;
            case 21: //Número expoñencial
                L = numeros(estado, L);
                if (L.id != 0) {
                    return L;
                } else {
                    estado = 0;
                    break;
                }
            case 22: //Integer
                L = numeros(estado, L);
                if (L.id != 0) {
                    return L;
                } else {
                    estado = 0;
                    break;
                }
            case 23:
                L = numeros(estado, L);
                if (L.id != 0) {
                    return L;
                } else {
                    estado = 0;
                    break;
                }
            case 30: //Atopamos o símbolo /
                c = nextChar();
                if (c == '/') {
                    estado = 31;
                    break;
                } else if (c == '*') {
                    estado = 32;
                    break;
                } else {
                    L.lexema[0] = '/';
                    L.lexema[1] = '\0';
                    L.id = '/';
                    L.linea = linea;
                    finLexema();
                    retrocederChar(1);
                    return L;
                }
            case 31: //Comentario línea
                L = comentarios(estado, L);
                return L;
            case 32: //Comentario párrafo
                L = comentarios(estado, L);
                return L;

            case 100: //Estado para o fin dun lexema
                id = buscarLexema(L.lexema, &L);
                //Se id é menor ca 0 isto significa que a palabra que atopamos non estaba presente na táboa de símbolos.
                if (id == 0) {
                    L.id = IDENTIFICADOR;
                    L.linea = linea;
                    insertarLexema(L);
                    finLexema();
                    return L;
                }
                L.linea = linea;
                finLexema();
                return L;
        }
    }
}

char* checkLenght(char *palabra) {

    if ((strlen(palabra) % 8) == 0) {
        //palabra = (char *) realloc(palabra, tam_lexema + strlen(palabra));
        char *new = (char *) malloc(tam_lexema + strlen(palabra));
        memcpy(new, palabra, strlen(palabra));
        return new;
    }
    return palabra;
}

Lexema comentarios(int estado, Lexema L) {

    char c;

    switch (estado) {
        case 31:
            do {
                c = nextChar();
                checkLenght(L.lexema);
                strncat(L.lexema, &c, 1);
                numchar++;
            } while (c != '\n' && numchar < 50);
            if (numchar >= 50) {
                while (c != '\n') {
                    c = nextChar();
                }
            } else {
                L.lexema[numchar - 1] = '\0';
            }
            L.id = COMENTARIO_LINHA;
            L.linea = linea;
            finLexema();
            retrocederChar(1);
            numchar = 0;
            return L;
        case 32:
            do {
                c = nextChar();
                if (c == '\n') {
                    linea++;
                } else if (c == '*') {
                    c = nextChar();
                    if (c == '/') {
                        flag = 1;
                    } else if (c == '*') {
                        while ((c = nextChar()) == '*');
                        retrocederChar(1);
                    } else {
                        retrocederChar(1);
                    }
                } else if (numchar < 50) {
                    checkLenght(L.lexema);
                    strncat(L.lexema, &c, 1);
                    numchar++;
                }
            } while (flag == 0);
            L.id = COMENTARIO_PARRAFO;
            L.linea = linea;
            finLexema();
            numchar = 0;
            flag = 0;
            return L;
    }

}

Lexema numeros(int estado, Lexema L) {

    char c;
    int flag = 1;
    do {
        switch (estado) {
            case 21: //Exponencial
                checkLenght(L.lexema);
                strncat(L.lexema, &c, 1);
                c = nextChar();
                if (c == '+' || c == '-' || c == '0') {
                    checkLenght(L.lexema);
                    strncat(L.lexema, &c, 1);
                    while (isdigit(c = nextChar())) {
                        checkLenght(L.lexema);
                        strncat(L.lexema, &c, 1);
                    }
                    if (c == ' ' || c == ',' || c == '+' || c == '-' || c == '*' || c == '/' || c == 'i') {
                        L.linea = linea;
                        L.id = IMAGINARY_LITERAL;
                        finLexema();
                        retrocederChar(1);
                        return L;
                    } else {
                        L.linea = linea;
                        while (!(c == ' ' || c == '\t' || c == ',' || c == ';' || c == '+' || c == '-' || c == '*' || c == '/')) {
                            checkLenght(L.lexema);
                            strncat(L.lexema, &c, 1);
                            c = nextChar();
                        }
                        printError(NUM_NON_VALIDO, L.linea, "Formato de numero exponencial non valido", L.lexema);
                        retrocederChar(1);
                        estado = 0;
                    }
                } else {
                    L.linea = linea;
                    while (!(c == ' ' || c == '\t' || c == ',' || c == ';' || c == '+' || c == '-' || c == '*' || c == '/')) {
                        checkLenght(L.lexema);
                        strncat(L.lexema, &c, 1);
                        c = nextChar();
                    }
                    printError(NUM_NON_VALIDO, L.linea, "Formato de numero exponencial non valido", L.lexema);
                    retrocederChar(1);
                    estado = 0;
                }
                break;
            case 22: //Integer
                checkLenght(L.lexema);
                if (c != '_')
                    strncat(L.lexema, &c, 1);
                while (isxdigit(c = nextChar())) {
                    checkLenght(L.lexema);
                    if (c != '_')
                        strncat(L.lexema, &c, 1);
                }
                if (c == ' ' || c == ',' || c == '+' || c == '-' || c == '*' || c == '/') {
                    L.linea = linea;
                    L.id = INTEGER_LITERAL;
                    finLexema();
                    retrocederChar(1);
                    return L;
                } else {
                    L.linea = linea;
                    while (!(c == ' ' || c == '\t' || c == ',' || c == ';' || c == '+' || c == '-' || c == '*' || c == '/')) {
                        checkLenght(L.lexema);
                        strncat(L.lexema, &c, 1);
                        c = nextChar();
                    }
                    printError(NUM_NON_VALIDO, L.linea, "Formato de numero Integer non valido", L.lexema);
                    retrocederChar(1);
                    estado = 0;
                }
                break;
            case 23: //FLoat
                checkLenght(L.lexema);
                strncat(L.lexema, &c, 1);
                while (isdigit(c = nextChar())) {
                    checkLenght(L.lexema);
                    strncat(L.lexema, &c, 1);
                }
                if (c == ' ' || c == ',' || c == '+' || c == '-' || c == '*' || c == '/' || c == ']') {
                    L.linea = linea;
                    L.id = FLOATINGPOINT_LITERAL;
                    finLexema();
                    retrocederChar(1);
                    return L;
                } else if (c == 'e') {
                    estado = 21;
                } else {
                    L.linea = linea;
                    while (!(c == ' ' || c == '\t' || c == ',' || c == ';' || c == '+' || c == '-' || c == '*' || c == '/')) {
                        checkLenght(L.lexema);
                        strncat(L.lexema, &c, 1);
                        c = nextChar();
                    }
                    printError(NUM_NON_VALIDO, L.linea, "Formato de numero float non valido", L.lexema);
                    retrocederChar(1);
                    estado = 0;
                }
                break;
        }
    } while (flag != 0);
    return L;
}
