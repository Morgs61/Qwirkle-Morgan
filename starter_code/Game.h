//
// Created by alex on 30/01/24.
//
#ifndef APT2023_A2_GAME_H
#define APT2023_A2_GAME_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#include "Board.h"
#include "LinkedList.h"
#include "Player.h"

class Game
{
public:
    Game(Player *player1, Player *player2, LinkedList *bag, Board *board,
         Player *currentPlayer);
    Game(std::vector<Player *> &players, LinkedList *bag, Board *board,
         Player *currentPlayer);
    ~Game();
    void launchGame();
    bool checkForEmptyPlayerHands(Player **players, int playerCount);
    void displayGameStatus();
    int getPlayerMenuSelection();
    bool processPlayerAction(int menuChoice);
    bool placeTiles();
    void placeTileHelp();
    bool replaceTile();
    void replaceTileHelp();
    void saveGame();
    bool isGameComplete();
    void declareWinner();
    void switchPlayer();
    void saveGameHelp();
    std::string toLower(std::string &str);
    void displayHelpMessageGameMenu();

private:
    Player *player1;
    Player *player2;
    Player *player3;
    Player *player4;
    LinkedList *bag;
    Board *board;
    Player *currentPlayer;
    int playerCount;
    std::vector<std::string> parsePlayerInput();
    bool validateTilePlacement(std::vector<std::string> &words,
                               std::vector<Tile *> &tilesToPlace,
                               std::vector<std::pair<int, int>> &tilePositions);
    void updateGameAfterTilePlacement(
        std::vector<Tile *> &tilesToPlace,
        std::vector<std::pair<int, int>> &tilePositions, int &numTiles);
    Tile *createAndValidateTile(
        const std::string &tileStr);                    // New method declaration
    void replaceTileAndUpdateHand(Tile *tileToReplace); // New method declaration
    std::vector<Player *> players;
};

#endif // APT2023_A2_GAME_H
