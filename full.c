#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>

struct Casas{
  int parede;
  int ocupado;
  int visivel;
  int saida;
  int cor;
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
  int py;
  int px;
  char c;
};
struct Player j={1, 100, 100, 20, 20, 10, 0, 0, 0, '@'};

int andar;

void menu(int *l, int *c){
  int y=(*l)/2, x=(*c)/2;
  if((*c)<70){
    mvprintw(y-2,x-7,"THE ASCENSION");
  }
  else if((*c)<110){
    mvprintw(y-8,x-2, "THE");
    mvprintw(y-7,x-35, ".o888o. .o88888 .o88888 .o88888 88.     8 .o88888 8 .o888o. 88.     8");
    mvprintw(y-6,x-35, "8     8 8       8       8       8*8.    8 8       8 8     8 8*8.    8");
    mvprintw(y-5,x-35, "8     8 8       8       8       8 *8.   8 8       8 8     8 8 *8.   8");
    mvprintw(y-4,x-35, "8888888 *88888. 8       88888   8  *8.  8 *88888. 8 8     8 8  *8.  8");
    mvprintw(y-3,x-35, "8     8       8 8       8       8   *8. 8       8 8 8     8 8   *8. 8");
    mvprintw(y-2,x-35, "8     8       8 8       8       8    *8.8       8 8 8     8 8    *8.8");
    mvprintw(y-1,x-35, "8     8 888880* *088888 *088888 8     *88 888880* 8 *08880* 8     *88");
  }
  else{
    mvprintw(y-11,x-2,"THE");
    mvprintw(y-10,x-53,".o8888888o.  .o8888888o .o888888888 .o888888888 888.       888  .o8888888o 888 .o88888888o. 888.       888");
    mvprintw(y-9,x-53, "88888888888 88888888888 88888888888 88888888888 8888.      888 88888888888 888 888888888888 8888.      888");
    mvprintw(y-8,x-53, "888     888 888         888         888         888*8.     888 888         888 888      888 888*8.     888");
    mvprintw(y-7,x-53, "888     888 888         888         888         888 *8.    888 888         888 888      888 888 *8.    888");
    mvprintw(y-6,x-53, "88888888888 8888888888. 888         88888888    888  *8.   888 8888888888. 888 888      888 888  *8.   888");
    mvprintw(y-5,x-53, "88888888888 *8888888888 888         88888888    888   *8.  888 *8888888888 888 888      888 888   *8.  888");
    mvprintw(y-4,x-53, "888     888         888 888         888         888    *8. 888         888 888 888      888 888    *8. 888");
    mvprintw(y-3,x-53, "888     888         888 888         888         888     *8.888         888 888 888      888 888     *8.888");
    mvprintw(y-2,x-53, "888     888 88888888888 88888888888 88888888888 888      *8888 88888888888 888 888888888888 888      *8888");
    mvprintw(y-1,x-53, "888     888 088888880*  *0888888888 *0888888888 888       *888 088888880*  888 *0888888880* 888       *888");
  }
  mvprintw(y+2,x-5,"1 - JOGO");
  mvprintw(y+4,x-7,"2 - TUTORIAL");
  mvprintw(y+6,x-7,"3 - CREDITOS");
}

void frame(int *l, int *c){
  for(int i=0; i<*c; i++){
    bp[0][i].parede=1; bp[*l-1][i].parede=1;
    bp[0][i].ocupado=0; bp[*l-1][i].ocupado=0;
    bp[0][i].c=' '; bp[*l-1][i].c=' ';
    bp[0][i].cor=1; bp[*l-1][i].cor=1;
    
    bp[1][i].parede=1; bp[*l-2][i].parede=1;
    bp[1][i].ocupado=0; bp[*l-2][i].ocupado=0;
    bp[1][i].c='#'; bp[*l-2][i].c='#';
    bp[1][i].cor=3; bp[*l-2][i].cor=3;
  }
  for(int i=1; i<*l-1; i++){
    bp[i][0].parede=1; bp[i][*c-1].parede=1;
    bp[i][0].ocupado=0; bp[i][*c-1].ocupado=0;
    bp[i][0].c=' '; bp[i][*c-1].c=' ';
    bp[i][0].cor=1; bp[i][*c-1].cor=1;
    
    bp[i][1].parede=1; bp[i][*c-2].parede=1;
    bp[i][1].ocupado=0; bp[i][*c-2].ocupado=0;
    bp[i][1].c='#'; bp[i][*c-2].c='#';
    bp[i][1].cor=3; bp[i][*c-2].cor=3;
  }
}

void grid3x3(int *l, int *c, int x){
  for(int i=2; i<*l-2; i++){
    for(int j=2; j<*c-2; j++){
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
        bp[i][j].cor=3;
      }
      else if(c<1){
        bp[i][j].parede=0;
        bp[i][j].ocupado=0;
        bp[i][j].c=' ';
        bp[i][j].cor=1;
      }
    }
  }
}

void saida(int *l, int *c){
  srand(time(NULL));
  int sy, sx;
  do{
   sy = rand() % (*l)+1;
   sx = rand() % (*c)+1;
  }while(bp[sy][sx].parede==1);
  bp[sy][sx].c='o';
  bp[sy][sx].saida=1;
  bp[sy][sx].cor=6;
}

void mapa(int *l, int *c){
  srand(time(NULL));
  double n;
  frame(l,c);
  for(int i=2; i<*l-2; i++){
    for(int j=2; j<*c-2; j++){
        n= drand48();
        if(n<0.27500){
          bp[i][j].parede=1;
          bp[i][j].ocupado=0;
          bp[i][j].c='#';
          bp[i][j].cor=3;
        }
        else{
          bp[i][j].parede=0;
          bp[i][j].ocupado=0;
          bp[i][j].c=' ';
          bp[i][j].cor=1;
        }
    }
  }
  grid3x3(l,c,5);
  grid3x3(l,c,2);
  saida(l,c);  
  do{
   j.py = rand() % *l+1;
   j.px = rand() % *c+1;
  }while(bp[j.py][j.px].parede==1 || bp[j.py][j.px].c=='o');
}

int action(int *t){
  int r=0;
  mvaddch(j.py, j.px, ' ');
  if(*t==27) andar+=100;
  else if (*t==56 && bp[j.py-1][j.px].parede==0) j.py--;
  else if (*t==50 && bp[j.py+1][j.px].parede==0) j.py++;
  else if (*t==52 && bp[j.py][j.px-1].parede==0) j.px--;
  else if (*t==54 && bp[j.py][j.px+1].parede==0) j.px++;
  else if (*t==55 && bp[j.py-1][j.px-1].parede==0) {j.py--; j.px--;}
  else if (*t==57 && bp[j.py-1][j.px+1].parede==0) {j.py--; j.px++;}
  else if (*t==49 && bp[j.py+1][j.px-1].parede==0) {j.py++; j.px--;}
  else if (*t==51 && bp[j.py+1][j.px+1].parede==0) {j.py++; j.px++;}
  mvaddch(j.py, j.px, j.c);
  if(bp[j.py][j.px].saida==1) r=1;
  return r;
}

int main(){
  int t=9, a=53, l, c, aux=1;
  andar=1;
  initscr();
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  init_pair(5, COLOR_RED, COLOR_BLACK);
  init_pair(6, COLOR_YELLOW, COLOR_BLACK);
  bkgdset(COLOR_BLACK);
  keypad(stdscr, 1);
  noecho();
  curs_set(0);
  getmaxyx(stdscr, l,c);
  do{
    clear();
    menu((&l), (&c));
    t=getch();
    switch(t){
      case 49:
        clear();
        while (andar<100){
          aux=andar;
          mapa(&l, &c);
          for(int i=0; i<l; i++){
            for(int j=0; j<c; j++){
              attron(COLOR_PAIR(bp[i][j].cor));
              mvaddch(i,j,bp[i][j].c);
              attroff(COLOR_PAIR(bp[i][j].cor));
            }
          }
          mvprintw(0,1, "level %d     hp:%d/%d     mp:%d/%d", j.level, j.hp_atual, j.hp_max, j.mp_atual, j.mp_max);
          mvprintw(l-1, c-10, "Floor %d", andar);
          mvaddch(j.py, j.px, j.c);
          do{
            a=getch();
            aux+=action(&a);
          } while (aux==andar);
          andar++;
        }
        clear();
        andar=1;
        printw("\t\t\tFIM... PARABENS\n\n\tPrima 'ESC' para sair do jogo ou qualquer outra tecla para voltar ao menu.");
        t=getch();
        break;
      case 50:
        clear();
        printw("\tUtilize o keypad para movimentar/atacar e pressione 'i' para abrir o inventário.");
        getch();
        break;
      case 51:
        clear();
        printw("\tJOAO\n\tALEXIS\n\tPATRICIA\n\tANA\n\tLCC-LA1");
        getch();
        break;
      case 27:
        clear();
        printw("\tTEM CERTEZA QUE DESEJA SAIR DO JOGO? (prima 'esc' novamente para sair)");
        t=getch();
        break;
      default:
        mvprintw(l-1, (c/2)-15, "Prima '1', '2', '3' ou 'ESC'.");
        getch();
        break;
    }
  } while (t!=27);
  refresh();
  endwin();
  return 0;
}
