//
// Created by micha on 24/01/2024.
//

#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include "Tile.h"

class Board {
public:
    Board();
    void displayBoard() const;
    void clear();
    size_t size() const; // what is this witchcraft. Copilot suggested it.
    std::vector<Tile*>& operator[](size_t index);

private:
    std::vector<std::vector<Tile *>> board;
};



#endif //BOARD_H