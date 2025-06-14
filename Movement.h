// Movement.h
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "GameState.h"

class Movement {
public:
    static bool isMaximumMove(GameState &state, char piece, int x, int y, int newX, int newY);
    static bool movePiece(GameState &state, char piece, int x, int y, int newX, int newY);
};

#endif