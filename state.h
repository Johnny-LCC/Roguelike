#ifndef ___STATE_H___
#define ___STATE_H___
struct Casas{
  int parede;
  int ocupado;
  int visivel;
  int saida;
  int cor;
  char c;
};

struct Player{
  int level;
  int hp_max;
  int hp_atual;
  int mp_max;
  int mp_atual;
  int xp_max;
  int xp_atual;
  int py;
  int px;
  char c;
};

struct Mobs{
  int n;
  int py;
  int px;
  char tipo[20];
};

struct state{
  struct Casas **bp;
  struct Player j;
  struct Mobs monstro[10];
  int andar;
};
#endif
