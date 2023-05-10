#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

struct Casas{
  int parede;
  int ocupado;
  int visivel;
  int saida;
  int cor;
  char c;
};

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

struct Mobs{
  int n;
  int py;
  int px;
  char tipo[20];
};

struct state{
  struct Casas bp[128][256];
  struct Player j;
  struct Mobs monstro[10];
  int andar;
};

void inicializa(struct state *s){
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
}

void menu(int *l, int *c){ //l, c -> LINES, COLS;!!!
  int y=(*l)/2, x=(*c)/2;
  if((*c)<40) mvprintw(y-2,x-7,"THE ASCENSION");
  else if((*c)<70){
    mvprintw(y-4,x-2, "THE");
    mvprintw(y-3,x-20, "      __   __  __       __  .  __  ");
    mvprintw(y-2,x-20, " /\\  |__  |   |_  |\\ | |__  | |  | |\\ |");
    mvprintw(y-1,x-20, "/  \\  __| |__ |__ | \\|  __| | |__| | \\|");
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

void intro(int *l, int *c){
  mvprintw((*l/2)-10,(*c/4)-10,"Em um mundo repleto de lendas e mitos,");
  mvprintw((*l/2)-9,(*c/4)-7,"ergue-se a imponente Torre.");
  mvprintw((*l/2)-8,(*c/4)-10,"Há quem acredite que aquele que alcançar o topo receberá um poder inigualável.\n\t...");
  getch();
  mvprintw((*l/2)-5,(*c/4)-10, "Ao longo dos tempos, heróis e criaturas lendárias se aventuraram na escalada desafiadora da torre, cada um buscando a glória e o domínio supremo.");
  mvprintw((*l/2)-3,(*c/4)-10, "Os relatos de suas corajosas jornadas ecoam através das eras, permeando as histórias populares e inspirando aspirantes a heróis.");
  mvprintw((*l/2)-1,(*c/4)-10, "Agora, é chegada a sua vez de enfrentar o desafio e trilhar o caminho rumo à Ascensão.");
  getch();
  mvprintw((*l/2)+5,(*c/4)-10,"Prepare-se para enfrentar perigos, desvendar segredos e desafiar as próprias lendas que buscaram a grandiosidade na torre.");
  mvprintw((*l/2)+7,(*c/4)-10,"O destino aguarda aqueles que ousarem subir até o seu ápice.\n\tBem-vindo a 'The Ascension'!");
  getch();
  mvprintw(*l-1, (*c/2)-10, "Prima qualquer tecla.");
}

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

void update_visibility(int *l, int *c, struct state *s) {
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
  else if(*t==9) generate_map(l, c, s);
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
  print_map(l, c, s);
}

int main(){
  struct state s;
  inicializa(&s);
  int t=9, a=53, l, c;
  int aux=1;
  //s.andar=1;
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
        intro(&l, &c);
        getch();
        while (s.andar<100){
          aux=s.andar;
          generate_map(&l, &c, &s);
          update_visibility(&l, &c, &s);
          print_map(&l, &c, &s);
          do{
            a=getch();
            action(&a, &l, &c, &s);
            if(s.bp[s.j.py][s.j.px].saida==1) aux++;
          } while (aux==s.andar && s.j.hp_atual!=0);
          s.andar++;
        }
        clear();
        s.andar=1;
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
