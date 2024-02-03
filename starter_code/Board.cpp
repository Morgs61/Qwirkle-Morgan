// Board.cpp

using namespace std;
#include <iostream>
#include <algorithm>
#include <iostream> // Include for std::cout, std::endl
#include <vector>   // Include for std::vector
#include "Board.h"

#define COLUMN_MAX 26
#define COLUMN_MIN 1
#define ROW_MAX 25
#define ROW_MIN 0

// contains uppercase letters A to Z
string labels[COLUMN_MAX];

Board::Board()
{
    for (int ch = 'A'; ch <= 'Z'; ch++)
    {
        labels[ch - 'A'] = ch;
    }
    board = std::vector<Tile *>(ROWS * COLS, nullptr);
}
bool checkTilePlacement(const std::vector<std::vector<Tile *>> &board, int row, int col);

// Decalre fixed size of board here
int BOARD_SIZE = 15;

Board::~Board()
{
    for (auto tile : board)
    {
        if (tile != nullptr)
        {
            delete tile;
        }
    }
}

std::vector<Tile *> &Board::getBoard()
{
    return board;
}

void Board::displayBoard()
{
    // Print the header rows
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < COLUMN_MAX; j++)
        {
            // Print column indices and separators
            if (i == 0 && j == 0)
            {
                cout << "   " << j << "  ";
            }
            else if (i == 0 && j < 10)
            {
                cout << j << "  ";
            }
            else if (i == 0 && j > 9)
            {
                cout << j << " ";
            }
            else if (i == 1 && j == 0)
            {
                cout << "  -"
                     << "--";
            }
            else if (i == 1 && j == COLUMN_MAX - 1)
            {
                cout << "----";
            }
            else if (i == 1)
            {
                cout << "---";
            }
        }
        cout << endl;
    }

    // Print the board content
    for (int i = 0; i < ROWS; i++)
    {
        cout << labels[i] << " "; // Print row labels
        for (int j = 0; j < COLS; ++j)
        {
            // Check if a tile exists at the current position
            if (board[i * COLS + j] != nullptr)
            {
                string tileString = board[i * COLS + j]->toString();
                cout << tileString + "|"; // Print the tile's string representation
            }
            // Print separators or empty spaces if no tile is present
            else if (j == 0)
            {
                cout << "|";
            }
            else
            {
                cout << "  |";
            }
        }
        cout << endl;
    }
}

void Board::placeTile(Tile *tile, int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
    {
        board[row * COLS + col] = tile;
    }
}

Tile *Board::getTileAt(int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
    {
        return board[row * COLS + col];
    }
    return nullptr;
}

std::string Board::getBoardState()
{
    string stateString = "";
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (board[i * COLS + j] != nullptr)
            {
                stateString += board[i * COLS + j]->toString() + "@" + labels[i] + to_string(j) + ", ";
            }
        }
    }
    if (!stateString.empty())
    {
        // Remove the last space and comma
        stateString.pop_back();
        stateString.pop_back();
    }
    return stateString;
}

bool Board::hasTileAt(int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
    {
        return board[row * COLS + col] != nullptr;
    }
    return false;
}

size_t Board::size() const
{
    return board.size(); // Assuming board is your vector of vectors
}
// Function to check surrounding tiles for a tile
bool checkSurroundingTiles(const std::vector<std::vector<Tile *>> &board, int row, int col)
{
    // Check if tile is on the edge of the board
    if (row == 0 || row == BOARD_SIZE - 1 || col == 0 || col == BOARD_SIZE - 1)
    {
        return true;
    }
    // Check if tile is surrounded by other tiles
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
    bool isBoardEmpty = std::all_of(board.begin(), board.end(), [](const std::vector<Tile *> &boardRow)
                                    { return std::all_of(boardRow.begin(), boardRow.end(), [](const Tile *tile)
                                                         { return tile == nullptr; }); });

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
        if (board[row][i]->getColour() != tile->getColour() && board[row][i]->getShape() != tile->getShape())
        {
            rowMatch = false;
            std::cout << "Tile does not match row values" << std::endl;
            break;
        }
    }
    for (int i = col + 1; i < BOARD_SIZE && board[row][i] != nullptr; ++i)
    {
        if (board[row][i]->getColour() != tile->getColour() && board[row][i]->getShape() != tile->getShape())
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
        if (board[i][col]->getColour() != tile->getColour() && board[i][col]->getShape() != tile->getShape())
        {
            colMatch = false;
            std::cout << "Tile does not match column values" << std::endl;
            break;
        }
    }
    for (int i = row + 1; i < BOARD_SIZE && board[i][col] != nullptr; ++i)
    {
        if (board[i][col]->getColour() != tile->getColour() && board[i][col]->getShape() != tile->getShape())
        {
            colMatch = false;
            std::cout << "Tile does not match column values" << std::endl;
            break;
        }
    }

    // Check for duplicate tile in the row
    for (int i = col - 1; i >= 0 && board[row][i] != nullptr; --i)
    {
        if (board[row][i]->getColour() == tile->getColour() && board[row][i]->getShape() == tile->getShape())
        {
            std::cout << "Duplicate tile found in row, invalid placement" << std::endl;
            return false;
        }
    }
    for (int i = col + 1; i < BOARD_SIZE && board[row][i] != nullptr; ++i)
    {
        if (board[row][i]->getColour() == tile->getColour() && board[row][i]->getShape() == tile->getShape())
        {
            std::cout << "Duplicate tile found in row, invalid placement" << std::endl;
            return false;
        }
    }

    // Check for duplicate tile in the column
    for (int i = row - 1; i >= 0 && board[i][col] != nullptr; --i)
    {
        if (board[i][col]->getColour() == tile->getColour() && board[i][col]->getShape() == tile->getShape())
        {
            std::cout << "Duplicate tile found in column, invalid placement" << std::endl;
            return false;
        }
    }
    for (int i = row + 1; i < BOARD_SIZE && board[i][col] != nullptr; ++i)
    {
        if (board[i][col]->getColour() == tile->getColour() && board[i][col]->getShape() == tile->getShape())
        {
            std::cout << "Duplicate tile found in column, invalid placement" << std::endl;
            return false;
        }
    }

    return true && rowMatch && colMatch && hasNeighbor;
}

// function to make sure the tile is placed next to another tile
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

bool checkSameTypeTiles(const std::vector<Tile *> &tilesToPlace, const std::vector<std::pair<int, int>> &positions)
{
    if (tilesToPlace.size() < 2)
    {
        // If there is only one tile, it is considered a valid move
        return true;
    }
    char baseColor = tilesToPlace[0]->getColour();
    int baseShape = tilesToPlace[0]->getShape();
    int baseRow = positions[0].first;
    int baseColumn = positions[0].second;

    for (size_t i = 1; i < tilesToPlace.size(); ++i)
    {
        // Check that all conditions are met for each tile
        if ((tilesToPlace[i]->getColour() != baseColor &&
             tilesToPlace[i]->getShape() != baseShape) ||
            (positions[i].first != baseRow &&
             positions[i].second != baseColumn))
        {
            // std::cout << "Tiles in the move have different color, shape, or they don't share the same column/row" << std::endl;
            return false; // Tiles in the move have different color, shape, or they don't share the same column/row
        }
    }
    return true; // All tiles in the move have the same color, shape, and share the same column or row
}
