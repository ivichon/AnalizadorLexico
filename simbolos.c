#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"
#include "abb.h"
#include "erros.h"
#define MAX_TAM_LEXEMA 128

abb arbore;
void inicializarTaboa(abb *arbore);

void initSimbolos() {
    FILE *arquivo;
    Lexema L;


    crea(&arbore);

    if ((arquivo = fopen("taboa.txt", "rt")) == NULL) {
        printf("O arquivo non existe. Procedendo a súa creación.\n");
        if ((arquivo = fopen("taboa.txt", "w")) == NULL) {
            printError(ERRO_ABRIR_ARQUIVO, -1, "Erro na creacion da taboa de simbolos", "");
        }
    } else {
        while (feof(arquivo) == 0) {
            L.lexema = (char *) malloc(MAX_TAM_LEXEMA * sizeof (char));
            fscanf(arquivo, "%s", L.lexema);
            fscanf(arquivo, "%d\n", &L.id);
            inserta(&arbore, L);
        }
        fclose(arquivo);
    }
}

int buscarLexema(char *lexema, Lexema *L) {

    buscaNodo(arbore, lexema, L);

    if ((*L).id != 0) {
        return (*L).id;
    } else {
        return 0;
    }

}

void insertarLexema(Lexema L) {

    inserta(&arbore, L);

}