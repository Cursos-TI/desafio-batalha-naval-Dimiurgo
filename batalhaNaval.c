#include <stdio.h>
#include <stdbool.h>

// Constantes do jogo
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para validar se as coordenadas estão dentro dos limites do tabuleiro
bool coordenadasValidas(int linha, int coluna, int orientacao) {
    // orientacao: 0 = horizontal, 1 = vertical
    if (orientacao == 0) { // Horizontal
        return (linha >= 0 && linha < TAMANHO_TABULEIRO && 
                coluna >= 0 && coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
    } else { // Vertical
        return (linha >= 0 && linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && 
                coluna >= 0 && coluna < TAMANHO_TABULEIRO);
    }
}

// Função para verificar se há sobreposição de navios
bool verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                          int linha, int coluna, int orientacao) {
    if (orientacao == 0) { // Horizontal
        for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++) {
            if (tabuleiro[linha][j] != AGUA) {
                return true; // Há sobreposição
            }
        }
    } else { // Vertical
        for (int i = linha; i < linha + TAMANHO_NAVIO; i++) {
            if (tabuleiro[i][coluna] != AGUA) {
                return true; // Há sobreposição
            }
        }
    }
    return false; // Não há sobreposição
}

// Função para posicionar um navio no tabuleiro
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     int linha, int coluna, int orientacao) {
    // Validar coordenadas
    if (!coordenadasValidas(linha, coluna, orientacao)) {
        printf("Erro: Coordenadas inválidas para o navio!\n");
        return false;
    }
    
    // Verificar sobreposição
    if (verificarSobreposicao(tabuleiro, linha, coluna, orientacao)) {
        printf("Erro: Navio se sobrepõe a outro navio!\n");
        return false;
    }
    
    // Posicionar o navio
    if (orientacao == 0) { // Horizontal
        for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++) {
            tabuleiro[linha][j] = NAVIO;
        }
        printf("Navio horizontal posicionado na linha %d, colunas %d-%d\n", 
               linha, coluna, coluna + TAMANHO_NAVIO - 1);
    } else { // Vertical
        for (int i = linha; i < linha + TAMANHO_NAVIO; i++) {
            tabuleiro[i][coluna] = NAVIO;
        }
        printf("Navio vertical posicionado na coluna %d, linhas %d-%d\n", 
               coluna, linha, linha + TAMANHO_NAVIO - 1);
    }
    
    return true;
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n");
    printf("Legenda: 0 = Água, 3 = Navio\n\n");
    
    // Cabeçalho com números das colunas
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Linha separadora
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("\n");
    
    // Linhas do tabuleiro com números das linhas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d|", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Declaração da matriz do tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializar o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    printf("=== BATALHA NAVAL ===\n");
    printf("Posicionando navios no tabuleiro %dx%d\n", TAMANHO_TABULEIRO, TAMANHO_TABULEIRO);
    printf("Cada navio ocupa %d posições\n\n", TAMANHO_NAVIO);
    
    // Coordenadas e orientações dos navios (definidas no código)
    // Navio 1: Horizontal na linha 4, colunas 2-4
    int navio1_linha = 4;
    int navio1_coluna = 2;
    int navio1_orientacao = 0; // 0 = horizontal
    
    // Navio 2: Vertical na coluna 8, linhas 7-9
    int navio2_linha = 7;
    int navio2_coluna = 8;
    int navio2_orientacao = 1; // 1 = vertical
    
    // Posicionar primeiro navio (horizontal)
    printf("Posicionando primeiro navio (horizontal):\n");
    if (!posicionarNavio(tabuleiro, navio1_linha, navio1_coluna, navio1_orientacao)) {
        printf("Falha ao posicionar o primeiro navio!\n");
        return 1;
    }
    
    // Posicionar segundo navio (vertical)
    printf("\nPosicionando segundo navio (vertical):\n");
    if (!posicionarNavio(tabuleiro, navio2_linha, navio2_coluna, navio2_orientacao)) {
        printf("Falha ao posicionar o segundo navio!\n");
        return 1;
    }
    
    // Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);
    
    // Estatísticas finais
    int total_posicoes_navios = 0;
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == NAVIO) {
                total_posicoes_navios++;
            }
        }
    }
    
    printf("=== ESTATÍSTICAS ===\n");
    printf("Navios posicionados: 2\n");
    printf("Total de posições ocupadas: %d\n", total_posicoes_navios);
    printf("Posições de água: %d\n", (TAMANHO_TABULEIRO * TAMANHO_TABULEIRO) - total_posicoes_navios);
    
    return 0;
}
