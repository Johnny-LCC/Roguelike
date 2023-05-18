#include <string.h>
#include <stdlib.h>

#include "init.h"

void init_jogo(struct state *s, int lines, int cols){
  //jogador
  s->j.level=1;
  s->j.hp_max=100;
  s->j.hp_atual=100;
  s->j.xp_max=10;
  s->j.xp_atual=0;
  s->j.px=0;
  s->j.py=0;
  s->j.atk=5;
  s->j.def=5;
  s->j.c='@';
  s->andar=1;
  s->l=lines;
  s->c=cols;
  
  //mapa
  s->bp=(struct Casas **) calloc(s->l, sizeof(struct Casas*));
  for(int i=0; i<s->l; i++){
    s->bp[i] = (struct Casas *) calloc(s->c, sizeof(struct Casas));
  }
  
  //inventário
  s->inventario = (struct Inventario *)calloc(sizeof(struct Inventario));
  strcpy(s->inventario->item.nome, "Espada simples");
  s->inventario->item.equipavel = 1; s->inventario->item.equipado = 1;
  s->inventario->item.dmg = {2,6};
  s->inventario->next = (struct Inventario *)calloc(sizeof(struct Inventario));
  strcpy(s->inventario->next->item.nome, "Escudo enferrujado");
  s->inventario->next->item.equipavel = 1; s->inventario->next->item.equipado = 1;
  s->inventario->next->item.arm = 10;
  s->inventario->next->next = (struct Inventario *)calloc(sizeof(struct Inventario));
  strcpy(s->inventario->next->next->item.nome, "Roupa gasta");
  s->inventario->next->next->item.equipavel = 1; s->inventario->next->next->item.equipado = 1;
  s->inventario->next->next->next=NULL;
  
  //monstros
  for(int i=0; i<10){
    s->monstro[i].py=0;
    s->monstro[i].px=0;
  }
  
  strcpy(s->monstro[0].tipo, "slime");
  s->monstro[0].hp_atual = 5; s->monstro[0].hp_max = 5;
  s->monstro[0].atk = 1; s->monstro[0].def = 3;
  s->monstro[0].dmg = {1,4}; s->monstro[0].arm = 2;
  
  strcpy(s->monstro[1].tipo, "wild beast");
  s->monstro[1].hp_atual = 7; s->monstro[1].hp_max = 7;
  s->monstro[1].atk = 3; s->monstro[1].def = 2;
  s->monstro[1].dmg = {1,4}; s->monstro[1].arm = 3;
  
  strcpy(s->monstro[2].tipo, "goblin");
  s->monstro[2].hp_atual = 10; s->monstro[2].hp_max = 10;
  s->monstro[2].atk = 2; s->monstro[2].def = 3;
  s->monstro[2].dmg = {1,6}; s->monstro[2].arm = 5;
  
  strcpy(s->monstro[3].tipo, "zombie");
  s->monstro[3].hp_atual = 15; s->monstro[3].hp_max = 15;
  s->monstro[3].atk = 2; s->monstro[3].def = 2;
  s->monstro[3].dmg = {1,6}; s->monstro[3].arm = 1;
  
  strcpy(s->monstro[4].tipo, "kobold");
  s->monstro[4].hp_atual = 15; s->monstro[4].hp_max = 15;
  s->monstro[4].atk = 3; s->monstro[4].def = 4;
  s->monstro[4].dmg = {1,8}; s->monstro[4].arm = 5;
  
  strcpy(s->monstro[5].tipo, "kobold");
  s->monstro[5].hp_atual = 15; s->monstro[5].hp_max = 15;
  s->monstro[5].atk = 3; s->monstro[5].def = 4;
  s->monstro[5].dmg = {1,8}; s->monstro[5].arm = 5;
  
  strcpy(s->monstro[6].tipo, "troll");
  s->monstro[6].hp_atual = 20; s->monstro[6].hp_max = 20;
  s->monstro[6].atk = 6; s->monstro[6].def = 3;
  s->monstro[6].dmg = {2,6}; s->monstro[6].arm = 5;
  
  strcpy(s->monstro[7].tipo, "orc");
  s->monstro[7].hp_atual = 20; s->monstro[7].hp_max = 20;
  s->monstro[7].atk = 3; s->monstro[7].def = 5;
  s->monstro[7].dmg = {2,6}; s->monstro[7].arm = 7;
  
  strcpy(s->monstro[8].tipo, "black knight");
  s->monstro[8].hp_atual = 15; s->monstro[8].hp_max = 15;
  s->monstro[8].atk = 6; s->monstro[8].def = 4;
  s->monstro[8].dmg = {1,8}; s->monstro[8].arm = 5;

  //ainda não terminei de escrever essa função.
}