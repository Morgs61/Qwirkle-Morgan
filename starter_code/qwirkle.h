#ifndef QWIRKLE_H
#define QWIRKLE_H

#include <vector>
#include <string>
#include "LinkedList.h"

struct Tile;

void initializeTileBag(std::vector<Tile> &tileBag);
void shuffleTileBag(std::vector<Tile> &tileBag);
void initializePlayerHands(LinkedList &player1Hand, LinkedList &player2Hand, std::vector<Tile> &tileBag);
void startNewGame();
void loadGame();
void initializeBoard(std::vector<std::vector<Tile *>> &board);
void displayBoard(const std::vector<std::vector<Tile *>> &board);

#endif // QWIRKLE_H