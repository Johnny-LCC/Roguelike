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

struct Item{
  char nome[20];
  int consumivel;
  int quantidade;
  int equipavel;
  int atk;
  int def;
  int stats;
};

struct Inventario{
  struct Item item;
  struct Inventario *next;
};

struct Mobs{
  int py;
  int px;
  char tipo[20];
};

struct state{
  struct Casas **bp;
  struct Player j;
  struct Inventario *inventario;
  struct Mobs monstro[10];
  int andar;
  int l;
  int c;
};
#endif
