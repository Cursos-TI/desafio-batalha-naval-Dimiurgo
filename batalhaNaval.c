#include <stdio.h>
#include <stdbool.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

bool coordenadasValidas(int linha, int coluna, int orientacao) {
    if (orientacao == 0) { // horizontal
        return linha >= 0 && linha < TAMANHO_TABULEIRO &&
               coluna >= 0 && coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO;
    } else { // vertical
        return linha >= 0 && linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
               coluna >= 0 && coluna < TAMANHO_TABULEIRO;
    }
}

bool verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                           int linha, int coluna, int orientacao) {
    if (orientacao == 0) { // horizontal
        for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++) {
            if (tabuleiro[linha][j] != AGUA) return true;
        }
    } else { // vertical
        for (int i = linha; i < linha + TAMANHO_NAVIO; i++) {
            if (tabuleiro[i][coluna] != AGUA) return true;
        }
    }
    return false;
}

bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linha, int coluna, int orientacao) {
    if (!coordenadasValidas(linha, coluna, orientacao)) {
        printf("Erro: Coordenadas inválidas!\n");
        return false;
    }
    if (verificarSobreposicao(tabuleiro, linha, coluna, orientacao)) {
        printf("Erro: Sobreposição detectada!\n");
        return false;
    }

    if (orientacao == 0) {
        for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++) {
            tabuleiro[linha][j] = NAVIO;
        }
        printf("Navio horizontal posicionado: [%d][%c] até [%d][%c]\n",
               linha, 'A' + coluna, linha, 'A' + coluna + 2);
    } else {
        for (int i = linha; i < linha + TAMANHO_NAVIO; i++) {
            tabuleiro[i][coluna] = NAVIO;
        }
        printf("Navio vertical posicionado: [%d][%c] até [%d][%c]\n",
               linha, 'A' + coluna, linha + 2, 'A' + coluna);
    }
    return true;
}

bool verificarSobreposicaoDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                                   int linha, int coluna, int direcao) {
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        int i = linha + k;
        int j = (direcao == 1) ? coluna + k : coluna - k;
        if (tabuleiro[i][j] != AGUA) return true;
    }
    return false;
}

bool coordenadasValidasDiagonal(int linha, int coluna, int direcao) {
    if (direcao == 1) {
        return linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
               coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO;
    } else {
        return linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
               coluna - (TAMANHO_NAVIO - 1) >= 0;
    }
}

bool posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                             int linha, int coluna, int direcao) {
    if (!coordenadasValidasDiagonal(linha, coluna, direcao)) {
        printf("Erro: Coordenadas inválidas para diagonal!\n");
        return false;
    }
    if (verificarSobreposicaoDiagonal(tabuleiro, linha, coluna, direcao)) {
        printf("Erro: Sobreposição em diagonal!\n");
        return false;
    }

    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        int i = linha + k;
        int j = (direcao == 1) ? coluna + k : coluna - k;
        tabuleiro[i][j] = NAVIO;
    }

    if (direcao == 1) {
        printf("Navio diagonal ↘: [%d][%c] até [%d][%c]\n",
               linha, 'A' + coluna, linha + 2, 'A' + coluna + 2);
    } else {
        printf("Navio diagonal ↙: [%d][%c] até [%d][%c]\n",
               linha, 'A' + coluna, linha + 2, 'A' + coluna - 2);
    }
    return true;
}

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n");
    printf("Legenda: 0 = Água, 3 = Navio\n\n");

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
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    printf("=== POSICIONANDO 4 NAVIOS ===\n");

    // Navio 1: horizontal
    posicionarNavio(tabuleiro, 0, 0, 0);  // A0-A2

    // Navio 2: vertical
    posicionarNavio(tabuleiro, 6, 9, 1);  // J6-J8

    // Navio 3: diagonal 1
    posicionarNavioDiagonal(tabuleiro, 1, 1, 1);  // B1-D3

    // Navio 4: diagonal 2
    posicionarNavioDiagonal(tabuleiro, 2, 8, -1); // I2-G4

    exibirTabuleiro(tabuleiro);

    return 0;
}


