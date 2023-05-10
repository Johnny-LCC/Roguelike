#ifndef ___MAPA_H___
#define ___MAPA_H___

#include "state.h"

void frame(int *l, int *c, struct state *s);
void grid3x3(int *l, int *c, int x, struct state *s);
void generate_map(int *l, int *c, struct state *s);
void print_map(int *l, int *c, struct state *s);

#endif
