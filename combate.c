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

void combate(int *l, int *c, int player.hp_atual/*, int hp_inimigo*/){  //colocar hp aqui ????, falta hp do inimigo
    
    int hp_inimigo = 40;
    int ataqueJogador = 5; //colocar itens do inventário
    int ataqueInimigo = 5; //trocar

    int heal = 5; //poções (?)

    srand(time(NULL)); //time(NULL) = tempo neste momento (inicializa o rand)(srand() is used to initialise random number generators. This function gives a starting point for producing the pseudo-random integer series. The argument is passed as a seed for generating a pseudo-random number.)
    int r = rand() % 2;  //pega um numero aleatório, divide por dois para ver o resto, dando 0 ou 1

    clear();

            
mvprintw("            ,'-',");
mvprintw("          :-----:");
mvprintw("      (''' , - , ''')");
mvprintw("      \   ' .  , `  /");
mvprintw("       \  '   ^  ? /");
mvprintw("        \ `   -  ,'");
mvprintw("         `j_ _,'");
mvprintw("    ,- -`\ \  /f");
mvprintw("  ,-      \_\/_/'-");
mvprintw(" ,                 `,");
mvprintw(" ,                   ,");
mvprintw("      /\          \ ");
mvprintw("|    /             \   ',");
mvprintw(",   f  :           :`,  ,");
mvprintw("<...\  ,           : ,- '");
mvprintw("\,,,,\ ;           : j  '");
mvprintw(" \    \            :/^^^^'");
mvprintw("  \    \            ; ''':");
mvprintw("    \   -,         -`.../");
mvprintw("     '    - -,`,--`");
mvprintw("      \_._'-- '---:");

mvprintw("HP do Jogador : ""%d", player.hp_atual"");

mvprintw("        _____");
mvprintw("    .-,;='';_),-.");
mvprintw("     \_\(),()/_/");
mvprintw("       (,___,)");
mvprintw("      ,-/`~`\-,___");
mvprintw("     / /).:.('--._)");
mvprintw("    {_[ (_,_)");
mvprintw("        | Y |");
mvprintw("      /  |  \ ");
mvprintw("      """ """ ");


    while(player.hp_atual>0 && hp_inimigo>0){

        //turno do jogador
        mvprintw("-- Turno do Jogador --");
        mvprintw("HP do Inimigo: ""%d", hp_inimigo"");
        mvprintw("a - Ataque");
        mvprintw("h - Curar");

        case 97:
            hp_inimigo -= ataqueJogador;
            mvprintw("O Jogador atacou o inimigo e deu ""%d", ataqueJogador" de dano.");
        
        case 104:
            player.hpinicial += heal;
            mvprintw("O jogador recebeu ""%d", heal" pontos de cura.");
        

        //turno do inimigo
        if(hp_inimigo > 0){
            mvprintw("-- Turno do Inimigo --");
            int escolhaInimigo = r;

            if(escolhaInimigo == 0){
                player.hp_atual -= ataqueInimigo;
            mvprintw("O inimigo atacou o Jogador e deu ""%d", ataqueInimigo" de dano.");
            } 
            else {
                hp_inimigo += heal;
                mvprintw("O inimigo recebeu ""%d", heal" pontos de cura.");
            }
        }

        if(player.hp_atual == 0){
            mvprintw("GAME OVER");
            mvprintw("Clique em qualquer tecla para voltar");
            getch();
            clear(); 
            menu((&l), (&c));
        }
        if(hp_inimigo == 0){
            mvprintw("VITÓRIA");
            mvprintw("Clique em qualquer tecla para continuar");
            getch();
            //fazer continuar
        }
    }

}
