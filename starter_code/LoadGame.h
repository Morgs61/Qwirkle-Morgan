#ifndef LOADGAME_H
#define LOADGAME_H

#include "Game.h"
#include "LinkedList.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class LoadGame
{
public:
    Game *loadGame(std::string filename);
    LinkedList *loadTileBag(std::ifstream &file);
    LinkedList *loadHand(std::string handString, LinkedList *bag);
    void loadPlayer(LinkedList *bag, std::string playerName, int playerScore, std::string playerHandStr, std::vector<Player *> &players);

private:
    Board *loadBoardState(std::string boardState);
    void loadBagContents(LinkedList *bag, std::string bagContents);
};

#endif // LOADGAME_H