#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analizador_lexico.h"

typedef char *tipoclave;

struct celda {
    Lexema info;
    struct celda *izq, *der;
};

typedef struct celda * abb;

void crea(abb *A) {
    *A = NULL;
}

void destruye(abb *A) {
    if (*A != NULL) {
        destruye(&(*A)->izq);
        destruye(&(*A)->der);
        free(*A);
        *A = NULL;
    }
}

unsigned esVacio(abb A) {
    return A == NULL;
}

void inserta(abb *A, Lexema L) {
    if (esVacio(*A)) {
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info = L;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    } else if (strcmp(L.lexema, (*A)->info.lexema) < 0)
        inserta(&(*A)->izq, L);
    else
        inserta(&(*A)->der, L);
}

Lexema suprime_min(abb *A) {
    abb aux;
    Lexema ele;
    if ((*A)->izq == NULL) {
        ele = (*A)->info;
        aux = *A;
        *A = (*A)->der;
        free(aux);
        return ele;
    } else
        return suprime_min(&(*A)->izq);

}

void suprime(abb *A, Lexema L) {
    abb aux;
    if (*A != NULL) {
        if (strcmp(L.lexema, (*A)->info.lexema) < 0)
            suprime(&(*A)->izq, L);
        else if (strcmp(L.lexema, (*A)->info.lexema) > 0)
            suprime(&(*A)->der, L);
        else if ((*A)->izq == NULL && (*A)->der == NULL) {
            free(*A);
            *A = NULL;
        } else if ((*A)->izq == NULL) {
            aux = *A;
            *A = (*A)->der;
            free(aux);
        } else if ((*A)->der == NULL) {
            aux = *A;
            *A = (*A)->izq;
            free(aux);
        } else
            (*A)->info = suprime_min(&(*A)->der);
    } else printf("O empregado non existe.\n");
}

unsigned esMiembro(abb A, Lexema L) {
    if (esVacio(A))
        return 0;
    else if (strcmp((A->info).lexema, L.lexema) == 0)
        return 1;
    else if (strcmp(A->info.lexema, L.lexema) > 0)
        return esMiembro(A->izq, L);
    else
        return esMiembro(A->der, L);
}

void info(abb A, Lexema *L) {
    *L = A->info;
}

abb izq(abb A) {
    return A->izq;
}

abb der(abb A) {
    return A->der;
}


void buscaNodo(abb A, tipoclave cl, Lexema *nodo) {
    if (esVacio(A)) {
        printf("Engadindo lexema: %s\n", cl);
    } else if (strcmp(A->info.lexema, cl) == 0)
        *nodo = A->info;
    else if (strcmp(A->info.lexema, cl) < 0)
        buscaNodo(der(A), cl, nodo);
    else
        buscaNodo(izq(A), cl, nodo);
}

void modifica(abb *A, tipoclave cl, Lexema nodo) {
    if (esVacio(*A)) {
        printf("Engadindo lexema: %s\n", cl);
    } else if (strcmp((*A)->info.lexema, cl) == 0)
        (*A)->info = nodo;
    else if (strcmp((*A)->info.lexema, cl) < 0)
        modifica(&(*A)->der, cl, nodo);
    else
        modifica(&(*A)->izq, cl, nodo);
}


