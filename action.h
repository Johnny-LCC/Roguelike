#ifndef ___ACTION_H___
#define ___ACTION_H___

#include "state.h"

int dice(int num, int faces);
void update_visibility(struct state *s);
void mcombate(struct state *s, int index);
void maction(struct state *s);
void combate(struct state *s, int y, int x);
void action(int *t, struct state *s);

#endif
