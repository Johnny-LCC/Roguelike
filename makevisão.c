

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

int calcular_distancia(Point i, Point f) {  // é calculada a distancia para definir o campo de visao do jogador, ou seja, se a celula for menor ou igual a distancia entao o jogador consegue ver 
    int dx = f.x - i.x; // dx mede a distancia horizontal entre a posição do jogador e a celula atual
    int dy = f.y - i.y; // dy ................. vertical ..........................................
    return sqrt(dx * dx + dy * dy); // sqrt retorna a raiz quadrada de um número, ou seja, forma euclidiana para calcular a distancia 
}

int calcular_angulo(Point i, Point f) { // calcula o angulo, ou seja, dentro do campo de visão só consegue ver um certo angulo
    return atan2(f.x - i.x, f.y - i.y) * 180 / M_PI; // multiplica por 180 para voltar a ter o resultado em graus e devide se por M_PI (representa o pi), converte o angulo de radianos em grau
}                 //dx      //dy

void calculate_fov(Point jogador, int raio_max, int fov_angulo, int** mapa_jogo, int comp_mapa , int altura_mapa)  {
    //a função calcula o campo de visao
     for (int x = 0; x < comp_mapa ; x++) {
        for (int y = 0; y < altura_mapa ; y++) {
            Point cel = { x, y };
            int distancia = calcular_distancia(jogador, cel);
            
            if (distancia<= raio_max) {
                int angulo = calcular_angulo(jogador, cel);
                int angulo_dif = abs(angulo - jogador.direction); //abs = valor absoluto da diferença
                
                if (angulo_dif <= fov_angulo / 2) {
                    mapa_jogo[x][y] = 1;  // Marca a célula como visível
                }
            }
        }
    }
}

int main() {
    int comp_mapa = 10;
    int altura_mapa = 10;
    int** mapa_jogo = malloc(comp_mapa * sizeof(int*));
    for (int i = 0; i < comp_mapa; i++) {
        mapa_jogo[i] = malloc(altura_mapa * sizeof(int));
        for (int j = 0; j < altura_mapa; j++) {
            mapa_jogo[i][j] = 0;  // Inicializa todas as células como não visíveis
        }
    }
    
    Point jogador = { 5, 5 };
    int raio_max = 3;
    int angulo_fov = 90;
    
    calculate_fov(jogador, raio_max, angulo_fov, mapa_jogo , comp_mapa, altura_mapa);
    
    // Exemplo de como acessar o mapa para verificar as células visíveis
    for (int x = 0; x < comp_mapa; x++) {
        for (int y = 0; y < altura_mapa ; y++) {
            if (mapa_jogo[x][y] == 1) {
                printf("Célula (%d, %d) é visível.\n", x, y);
            }
        }
    }
    
    // Libera a memória alocada para o mapa
    for (int i = 0; i < comp_mapa; i++) {
        free(mapa_jogo[i]);
    }
    free(mapa_jogo);
    
    return 0;
}
