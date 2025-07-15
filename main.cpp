// g++ -Wall -Wextra -g3 main.cpp GameState.cpp Movement.cpp EstadoJogo.cpp -o output/main.exe
// .\output\main.exe

#include "GameState.h" 
#include "Movement.h" 
#include "EstadoJogo.h" 
#include <string> // 

int main() {
    GameState game; 
    
    ArvoreEstados arvore(game); 
    
    game.printBoard();

    char sequencia[] = {'V', 'B', 'A', 'B'};  
    int posicaoAtual = 0;
    bool jogoAtivo = true;
    int x, y, newX, newY;
    char comando;

    while(jogoAtivo) {
        char pecaAtual = sequencia[posicaoAtual];
        
        string cor = (pecaAtual == 'V') ? " (vermelha)" : (pecaAtual == 'A') ? " (azul)" : " (preto)";
        cout << "\nVez da peca " << pecaAtual << cor << endl;
        cout << "Digite comando (v: voltar) ou posicao atual (x y): ";
        
        string entrada;
        cin >> entrada;
    
        if (entrada.length() == 1 && entrada[0] >= 'a' && entrada[0] <= 'z') {
            comando = entrada[0];
            
            if (comando == 'v') {
                
                if (arvore.voltarJogada()) {
                    
                    game = arvore.getEstadoAtual();
                    game.printBoard();
                    
                    posicaoAtual--;
                    if (posicaoAtual < 0) {
                        posicaoAtual = 3;
                    }
                }
                continue;
            }
            else {
                cout << "Comando invalido! Use v ou digite coordenadas." << endl;
                continue; 
            }
        }
        
        x = stoi(entrada); 
        cin >> y;
        cout << "Digite a nova posicao (x y): ";
        cin >> newX >> newY;

        // Verifica vitória (se esta cercado) após movimento do B
        if(game.isVictory('B', x, y)) { // x e y é a posição do bobail
            cout << "Fim de jogo!" << endl;
            jogoAtivo = false;
            break;
        }

        if(Movement::movePiece(game, pecaAtual, x, y, newX, newY)) {
            
            arvore.adicionarEstado(game, pecaAtual, x, y, newX, newY);
            
            game.printBoard();

            if(game.isVictoryLinha('B')){ 
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
    
    // MOSTRA ÁRVORE FINAL DO JOGO
    cout << "\n=== FIM DO JOGO ===" << endl;
    cout << "Mostrando arvore completa de jogadas realizadas:" << endl;
    arvore.mostrarArvore();
    
    return 0; 
            
}