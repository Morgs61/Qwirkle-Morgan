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
#include "Board.h"


class Game {
public:
    Game(Player** players, int playerCount, std::vector<Tile> *bag, Board board, int currentPlayerTurn);
    ~Game();
    void launchGame();
    bool checkForEmptyPlayerHands(Player** players, int playerCount);
private:
    Player** players;
    std::vector<Tile> *bag;
    Board board;
    int currentPlayerTurn;
    int playerCount;


};


#endif //APT2023_A2_GAME_H