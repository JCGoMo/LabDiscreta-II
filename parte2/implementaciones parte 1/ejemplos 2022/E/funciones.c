#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"

#include <string.h>
#include <stdint.h>

//Hace fallar el programa siempre que el input no cumpla con el formato.
static void validez_formato(int resultado){
    if (resultado != 0){
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }    
}

Grafo ConstruccionDelGrafo(){
    Grafo G = (Grafo)malloc(sizeof(struct GrafoSt));
    u32 res = 0;
    u32 n1,n2;
	u32* indice_orden = NULL;
    char buffer[255],indicador,edge[5];

	G->delta = 0;
    while (fgets(buffer, 255, stdin) != NULL && buffer[0] == 'c' && buffer[1] == ' ');
    res = sscanf(buffer, "%c %s %u %u", &indicador, edge, &G->cant_v, &G->cant_l); 
	//sscanf=en vez de leer desde un file lee desde cadena de caracteres.
    if (res != 4 || (indicador != 'p') || strcmp(edge, "edge")) {
        validez_formato(1);
    }

	G->orden = malloc(G->cant_v * sizeof(Vertice));
	G->hashTable = calloc((G->cant_v)*2, sizeof(list));
	indice_orden = malloc(sizeof(u32));
	*indice_orden = 0u;
	// indice_orden es el indice al que se debe agregar el siguiente vertice en el arreglo orden.
	/*
	Se leen los lados desde stdin y se agregan a la estructura del grafo.
	Implica agregar vertices que no habian sido agregados a la hashtable y al arreglo orden.
			agregar mutuamente como vecinos a ambos vertices.
	*/
	for (u32 i = 0u; i < G->cant_l; ++i) {
		if(fgets(buffer, 255, stdin) == NULL){
			exit(EXIT_FAILURE);
		}
		res = sscanf(buffer, "%c %u %u", &indicador, &n1, &n2);
		if(res == 3) {
			if(indicador != 'e') {
				DestruccionDelGrafo(G);
				validez_formato(1);
			}
			agregarLado(G, n1, n2, indice_orden);

		} else {
			DestruccionDelGrafo(G);
			validez_formato(1);
		}
	}
	free(indice_orden);
	qsort(G->orden, G->cant_v, sizeof(Vertice), compOrdenNatural);
	for(u32 i = 0u; i < G->cant_v; ++i){
		G->orden[i]->indice = i;
		if(G->orden[i]->grado > G->delta){
			G->delta = G->orden[i]->grado;
		}
	}

	//Devolver un puntero al grafo generado
    return G;
}

void DestruccionDelGrafo(Grafo G){
    //Liberar la memoria pedida para cada lista de vértices y sus elementos.
	//u32 nombre = 0u, indice = 0;
	for (u32 i = 0; i < (G->cant_v*2); ++i) {
		destroy_list(G->hashTable[i]);
	}	
	//Liberar la memoria pedida para el arreglo de punteros a vértices
	free(G->hashTable);
	//Liberar la memoria pedida para el orden del grafo
	free(G->orden);
	//Liberar la memoria pedida para la estructura del grafo
	free(G);
}

u32 NumeroDeVertices(Grafo G){
    return G->cant_v;
}

u32 NumeroDeLados(Grafo G){
    return G->cant_l;
}

u32 Delta(Grafo G){
	return G->delta;
}

u32 Nombre(u32 i,Grafo G){
    return G->orden[i]->nombre;
}

u32 Grado(u32 i,Grafo G){
    return G->orden[i]->grado;
}

u32 IndiceONVecino(u32 j,u32 k,Grafo G){
	if ((k >= G->orden[j]->grado)) {
        return UINT32_MAX;
    }
    return G->orden[j]->vecinos[k]->indice;
}


void agregarLado(Grafo G, u32 nombre1, u32 nombre2, u32* indice){
	u32 pos1, pos2;
	Vertice v1, v2;
	list l_v1, l_v2;
	//Calcula la posición en la hash table según el nombre del vértice.
	pos1 = funcion_hash(G->cant_v,nombre1);
	pos2 = funcion_hash(G->cant_v,nombre2);
	//Se asigna a l_vx la lista de vertices que corresponde con el hash posx.
	l_v1 = G->hashTable[pos1];
	l_v2 = G->hashTable[pos2];
	//Busca un vértice en la lista con el valor nombre nombrex.
	v1 = search_list(l_v1, nombre1);
	v2 = search_list(l_v2, nombre2);

	/*
	Si no se encontro ningún vértice con ese nombre: se crea; se agrega al arreglo orden y
	a la lista en la hash table; y se incrementa el indice_orden.
	*/
	if(v1 == NULL){
		v1 = crearVertice(nombre1);
		G->orden[*indice] = v1;
		*indice = *indice + 1u;
		G->hashTable[pos1] = addl_list(l_v1, v1);
	}
	
	if(v2 == NULL){
		v2 = crearVertice(nombre2);
		G->orden[*indice] = v2;
		*indice = *indice + 1u;
		G->hashTable[pos2] = addl_list(l_v2, v2);
	}
	
	/*
	Agrega a v1 y v2 como vecinos mutuamente.
	*/
	agregarVecinos(v1, v2);
}



Vertice crearVertice(u32 nombre){
	Vertice vertice = malloc(sizeof(struct verticeSt));
	//Vertice *vecinos = NULL;
	if(vertice == NULL){
		fprintf(stderr, "Allocation memory failed.\n");
        exit(EXIT_FAILURE);
	}
	vertice->tamArray = 20;
	vertice->nombre = nombre;
	vertice->grado = 0;
	vertice->vecinos = malloc(vertice->tamArray *sizeof(Vertice));
	return vertice;
}

void agregarVecinos(Vertice v1, Vertice v2) {
	//El elemento se insertará en el último lugar del arreglo de vecinos
	u32 pos1 = v1->grado, pos2 = v2->grado;
	//Si el arreglo está lleno, aumenta su tamaño.
	if(v1->grado >= v1->tamArray) {
		Vertice *vecinos;
		v1->tamArray += 4;
		vecinos = realloc(v1->vecinos, v1->tamArray * sizeof(*v1->vecinos));
		v1->vecinos = vecinos;
	}
	if(v2->grado >= v2->tamArray) {
		Vertice *vecinos;
		v2->tamArray += 4;
		vecinos = realloc(v2->vecinos, v2->tamArray * sizeof(*v2->vecinos));
		v2->vecinos = vecinos;
	}
	//Insertar el vecino al final del array
	v1->vecinos[pos1] = v2;
	v2->vecinos[pos2] = v1;
	//Actualizar el n° de vecinos
	++v1->grado;
	++v2->grado;
}

u32 funcion_hash(u32 cantidad,u32 nombre){
	return nombre % (cantidad * 2);
}

int compOrdenNatural(const void *a, const void *b) {
	//Casteo
	Vertice verticeA = *(Vertice*)a;
	Vertice verticeB = *(Vertice*)b;
	//Comparación
	if (verticeA->nombre > verticeB->nombre)
		return 1;
	else
		return -1;
}
