#ifndef ___MENU_H___
#define ___MENU_H___

#include "state.h"

void menu(int l, int c);
void intro(int l, int c);
void outro(struct state *s);
void tutorial(void);
void credit(struct state *s);

#endif
