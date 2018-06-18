#include <stdio.h>
#include <stdlib.h>
#include "erros.h"
#define TAM 128

char *buffer1, *buffer2;
int inicio = 0, delantero = -1, buff_actual = 1, fin_arq = 0;
FILE *arq;

void cargarBuffer1() {
    int lidos;
    
    lidos = fread(buffer1, sizeof (char), TAM, arq);
    if (lidos != TAM) {
        buffer1[lidos] = EOF;
        fin_arq = 1;
    }
}

void cargarBuffer2() {
    int lidos;

    lidos = fread(buffer2, sizeof (char), TAM, arq);
    if (lidos != TAM) {
        buffer2[lidos] = EOF;
        fin_arq = 1;
    }
}

void initEntrada() {

    if ((arq = fopen("concurrentSum.go", "r")) == NULL) {
        printError(ERRO_ABRIR_ARQUIVO, -1, "Erro durante a apertura do arquivo regression.d", "");
    } else {
        buffer1 = (char *) malloc((TAM + 1) * sizeof (char));
        buffer2 = (char *) malloc((TAM + 1) * sizeof (char));
        cargarBuffer1();
        buffer1[TAM] = EOF;
        buffer2[TAM] = EOF;
    }
}

char nextChar() {
    switch (buff_actual) {
        case 1:
            if (buffer1[delantero + 1] != EOF) {
                delantero++;
                return (buffer1[delantero]);
            } else if (buffer1[delantero + 1] == EOF && fin_arq == 0) {
                buff_actual = 2;
                cargarBuffer2();
                inicio = 0;
                delantero = 0;
                return buffer2[delantero];
            } else if (buffer1[delantero + 1] == EOF && fin_arq == 1) {
                return buffer1[delantero + 1];
            }
            break;
        case 2:
            if (buffer2[delantero + 1] != EOF) {
                delantero++;
                return (buffer2[delantero]);
            } else if (buffer2[delantero + 1] == EOF && fin_arq == 0) {
                buff_actual = 1;
                cargarBuffer1();
                inicio = 0;
                delantero = 0;
                return buffer1[delantero];
            } else if (buffer1[delantero] == EOF && fin_arq == 1) {
                return buffer1[delantero + 1];
            }
            break;
    }
}

void finLexema() {
    inicio = delantero;
}

void retrocederChar(int num) {
    /*int aux;
    if ((delantero - num) < 0) {
        aux = num - delantero;
        if (buff_actual == 1)
            buff_actual = 2;
        else
            buff_actual = 1;
        delantero = TAM - aux;
        inicio = delantero;
    } else
     */ delantero = delantero - num;
}