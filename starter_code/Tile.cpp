#include "Tile.h"
#include <iostream>
// Constructor implementation
Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape) {
    // Any additional initialization if needed
}

// Destructor implementation (if needed)
 // Add missing include statement

Tile::~Tile() {
    // Any destruction if needed
}

#include <vector> // Add missing include statement

void printTileBag(const std::vector<Tile>& tileBag) {
    std::cout << "Tile Bag: ";
    for (const Tile& tile : tileBag) {
        std::cout << tile.colour << tile.shape << " ";
    }
    std::cout << "\nNumber of tiles in bag: " << tileBag.size() << std::endl;
}