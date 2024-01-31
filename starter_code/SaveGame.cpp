#include "GameSave.h"
#include "Player.h"
#include "Board.h"
#include "LinkedList.h"
#include <iostream>
using std::endl;

void saveGame(Player *player1, Player *player2, Board *board, LinkedList *bag, Player *currentPlayer, std::string outputFileName)
{
    std::ofstream outFile(outputFileName);

    outputPlayer(player1, outFile);
    outputPlayer(player2, outFile);

    outFile << "26,26" << std::endl;

    // Output board state
    for (size_t i = 0; i < board->getHeight(); ++i)
    {
        for (size_t j = 0; j < board->getWidth(); ++j)
        {
            Tile *tile = board->getTileAtPosition(i, j);
            if (tile != nullptr)
            {
                outFile << tile->colour << tile->shape << "@" << static_cast<char>('A' + i) << j + 1 << std::endl;
            }
        }
    }

    // Output tile bag contents
    outFile << bag->toString() << std::endl;

    // Output current player name
    outFile << currentPlayer->getName() << std::endl;

    outFile.close();

    std::cout << "Game successfully saved." << std::endl;
}

void outputPlayer(Player *player, std::ofstream &outFile)
{
    outFile << player->getName() << std::endl;
    outFile << player->getScore() << std::endl;
    outFile << player->getHand()->toString() << std::endl;
}
