#include <ncurses.h>
#include "menu.h"

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
  mvprintw((l/2)-10,(c/2)-19,"Em um mundo repleto de lendas e mitos,");
  mvprintw((l/2)-9,(c/2)-14, "ergue-se a imponente Torre.");
  mvprintw((l/2)-8,(c/2)-38, "Há quem acredite que aquele que alcançar o topo receberá um poder inigualável.");
  mvprintw((l/2)-7,(c/2)-2, "...");
  getch();
  mvprintw((l/2)-6,(c/2)-39, "Ao longo dos tempos, heróis e criaturas lendárias se aventuraram na escalada");
  mvprintw((l/2)-5,(c/2)-33, "desafiadora da torre, cada um buscando a glória e o domínio supremo.");
  mvprintw((l/2)-3,(c/2)-31, "Os relatos de suas corajosas jornadas ecoam através das eras,");
  mvprintw((l/2)-2,(c/2)-32, "permeando as histórias populares e inspirando aspirantes a heróis.");
  mvprintw((l/2)-1,(c/2)-42, "Agora, é chegada a sua vez de enfrentar o desafio e trilhar o caminho rumo à Ascensão.");
  getch();
  mvprintw((l/2)+5,(c/2)-39, "Prepare-se para enfrentar perigos, desvendar segredos e desafiar lendas vivas.");
  mvprintw((l/2)+7,(c/2)-30, "O destino aguarda aqueles que ousarem subir até o seu ápice.");
  mvprintw((l/2)+8,(c/2)-14, "Bem-vindo a 'The Ascension'!");
  getch();
  mvprintw(l-1, (c/2)-10, "Prima qualquer tecla");;
}

void outro(struct state *s){
 if(s->j.hp_atual > 0 && s->andar <= 100){
   mvprintw(((s->l)/2)-5,((s->c)/2)-4,"PARABENS");
   mvprintw(((s->l)/2)-3,((s->c)/2)-32,"A subida não foi fácil, houveram inúmeros desafios no caminho...");
   mvprintw(((s->l)/2)-2,((s->c)/2)-45,"Mas, enquanto contemplas a vista que se estende diante dos seus olhos, sabes que valeu a pena.");
   mvprintw(((s->l)/2)-1,((s->c)/2)-36,"Sabes que alcançastes o auge... tanto da torre quanto da sua própria jornada.");
   mvprintw(((s->l)/2)+1,((s->c)/2)-42,"Seu nome ecoará através das eras, e sua jornada mítica será contada em canções e lendas.");
   mvprintw(((s->l)/2)+2,((s->c)/2)-18,"Mas será mesmo que este é 'O FIM'..?");
   mvprintw((s->l)-1,((s->c)/2)-37,"Prima 'ESC' para sair do jogo ou qualquer outra tecla para voltar ao menu");
 } 
 else{
   mvprintw(((s->l)/2)-1,((s->c)/2)-4, "GAME OVER");
   mvprintw(((s->l)/2)+1,((s->c)/2)-7,"Tente novamente...");
   mvprintw((s->l)-1,((s->c)/2)-37,"Prima 'ESC' para sair do jogo ou qualquer outra tecla para voltar ao menu");
 }
}

void tutorial(void){
  mvprintw(1, 1, "INFO:");
  mvprintw(2, 1, "- No topo da tela, poderá ver o seu nível, a sua barra de vida e a experiência que acumulaste;");
  mvprintw(3, 1, "- No inferiro da tela, pode ver a vida dos inimigos que estão visíveis e o andar em que se encontra;");
  mvprintw(5, 1, "MOVIMENTO:");
  mvprintw(6, 1, "- Utilize o keypad para movimentar o personagem;");
  mvprintw(7, 1, "- Os inimigos te perseguem automaticamente enqunato te verem;");
  mvprintw(8, 1, "- O seu objetivo é chegar no andar 100, para isso, procure pela saída de cada andar;");
  mvprintw(10, 1, "COMBATE:");
  mvprintw(11, 1, "- Ataque os inimigos ao andar para cima deles;");
  mvprintw(12, 1, "- Da mesma forma, os inimigos atacarão quando te alcançarem;");
  mvprintw(13, 1, "- Ao derrotar um inimigo, ganhará pontos de experiência;");
  mvprintw(14, 1, "- Se a experiência ganha ultrapassar o limite, avançará de nível e ganhará uma recompensa;");
  mvprintw(16, 1, "RECOMPENSAS:");
  mvprintw(17, 1, "- Ao passar de nível, a recompesa será um dos seguintes:");
  mvprintw(18, 1, "\t+ 1pt de ATAQUE.");
  mvprintw(19, 1, "\t+ 1pt de DEFESA.");
  mvprintw(20, 1, "\t+ 2D20 de CURA (não podendo ultrapassar o seu HP máximo).");
  mvprintw(22, 1, "COMANDOS EXTRAS:");
  mvprintw(23, 1, "- 'i': para ver o seus status e seu inventário além dos status dos inimigos visíveis;");
  mvprintw(24, 1, "- 'ESC': poderás sair do jogo.");
}

void credit(struct state *s){
  box(stdscr, 0, 0);
  mvprintw((s->l/2)-4, (s->c/2)-15,"JOGO CRIADO E DESENVOLVIDO POR:");
  mvprintw((s->l/2)-2, (s->c/2)-11,"JOAO FONSECA - A102512");
  mvprintw((s->l/2)-1, (s->c/2)-12,"ALEXIS CORREIA - A102495");
  mvprintw((s->l/2)  , (s->c/2)-12,"PATRICIA BASTOS - A102502");
  mvprintw((s->l/2)+1, (s->c/2)-9, "ANA TAXA - A102490");
  mvprintw((s->l/2)+5, (s->c/2)-16,"LABORATORIO DE ALGORITMIA I - LCC");
}
