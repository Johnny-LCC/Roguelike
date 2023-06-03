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

void listar(struct state *s){
  WINDOW *new = newwin(s->l, s->c, 0, 0);
  box(new, 0, 0);
  mvwprintw(new, 1, 1, "STATUS:");
  mvwprintw(new, 2, 1, "ATK: %d\tDEF: %d", s->j.atk, s->j.def);
  mvwprintw(new, 3, 1, "DMG: %dD%d\tARM: %d", s->j.dmg.n_dados, s->j.dmg.n_faces, s->j.arm);
  mvwprintw(new, 5, 1, "INVENTARIO:");
  int i=6;
  struct Inventario *aux = s->inventario;
  while (aux != NULL){
    mvwprintw(new, i, 1, "%s(EQUIPADO):", aux->item.nome);
    mvwprintw(new, i+1, 1, "\tDano:%dD%d", aux->item.dmg.n_dados, aux->item.dmg.n_faces);
    mvwprintw(new, i+2, 1, "\tDefesa:+%d", aux->item.arm);
    aux = aux->next;
    i+=3;
  }
  free(aux);
  i=1;
  for(int j=0; j<(s->andar)%10; j++){
    if(s->bp[s->mobs[j].py][s->mobs[j].px].visivel==1){
      mvwprintw(new, i, (s->c)/2, "%s:", s->mobs[j].inimigo.tipo);
      mvwprintw(new, i+1, (s->c)/2, "ATK: %d\tDEF: %d", s->mobs[j].inimigo.atk, s->mobs[j].inimigo.def);
      mvwprintw(new, i+2, (s->c)/2, "DMG: %dD%d\tARM: %d", s->mobs[j].inimigo.dmg.n_dados, s->mobs[j].inimigo.dmg.n_faces, s->mobs[j].inimigo.arm);
      i+=4;
    }
  }
  wgetch(new);
  endwin();
}

void equipar(struct state *s, int itemID){
  struct Inventario *aux = s->inventario;

    while (aux != NULL) {
    if (aux->item.id == itemID) {
      aux->item.equipado = 1;  
    } else {
      if(aux->item.arma == 1) aux->item.equipado = 0; 
    }
    
    aux = aux->next;
  }
}


void update_Inventario(struct state *s, char* nome, int equipavel, int equipado, int dados, int faces, int id, int arma) {
  struct Inventario *aux = s->inventario;
  WINDOW *warning;

  while (aux != NULL) {
    if (strcmp(aux->item.nome, nome) == 0){
      aux->quantidade++;
      break;
    }
    else if (aux->next == NULL) {
      aux->next = (struct Inventario *)malloc(sizeof(struct Inventario));
      strcpy(aux->next->item.nome, nome);
      aux->next->item.equipavel = equipavel;
      aux->next->item.equipado = equipado;
      aux->next->item.dmg.n_dados = dados;
      aux->next->item.dmg.n_faces = faces;
      aux->next->item.id = id;
      aux->next->item.arma = arma;
      warning = newwin(5, 30, ((s->l)/2)-2, ((s->c)/2)-15);
      box(warning, 0, 0);
      mvwprintw(warning, 2, 1, "Encontrou uma %s", nome);
      wgetch(warning);
      endwin();
      break;
    }
    aux = aux->next;
  }
}

int dice(int num, int faces){
  srand(time(NULL));
  int r=0;
  for(int i=0; i<num; i++){
    r += (rand() % faces)+1;
  }
  return r;
}

void drop(struct state *s){
  srand(time(NULL));
  int r = rand() % 10;
  if (r==3) {
     update_Inventario(s, "Motosserra", 1, 0, 3, 6, 1, 1);
  }
  else if (r==4) {
    update_Inventario(s, "Acha", 1, 0, 1, 12, 1, 1);
  }
  else if (r==5) {
      update_Inventario(s, "Adaga", 1, 0, 2, 4, 1, 1);
  }
  else if (r==6) {
     update_Inventario(s, "Espada Longa", 1, 0, 2, 8, 1, 1);
  } 
}

void reward(struct state *s){
  int h;
  srand(time(NULL));
  int r = rand() % 3;
  if (r==0) s->j.atk++;
  else if (r==1) s->j.def++;
  else {
    h = dice(2, 20);
    if(s->j.hp_atual + h > 100) s->j.hp_atual = 100;
    else s->j.hp_atual += h;
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
        char aux; int caux, yy, xx;
        yy = s->mobs[i].py;
        xx = s->mobs[i].px;
        if(dy > 0) s->mobs[i].py++;
        else if(dy < 0) s->mobs[i].py--;
        if(dx > 0) s->mobs[i].px++;
        else if(dx < 0) s->mobs[i].px--;
        if (s->bp[yy][xx].saida==1){
          aux='o'; caux=6;
        }
        else {aux='.'; caux=2;}
        s->bp[yy][xx].c=aux;
        s->bp[yy][xx].cor=caux;
        s->bp[yy][xx].ocupado=0;
        s->bp[yy][xx].parede=0;
        s->bp[s->mobs[i].py][s->mobs[i].px].c='X';
        s->bp[s->mobs[i].py][s->mobs[i].px].cor=5;
        s->bp[s->mobs[i].py][s->mobs[i].px].ocupado=1;
        s->bp[s->mobs[i].py][s->mobs[i].px].parede=0;
      }
    }
  }
}

void combate(struct state *s, int y, int x){
  int a, d, r;
  srand(time(NULL));
  //int v = rand() % 5;
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
        else{
          warning = newwin(5, 30, ((s->l)/2)-2, ((s->c)/2)-15);
          box(warning, 0, 0);
          mvwprintw(warning, 2, 1, "O ataque não surgiu efeito.");
          mvwprintw(warning, 3, 4, "O inimigo defendeu-se.");
          wgetch(warning);
          endwin();
        }
      }
      else{
        warning = newwin(5, 30, ((s->l)/2)-2, ((s->c)/2)-15);
        box(warning, 0, 0);
        mvwprintw(warning, 2, 3, "O ataque falhou...");
        wgetch(warning);
        endwin();
      }
      if (s->mobs[i].inimigo.hp_atual <= 0){
        warning = newwin(5, 30, ((s->l)/2)-2, ((s->c)/2)-15);
        box(warning, 0, 0);
        mvwprintw(warning, 2, 2, "Você derrotou o inimigo.");
        wgetch(warning);
        endwin();
        s->bp[s->mobs[i].py][s->mobs[i].px].c = '.';
        s->bp[s->mobs[i].py][s->mobs[i].px].cor = 2;
        s->bp[s->mobs[i].py][s->mobs[i].px].ocupado = 0;
        s->j.xp_atual += 5;
        drop(s);
        if (s->j.xp_atual >= s->j.xp_max){
          s->j.xp_atual -= s->j.xp_max;
          s->j.xp_max += 5;
          s->j.level++;
          reward(s);
        }
      }
    }
  }
}

void action(int *t, struct state *s){
  WINDOW *new;
  int aux;
  s->bp[s->j.py][s->j.px].c='.'; s->bp[s->j.py][s->j.px].cor=2;
  switch (*t){
    case 27:
      new = newwin(7, 40, ((s->l)/2)-4, ((s->c)/2)-20);
      box(new, 0, 0);
      mvwprintw(new, 1, 3, "Certeza que desajas sair do jogo?");
      mvwprintw(new, 2, 4, "O seu progresso não será salvo.");
      mvwprintw(new, 3, 5, "(Aperte 'ESC' para confirmar)");
      aux=wgetch(new);
      s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
      if (aux==27) s->andar+=100;
      break;
    case 105:
      listar(s);
      s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
      break;
    case 56:
      if (s->bp[s->j.py-1][s->j.px].ocupado==1) combate(s, -1, 0);
      else if  (s->bp[s->j.py-1][s->j.px].parede==0) s->j.py--;
      s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
      maction(s);
      update_visibility(s);
      break;
    case 50:
      if (s->bp[s->j.py+1][s->j.px].ocupado==1) combate(s, 1, 0);
      else if (s->bp[s->j.py+1][s->j.px].parede==0) s->j.py++;
      s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
      maction(s);
      update_visibility(s);
      break;
    case 52:
      if (s->bp[s->j.py][s->j.px-1].ocupado==1) combate(s, 0, -1);
      else if (s->bp[s->j.py][s->j.px-1].parede==0) s->j.px--;
      s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
      maction(s);
      update_visibility(s);
      break;
    case 54:
      if (s->bp[s->j.py][s->j.px+1].ocupado==1) combate(s, 0, 1);
      else if (s->bp[s->j.py][s->j.px+1].parede==0) s->j.px++;
      s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
      maction(s);
      update_visibility(s);
      break;
    case 55:
      if (s->bp[s->j.py-1][s->j.px-1].ocupado==1) combate(s, -1, -1);
      else if (s->bp[s->j.py-1][s->j.px-1].parede==0) {s->j.py--; s->j.px--;}
      s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
      maction(s);
      update_visibility(s);
      break;
    case 57:
      if (s->bp[s->j.py-1][s->j.px+1].ocupado==1) combate(s, -1, 1);
      else if (s->bp[s->j.py-1][s->j.px+1].parede==0) {s->j.py--; s->j.px++;}
      s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
      maction(s);
      update_visibility(s);
      break;
    case 49:
      if (s->bp[s->j.py+1][s->j.px-1].ocupado==1) combate(s, 1, -1);
      else if (s->bp[s->j.py+1][s->j.px-1].parede==0) {s->j.py++; s->j.px--;}
      s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
      maction(s);
      update_visibility(s);
      break;
    case 51:
      if (s->bp[s->j.py+1][s->j.px+1].ocupado==1) combate(s, 1, 1);
      else if (s->bp[s->j.py+1][s->j.px+1].parede==0) {s->j.py++; s->j.px++;}
      s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
      maction(s);
      update_visibility(s);
      break;
    default:
      s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
      maction(s);
      update_visibility(s);
      break;
  }
}
