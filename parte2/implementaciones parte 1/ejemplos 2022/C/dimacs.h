#ifndef DIMACS_H

#define DIMACS_H
// #include "EstructuraGrafo.h"

typedef unsigned int u32;

typedef struct dimacsData_s {
    u32 n; // Cantidad de vértices
    u32 m; // Cantidad de lados
    u32** lados; // Matriz de Mx2
                 //  [ [v1, v2],
                 //    [v4, v5],...   ]
} dimacsData;

/** El llamador es dueño de la memoria retornada. */
dimacsData* obtenerDimacsDataDesdeStdIn();

/** Libera la memoria de dimacsData **/
dimacsData* destruirDimacsData(dimacsData* dd);

#endif /* end of include guard DIMACS_H */
