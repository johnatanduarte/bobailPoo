// g++ -Wall -Wextra -g3 main.cpp GameState.cpp Movement.cpp -o output/main.exe
// .\output\main.exe

// main.cpp

#include "GameState.h" // Tem que instanciar, ou seja, precisa de um bjeto para acessar
#include "Movement.h" // Tem métodos de classe, não precisa instanciar pois são státicos

int main() {
    GameState game; //A classe GameState esta instanciando o objeto game
    game.printBoard();

    char sequencia[] = {'V', 'B', 'A', 'B'};  
    int posicaoAtual = 0;
    bool jogoAtivo = true;
    int x, y, newX, newY;

    while(jogoAtivo) {
        char pecaAtual = sequencia[posicaoAtual];
        
        string cor = (pecaAtual == 'V') ? " (vermelha)" : (pecaAtual == 'A') ? " (azul)" : " (preto)";
        cout << "\nVez da peca " << pecaAtual << cor << endl;
        cout << "Digite a posicao atual (x y): ";
        cin >> x >> y;
        cout << "Digite a nova posicao (x y): ";
        cin >> newX >> newY;

        // Verifica vitória (se esta cercado) após movimento do B
        if(game.isVictory('B', x, y)) { // x e y é a posição do bobail
            cout << "Fim de jogo!" << endl;
            jogoAtivo = false;
            break;
        }

        if(Movement::movePiece(game, pecaAtual, x, y, newX, newY)) {
            game.printBoard();

            if(game.isVictoryLinha('B')){ // Verifica vitória nas linhas superiores e inferiores
                jogoAtivo = false;
                break;
            } 
            
            // Avança para próxima peça
            posicaoAtual++;
            if(posicaoAtual >= 4) {
                posicaoAtual = 0;
            }
            
        } else {
            cout << "Movimento invalido! Tente novamente." << endl;
        } 
    }
    
    return 0;
}