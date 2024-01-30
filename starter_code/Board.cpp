// Board.cpp

#include <algorithm>
#include <iostream>  // Include for std::cout, std::endl
#include <vector>    // Include for std::vector
#include "Board.h"
#include "Tile.h"

bool checkTilePlacement(const std::vector<std::vector<Tile *>> &board, int row, int col);

//Decalre fixed size of board here
int BOARD_SIZE = 15;

//return size of board
int Board::getSize()
{
    return BOARD_SIZE;
}

void initializeBoard(std::vector<std::vector<Tile *>> &board)
{
    // Initialize the board with nullptr
    for (int i = 1; i <= BOARD_SIZE; ++i)
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
    for (int i = 1; i <= BOARD_SIZE; ++i)
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
    // Check if board is empty, allowing first tile placement anywhere
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

    // Check existing checks for adjacent tiles
    bool hasNeighbor = checkTilePlacement(board, row, col);
    if (!hasNeighbor)
    {
        std::cout << "Tile must be placed next to another tile" << std::endl;
        return false;
    }

    // Check along the row within a limited range
    bool rowMatch = true;
    for (int i = col - 1; i >= 0 && board[row][i] != nullptr; --i)
    {
        if (board[row][i]->colour != tile->colour && board[row][i]->shape != tile->shape)
        {
            rowMatch = false;
            std::cout << "Tile does not match row values" << std::endl;
            break;
        }
    }
    for (int i = col + 1; i < BOARD_SIZE && board[row][i] != nullptr; ++i)
    {
        if (board[row][i]->colour != tile->colour && board[row][i]->shape != tile->shape)
        {
            rowMatch = false;
            std::cout << "Tile does not match row values" << std::endl;
            break;
        }
    }

    // Check along the column within a limited range
    bool colMatch = true;
    for (int i = row - 1; i >= 0 && board[i][col] != nullptr; --i)
    {
        if (board[i][col]->colour != tile->colour && board[i][col]->shape != tile->shape)
        {
            colMatch = false;
            std::cout << "Tile does not match column values" << std::endl;
            break;
        }
    }
    for (int i = row + 1; i < BOARD_SIZE && board[i][col] != nullptr; ++i)
    {
        if (board[i][col]->colour != tile->colour && board[i][col]->shape != tile->shape)
        {
            colMatch = false;
            std::cout << "Tile does not match column values" << std::endl;
            break;
        }
    }

    // Check for duplicate tile in the row
    for (int i = col - 1; i >= 0 && board[row][i] != nullptr; --i)
    {
        if (board[row][i]->colour == tile->colour && board[row][i]->shape == tile->shape)
        {
            std::cout << "Duplicate tile found in row, invalid placement" << std::endl;
            return false;
        }
    }
    for (int i = col + 1; i < BOARD_SIZE && board[row][i] != nullptr; ++i)
    {
        if (board[row][i]->colour == tile->colour && board[row][i]->shape == tile->shape)
        {
            std::cout << "Duplicate tile found in row, invalid placement" << std::endl;
            return false;
        }
    }

    // Check for duplicate tile in the column
    for (int i = row - 1; i >= 0 && board[i][col] != nullptr; --i)
    {
        if (board[i][col]->colour == tile->colour && board[i][col]->shape == tile->shape)
        {
            std::cout << "Duplicate tile found in column, invalid placement" << std::endl;
            return false;
        }
    }
    for (int i = row + 1; i < BOARD_SIZE && board[i][col] != nullptr; ++i)
    {
        if (board[i][col]->colour == tile->colour && board[i][col]->shape == tile->shape)
        {
            std::cout << "Duplicate tile found in column, invalid placement" << std::endl;
            return false;
        }
    }

    return true && rowMatch && colMatch && hasNeighbor;
}




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

bool checkSameTypeTiles(const std::vector<Tile*>& tilesToPlace) {
    if (tilesToPlace.size() < 2) {
        // If there is only one tile, it is considered a valid move
        return true;
    }

    // Check if all tiles in the current move have the same color or the same shape
    for (size_t i = 0; i < tilesToPlace.size(); ++i) {
        char currentColor = tilesToPlace[i]->colour;
        int currentShape = tilesToPlace[i]->shape;


        for (size_t j = i + 1; j < tilesToPlace.size(); ++j) {
            if (tilesToPlace[j]->colour != currentColor && tilesToPlace[j]->shape != currentShape) {
                std::cout << "Tiles in the move have different color or shape" << std::endl;
                return false;  // Tiles in the move have different color or shape
            }
        }
    }

    return true;  // All tiles in the move have the same color or the same shape
}

