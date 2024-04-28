#ifndef __ESTRUCTURAGRAFO_H
#define __ESTRUCTURAGRAFO_H

#include <stdint.h>

typedef uint32_t u32;

typedef struct VerticeSt {
	u32 nombre;
	u32 grado;
	u32 *vecinos;
} VerticeSt;

typedef struct GrafoSt {
	u32 n;
	u32 m;
	u32 delta;
	VerticeSt vertices[];
} GrafoSt;

#endif
