#include <stdio.h>
#include <stdlib.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"


// Funcion para liberar memoria. Dado un puntero, libera la
// memoria apuntada por el mismo
void liberar(void * a){
    free(a);
    a = NULL;
}


// Funcion búsqueda binaria para encontrar posición de un vértice (key)
u32 busquedaBinaria(u32 vNombre[], u32 inicio, u32 final, u32 key){
    u32 medio = -1;

    while(inicio <= final)
    {
        medio = (u32) ((inicio+final) / 2);

        if (vNombre[medio] == key)
            return medio;
        else if (key < vNombre[medio])
            final = medio - 1;
        else
            inicio = medio + 1;
    }

    return medio;
}


// Función comparadora para qsort
int sortDupla (const void * _a, const void * _b){
    Dupla a, b;
    a = (Dupla) _a;
    b = (Dupla) _b;

    if (a->v1 == b->v1){
        if (a->v2 < b->v2){
            return -1;
        }
        else if (a->v2 == b->v2){
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        if(a->v1 < b->v1){
            return -1;
        }
        else if (a->v1 > b->v1) {
            return 1;
        }
    }
}



// 4 - Funciones De Construcción/Destrucción del grafo

Grafo ConstruccionDelGrafo(){

    Grafo g = NULL;
    Dupla vArray = NULL; // Array de vértices

    char buffer[BUFFSIZE]; // Buffer para leer las líneas del archivo
    u32 n = 0; // Vertices
    u32 m = 0; // Lados
    u32 v1, v2;     // Vértices de e v1 v2
    u32 deltaG = 0;

    u32 pvn;        // posición del vertice
    u32 visitado;   // vórtice visto?
    u32 limite;     // para ciclos
    u32 grado;
    u32 totVistos;
    int pos;        // lo utilizo para la búsqueda binaria



    // Ignoramos los comentarios, devolvemos NULL si no se pudo leer
    do
    {
        if ( fgets(buffer, BUFFSIZE, stdin) == NULL )
        {
            return NULL;
        }
    } while(buffer[0] == 'c');


    // Fin de comentarios, ahora obtenemos n & m --> p edge n m
    sscanf(buffer, "p edge %u %u", &n, &m);

    // Si la primera linea que no es comentario no es de la forma: p edge n m,
    // devolvemos NULL
    if (buffer[0] != 'p')
    {
        printf("ERROR EN PRIMERA LINEA SIN COMENTARIO\n");
        return NULL;
    }

    // Arreglo de lados
    vArray = (Dupla) malloc (2*m*sizeof(struct DuplaSt));
    
   if (!vArray)
    {
        printf("failed memory allocation for" 'vArray');
        return NULL;
    }
    // Leemos las m líneas
    for (u32 i = 0; i < m; i++){
        
        if ( fgets(buffer, BUFFSIZE, stdin) == NULL )
        {
            liberar(vArray);
            return NULL;
        }
        // Si no es un lado, devolvemos NULL
        if (buffer[0] != 'e') {
            liberar(vArray);
            printf("ERROR, NO ES UN LADO\n");
            return NULL;
        }

        // Obtenemos e v1 v2
        sscanf(buffer, "e %u %u", &v1, &v2);

        // Los colocamos en el arreglo de lados doble
        vArray[i].v1 = v1;
        vArray[i].v2 = v2;
        // Damos vuelta el lado: (3,1) -> (1,3)
        vArray[i+m].v1 = v2;
        vArray[i+m].v2 = v1;

    }
    
    // Ordenamos el arreglo de lados
    qsort(vArray, 2*m, sizeof(struct DuplaSt), sortDupla);

    // Aloco memoria para el grafo y la libero en caso de error
    g = malloc(sizeof(struct GrafoSt));

    if (!g){
        liberar(vArray);
        printf("failed memory allocation for 'g'");
        return NULL;
    }

    // Arreglo de nombres de los vértices
    g->vNombre = (u32*) malloc(n*sizeof(unsigned int));

    if (!g->vNombre){
        liberar(vArray);
        liberar(g);
        printf("failed memory allocation for 'g->vNombre'");
        return NULL;
    }


    // Arreglo de grados de los vértices
    g->vGrado = (Dupla) malloc(n*sizeof(struct DuplaSt));

    if (!g->vGrado)
    {
        liberar(vArray);
        liberar(g->vNombre);
        liberar(g);
        printf("failed memory allocation for 'g->vGrado'");
        return NULL;
    }

    // Arreglo de lados de los vértices
    g->vLados = malloc(n*sizeof(unsigned int*));

    if (!g->vLados)
    {
        liberar(vArray);
        liberar(g->vNombre);
        liberar(g->vGrado);
        liberar(g);
        printf("failed memory allocation for'g->vLados'");
        return NULL;
    }

    // Arreglo de orden de los vértices
    g->vOrden = malloc(n*sizeof(unsigned int));

    if (!g->vOrden){
        liberar(vArray);
        liberar(g->vNombre);
        liberar(g->vGrado);
        liberar(g->vLados);
        liberar(g);
        printf("failed memory allocation for'g->vOrden'");
        return NULL;
    }


    /*---------------------------------------------------------------------------*/


/*Meto el nombre, grado y orden en sus arreglos correspondientes*/
    pvn = 0;
    visitado = vArray[0].v1;
    limite = 2*m;   // Esto para que no evalue en cada iteracion

    g->n = n;
    g->m = m;

    g->vNombre[0] = visitado;
    g->vGrado[0].v1 = 1;    // Grado
    g->vGrado[0].v2 = 0;    // Grado orden
    g->vOrden[0] = 0;
    totVistos = 1;

    for(u32 i = 1; i < limite; i++)
    {
        if (vArray[i].v1 != visitado)
        {
            visitado = vArray[i].v1;
            pvn++;
            g->vNombre[pvn] = visitado;     // Meto en el array el nombre del vertice
            g->vGrado[pvn].v1 = 1;             // 1 por su vecino v2 de la dupla
            g->vGrado[pvn].v2 = pvn;
            g->vOrden[pvn] = pvn;
            totVistos++;
        }
        else
        {
            g->vGrado[pvn].v1 += 1;
        }
    }

    if (totVistos != n)
    {
        liberar(vArray);
        liberar(g->vNombre);
        liberar(g->vGrado);
        liberar(g->vLados);
        liberar(g);
        printf("CANTIDAD DE VERTICES LEIDOS NO ES LA DECLARADA\n");
        return NULL;
    }

    // Lados
    for(u32 i = 0; i < n; i++)
    {
        g->vLados[i] = (unsigned int*) malloc(g->vGrado[i].v1*sizeof(unsigned int));
    }

    pvn = 0;
    visitado = vArray[0].v1;
    grado = 0;
    deltaG = 1;
    
    // Busco la posición del 1er vecino del 1er vértice
    pos = busquedaBinaria(g->vNombre, 0, n-1, vArray[0].v2);

    // 1er vecino del 1er vértice
    g->vLados[0][0] = pos;

    // Armo array de vecinos de cada vértice ("vLados") y 
    for(u32 i = 1; i < limite; i++)
    {
        if (vArray[i].v1 != visitado)
        {
            visitado = vArray[i].v1;
            grado = 0;
            pvn++;
            
        }
        else
        {
            grado++;
            if (grado > deltaG){
                deltaG = grado;
            }

        }

        pos = busquedaBinaria(g->vNombre, 0, n-1, vArray[i].v2);
        g->vLados[pvn][grado] = pos;
    }


/*    liberamos vArray ya que no lo necesitamos mas*/
    liberar(vArray);

    return g;
}

void DestruccionDelGrafo(Grafo G){
    if (G == NULL)
        return;

    u32 n = NumeroDeVertices(G);

    liberar(G->vNombre);
    liberar(G->vGrado);
    liberar(G->vOrden);

    for(u32 i = 0; i < n; i++)
        liberar(G->vLados[i]);

    liberar(G->vLados);
    liberar(G);
}


// --------------------------------------------------------------
// 5 Funciones para extraer informacion de datos del grafo
// --------------------------------------------------------------

u32 NumeroDeVertices(Grafo G){
    if (G == NULL)
        return UINTMAX;

    return G->n;
}

u32 NumeroDeLados(Grafo G){
    if (G == NULL)
        return UINTMAX;

    return G->m;
}

u32 Delta(Grafo G){
    if (G == NULL)
        return UINTMAX;

    return G->deltaG;
}


// --------------------------------------------------------------
// 6 - Funciones para extraer información de los de los vértices
// --------------------------------------------------------------

u32 Nombre(Grafo G, u32 i){
    if (G == NULL)
        return UINTMAX;

    return G->vNombre[G->vOrden[i]];   
}


u32 Grado(Grafo G, u32 i){
    if (G == NULL || i >= NumeroDeVertices(G))
        return UINTMAX;

    return G->vGrado[G->vOrden[i]].v1;
}


u32 IndiceONVecino(u32 j,u32 k,Grafo G){
    if (k >= NumeroDeVertices(G))
        return UINTMAX;
    if (j < G->vGrado[k].v1)
        return UINTMAX;

    return G->vNombre[G->vLados[G->vOrden[k]][j]];
}
