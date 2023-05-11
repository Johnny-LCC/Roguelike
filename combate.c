#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "state.h"
#include "mapa.h"
#include "action.h"


//como começar, como usar o hp atual do player decidido noutros sitios para aqui (?)


void combate(int *l, int *c, int j.hp_inicial, int hp_inimigo){  //colocar hp aqui ????, falta hp do inimigo
    
    int ataqueJogador = 5; 
    int ataqueInimigo = 5; //trocar

    int heal = 5; //poções (?)

    srand(time(NULL));
    int r = rand();  //???? aleatorio

    while(j.hp_inicial>0 && hp_inimigo>0){

        //turno do jogador
        mvprintw("-- Turno do Jogador --");
        mvprintw("HP do Jogador : ""%d", j.hp_inicial"");
        mvprintw("HP do Inimigo: ""%d", hp_inimigo"");
        mvprintw("a - Ataque");
        mvprintw("h - Curar");
        mvprintw("r - Fugir");

        string escolha = mvscanw();

        if(escolha == "a"){
            hp_inimigo -= ataqueJogador;
            mvprintw("O Jogador atacou o inimigo e deu ""%d", ataqueJogador" de dano.");
        } 
        else if(escolha == "h"){
            j.hpinicial += heal;
            mvprintw("O jogador recebeu ""%d", heal" pontos de cura.");
        }
        else break;

        //turno do inimigo
        if(hp_inimigo > 0){
            mvprintw("-- Turno do Inimigo --");
            int escolhaInimigo = r;

            if(escolhaInimigo == 0){
                j.hp_inicial -= ataqueInimigo;
            mvprintw("O inimigo atacou o Jogador e deu ""%d", ataqueInimigo" de dano.");
            } 
            else {
                hp_inimigo += heal;
                mvprintw("O inimigo recebeu ""%d", heal" pontos de cura.");
            }
        }
    }

}
