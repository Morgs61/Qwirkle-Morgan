#include <fstream>
#include <iostream>

#include "Board.h"
#include "LinkedList.h"
#include "SaveGame.h"

void SaveGame::saveGameState(std::string filename, Player *player1,
                             Player *player2, Board *board, LinkedList *bag,
                             Player *currentPlayer)
{
  std::ofstream file(filename);

  if (!file.is_open())
  {
    std::cerr << "Failed to open file for saving: " << filename << std::endl;
    return;
  }

  // Save player details
  savePlayerDetails(file, player1);
  savePlayerDetails(file, player2);

  // Save board state
  saveBoardState(file, board);

  // Save tile bag
  saveTileBag(file, bag);

  // Save the name of the current player
  file << currentPlayer->getName() << std::endl;

  file.close();
}

void SaveGame::saveGameStateMultiplayer(std::string filename, std::vector<Player *> &players,
                                        Board *board, LinkedList *bag, Player *currentPlayer)
{
  std::ofstream file(filename);

  if (!file.is_open())
  {
    std::cerr << "Failed to open file for saving: " << filename << std::endl;
    return;
  }

  if (players.size() >= 3 && players.size() <= 4)
  {
    // Save player details
    for (Player *player : players)
    {
      savePlayerDetails(file, player);
    }

    // Save board state
    saveBoardState(file, board);

    // Save tile bag
    saveTileBag(file, bag);

    // Save the name of the current player
    file << currentPlayer->getName() << std::endl;
  }
  else
  {
    // Handle cases with invalid number of players
    std::cerr << "Invalid number of players for saving the game." << std::endl;
  }

  file.close();
}

void SaveGame::savePlayerDetails(std::ofstream &file, Player *player)
{
  file << player->getName() << std::endl;
  file << player->getScore() << std::endl;
  file << player->getHand()->toString() << std::endl;
}

void SaveGame::saveBoardState(std::ofstream &file, Board *board)
{
  file << board->getHeight() << "," << board->getWidth() << std::endl;

  // Get the board state string from the Board object
  std::string boardState = board->getBoardState();

  // Write the board state string to the file
  file << boardState << std::endl;
}

void SaveGame::saveTileBag(std::ofstream &file, LinkedList *bag)
{
  file << bag->toString() << std::endl;
}
