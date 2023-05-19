#ifndef ___ACTION_H___
#define ___ACTION_H___

#include "state.h"

void update_visibility(struct state *s);
void listar(struct state *s);
void reward(struct state *s);
int dice(int num, int faces);
void mcombate(struct state *s, int index);
void maction(struct state *s);
void combate(struct state *s, int y, int x);
void action(int *t, struct state *s);

#endif
