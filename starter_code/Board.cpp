// Board.cpp

#include <iostream>  // Include for std::cout, std::endl
#include <vector>    // Include for std::vector
#include "Board.h"
#include "Tile.h"

//Decalre fixed size of board here
int BOARD_SIZE = 15;

Board::Board() {
    // Initialize the board with nullptr
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::vector<Tile *> row;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            row.push_back(nullptr);
        }
        board.push_back(row);
    }
}

void Board::displayBoard() const {
    // Display the board
    std::cout << "\nBoard:" << std::endl;
    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (i < 10) {
            std::cout << "  " << i << " ";
        } else {
            std::cout << " " << i << " ";
        }
    }
    std::cout << std::endl;
    // place underline under column headers
    for (int i = 0; i <= BOARD_SIZE; ++i) {
        std::cout << "____";
    }
    std::cout << std::endl;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        char rowLabel = 'A' + i;
        std::cout << rowLabel << " |";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == nullptr) {
                std::cout << "   |";
            } else {
                std::cout << "" << board[i][j]->colour << "" << board[i][j]->shape << "|";
            }
        }
        std::cout << std::endl;
    }
}
void Board::clear() {
    for (auto & row : board) {
        for (auto & tile : row) {
            delete tile;
            tile = nullptr;
        }
        row.clear();
    }
    board.clear();
}

std::vector<Tile*>& Board::operator[](size_t index) {
    return board[index];
}

// TODO: work out why this is needed.
size_t Board::size() const {
    return board.size();
}