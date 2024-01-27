
#include <iostream> // Include for std::cout, std::endl
#include <vector>   // Include for std::vector
#include "Board.h"
#include "Tile.h"

// Use constants for board size and bounds
#define COLUMN_MAX 26
#define COLUMN_MIN 1
#define ROW_MAX 25
#define ROW_MIN 0

void initializeBoard(std::vector<std::vector<Tile *>> &board)
{
    // Initialize the board with nullptr
    for (int i = ROW_MIN; i <= ROW_MAX; ++i)
    {
        std::vector<Tile *> row;
        for (int j = COLUMN_MIN; j <= COLUMN_MAX; ++j)
        {
            row.push_back(nullptr);
        }
        board.push_back(row);
    }
}

void displayBoard(std::vector<std::vector<Tile *>> &board)
{
    // Display the board
    std::cout << "\nBoard:" << std::endl;
    std::cout << "  ";
    for (int i = COLUMN_MIN; i <= COLUMN_MAX; ++i)
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
    for (int i = 0; i <= (COLUMN_MAX - COLUMN_MIN + 1); ++i)
    {
        std::cout << "____";
    }
    std::cout << std::endl;

    for (int i = ROW_MIN; i < (ROW_MAX + ROW_MIN); ++i)
    {
        char rowLabel = 'A' + i;
        std::cout << rowLabel << " |";
        for (int j = COLUMN_MIN; j <= COLUMN_MAX; ++j)
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

int Board::getRows()
{
    // Return the number of rows
    return (ROW_MAX + ROW_MIN);
}

int Board::getCols()
{
    // Return the number of columns
    return (COLUMN_MAX - COLUMN_MIN + 1);
}

std::vector<std::vector<char>> Board::getCurrentState()
{
    // Return the current state of the board
    std::vector<std::vector<char>> state;
    for (int i = ROW_MIN; i < (ROW_MAX + ROW_MIN); ++i)
    {
        std::vector<char> row;
        for (int j = COLUMN_MIN; j <= COLUMN_MAX; ++j)
        {
            if (board[i][j] == nullptr)
            {
                row.push_back(' ');
            }
            else
            {
                row.push_back(board[i][j]->colour);
            }
        }
        state.push_back(row);
    }
    return state;
}

void Board::placeTileOnBoard(Tile *tile, int row, int col)
{
    // Place a Tile on the board at the specified row and column
    if (row >= ROW_MIN && row < (ROW_MAX + ROW_MIN) && col >= COLUMN_MIN && col <= COLUMN_MAX)
    {
        board[row][col] = tile;
    }
}

Tile *Board::getTileAtPosition(int row, int col)
{
    // Get the Tile at the specified row and column
    if (row >= ROW_MIN && row < (ROW_MAX + ROW_MIN) && col >= COLUMN_MIN && col <= COLUMN_MAX)
    {
        return board[row][col];
    }
    return nullptr;
}

bool Board::doesTileExistAtPosition(int row, int col)
{
    // Check if there is a Tile at the specified row and column
    if (row >= ROW_MIN && row < (ROW_MAX + ROW_MIN) && col >= COLUMN_MIN && col <= COLUMN_MAX)
    {
        return board[row][col] != nullptr;
    }
    return false;
}
