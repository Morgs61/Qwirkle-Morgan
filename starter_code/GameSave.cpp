#include "GameSave.h"
#include "Player.h"
#include "Board.h"
#include "LinkedList.h"
#include <iostream>
using std::endl;

// Define the operator<< overload for std::vector<std::vector<char>> outside the class definition
std::ofstream &operator<<(std::ofstream &ofs, std::vector<std::vector<char>> &vec)
{
    for (auto &innerVec : vec)
    {
        for (char c : innerVec)
        {
            ofs << c;
        }
        ofs << '\n'; // Add newline after each inner vector
    }
    return ofs;
}

// Constructor definition
GameSave::GameSave(Player *player1, Player *player2, Board *board, LinkedList *tileBag, Player *currentPlayer, std::string outputFileName)
{
    outFile.open("Tests/" + outputFileName + ".txt");

    // Output details of player 1
    outputPlayer(player1);

    // Output details of player 2
    outputPlayer(player2);

    // Write the fixed-size board state (assuming it's a 26x26 board)
    outFile << "26,26" << std::endl;

    // Write the current state of the board
    // Iterate through each row of the vector
    for (auto &row : board->getCurrentState())
    {
        // Iterate through each character in the row and write it to the output file
        for (char c : row)
        {
            outFile << c;
        }
        // Write a newline character after each row
        outFile << std::endl;
    }

    // Write the string representation of the tile bag
    outFile << tileBag->toString() << std::endl;

    // Write the name of the current player
    outFile << currentPlayer->getName();
}

void GameSave::outputPlayer(Player *player)
{
    // Write the player's name to the file
    outFile << player->getName() << endl;

    // Write the player's score to the file
    outFile << player->getScore() << endl;

    // Write the string representation of the player's hand to the file
    outFile << player->getHand()->toString() << endl;
}
