#ifndef ___TESOUROS_H___
#define ___TESOUROS_H___

#include "state.h"

void generate_treasure(struct state *s, struct Tesouro *t);
void check_treasure_collision(struct state *s, struct Tesouro *t);


#endif
