// Movement.cpp
#include "Movement.h"
#include <cmath>

bool Movement::isMaximumMove(GameState &state, char piece, int x, int y, int newX, int newY) {
    bool isDiagonal = abs(x - newX) == abs(y - newY);
    bool isOrthogonal = x == newX || y == newY;

    if (!isDiagonal && !isOrthogonal) {
        cout << "Movimento deve ser ortogonal ou diagonal!" << endl;
        return false;
    }

    if (piece == 'B') {
        if (abs(x - newX) <= 1 && abs(y - newY) <= 1) {
            if (state.board[newX][newY] != '.') {
                cout << "Posicao de destino ocupada!" << endl;
                return false;
            }
            return true;
        } else {
            cout << "A peca B so pode mover uma posicao!" << endl;
            return false;
        }
    }

    int stepX = (newX > x) ? 1 : ((newX < x) ? -1 : 0);
    int stepY = (newY > y) ? 1 : ((newY < y) ? -1 : 0);

    while (true) {
        int nextX = x + stepX;
        int nextY = y + stepY;

        if (nextX < 0 || nextX >= SIZE || nextY < 0 || nextY >= SIZE) {
            break;
        }
        if (state.board[nextX][nextY] != '.') {
            break;
        }
        x = nextX;
        y = nextY;
    }

    if (x == newX && y == newY) {
        return true;
    }

    cout << "As pecas V e A devem mover o maximo possivel!" << endl;
    return false;
}

bool Movement::movePiece(GameState &state, char piece, int x, int y, int newX, int newY) {
    if (state.board[x][y] != piece) {
        cout << "peca errada, mova a peca: " << piece << endl;
        return false;
    }
    if (newX < 0 || newX >= SIZE || newY < 0 || newY >= SIZE) {
        cout << "Movimento fora dos limites!" << endl;
        return false;
    }
    if (state.board[x][y] == '.') {
        cout << "Nao ha peca na posicao inicial!" << endl;
        return false;
    }
    if (!isMaximumMove(state, piece, x, y, newX, newY)) {
        return false;
    }

    state.board[newX][newY] = state.board[x][y];
    state.board[x][y] = '.';
    return true;
}
