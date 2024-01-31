//
// Created by micha on 24/01/2024.
//

#ifndef BOARD_H
#define BOARD_H



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

 //   bool checkSurroundingTilesMatch(int row, int col, Tile* tile, bool& valid);


};



#endif //BOARD_H