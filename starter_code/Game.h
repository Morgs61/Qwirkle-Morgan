//
// Created by alex on 30/01/24.
//

// Game.h
#ifndef APT2023_A2_GAME_H
#define APT2023_A2_GAME_H

#include "LinkedList.h"
#include "Player.h"
#include "Board.h"

class Game
{
public:
    Game(Player *player1, Player *player2, LinkedList *bag, Board *board, Player *currentPlayer);
    ~Game();
    void launchGame();
    bool checkForEmptyPlayerHands(Player **players, int playerCount);



private:
    Player *player1;
    Player *player2;
    LinkedList *bag;
    Board *board;
    Player *currentPlayer;
    int playerCount;
};

#endif // APT2023_A2_GAME_H
