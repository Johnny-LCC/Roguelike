#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "state.h"
#include "init.h"
#include "menu.h"
#include "mapa.h"
#include "action.h"

int main(){
  struct state s;
  WINDOW *win;
  int t=9, a=53;
  int aux=1;
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
  do{
    init_jogo(&s, LINES, COLS);
    clear();
    menu(LINES, COLS);
    t=getch();
    switch(t){
      case 49:
        clear();
        intro(LINES, COLS);
        getch();
        while (s.andar<100 && s.j.hp_atual>0){
          aux=s.andar;
          generate_map(&s);
          update_visibility(&s);
          print_map(&s);
          do{
            a=getch();
            action(&a, &s);
            print_map(&s);
            if(s.bp[s.j.py][s.j.px].saida==1) aux++;
          } while (aux==s.andar && s.j.hp_atual>0);
          s.andar++;
        }
        clear();
        outro(&s);
        t=getch();
        s.andar=1;
        break;
      case 50:
        clear();
        tutorial();
        getch();
        break;
      case 51:
        clear();
        credit(&s);
        getch();
        break;
      case 27:
        win = newwin(6, 40, (s.l/2)-3, (s.c/2)-20 );
        box(win, 0, 0);
        mvwprintw(win, 2, 2, "TEM CERTEZA QUE DESEJA SAIR DO JOGO?");
        mvwprintw(win, 3, 3, "(prima 'ESC' novamente para sair)");
        t=wgetch(win);
        //endwin();
        break;
      default:
        mvprintw(s.l-1, (s.c/2)-15, "Prima '1', '2', '3' ou 'ESC'.");
        getch();
        break;
    }
  } while (t!=27);
  refresh();
  endwin();
  return 0;
}
