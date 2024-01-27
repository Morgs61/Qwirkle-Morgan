//
// Created by micha on 24/01/2024.
//

#ifndef BOARD_H
#define BOARD_H

class Tile; // Forward declaration

class Board
{
public:
   Board();
   ~Board();

   void initializeBoard(std::vector<std::vector<Tile *>> &board);
   void displayBoard(std::vector<std::vector<Tile *>> &board);
   // void addTileToBoard(Tile* tile, int row, int col);

   int getRows();
   int getCols();

   std::vector<std::vector<char>> getCurrentState();

   void placeTileOnBoard(Tile *tile, int row, int col);
   Tile *getTileAtPosition(int row, int col);
   bool doesTileExistAtPosition(int row, int col);

private:
   std::vector<std::vector<Tile *>> board;
};

#endif // BOARD_H