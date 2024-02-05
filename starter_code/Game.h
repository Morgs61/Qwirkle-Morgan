//
// Created by alex on 30/01/24.
//

// Game.h
#ifndef APT2023_A2_GAME_H
#define APT2023_A2_GAME_H

#include <vector>
#include <string>
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"

class Game
{
public:
    Game(Player *player1, Player *player2, LinkedList *bag, Board *board, Player *currentPlayer);
    ~Game();
    void launchGame();
    bool checkForEmptyPlayerHands(Player **players, int playerCount);
    void displayGameStatus();
    int getPlayerMenuSelection();
    bool processPlayerAction(int menuChoice);
    void placeTiles();
    void replaceTile();
    void saveGame();
    bool isGameComplete();

private:
    Player *player1;
    Player *player2;
    LinkedList *bag;
    Board *board;
    Player *currentPlayer;
    int playerCount;
    std::vector<std::string> parsePlayerInput();
    bool validateTilePlacement(std::vector<std::string>& words, std::vector<Tile*>& tilesToPlace, std::vector<std::pair<int, int>>& tilePositions);
    void updateGameAfterTilePlacement(std::vector<Tile*>& tilesToPlace, std::vector<std::pair<int, int>>& tilePositions, int& numTiles);
    Tile* createAndValidateTile(const std::string& tileStr); // New method declaration
    void replaceTileAndUpdateHand(Tile* tileToReplace); // New method declaration
};

#endif // APT2023_A2_GAME_H
