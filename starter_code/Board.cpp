
using namespace std;
#include <iostream>
#include "Board.h"

#define COLUMN_MAX 26
#define COLUMN_MIN 1
#define ROW_MAX 25
#define ROW_MIN 0

// contains uppercase letters A to Z
string init[COLUMN_MAX];

Board::Board()
{
    for (int ch = 'A'; ch <= 'Z'; ch++)
    {
        init[ch - 'A'] = ch;
    }
    board = std::vector<Tile *>(ROWS * COLS, nullptr);
}

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
        cout << init[i] << " "; // Print row labels
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
                stateString += board[i * COLS + j]->toString() + "@" + init[i] + to_string(j) + ", ";
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