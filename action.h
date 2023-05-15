#ifndef ___ACTION_H___
#define ___ACTION_H___

#include "state.h"

void update_visibility(int *l, int *c, struct state *s);
void mmovement_alt(struct state *s);
void listar(struct state *s);
void combate(struct state *s);
void action(int *t, int *l, int *c, struct state *s);

#endif
