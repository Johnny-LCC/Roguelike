#ifndef ___MAPA_H___
#define ___MAPA_H___

#include "state.h"

void frame(struct state *s);
void grid3x3(int x, struct state *s);
void generate_map(struct state *s);
void print_map(struct state *s);

#endif
