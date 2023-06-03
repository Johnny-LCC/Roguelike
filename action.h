#ifndef ___ACTION_H___
#define ___ACTION_H___

#include "state.h"

void update_visibility(struct state *s);
void listar(struct state *s);
void equipar(struct state *s, int itemID);
void update_Inventario(struct state *s, char* nome, int equipavel, int equipado, int dados, int faces, int id, int arma);
void reward(struct state *s);
void drop(struct state *s);
int dice(int num, int faces);
void mcombate(struct state *s, int index);
void maction(struct state *s);
void combate(struct state *s, int y, int x);
void action(int *t, struct state *s);

#endif
