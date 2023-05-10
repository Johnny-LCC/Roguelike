#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

//#include "state.h"
#include "action.h"

void update_visibility(int *l, int *c, struct state *s){
    for (int y = 1; y < *l-1; y++) {
        for (int x = 1; x < *c-1; x++) {
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
        while (ray_pos_x >= 0 && ray_pos_x < *c && ray_pos_y >= 0 && ray_pos_y < *l) {
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

void mmovement_alt(struct state *s){
  for(int i=0; i<(s->andar%10); i++){
    if(s->bp[s->monstro[i].py][s->monstro[i].px].visivel==1){
      s->bp[s->monstro[i].py][s->monstro[i].px].c='.';
      s->bp[s->monstro[i].py][s->monstro[i].px].cor=2;
      s->bp[s->monstro[i].py][s->monstro[i].px].ocupado=0;
      s->bp[s->monstro[i].py][s->monstro[i].px].parede=0;
      int dx = (s->j.px - s->monstro[i].px);
      int dy = (s->j.py - s->monstro[i].py);
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

void action(int *t, int *l, int *c, struct state *s){
  s->bp[s->j.py][s->j.px].c='.'; s->bp[s->j.py][s->j.px].cor=2; 
  if(*t==27) s->andar+=100;
  //else if(*t==9) generate_map(l, c, s);
  else if (*t==56 && s->bp[s->j.py-1][s->j.px].parede==0) s->j.py--;
  else if (*t==50 && s->bp[s->j.py+1][s->j.px].parede==0) s->j.py++;
  else if (*t==52 && s->bp[s->j.py][s->j.px-1].parede==0) s->j.px--;
  else if (*t==54 && s->bp[s->j.py][s->j.px+1].parede==0) s->j.px++;
  else if (*t==55 && s->bp[s->j.py-1][s->j.px-1].parede==0) {s->j.py--; s->j.px--;}
  else if (*t==57 && s->bp[s->j.py-1][s->j.px+1].parede==0) {s->j.py--; s->j.px++;}
  else if (*t==49 && s->bp[s->j.py+1][s->j.px-1].parede==0) {s->j.py++; s->j.px--;}
  else if (*t==51 && s->bp[s->j.py+1][s->j.px+1].parede==0) {s->j.py++; s->j.px++;}
  s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
  mmovement_alt(s);
  update_visibility(l, c, s);
  //print_map(l, c, s);
}
