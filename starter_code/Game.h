//
// Created by alex on 30/01/24.
//

// Game.h
#ifndef APT2023_A2_GAME_H
#define APT2023_A2_GAME_H

#include <vector>
#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"

class Game {
public:
    Game(std::vector<Player*> players, LinkedList *bag, Board *board, int currentPlayerTurn, bool isEnhanced);
    // Other methods...

private:
    std::vector<Player*> players;
    Board* board;
    LinkedList* bag;
    int currentPlayerTurn;
    int playerCount;
};


#endif //APT2023_A2_GAME_H