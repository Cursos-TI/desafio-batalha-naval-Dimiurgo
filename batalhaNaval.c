#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5

#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Inicializa o tabuleiro com água 
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Gera a matriz da habilidade em formato de cone
void gerarMatrizCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == 0 && j == 2)
                matriz[i][j] = 1;
            else if (i == 1 && j >= 1 && j <= 3)
                matriz[i][j] = 1;
            else if (i == 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera a matriz da habilidade em formato de cruz
void gerarMatrizCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == 2 || j == 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera a matriz da habilidade em formato de octaedro 
void gerarMatrizOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Marca no tabuleiro as posições afetadas pelas habilidades
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int origemLinha, int origemColuna, int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha = origemLinha - 2 + i;
            int coluna = origemColuna - 2 + j;

            if (linha >= 0 && linha < TAMANHO_TABULEIRO &&
                coluna >= 0 && coluna < TAMANHO_TABULEIRO &&
                matriz[i][j] == 1) {
                tabuleiro[linha][coluna] = HABILIDADE;
            }
        }
    }
}

// Posiciona navios 
void posicionarNavios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    tabuleiro[4][2] = NAVIO;
    tabuleiro[4][9] = NAVIO;
    tabuleiro[5][1] = NAVIO;
    tabuleiro[5][9] = NAVIO;
    tabuleiro[6][0] = NAVIO;
    tabuleiro[6][9] = NAVIO;
    tabuleiro[7][2] = NAVIO;
    tabuleiro[8][3] = NAVIO;
    tabuleiro[9][4] = NAVIO;
    tabuleiro[9][7] = NAVIO;
    tabuleiro[9][8] = NAVIO;
    tabuleiro[9][9] = NAVIO;
}

// Exibe o tabuleiro no console com letras de (A-J)
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (char letra = 'A'; letra < 'A' + TAMANHO_TABULEIRO; letra++) {
        printf(" %c ", letra);
    }
    printf("\n   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d|", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    gerarMatrizCone(cone);
    gerarMatrizCruz(cruz);
    gerarMatrizOctaedro(octaedro);

    aplicarHabilidade(tabuleiro, 2, 2, cone);       // Cone com origem em C2
    aplicarHabilidade(tabuleiro, 2, 7, cruz);       // Cruz com origem em H2
    aplicarHabilidade(tabuleiro, 6, 5, octaedro);   // Octaedro com origem em F6

    posicionarNavios(tabuleiro);

    exibirTabuleiro(tabuleiro);

    return 0;
}





