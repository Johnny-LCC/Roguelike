#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

//#include "state.h"
#include "mapa.h"

void frame(int *l, int *c, struct state *s){
  for(int i=0; i<*c; i++){
    s->bp[0][i].parede=1; s->bp[*l-1][i].parede=1;
    s->bp[0][i].ocupado=0; s->bp[*l-1][i].ocupado=0;
    s->bp[0][i].c=' '; s->bp[*l-1][i].c=' ';
    s->bp[0][i].cor=1; s->bp[*l-1][i].cor=1;
    
    s->bp[1][i].parede=1; s->bp[*l-2][i].parede=1;
    s->bp[1][i].ocupado=0; s->bp[*l-2][i].ocupado=0;
    s->bp[1][i].c='#'; s->bp[*l-2][i].c='#';
    s->bp[1][i].cor=3; s->bp[*l-2][i].cor=3;
  }
  for(int i=1; i<*l-1; i++){
    s->bp[i][0].parede=1; s->bp[i][*c-1].parede=1;
    s->bp[i][0].ocupado=0; s->bp[i][*c-1].ocupado=0;
    s->bp[i][0].c=' '; s->bp[i][*c-1].c=' ';
    s->bp[i][0].cor=1; s->bp[i][*c-1].cor=1;
    
    s->bp[i][1].parede=1; s->bp[i][*c-2].parede=1;
    s->bp[i][1].ocupado=0; s->bp[i][*c-2].ocupado=0;
    s->bp[i][1].c='#'; s->bp[i][*c-2].c='#';
    s->bp[i][1].cor=3; s->bp[i][*c-2].cor=3;
  }
}

void grid3x3(int *l, int *c, int x, struct state *s){
  for(int i=2; i<*l-2; i++){
    for(int j=2; j<*c-2; j++){
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

void generate_map(int *l, int *c, struct state *s){
  srand(time(NULL));
  double n;
  frame(l,c,s);
  for(int i=2; i<*l-2; i++){
    for(int j=2; j<*c-2; j++){
        n= rand() % 10;
        if(n < 2){
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
  grid3x3(l,c,6,s);
  grid3x3(l,c,4,s);
  int sy, sx;
  do{
   sy = rand() % (*l);
   sx = rand() % (*c);
  }while(s->bp[sy][sx].parede==1);
  s->bp[sy][sx].c='o';
  s->bp[sy][sx].saida=1;
  s->bp[sy][sx].cor=6;  
  do{
   s->j.py = rand() % *l;
   s->j.px = rand() % *c;
  }while(s->bp[s->j.py][s->j.px].parede==1 || s->bp[s->j.py][s->j.px].c=='o');
  s->bp[s->j.py][s->j.px].c=s->j.c; s->bp[s->j.py][s->j.px].cor=4;
  for(int i=0; i<(s->andar % 10); i++){
    do{
     s->monstro[i].py = rand() % *l;
     s->monstro[i].px = rand() % *c;
    }while(s->bp[s->monstro[i].py][s->monstro[i].px].parede==1 || s->bp[s->monstro[i].py][s->monstro[i].px].saida==1 || s->bp[s->monstro[i].py][s->monstro[i].px].c=='@');
    s->bp[s->monstro[i].py][s->monstro[i].px].c='X'; s->bp[s->monstro[i].py][s->monstro[i].px].cor=5; s->bp[s->monstro[i].py][s->monstro[i].px].ocupado=1; 
  }
}

void print_map(int *l, int *c, struct state *s){
  for(int i=0; i<*l; i++){
    for(int j=0; j<*c; j++){
      if(s->bp[i][j].visivel==1 || s->bp[i][j].parede==1){
        int cor = s->bp[i][j].cor;
        attron(COLOR_PAIR(cor));
        mvaddch(i, j, s->bp[i][j].c);
        attroff(COLOR_PAIR(cor));
      }
      else(mvaddch(i,j,' ')); 
    }
  }
  mvprintw(0,1, "level %d\t\thp:%d/%d\t\tmp:%d/%d", s->j.level, s->j.hp_atual, s->j.hp_max, s->j.mp_atual, s->j.mp_max);
  mvprintw(*l-1, *c-10, "Floor %d", s->andar);
}
