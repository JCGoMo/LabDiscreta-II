#include "EstructuraGrafo.h"
//#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

#define NUMERO_MAXIMO 4294967295  //  2^32 - 1


typedef struct LadoSt *Lados;
typedef struct LadoSt Lado;

struct LadoSt {
    u32 x;
    u32 y;
};

Lado CrearLado(u32 x, u32 y) {
    Lado l;
    l.x = x;
    l.y = y;
    return l;
}

Lados ConstruirLados(u32 m) {
    Lados l = calloc(m, sizeof(struct LadoSt));
    return (l);
}

Lados AgregarLados(Lados l, u32 i, u32 x, u32 y) {
    l[2*i] = CrearLado(x,y);
    l[2*i+1] = CrearLado(y,x);
    return (l);
}

static int CompararLados(const void* a, const void* b) {
    Lado *x1 = (Lado*) a;
    Lado *x2 = (Lado*) b;
    if( x1->x < x2->x ) {
        return -1;
    } else if(x1->x > x2->x) {
        return 1;
    } else {
        return 0;
    }
}

void OrdenarLados(Lados l, u32 m) {
   qsort(l, m, sizeof(struct LadoSt), CompararLados);
}

u32 VerticeXDelLado(Lados l, u32 i) {
    return (l[i].x);
}

u32 VerticeYDelLado(Lados l, u32 i) {
    return (l[i].y);
}

static u32 BusquedaBinaria(Vertices v, u32 nombre, u32 left, u32 rigth) {
    if(rigth >= left){
        u32 med = (left + rigth) / 2;

        if (v[med].nombre == nombre) return med;
        if (v[med].nombre > nombre) return BusquedaBinaria(v, nombre, left, med - 1);        
        return BusquedaBinaria(v, nombre, med + 1, rigth);

    } 
    return -1;
}

/**
 * guarda memoria para un arreglo de tamaño n (de u32),
 * en el cual se pondra el "orden" de los vertices.
**/
static u32 *OrdenDeVertices(u32 n) {
    u32 *orden = calloc(n, sizeof(u32));
    for (u32 i = 0; i < n; i++) {
        orden[i] = i;
    }
    return orden;
}

static u32 ObtenerDelta(Vertices v, u32 n) {
    u32 delta = 0;
    for(u32 i = 0; i < n; i++) {
        if (delta <= v[i].grado) delta = v[i].grado;
    }
    return delta;
}

static Grafo CargarDatosGrafo(u32 n, u32 m, Vertices v, u32* orden) {
    Grafo G = (Grafo)malloc(sizeof(struct GrafoSt));
    G->n = n;
    G->m = m;
    G->v = v;
    G->orden = orden;
    G->delta = ObtenerDelta(v, n);
    return G;
}

static Vertice CrearVertice(u32 nombre, u32 color, u32 grado, u32 *vecinos) {
    Vertice v;
    v.nombre = nombre;
    v.color = color;
    v.grado = grado;
    v.vecinos = vecinos;
    return (v);
}

/**
 * dado el arreglo de lados de tamaño l (todos los lados ya ordenados por su primera componente),
 * retorna un arreglo de vertics.
 * la busqueda binaria se hace para encontrar a los vecinos del vertice dentro del arreglo de lados.
**/
static Vertices ListaVertices(u32 n, u32 l, Lados lados) {
    Vertices vertices = calloc(n, sizeof(struct VerticeSt));
    u32 v1 = VerticeXDelLado(lados,0);
    Vertice vertice = CrearVertice(v1, 0, 1, NULL);
    vertices[0] = vertice;
    u32 j = 1;
    for(u32 i = 1; i < l; i++) {
        u32 v2 = VerticeXDelLado(lados, i);
        if(v1 != v2) {
            v1 = v2;
            vertices[j] = CrearVertice(v1, j, 1, NULL);
            j++;
        } else {
            vertices[j-1].grado++;
        }
    }
    if(j != n) {
        free(vertices);
        vertices = NULL;
        return vertices;
    }
    u32 s = 0;     // este indice es para recorrer el arreglo de lados
    for(u32 i = 0; i < n; i++) {
        u32* vecinos = calloc(vertices[i].grado, sizeof(u32));
        u32 k = vertices[i].grado;
        for(u32 j = 0; j < k; j++) {
            vecinos[j] = BusquedaBinaria(vertices, VerticeYDelLado(lados,s), 0, n - 1);
            s++;
        }
        vertices[i].vecinos = vecinos;
    }
    return (vertices);
}

Grafo ConstruccionDelGrafo() {
    Grafo G = NULL;
    u32 n, m, x = 0;
    u32 y, i = 0;
    Lados lados = NULL;
    Vertices vertices = NULL;
    u32 *orden = NULL;
    char c;
    while(fscanf(stdin, " %c", &c) != EOF) {
        if(c == 'p') {
            fscanf(stdin, " edge %u %u", &n, &m);
            lados = ConstruirLados(2*m);
            break;
        } else if(c == 'c') {
            fscanf(stdin, "%*[^\n]\n");
        } else {
            printf("error al leer comentarios\n");
            return G;
        }
    }
    while(i < m && fscanf(stdin, " %c", &c) != EOF) {
        if(c == 'e') {
            fscanf(stdin, "%u %u", &x, &y);
            lados = AgregarLados(lados,i,x,y);
            i++;
        } else {
            printf("error con formato de entrada\n");
            free(lados);
            return G;
        }
    }
    if(i != m) {
        printf("error al leer lado\n");
        free(lados);
        return G;
    }
    OrdenarLados(lados, 2*m);
    vertices = ListaVertices(n, 2*m, lados);
    if(vertices == NULL) {
        free(lados);
        printf("cantidad de vertices declarados no es la misma\n");
        return G;
    }
    // crea el el arreglo que contiene el orden de los vertices,
    // que por defecto va a ser el orden natural, ya que "vertices" (osea el arreglo de los vertices) ya está
    // ordenado naturalmente, entonces orden[i] sera el i-esimo vertice de "vertices", el cual tambien será el i-esimo
    // vertice en el orden natural.
    orden = OrdenDeVertices(n);
    free(lados);
    G = CargarDatosGrafo(n, m, vertices, orden);
    return G;
}

void DestruccionDelGrafo(Grafo G) {
    for(u32 i = 0; i < G->n; i++) {
        free(G->v[i].vecinos);
    }
    free(G->v);
    free(G->orden);
    free(G);
}

u32 NumeroDeVertices(Grafo G) {
    return G->n;
}

u32 NumeroDeLados(Grafo G) {
    return G->m;
}

u32 Delta(Grafo G) {
    return G->delta;
}

u32 Nombre(Grafo G, u32 i) {
    return G->v[G->orden[i]].nombre;

}

u32 Grado(Grafo G, u32 i) {
    return ((i >= G->n) ? NUMERO_MAXIMO : G->v[G->orden[i]].grado);
}

u32 IndiceONVecino(u32 j, u32 k, Grafo G) {
	if((k >= G->n) || (k < G->n && j >= G->v[G->orden[k]].grado)) {
		return NUMERO_MAXIMO;
	}
	u32 nickname = G->v[G->orden[k]].vecinos[j];
	u32 n = G->n;
    for (u32 i = 0; i < n; i++) {
    	if(G->v[G->orden[i]].nombre == nickname) {
        	return i;
        }
    }
    return 0;
}
