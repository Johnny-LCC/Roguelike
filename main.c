#define _XOPEN_SOURCE
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>

struct Casas{
  int parede;
  int ocupado;
  char c;
};
struct Casas bp[128][256];

struct Player{
  int level;
  int hp_max;
  int hp_atual;
  int mp_max;
  int mp_atual;
  int xp_max;
  int xp_atual;
  int px;
  int py;
  char c;
};


struct Mobs{
  int inimigo;
  struct Mobs *prox;
};

struct State{
  struct Casas bp[128][256];
  struct Player j;
  struct Mobs inimigos;
  int floor;
};
State jogo;
jogo.j={1, 100, 100, 20, 20, 10, 0, 10, 10, '@'};

int frame(int l, int c){
  for(int i=0; i<c; i++){
    jogo.bp[0][i].parede=1; jogo.bp[l-1][i].parede=1;
    jogo.bp[0][i].ocupado=0; jogo.bp[l-1][i].ocupado=0;
    jogo.bp[0][i].c=' '; jogo.bp[l-1][i].c=' ';
    jogo.bp[1][i].parede=1; jogo.bp[l-2][i].parede=1;
    jogo.bp[1][i].ocupado=0; jogo.bp[l-2][i].ocupado=0;
    jogo.bp[1][i].c='#'; bp[l-2][i].c='#';
  }
  for(int i=1; i<l-1; i++){
    bp[i][0].parede=1; bp[i][c-1].parede=1;
    bp[i][0].ocupado=0; bp[i][c-1].ocupado=0;
    bp[i][0].c=' '; bp[i][c-1].c=' ';
    bp[i][1].parede=1; bp[i][c-2].parede=1;
    bp[i][1].ocupado=0; bp[i][c-2].ocupado=0;
    bp[i][1].c='#'; bp[i][c-2].c='#';
  }
  return 0;
}

int grid3x3(int l, int c, int x){
  for(int i=2; i<l-2; i++){
    for(int j=2; j<c-2; j++){
      int c=0;
      if(bp[i-1][j].parede==1) c++;
      else if(bp[i-1][j+1].parede==1) c++;
      else if(bp[i][j+1].parede==1) c++;
      else if(bp[i+1][j+1].parede==1) c++;
      else if(bp[i+1][j].parede==1) c++;
      else if(bp[i+1][j-1].parede==1) c++;
      else if(bp[i][j-1].parede==1) c++;
      else if(bp[i-1][j-1].parede==1) c++;
      if(c>=x){
        bp[i][j].parede=1;
        bp[i][j].ocupado=0;
        bp[i][j].c='#';
      }
      else if(c<1){
        bp[i][j].parede=0;
        bp[i][j].ocupado=0;
        bp[i][j].c='.';
      }
    }
  }
  return 0;
}

int mapa(int l, int c){
  double n, aux=0;
  frame(l,c);
  for(int i=2; i<l-2; i++){
    for(int j=2; j<c-2; j++){
        n= drand48();
        if(n<0.3){
          bp[i][j].parede=1;
          bp[i][j].ocupado=0;
          bp[i][j].c='#';
        }
        else{
          bp[i][j].parede=0;
          bp[i][j].ocupado=0;
          if (n>=0.9 && aux==0) { bp[i][j].c='1'; aux++;} else bp[i][j].c='.';
        }
    }
  }
  grid3x3(l,c,5);
  grid3x3(l,c,2);
  for(int i=0; i<l; i++){
    for(int j=0; j<c; j++){
      mvaddch(i,j,bp[i][j].c);
    }
  }
  return 0;
}

int movement(int t){
  mvaddch(j.py, j.px, '.');
  if (t==56 && bp[j.py-1][j.px].parede==0) j.py--;
  else if (t==50 && bp[j.py+1][j.px].parede==0) j.py++;
  else if (t==52 && bp[j.py][j.px-1].parede==0) j.px--;
  else if (t==54 && bp[j.py][j.px+1].parede==0) j.px++;
  else if (t==55 && bp[j.py-1][j.px-1].parede==0) {j.py--; j.px--;}
  else if (t==57 && bp[j.py-1][j.px+1].parede==0) {j.py--; j.px++;}
  else if (t==49 && bp[j.py+1][j.px-1].parede==0) {j.py++; j.px--;}
  else if (t==51 && bp[j.py+1][j.px+1].parede==0) {j.py++; j.px++;}
  mvaddch(j.py, j.px, j.c);
  return 0;
}

int main(){
  int t=9, l, c;
  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  bkgdset(COLOR_BLACK);
  //attrset(COLOR_PAIR(1) | A_BOLD);
  keypad(stdscr, 1);
  noecho();
  curs_set(0);
  getmaxyx(stdscr, l,c);
  do{
    if(t==9){
      mapa(l,c);
      mvprintw(0,1, "level %d     hp:%d/%d     mp:%d/%d", j.level, j.hp_atual, j.hp_max, j.mp_atual, j.mp_max);
      mvaddch(j.py, j.px, j.c);
    }
    else {
      mvprintw(0,1, "level %d     hp:%d/%d     mp:%d/%d", j.level, j.hp_atual, j.hp_max, j.mp_atual, j.mp_max);
      movement(t);
    }
  } while ((t=getch()) != 27); // 27=='esc'(ASCII)
  refresh();
  getch();
  endwin();
  return 0;
}
