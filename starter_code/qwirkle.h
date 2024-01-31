#ifndef QWIRKLE_H
#define QWIRKLE_H

#include <vector>
#include <string>
#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"
#include "Game.h"

struct Tile;

void initializeTileBag(std::vector<Tile> &tileBag);
void shuffleTileBag(std::vector<Tile> &tileBag);
void initializePlayerHand(LinkedList *playerHand, std::vector<Tile> *tileBag);
void startNewGame();
void loadGame();
void initializeBoard(std::vector<std::vector<Tile *>> &board);
void displayBoard(const std::vector<std::vector<Tile *>> &board);
bool checkForEmptyPlayerHands(Player **players, int numPlayers);
void startGame();

#endif // QWIRKLE_H