#include <stdlib.h>
#include "tesouros.h"
#include <ncurses.h>

void generate_treasure(struct state *s, struct Tesouro *t) { // gera uma alma aleatoria no mapa
  do {
    t->ty = rand() % s->l;
    t->tx = rand() % s->c;
  } while (s->bp[t->ty][t->tx].parede == 1 || s->bp[t->ty][t->tx].c == 'o' || s->bp[t->ty][t->tx].c == '@');
  t->c = 'A';
  s->bp[t->ty][t->tx].c = t->c;
  s->bp[t->ty][t->tx].cor = 7;

  attron(COLOR_PAIR(7)); // Ativar a cor roxa
  mvaddch(t->ty, t->tx, t->c); // Imprimir o tesouro com a cor roxa
  attroff(COLOR_PAIR(7));
}

void check_treasure_collision(struct state *s, struct Tesouro *t) { // verifica se o jogador encontrou a alma e, nesse caso, muda o caracter,o hp e o atk do jogador 
       WINDOW *warning2;

    if (s->j.py == t->ty && s->j.px == t->tx) {
        warning2 = newwin(5, 30, ((s->l)/2)-2, ((s->c)/2)-15);
        box(warning2, 0, 0);
        mvwprintw(warning2, 2, 3, "Você encontrou uma alma corrompida, esta o possuirá e tornará você seu hospedeiro");
        wgetch(warning2);
        endwin();
        s->j.c='$';
        s->j.hp_max=150;
        s->j.hp_atual=150;
        s->j.atk=10;
    }
}
