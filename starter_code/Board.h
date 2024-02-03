//
// Created by micha on 24/01/2024.
//

#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"



class Board {
public:

   	Board();
   	~Board();

   	void initializeBoard();
   	void displayBoard();
   	//void addTileToBoard(Tile* tile, int row, int col);
   	bool checkSurroundingTilesMatch();
	bool checkTilePlacement();
	int getSize();
	bool checkSameTypeTiles();
    bool checkSameRowOrColumn();
// Ensure the forward declaration matches this signature

int calculateScore(const std::vector<Tile *> &tilesToPlace, const std::vector<std::pair<int, int>> &positions, std::vector<std::vector<Tile *>> &board);



 //   bool checkSurroundingTilesMatch(int row, int col, Tile* tile, bool& valid);


};



#endif //BOARD_H