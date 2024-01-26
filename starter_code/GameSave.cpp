#include "GameSave.h"
#include "Player.h"
#include "Board.h"
#include "LinkedList.h"
#include "Tile.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Constructor for saving the game
GameSave::GameSave(Player *player1, Player *player2, Board *board, LinkedList *tileBag, Player *currentPlayer, string filename)
{
    saveGame(player1, player2, board, tileBag, currentPlayer, filename);
}

// Function to save the game
void GameSave::saveGame(Player *player1, Player *player2, Board *board, LinkedList *tileBag, Player *currentPlayer, string filename)
{
    ofstream outFile(filename);

    // Save player information
    outFile << player1->getName() << endl;
    outFile << player1->getScore() << endl;
    outFile << player1->getHand()->toString() << endl;

    outFile << player2->getName() << endl;
    outFile << player2->getScore() << endl;
    outFile << player2->getHand()->toString() << endl;

    // Save board information
    outFile << board->getRows() << "," << board->getCols() << endl;
    outFile << board->getState() << endl;

    // Save tile bag contents
    vector<Tile *> bagTiles = tileBag->getAllTiles();
    for (Tile *tile : bagTiles)
    {
        outFile << tile->toString() << ",";
    }
    outFile << endl;

    // Save current player name
    outFile << currentPlayer->getName() << endl;

    cout << "Game successfully saved." << endl;
}
