// Board.cpp

#include <algorithm>
#include <iostream>  // Include for std::cout, std::endl
#include <vector>    // Include for std::vector
#include "Board.h"
#include "Tile.h"

bool checkTilePlacement(const std::vector<std::vector<Tile *>> &board, int row, int col);

//Decalre fixed size of board here
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
            std::cout << " " << i << " ";
        }
        else
        {
            std::cout << " " << i << "";
        }
    }
    std::cout << std::endl;
    // place underline under column headers
    for (int i = 0; i <= BOARD_SIZE; ++i)
    {
        std::cout << "___";

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
                std::cout << "  |";
            }
            else
            {
                std::cout << "" << board[i][j]->colour << "" << board[i][j]->shape << "|";
            }
        }
        std::cout << std::endl;
    }
}

//Function to check surrounding tiles for a tile
bool checkSurroundingTiles(const std::vector<std::vector<Tile *>> &board, int row, int col)
{
    //Check if tile is on the edge of the board
    if (row == 0 || row == BOARD_SIZE - 1 || col == 0 || col == BOARD_SIZE - 1)
    {
        return true;
    }
    //Check if tile is surrounded by other tiles
    else if (board[row - 1][col] != nullptr || board[row + 1][col] != nullptr || board[row][col - 1] != nullptr || board[row][col + 1] != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkSurroundingTilesMatch(const std::vector<std::vector<Tile *>> &board, int row, int col, Tile *tile)
{
    // Check if the board is empty, allowing the first tile to be placed anywhere
    bool isBoardEmpty = std::all_of(board.begin(), board.end(), [](const std::vector<Tile *> &boardRow) {
        return std::all_of(boardRow.begin(), boardRow.end(), [](const Tile *tile) {
            return tile == nullptr;
        });
    });

    if (isBoardEmpty)
    {
        std::cout << "Board is empty" << std::endl;
        return true;
    }
    bool check = checkTilePlacement(board, row, col);
    if (!check)
    {
        std::cout << "Tile must be placed next to another tile" << std::endl;
        return false;
    }else{

    // Check if tile is on the edge of the board
    if (row == 0 || row == BOARD_SIZE - 1 || col == 0 || col == BOARD_SIZE - 1)
    {
        // Allow placement adjacent to tiles on the edge, but check if it's adjacent to the correct tile
        if ((row > 0 && board[row - 1][col] != nullptr && (board[row - 1][col]->colour == tile->colour || board[row - 1][col]->shape == tile->shape)) ||
            (row < BOARD_SIZE - 1 && board[row + 1][col] != nullptr && (board[row + 1][col]->colour == tile->colour || board[row + 1][col]->shape == tile->shape)) ||
            (col > 0 && board[row][col - 1] != nullptr && (board[row][col - 1]->colour == tile->colour || board[row][col - 1]->shape == tile->shape)) ||
            (col < BOARD_SIZE - 1 && board[row][col + 1] != nullptr && (board[row][col + 1]->colour == tile->colour || board[row][col + 1]->shape == tile->shape)))
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    // Check if tile is surrounded by other tiles with the same color or shape
    if ((board[row - 1][col] != nullptr) &&
        (board[row - 1][col]->colour != tile->colour || board[row - 1][col]->shape != tile->shape))
    {
        return false;
    }
    else if ((board[row + 1][col] != nullptr) &&
             (board[row + 1][col]->colour != tile->colour || board[row + 1][col]->shape != tile->shape))
    {
        return false;
    }
    else if ((board[row][col - 1] != nullptr) &&
             (board[row][col - 1]->colour != tile->colour || board[row][col - 1]->shape != tile->shape))
    {
        return false;
    }
    else if ((board[row][col + 1] != nullptr) &&
             (board[row][col + 1]->colour != tile->colour || board[row][col + 1]->shape != tile->shape))
    {
        return false;
    }

    return true;
}}



//function to make sure the tile is placed next to another tile
bool checkTilePlacement(const std::vector<std::vector<Tile *>> &board, int row, int col)
{
    // Check if any neighboring positions have a tile
    bool hasNeighbor = false;

    // Check above
    if (row > 0 && board[row - 1][col] != nullptr)
    {
        hasNeighbor = true;
    }

    // Check below
    if (row < BOARD_SIZE - 1 && board[row + 1][col] != nullptr)
    {
        hasNeighbor = true;
    }

    // Check left
    if (col > 0 && board[row][col - 1] != nullptr)
    {
        hasNeighbor = true;
    }

    // Check right
    if (col < BOARD_SIZE - 1 && board[row][col + 1] != nullptr)
    {
        hasNeighbor = true;
    }

    return hasNeighbor;
}

