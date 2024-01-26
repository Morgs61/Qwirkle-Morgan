// Board.cpp

#include <iostream> // Include for std::cout, std::endl
#include <vector>   // Include for std::vector
#include "Board.h"
#include "Tile.h"

// Decalre fixed size of board here
int BOARD_SIZE = 15;

void initializeBoard(std::vector<std::vector<Tile *>> &board)
{
    // Initialize the board with nullptr
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        std::vector<Tile *> row;
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            row.push_back(nullptr);
        }
        board.push_back(row);
    }
}

void displayBoard(const std::vector<std::vector<Tile *>> &board)
{
    // Display the board
    std::cout << "\nBoard:" << std::endl;
    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        if (i < 10)
        {
            std::cout << "  " << i << " ";
        }
        else
        {
            std::cout << " " << i << " ";
        }
    }
    std::cout << std::endl;
    // place underline under column headers
    for (int i = 0; i <= BOARD_SIZE; ++i)
    {
        std::cout << "____";
    }
    std::cout << std::endl;

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        char rowLabel = 'A' + i;
        std::cout << rowLabel << " |";
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j] == nullptr)
            {
                std::cout << "   |";
            }
            else
            {
                std::cout << "" << board[i][j]->colour << "" << board[i][j]->shape << "|";
            }
        }
        std::cout << std::endl;
    }
}
