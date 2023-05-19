#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "mapa.h"

void frame(struct state *s){
  for(int i=0; i < s->c; i++){
    s->bp[0][i].parede=1; s->bp[s->l-1][i].parede=1;
    s->bp[0][i].ocupado=0; s->bp[s->l-1][i].ocupado=0;
    s->bp[0][i].c=' '; s->bp[s->l-1][i].c=' ';
    s->bp[0][i].cor=1; s->bp[s->l-1][i].cor=1;
    
    s->bp[1][i].parede=1; s->bp[s->l-2][i].parede=1;
    s->bp[1][i].ocupado=0; s->bp[s->l-2][i].ocupado=0;
    s->bp[1][i].c='#'; s->bp[s->l-2][i].c='#';
    s->bp[1][i].cor=3; s->bp[s->l-2][i].cor=3;
  }
  for(int i=1; i < s->l-1; i++){
    s->bp[i][0].parede=1; s->bp[i][s->c-1].parede=1;
    s->bp[i][0].ocupado=0; s->bp[i][s->c-1].ocupado=0;
    s->bp[i][0].c=' '; s->bp[i][s->c-1].c=' ';
    s->bp[i][0].cor=1; s->bp[i][s->c-1].cor=1;
    
    s->bp[i][1].parede=1; s->bp[i][s->c-2].parede=1;
    s->bp[i][1].ocupado=0; s->bp[i][s->c-2].ocupado=0;
    s->bp[i][1].c='#'; s->bp[i][s->c-2].c='#';
    s->bp[i][1].cor=3; s->bp[i][s->c-2].cor=3;
  }
}

void grid3x3(int x, struct state *s){
  for(int i=2; i < s->l-2; i++){
    for(int j=2; j < s->c-2; j++){
      int cont=0;
      if(s->bp[i-1][j].parede==1) cont++;
      else if(s->bp[i-1][j+1].parede==1) cont++;
      else if(s->bp[i][j+1].parede==1) cont++;
      else if(s->bp[i+1][j+1].parede==1) cont++;
      else if(s->bp[i+1][j].parede==1) cont++;
      else if(s->bp[i+1][j-1].parede==1) cont++;
      else if(s->bp[i][j-1].parede==1) cont++;
      else if(s->bp[i-1][j-1].parede==1) cont++;
      if(cont>=x){
        s->bp[i][j].parede=1;
        s->bp[i][j].ocupado=0;
        s->bp[i][j].c='#';
        s->bp[i][j].cor=3;
      }
      else if(cont<1){
        s->bp[i][j].parede=0;
        s->bp[i][j].ocupado=0;
        s->bp[i][j].c='.';
        s->bp[i][j].cor=2;
      }
    }
  }
}

void generate_map(struct state *s){
  srand(time(NULL));
  double n;
  frame(s);
  for(int i=2; i< s->l-2; i++){
    for(int j=2; j< s->c-2; j++){
        n= rand() % 100;
        if(n < 20){
          s->bp[i][j].parede=1;
          s->bp[i][j].ocupado=0;
          s->bp[i][j].c='#';
          s->bp[i][j].cor=3;
        }
        else{
          s->bp[i][j].parede=0;
          s->bp[i][j].ocupado=0;
          s->bp[i][j].c='.';
          s->bp[i][j].cor=2;
        }
    }
  }
  grid3x3(6,s);
  grid3x3(4,s);
  int sy, sx;
  do{
   sy = rand() % (s->l);
   sx = rand() % (s->c);
  }while(s->bp[sy][sx].parede==1);
  s->bp[sy][sx].c='o';
  s->bp[sy][sx].saida=1;
  s->bp[sy][sx].cor=6;  
  do{
   s->j.py = rand() % s->l;
   s->j.px = rand() % s->c;
  }while(s->bp[s->j.py][s->j.px].parede==1 || s->bp[s->j.py][s->j.px].c=='o');
  s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
  for(int i=0; i<(s->andar % 10); i++){
    int index = rand()%10;
    s->mobs[i].inimigo=s->monstro[index];
    do{
     s->mobs[i].py = rand() % s->l;
     s->mobs[i].px = rand() % s->c;
    }while(s->bp[s->mobs[i].py][s->mobs[i].px].parede==1 || s->bp[s->mobs[i].py][s->mobs[i].px].saida==1 || s->bp[s->mobs[i].py][s->mobs[i].px].c=='@');
    s->bp[s->mobs[i].py][s->mobs[i].px].c='X'; s->bp[s->mobs[i].py][s->mobs[i].px].cor=5; s->bp[s->mobs[i].py][s->mobs[i].px].ocupado=1; 
  }
}

void print_map(struct state *s){
  for(int i=0; i < s->l; i++){
    for(int j=0; j < s->c; j++){
      if(s->bp[i][j].visivel==1 || s->bp[i][j].parede==1){
        int cor = s->bp[i][j].cor;
        attron(COLOR_PAIR(cor));
        mvaddch(i, j, s->bp[i][j].c);
        attroff(COLOR_PAIR(cor));
      }
      else(mvaddch(i,j,' ')); 
    }
  }
  mvprintw(0,1, "level %d\t\thp:%d/%d\t\txp:%d/%d", s->j.level, s->j.hp_atual, s->j.hp_max, s->j.xp_atual, s->j.xp_max);
  mvprintw(s->l-1, s->c-10, "Floor %d", s->andar);
  int aux=1;
  for(int i=0; i<(s->andar)%10; i++){
    if(s->bp[s->mobs[i].py][s->mobs[i].px].visivel==1 && s->mobs[i].inimigo.hp_atual > 0){
      mvprintw(s->l-1, aux, "%s: %d/%d", s->mobs[i].inimigo.tipo, s->mobs[i].inimigo.hp_atual, s->mobs[i].inimigo.hp_max);
      aux+=20;
    }
  }
}
