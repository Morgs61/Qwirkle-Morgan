#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
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
   bool checkTilePlacement();
   int getSize();
   bool checkSameTypeTiles();
   bool checkSameRowOrColumn();

   //   bool checkSurroundingTilesMatch(int row, int col, Tile* tile, bool& valid);

   // Method to get the tile at the specified row and column
   Tile *getTileAt(int row, int col);

   // Method to get the state of the board as a string
   std::string getBoardState();

   // Method to check if a tile exists at the specified row and column
   bool hasTileAt(int row, int col);

   // Method to get the size of the board
   size_t size() const;

private:
   std::vector<Tile *> board; // Vector to store pointers to tiles representing the board
   std::string init[ROWS];    // Array to store row labels (uppercase letters A to Z)
};

#endif // BOARD_H
