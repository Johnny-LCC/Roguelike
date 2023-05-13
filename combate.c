#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "state.h"
#include "mapa.h"
#include "action.h"

//colocar coordenadas nos mvprintw

//como começar, como usar o hp atual do player decidido noutros sitios para aqui (?)

void combate(int *l, int *c, int j.hp_atual/*, int hp_inimigo*/){  //colocar hp aqui ????, falta hp do inimigo
    
    int hp_inimigo = 40;
    int ataqueJogador = 5; 
    int ataqueInimigo = 5; //trocar

    int heal = 5; //poções (?)

    srand(time(NULL));
    int r = rand();  //???? aleatorio

    while(j.hp_atual>0 && hp_inimigo>0){

        //turno do jogador
        mvprintw("-- Turno do Jogador --");
        mvprintw("HP do Jogador : ""%d", j.hp_atual"");
        mvprintw("HP do Inimigo: ""%d", hp_inimigo"");
        mvprintw("a - Ataque");
        mvprintw("h - Curar");
        mvprintw("r - Fugir");

        char escolha[] = mvscanw();

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
                j.hp_atual -= ataqueInimigo;
            mvprintw("O inimigo atacou o Jogador e deu ""%d", ataqueInimigo" de dano.");
            } 
            else {
                hp_inimigo += heal;
                mvprintw("O inimigo recebeu ""%d", heal" pontos de cura.");
            }
        }

        if(j.hp_atual == 0){
            mvprintw("GAME OVER");
            mvprintw("espaço para voltar");
            //fazer voltar ao menu inicial 
        }
        if(hp_inimigo == 0){
            mvprintw("YOU WIN");
            //fazer continuar
        }
    }

}
