
#ifndef GAMESAVE_H
#define GAMESAVE_H

#include "Player.h"
#include "Board.h"
#include "LinkedList.h"
#include <string>

class GameSave
{
public:
    GameSave(Player *player1, Player *player2, Board *board, LinkedList *tileBag, Player *currentPlayer, std::string filename);
    void saveGame(Player *player1, Player *player2, Board *board, LinkedList *tileBag, Player *currentPlayer, std::string filename);
};

#endif // GAMESAVE_H