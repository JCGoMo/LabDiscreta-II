#include <stdio.h>
#include <stdlib.h>


typedef unsigned int u32;
typedef struct DuplaSt *Dupla;
typedef struct GrafoSt *Grafo;


#define BUFFSIZE 80
#define UINTMAX 4294967295


struct GrafoSt {
    u32 n; // cant vertices
    u32 m; // cant lados
    u32 *vNombre;  // array con nombres de los vertices
    Dupla vGrado;   // Array grado de los vertices
    u32 **vLados;  // Array de lados de los vertices
    u32 *vOrden;
    u32 deltaG;
};


struct DuplaSt {
    u32 v1;
    u32 v2;
};


// Funciones auxiliares

int sortDupla(const void * _a, const void * _b);
void liberar (void * a);
u32 busquedaBinaria(u32 vNombre[], u32 inicio, u32 final, u32 key);
