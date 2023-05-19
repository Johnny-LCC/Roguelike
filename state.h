#ifndef ___STATE_H___
#define ___STATE_H___

struct Casas{
  int parede;
  int ocupado;
  int visivel;
  int saida;
  //int drop;
  int cor;
  char c;
};

struct Dano{
  int n_dados;
  int n_faces;
};

struct Player{
  int level;
  int hp_max;
  int hp_atual;
  int xp_max;
  int xp_atual;
  int atk;
  int def;
  struct Dano dmg;
  int arm;
  int py;
  int px;
  char c;
};

struct Item{
  char nome[20];
  int consumivel;
  int equipavel;
  int equipado;
  int id;
  struct Dano dmg;
  int arm;
  int heal;
};

struct Inventario{
  struct Item item;
  int quantidade;
  struct Inventario *next;
};

struct Monstro{
  int hp_max;
  int hp_atual;
  int atk;
  int def;
  struct Dano dmg;
  int arm;
  char tipo[20];
};

struct Mobs{
  int py;
  int px;
  struct Monstro inimigo;
};

struct state{
  struct Casas **bp;
  struct Player j;
  //struct Item drops[10];
  struct Inventario *inventario;
  struct Monstro monstro[10];
  struct Mobs mobs[10];
  int andar;
  int l;
  int c; 
};

#endif
