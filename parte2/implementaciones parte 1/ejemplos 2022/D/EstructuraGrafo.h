typedef unsigned int u32;

typedef struct graph GrafoSt;

typedef struct tupla_s* tupla;

struct tupla_s {
    u32 v1;
    u32 v2;
};

struct graph {
    u32 n;
    u32 m;
    u32* nombres;
    u32* grados;
    u32** vecinos;
    u32 delta;
};