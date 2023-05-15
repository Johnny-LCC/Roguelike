#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "action.h"

void update_visibility(struct state *s){
    for (int y = 1; y < s->l-1; y++) {
        for (int x = 1; x < s->c-1; x++) {
            if (s->bp[y][x].visivel == 1) {
              s->bp[y][x].visivel = 0;
            }
        }
    }
    for (int angle = 0; angle < 360; angle++) {
        float ray_angle = angle * M_PI / 180.0;
        float ray_x = cos(ray_angle);
        float ray_y = sin(ray_angle);
        
        float ray_pos_x = s->j.px + 0.5;
        float ray_pos_y = s->j.py + 0.5;
        while (ray_pos_x >= 0 && ray_pos_x < s->c && ray_pos_y >= 0 && ray_pos_y < s->l) {
            int cell_x = (int)ray_pos_x;
            int cell_y = (int)ray_pos_y;
            if (s->bp[cell_y][cell_x].parede == 1) {
                s->bp[cell_y][cell_x].visivel=1;
                break;
            }
            s->bp[cell_y][cell_x].visivel = 1;
            ray_pos_x += ray_x;
            ray_pos_y += ray_y;
        }
    }
}

void maction(struct state *s){
  for(int i=0; i<(s->andar%10); i++){
    int dx = (s->j.px - s->monstro[i].px);
    int dy = (s->j.py - s->monstro[i].py);
    if((dx==1 || dx==0 || dx==-1) && (dy==1 || dy==0 || dy==-1)){
      s->j.hp_atual--;
    }
    else if (s->bp[s->monstro[i].py][s->monstro[i].px].visivel==1){
      s->bp[s->monstro[i].py][s->monstro[i].px].c='.';
      s->bp[s->monstro[i].py][s->monstro[i].px].cor=2;
      s->bp[s->monstro[i].py][s->monstro[i].px].ocupado=0;
      s->bp[s->monstro[i].py][s->monstro[i].px].parede=0;
      if(dy > 0) s->monstro[i].py++;
      else if(dy < 0) s->monstro[i].py--;
      if(dx > 0) s->monstro[i].px++;
      else if(dx < 0) s->monstro[i].px--;
      s->bp[s->monstro[i].py][s->monstro[i].px].c='X';
      s->bp[s->monstro[i].py][s->monstro[i].px].cor=5;
      s->bp[s->monstro[i].py][s->monstro[i].px].ocupado=1;
      s->bp[s->monstro[i].py][s->monstro[i].px].parede=0;
    }
  }
}

void listar(struct state *s){
  WINDOW *new = newwin(s->l, s->c, 0, 0);
  box(new, 0, 0);
  int i=1;
  struct Inventario *aux = s->inventario;
  while (aux != NULL){
    mvwprintw(new, i, 1, "%s (+%d)", aux->item.nome, aux->item.stats);
    aux = aux->next;
    i++;
  }
  free(aux);
  wgetch(new);
  endwin();
}

void combate(struct state *s){
  WINDOW *new = newwin(s->l, s->c, 0, 0);
  box(new, 0, 0);
  mvwprintw(new, 1, 1, "1. Ataque rápido");
  mvwprintw(new, 2, 1, "2. Ataque forte");
  mvwprintw(new, 3, 1, "3. Defender");
  mvwprintw(new, 4, 1, "4. Esquivar");
  wgetch(new);
  endwin();
}

void action(int *t, struct state *s){
  s->bp[s->j.py][s->j.px].c='.'; s->bp[s->j.py][s->j.px].cor=2; 
  if(*t==27) s->andar+=100;
  else if(*t==99) combate(s);
  else if(*t==105) listar(s);
  else if (*t==56 && s->bp[s->j.py-1][s->j.px].parede==0) s->j.py--;
  else if (*t==50 && s->bp[s->j.py+1][s->j.px].parede==0) s->j.py++;
  else if (*t==52 && s->bp[s->j.py][s->j.px-1].parede==0) s->j.px--;
  else if (*t==54 && s->bp[s->j.py][s->j.px+1].parede==0) s->j.px++;
  else if (*t==55 && s->bp[s->j.py-1][s->j.px-1].parede==0) {s->j.py--; s->j.px--;}
  else if (*t==57 && s->bp[s->j.py-1][s->j.px+1].parede==0) {s->j.py--; s->j.px++;}
  else if (*t==49 && s->bp[s->j.py+1][s->j.px-1].parede==0) {s->j.py++; s->j.px--;}
  else if (*t==51 && s->bp[s->j.py+1][s->j.px+1].parede==0) {s->j.py++; s->j.px++;}
  s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
  maction(s);
  update_visibility(s);
}
