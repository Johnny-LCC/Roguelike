#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "action.h"

int dice(int num, int faces){
  srand(time(NULL));
  int r=0;
  for(int i=0; i<num; i++){
    r += (rand() % faces)+1;
  }
  return r;
}

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

void mcombate(struct state *s, int index){
  int a, d, r;
  struct Inventario *aux = s->inventario;
  while( aux!=NULL && aux->item.equipado!=1 && aux->item.id!=1){
    aux=aux->next;
  }
  a = s->mobs[index].inimigo.atk + dice(1, 20);
  d = s->j.def + dice(1, 20);
  if (a > d){
    r = dice(s->mobs[index].inimigo.dmg.n_dados, s->mobs[index].inimigo.dmg.n_faces);
    if (r > aux->item.arm) s->j.hp_atual -= (r-aux->item.arm);
  }
}

void maction(struct state *s){
  for(int i=0; i<(s->andar%10); i++){
    if(s->mobs[i].inimigo.hp_atual > 0){
      int dx = (s->j.px - s->mobs[i].px);
      int dy = (s->j.py - s->mobs[i].py);
      if((dx==1 || dx==0 || dx==-1) && (dy==1 || dy==0 || dy==-1)){
        mcombate(s, i);
      }
      else if (s->bp[s->mobs[i].py][s->mobs[i].px].visivel==1){
        s->bp[s->mobs[i].py][s->mobs[i].px].c='.';
        s->bp[s->mobs[i].py][s->mobs[i].px].cor=2;
        s->bp[s->mobs[i].py][s->mobs[i].px].ocupado=0;
        s->bp[s->mobs[i].py][s->mobs[i].px].parede=0;
        if(dy > 0) s->mobs[i].py++;
        else if(dy < 0) s->mobs[i].py--;
        if(dx > 0) s->mobs[i].px++;
        else if(dx < 0) s->mobs[i].px--;
        s->bp[s->mobs[i].py][s->mobs[i].px].c='X';
        s->bp[s->mobs[i].py][s->mobs[i].px].cor=5;
        s->bp[s->mobs[i].py][s->mobs[i].px].ocupado=1;
        s->bp[s->mobs[i].py][s->mobs[i].px].parede=0;
      }
    }
  }
}

void listar(struct state *s){
  WINDOW *new = newwin(s->l, s->c, 0, 0);
  box(new, 0, 0);
  int i=1;
  struct Inventario *aux = s->inventario;
  while (aux != NULL){
    mvwprintw(new, i, 1, "%s:", aux->item.nome);
    mvwprintw(new, i+1, 1, "\t+%dD%d de dano)", aux->item.dmg.n_dados, aux->item.dmg.n_faces);
    mvwprintw(new, i+2, 1, "+%d", aux->item.arm);
    aux = aux->next;
    i++;
  }
  free(aux);
  wgetch(new);
  endwin();
}

void combate(struct state *s, int y, int x){
  int a, d, r;
  WINDOW *warning;
  struct Inventario *aux = s->inventario;
  while( aux!=NULL && aux->item.equipado!=1 && aux->item.id!=0){
    aux=aux->next;
  }
  a = s->j.atk + dice(1, 20);
  for(int i=0; i < (s->andar)%10; i++){
    if(s->mobs[i].py == s->j.py+y && s->mobs[i].px == s->j.px+x){
      d = s->mobs[i].inimigo.def + dice(1, 20);
      if (a > d){
        r=dice(aux->item.dmg.n_dados, aux->item.dmg.n_faces);
        if(r > s->mobs[i].inimigo.arm) s->mobs[i].inimigo.hp_atual -= (r-s->mobs[i].inimigo.arm); 
      }
      else{
        warning = newwin(5, 30, ((s->l)/2)-2, ((s->c)/2)-15);
        box(warning, 0, 0);
        mvwprintw(warning, 2, 3, ("O ataque falhou..."));
        wgetch(warning);
        endwin();
      }
      if (s->mobs[i].inimigo.hp_atual <= 0){
        warning = newwin(5, 30, ((s->l)/2)-2, ((s->c)/2)-15);
        box(warning, 0, 0);
        mvwprintw(warning, 2, 1, ("Você derrotou um inimigo!"));
        wgetch(warning);
        endwin();
        s->bp[s->mobs[i].py][s->mobs[i].px].c = '.';
        s->bp[s->mobs[i].py][s->mobs[i].px].cor = 2;
        s->bp[s->mobs[i].py][s->mobs[i].px].ocupado = 0;
        //reward(s);
      }
    }
  }
}

void action(int *t, struct state *s){ 
  s->bp[s->j.py][s->j.px].c='.'; s->bp[s->j.py][s->j.px].cor=2;
  switch (*t){
    case 9:
      s->andar+=100;
      break;
    case 27:
      listar(s);
      break;
    case 56:
      if (s->bp[s->j.py-1][s->j.px].ocupado==1) combate(s, -1, 0);
      else if  (s->bp[s->j.py-1][s->j.px].parede==0) s->j.py--;
      break;
    case 50:
      if (s->bp[s->j.py+1][s->j.px].parede==1) combate(s, 1, 0);
      else if (s->bp[s->j.py+1][s->j.px].parede==0) s->j.py++;
      break;
    case 52:
      if (s->bp[s->j.py][s->j.px-1].ocupado==1) combate(s, 0, -1);
      else if (s->bp[s->j.py][s->j.px-1].parede==0) s->j.px--;
      break;
    case 54:
      if (s->bp[s->j.py][s->j.px+1].ocupado==1) combate(s, 0, 1);
      else if (s->bp[s->j.py][s->j.px+1].parede==0) s->j.px++;
      break;
    case 55:
      if (s->bp[s->j.py-1][s->j.px-1].ocupado==1) combate(s, -1, -1);
      else if (s->bp[s->j.py-1][s->j.px-1].parede==0) {s->j.py--; s->j.px--;}
      break;
    case 57:
      if (s->bp[s->j.py-1][s->j.px+1].ocupado==1) combate(s, -1, 1);
      else if (s->bp[s->j.py-1][s->j.px+1].parede==0) {s->j.py--; s->j.px++;}
      break;
    case 49:
      if (s->bp[s->j.py+1][s->j.px-1].ocupado==1) combate(s, 1, -1);
      else if (s->bp[s->j.py+1][s->j.px-1].parede==0) {s->j.py++; s->j.px--;}
      break;
    case 51:
      if (s->bp[s->j.py+1][s->j.px+1].ocupado==1) combate(s, 1, 1);
      else if (s->bp[s->j.py+1][s->j.px+1].parede==0) {s->j.py++; s->j.px++;}
      break;
    default:
      break;
  }
  s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
  maction(s);
  update_visibility(s);
}
