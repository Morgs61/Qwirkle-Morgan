#include "GameSave.h"
#include "Player.h"
#include "Board.h"
#include "LinkedList.h"
#include <iostream>
using std::endl;

GameSave::GameSave(Player *player1, Player *player2, Board *board, LinkedList *bag, Player *currentPlayer, std::string outputFileName, int playerCount)
{
    outFile.open("Tests/" + outputFileName + ".txt");

    // Output the total number of players
    outFile << playerCount << endl;

    // Output details of player 1
    outputPlayer(player1);

    // Output details of player 2
    outputPlayer(player2);

    // Write the fixed-size board state (assuming it's a 26x26 board)
    outFile << "26,26" << endl;

    // Write the current state of the board
    outFile << board->getState() << endl;

    // Write the string representation of the tile bag
    outFile << bag->toString() << endl;

    // Write the name of the current player
    outFile << currentPlayer->getName();
}

void GameSaver::outputPlayer(Player *player)
{
    // Write the player's name to the file
    outFile << player->getName() << endl;

    // Write the player's points to the file
    outFile << player->getPoints() << endl;

    // Write the string representation of the player's hand to the file
    outFile << player->getHand()->toString() << endl;
}
