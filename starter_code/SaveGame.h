#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include "Board.h"
#include "LinkedList.h"
#include "Player.h"

class SaveGame
{
public:
  static void saveGameState(std::string filename, Player *player1,
                            Player *player2, Board *board, LinkedList *bag,
                            Player *currentPlayer);

  static void saveGameStateMultiplayer(std::string filename, std::vector<Player *> &players,
                                       Board *board, LinkedList *bag, Player *currentPlayer);

private:
  static void savePlayerDetails(std::ofstream &file, Player *player);
  static void saveBoardState(std::ofstream &file, Board *board);
  static void saveTileBag(std::ofstream &file, LinkedList *bag);
};

#endif // SAVE_GAME_H
