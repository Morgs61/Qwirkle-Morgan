#include "SaveGame.h"
#include <fstream>
#include <iostream>

void SaveGame::saveGameState(std::string filename, Player *player1, Player *player2, Board *board, LinkedList *bag, Player *currentPlayer)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Failed to open file for saving: " << filename << std::endl;
        return;
    }

    // Save player details
    savePlayerDetails(file, player1);
    savePlayerDetails(file, player2);

    // Save board state
    saveBoardState(file, board);

    // Save tile bag
    saveTileBag(file, bag);

    // Save the name of the current player
    file << currentPlayer->getName() << std::endl;

    file.close();
}

void SaveGame::savePlayerDetails(std::ofstream &file, Player *player)
{
    file << player->getName() << std::endl;
    file << player->getScore() << std::endl;
    file << player->getHand()->toString() << std::endl;
}

void SaveGame::saveBoardState(std::ofstream &file, Board *board)
{
    file << board->getHeight() << "," << board->getWidth() << std::endl;

    // Get the board state string from the Board object
    std::string boardState = board->getBoardState();

    // Write the board state string to the file
    file << boardState << std::endl;
}

void SaveGame::saveTileBag(std::ofstream &file, LinkedList *bag)
{
    file << bag->toString() << std::endl;
}
