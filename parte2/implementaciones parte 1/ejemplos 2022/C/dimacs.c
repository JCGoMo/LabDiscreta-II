#include "dimacs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 1024

/** El llamador es dueño de la memoria retornada. */
static char* primeraLineaDeStdInSinComentarios() {
    // Ignorar comentarios
    char *siguiente_linea = malloc(sizeof(char)*BLOCK_SIZE);
    fgets(siguiente_linea, BLOCK_SIZE, stdin);
    while(siguiente_linea[0] != 'p') {
        fgets(siguiente_linea, BLOCK_SIZE, stdin);
        if(feof(stdin)){
            // Dimacs malformado.
            return NULL;
        }
    }
    return siguiente_linea;
}

dimacsData* obtenerDimacsDataDesdeStdIn() {
    dimacsData* dd = malloc(sizeof(dimacsData));
    // N & M
    char *siguiente_linea;
    siguiente_linea = primeraLineaDeStdInSinComentarios();
    if (siguiente_linea == NULL) { /* Dimacs malformado */ }
    printf("%s\n", siguiente_linea);
    sscanf(siguiente_linea, "%*c %*s %u %u", &dd->n, &dd->m);
    printf("Son: %u vertices, y %u lados.\n", dd->n, dd->m);
    // Lados
    dd->lados = malloc(sizeof(u32*)*dd->m);
    u32 c = 0;
    while(c < dd->m) {
        fgets(siguiente_linea, BLOCK_SIZE, stdin);
        u32* par = malloc(sizeof(u32) * 2);
        sscanf(siguiente_linea, "%*c %u %u", &par[0], &par[1]);
        /* printf("Nuevo lado encontrado: %u -> %u   (%u)\n", par[0], par[1], c); */
        dd->lados[c] = par;
        // Scaneo otra vez
        c++;
        if(feof(stdin) && c < dd->m){
            // DestruccionDelGrafo(newGrafo);
            // Dimacs malformado.
            break;
        }
    }

    //clean and return.
    free(siguiente_linea);
    return dd;
}

dimacsData* destruirDimacsData(dimacsData* dd) {
    for(u32 i=0; i<dd->m; i++) {
        free(dd->lados[i]);
    }
    free(dd->lados);
    free(dd);
    return NULL;
}
