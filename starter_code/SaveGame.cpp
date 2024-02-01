#include <iostream>
#include <fstream>
#include <sstream>
#include "SaveGame.h"

void SaveGame::saveGameState(std::string filename, Player *currentPlayer, Player *otherPlayer, Board *board, LinkedList *bag)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error: Unable to open file for saving." << std::endl;
        return;
    }

    // Save player 1 details
    savePlayerDetails(file, currentPlayer);
    // Save player 2 details
    savePlayerDetails(file, otherPlayer);
    // Save current board shape
    file << board->getHeight() << "," << board->getWidth() << std::endl;
    // Save board state
    saveBoardState(file, board);
    // Save tile bag contents
    saveTileBag(file, bag);
    // Save current player name
    file << currentPlayer->getName() << std::endl;

    std::cout << "Game successfully saved to " << filename << std::endl;
}

void SaveGame::savePlayerDetails(std::ofstream &file, Player *player)
{
    file << player->getName() << std::endl;
    file << player->getScore() << std::endl;
    file << player->getHand()->toString() << std::endl;
}

void SaveGame::saveBoardState(std::ofstream &file, Board *board)
{
    for (int i = 0; i < board->getHeight(); ++i)
    {
        for (int j = 0; j < board->getWidth(); ++j)
        {
            Tile *tile = board->getTileAt(i, j);
            if (tile != nullptr)
            {
                file << tile->toString() << "@" << char('A' + i) << j + 1 << ", ";
            }
        }
    }
    file << std::endl;
}

void SaveGame::saveTileBag(std::ofstream &file, Bag *bag)
{
    file << bag->toString() << std::endl;
}
