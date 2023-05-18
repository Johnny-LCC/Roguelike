#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "state.h"
#include "mapa.h"
#include "action.h"

void inicializa(struct state *s, int lines, int cols){
  s->j.level=1;
  s->j.hp_max=100;
  s->j.hp_atual=100;
  s->j.mp_max=20;
  s->j.mp_atual=20;
  s->j.xp_max=10;
  s->j.xp_atual=0;
  s->j.px=0;
  s->j.py=0;
  s->j.c='@';
  
  s->andar=1;
  s->l=lines;
  s->c=cols;
  
  s->bp=(struct Casas **) calloc(s->l, sizeof(struct Casas*));
  for(int i=0; i<s->l; i++){
    s->bp[i] = (struct Casas *) calloc(s->c, sizeof(struct Casas));
  }
  
  s->inventario = (struct Inventario *)malloc(sizeof(struct Inventario));
  strcpy(s->inventario->item.nome, "Espada simples");
  s->inventario->item.equipavel = 1;
  s->inventario->item.stats = 5;
  s->inventario->next = (struct Inventario *)malloc(sizeof(struct Inventario));
  strcpy(s->inventario->next->item.nome, "Escudo simples");
  s->inventario->next->item.equipavel = 2;
  s->inventario->next->item.stats = 5;
  s->inventario->next->next = (struct Inventario *)malloc(sizeof(struct Inventario));
  strcpy(s->inventario->next->next->item.nome, "Roupa gasta");
  s->inventario->next->next->item.equipavel = 1;
  s->inventario->next->next->item.stats = 0;
  s->inventario->next->next->next=NULL;
}

void menu(int l, int c){
  int y=l/2, x=c/2;
  if(c<40) mvprintw(y-2,x-7,"THE ASCENSION");
  else if(c<70){
    mvprintw(y-4,x-2, "THE");
    mvprintw(y-3,x-20, "      __   __  __       __  .  __  ");
    mvprintw(y-2,x-20, " /\\  |__  |   |_  |\\ | |__  | |  | |\\ |");
    mvprintw(y-1,x-20, "/  \\  __| |__ |__ | \\|  __| | |__| | \\|");
  }
  else if(c<110){
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
  mvprintw(y+2,x-5,"1. JOGO");
  mvprintw(y+4,x-7,"2. TUTORIAL");
  mvprintw(y+6,x-7,"3. CREDITOS");
}

void intro(int l, int c){
  mvprintw((l/2)-10,(c/4)-10,"Em um mundo repleto de lendas e mitos,");
  mvprintw((l/2)-9,(c/4)-7,"ergue-se a imponente Torre.");
  mvprintw((l/2)-8,(c/4)-10,"Há quem acredite que aquele que alcançar o topo receberá um poder inigualável.\n\t...");
  getch();
  mvprintw((l/2)-5,(c/4)-10, "Ao longo dos tempos, heróis e criaturas lendárias se aventuraram na escalada desafiadora da torre, cada um buscando a glória e o domínio supremo.");
  mvprintw((l/2)-3,(c/4)-10, "Os relatos de suas corajosas jornadas ecoam através das eras, permeando as histórias populares e inspirando aspirantes a heróis.");
  mvprintw((l/2)-1,(c/4)-10, "Agora, é chegada a sua vez de enfrentar o desafio e trilhar o caminho rumo à Ascensão.");
  getch();
  mvprintw((l/2)+5,(c/4)-10,"Prepare-se para enfrentar perigos, desvendar segredos e desafiar as próprias lendas que buscaram a grandiosidade na torre.");
  mvprintw((l/2)+7,(c/4)-10,"O destino aguarda aqueles que ousarem subir até o seu ápice.\n\tBem-vindo a 'The Ascension'!");
  getch();
  mvprintw(l-1, (c/2)-10, "Prima qualquer tecla.");
}

int main(){
  struct state s;
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
  inicializa(&s, LINES, COLS);
  do{
    clear();
    menu(LINES, COLS);
    t=getch();
    switch(t){
      case 49:
        clear();
        intro(LINES, COLS);
        getch();
        while (s.andar<100 && s.j.hp_atual!=0){
          aux=s.andar;
          generate_map(&s);
          update_visibility(&s);
          print_map(&s);
          do{
            a=getch();
            action(&a, &s);
            print_map(&s);
            if(s.bp[s.j.py][s.j.px].saida==1) aux++;
          } while (aux==s.andar && s.j.hp_atual!=0);
          s.andar++;
        }
        clear();
        s.andar=1;
        if (s.j.hp_atual!=0) printw("\t\t\tFIM... PARABENS\n\n\tPrima 'ESC' para sair do jogo ou qualquer outra tecla para voltar ao menu.");
        else printw("\t\t\tGAME OVER...\tTente novamente...");
        t=getch();
        break;
      case 50:
        clear();
        printw("\tUtilize o keypad para movimentar/atacar e pressione 'i' para abrir o inventário.");
        getch();
        break;
      case 51:
        clear();
        printw("\tJOAO FONSECA - A102512\n\tALEXIS CORREIA - A102495\n\tPATRICIA BASTOS - A102502\n\tANA TAXA - A102490\n\tLABORATORIO DE ALGORITMIA I - LCC");
        getch();
        break;
      case 27:
        clear();
        printw("\tTEM CERTEZA QUE DESEJA SAIR DO JOGO? (prima 'ESC' novamente para sair)");
        t=getch();
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
