#ifndef QWIRKLE_H
#define QWIRKLE_H

#include <vector>
#include <string>
#include "LinkedList.h"

struct Tile;

void initializeTileBag(std::vector<Tile> &tileBag);
void shuffleTileBag(std::vector<Tile> &tileBag);
void initializePlayerHands(LinkedList &player1Hand, LinkedList &player2Hand, const std::vector<Tile> &tileBag);
void startNewGame();

#endif // QWIRKLE_H