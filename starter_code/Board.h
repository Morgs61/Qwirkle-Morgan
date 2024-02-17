#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

#include "Tile.h"

#define ROWS 26
#define COLS 27
#define STATE_TOKEN_LEN 5

class Board
{
public:
    // Constructor to initialize the board
    Board();

    // Destructor to release memory allocated for tiles
    ~Board();

    std::vector<Tile *> &getBoard();
    // Method to place a tile on the board at the specified row and column
    void placeTile(Tile *tile, int row, int col);
    void initializeBoard();
    void displayBoard();
    // void addTileToBoard(Tile* tile, int row, int col);
    bool checkSurroundingTilesMatch();
    bool checkTilePlacement(const std::vector<std::vector<Tile *>> &board,
                            int row, int col);
    int getSize();
    size_t size() const;
    bool checkSameTypeTiles();
    bool checkSameRowOrColumn();
    void setTileAtPosition(int row, int col, Tile *tile);
    bool checkSameTypeTiles(const std::vector<Tile *> &tilesToPlace,
                            const std::vector<std::pair<int, int>> &positions);
    bool checkSurroundingTilesMatch(int row, int col, Tile *tile);
    int calculateScore(const std::vector<Tile *> &tilesToPlace,
                       const std::vector<std::pair<int, int>> &positions);

    // Method to get the tile at the specified row and column
    Tile *getTileAt(int row, int col);

    // Method to get the state of the board as a string
    std::string getBoardState();

    // Method to check if a tile exists at the specified row and column
    bool hasTileAt(int row, int col);

    // Get the height of the board
    int getHeight() { return ROWS; }

    // Get the width of the board
    int getWidth() { return COLS; }

    int calculatePatternScore(int row, int col, int deltaX, int deltaY);

    bool tilesMatch(Tile *tile1, Tile *tile2);

private:
    std::vector<Tile *>
        board; // Vector to store pointers to tiles representing the board
    std::string
        labels[ROWS]; // Array to store row labels (uppercase letters A to Z)
};

#endif // BOARD_H
