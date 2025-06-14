// GameState.cpp
#include "GameState.h"

GameState::GameState() {
    initializeBoard();
}

void GameState::initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.';
        }
    }
    for (int i = 0; i < SIZE; i++) {
        board[0][i] = 'A';
        board[4][i] = 'V';
    }
    board[2][2] = 'B';
}

void GameState::printBoard() {
    cout << "     ";
    for (int col = 0; col < SIZE; col++) {
        cout << "y" << col << "  ";
    }
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << "   +";
        for (int j = 0; j < SIZE; j++) {
            cout << "---+";
        }
        cout << endl;

        cout << "x" << i << " |";
        for (int j = 0; j < SIZE; j++) {
            char c = board[i][j];
            if (c == 'V') {
                cout << " \033[31mo\033[0m |";
            } else if (c == 'A') {
                cout << " \033[34mo\033[0m |";
            } else if (c == 'B') {
                cout << " \033[30mo\033[0m |";
            } else {
                cout << " . |";
            }
        }
        cout << endl;
    }

    cout << "   +";
    for (int j = 0; j < SIZE; j++) {
        cout << "---+";
    }
    cout << endl;
}

bool GameState::isVictory(char piece, int x, int y) {

    if (board[x][y] != piece){
        return false;
    } 

    int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};
    bool cercado = true;
    for (int i = 0; i < 8; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE) {
            if (board[newX][newY] == '.') {
                cercado = false;
                break;
            }
        }
    }
    return cercado;
}

bool GameState::isVictoryLinha(char piece) {
    for (int i = 0; i < SIZE; i++) {
        if (board[0][i] == piece) {
            cout << "Vitoria Azul" << endl;
            return true;
        }
        if (board[4][i] == piece) {
            cout << "Vitoria vermelha" << endl;
            return true;
        }
    }
    return false;
}