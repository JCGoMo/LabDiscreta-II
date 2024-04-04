#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

typedef struct NombreYPosSt {
	u32 nombre;
	u32 pos;
} NombreYPosSt;

static int cmp(const void *_a, const void *_b)
{
	const NombreYPosSt *a = _a;
	const NombreYPosSt *b = _b;
	if (a->nombre < b->nombre)
		return -1;
	if (a->nombre > b->nombre)
		return 1;
	return 0;
}

static u32 *Lectura(u32 * n, u32 * m)
{
	char c;
	int res;
	// Salteamos comentarios
	res = scanf("%c", &c);
	if (res != 1)
		return NULL;
	while (c == 'c') {
		res = scanf("%*[^\n] ");	// Solo guardamos esto porque sino gcc se queja
		res = scanf("%c", &c);
		if (res != 1)
			return NULL;
	}
	if (c != 'p')
		return NULL;
	// Fin de comentarios, encontramos la 'p', debe seguir " edge n m"
	res = scanf(" edge %" PRIu32 " %" PRIu32, n, m);
	if (res != 2)
		return NULL;
	// Siguen los lados, pedimos memoria para leerlos
	u32 *lados = malloc(*m * 2 * sizeof(u32));
	if (lados == NULL)
		return NULL;

	for (size_t i = 0; i < *m * 2; i += 2) {
		res =
		    scanf(" e %" PRIu32 " %" PRIu32, &lados[i], &lados[i + 1]);
		if (res != 2) {
			free(lados);
			return NULL;
		}
	}
	return lados;

}

Grafo ConstruccionDelGrafo()
{
	u32 *lados, n, m;
	lados = Lectura(&n, &m);
	if (lados == NULL)
		return NULL;
	// Terminamos lectura. Creamos nuestro grafo.
	Grafo g = malloc(sizeof(GrafoSt) + sizeof(VerticeSt) * n);
	if (g == NULL) {
		free(lados);
		return NULL;
	}
	g->n = n;
	g->m = m;
	g->delta = 0;

	// Copiamos lados a un nuevo array para ser ordenado
	NombreYPosSt *nodos = malloc(sizeof(NombreYPosSt) * m * 2);
	if (nodos == NULL) {
		free(g);
		free(lados);
		return NULL;
	}
	for (size_t i = 0; i < m * 2; ++i) {
		nodos[i].nombre = lados[i];
		nodos[i].pos = i;
	}

	qsort(nodos, m * 2, sizeof(NombreYPosSt), cmp);

	// Recorremos nodos, aprovechando que tenemos la pos. original para
	// reescribir lados en Orden Natural.
	u32 ONactual = 0;
	u32 nombreactual = nodos[0].nombre;
	u32 gradoactual = 0;
	for (size_t i = 0; i < m * 2; ++i) {
		if (nodos[i].nombre != nombreactual) {
			// Terminamos con un vertice, lo guardamos
			g->vertices[ONactual].nombre = nombreactual;
			g->vertices[ONactual].grado = gradoactual;
			if (g->delta < gradoactual)
				g->delta = gradoactual;
			// Nos preparamos para el sig. vertice
			ONactual++;
			nombreactual = nodos[i].nombre;
			gradoactual = 0;
		}
		lados[nodos[i].pos] = ONactual;
		gradoactual++;
	}
	// No nos olvidemos del ultimo!
	g->vertices[ONactual].nombre = nombreactual;
	g->vertices[ONactual].grado = gradoactual;
	if (g->delta < gradoactual)
		g->delta = gradoactual;

	free(nodos);

	// Armamos las listas de adyacencia
	for (size_t i = 0; i < n; ++i) {
		g->vertices[i].vecinos =
		    malloc(g->vertices[i].grado * sizeof(u32));
		// Necesitabamos el grado para pedir memoria. Como ya hicimos esto,
		// lo podemos reiniciar para usarlo como indice en la lista de vecinos
		g->vertices[i].grado = 0;
		if (g->vertices[i].vecinos == NULL) {
			for (size_t j = 0; j < i; ++j)
				free(g->vertices[j].vecinos);
			free(g);
			free(lados);
			return NULL;
		}
	}
	for (size_t i = 0; i < m * 2; i += 2) {
		u32 a = lados[i], b = lados[i + 1];
		g->vertices[a].vecinos[g->vertices[a].grado++] = b;
		g->vertices[b].vecinos[g->vertices[b].grado++] = a;
	}
	// Al final de este ciclo el .grado de cada vertice vuelve a ser correcto.

	free(lados);

	return g;

}

void DestruccionDelGrafo(Grafo g)
{
	assert(g != NULL);
	for (size_t i = 0; i < g->n; ++i) {
		free(g->vertices[i].vecinos);
	}
	free(g);
}

u32 NumeroDeVertices(Grafo g)
{
	assert(g != NULL);
	return g->n;
}

u32 NumeroDeLados(Grafo g)
{
	assert(g != NULL);
	return g->m;
}

u32 Delta(Grafo g)
{
	assert(g != NULL);
	return g->delta;
}

u32 Nombre(u32 i, Grafo g)
{
	assert(g != NULL);
	assert(i < g->n);
	return g->vertices[i].nombre;
}

u32 Grado(u32 i, Grafo g)
{
	assert(g != NULL);
	if(i >= g->n)
		return UINT32_MAX;
	return g->vertices[i].grado;
}

u32 IndiceONVecino(u32 j, u32 k, Grafo g)
{
	assert(g != NULL);
	if(k >= g->n || j >= g->vertices[k].grado)
		return UINT32_MAX;
	return g->vertices[k].vecinos[j];
}
