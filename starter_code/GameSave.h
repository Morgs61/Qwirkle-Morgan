#ifndef GAMESAVER_H
#define GAMESAVE_H

#include "Player.h"
#include "Board.h"
#include "LinkedList.h"
#include <fstream>
#include <string>

class GameSave
{
public:
    // Constructor to save the game state to a file
    GameSave(Player *player1, Player *player2, Board *board, LinkedList *bag, Player *currentPlayer, std::string outputFileName, int playerCount);

private:
    std::ofstream outFile;

    // Helper function to output player details to the file
    void outputPlayer(Player *player);
};

#endif // GAMESAVE_H
