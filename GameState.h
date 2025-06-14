// GameState.h
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
using namespace std;

const int SIZE = 5;

class GameState {
public:
    char board[SIZE][SIZE];

    GameState();
    void initializeBoard();
    void printBoard();
    bool isVictory(char piece, int x, int y);
    bool isVictoryLinha(char piece);
};

#endif