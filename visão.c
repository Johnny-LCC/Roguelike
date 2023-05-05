#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rogue.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 10

int playerX, playerY;
char map[MAP_HEIGHT][MAP_WIDTH];

int visible[MAP_HEIGHT][MAP_WIDTH];
void printMap() {
    system("clear");
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == playerX && y == playerY) {
                printf("@");
            } else if (visible[y][x]) {
                printf("%c", map[y][x]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
void updateVisible() {
    // Limpar matriz visible
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            visible[y][x] = 0;
        }
    }

    // Definir células visíveis ao redor do jogador
    for (int y = playerY - 1; y <= playerY + 1; y++) {
        for (int x = playerX - 1; x <= playerX + 1; x++) {
            if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
                visible[y][x] = 1;
            }
        }
    }

    // Definir células não visíveis bloqueadas por paredes
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == '#') {
                visible[y][x] = 0;
            }
        }
    }
}
int main() {
    initMap();
    playerX = MAP_WIDTH / 2;
    playerY = MAP_HEIGHT / 2;

    while (1) {
        printMap();
        char input = getch();
        movePlayer(input);
        updateVisible();
    }

    return 0;
}

