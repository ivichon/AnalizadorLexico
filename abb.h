#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analizador_lexico.h"

typedef char *tipoclave;
typedef void *abb; //tipo opaco

void crea(abb *A);
void destruye(abb *A);
unsigned esVacio(abb A);
void inserta(abb *A, Lexema L);
Lexema suprime_min(abb *A);
void suprime(abb *A, Lexema L);
unsigned esMiembro(abb A, Lexema L);
abb izq(abb A);
abb der(abb A);
void info(abb A, Lexema *L);
void buscaNodo(abb A, tipoclave cl, Lexema *nodo);
void modifica(abb *A, tipoclave cl, Lexema nodo);

