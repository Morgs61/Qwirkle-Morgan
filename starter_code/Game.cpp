
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>

#include "Board.h"
#include "Game.h"
#include "LinkedList.h"
#include "Player.h"
#include "SaveGame.h"
#include "Tile.h"
#include "qwirkle.h"


Game::Game(Player** players, int numPlayers, LinkedList* bag, Board* board, Player* currentPlayer) {
  this->players = players;
  this->numPlayers = numPlayers;
  this->bag = bag;
  this->board = board;
  this->currentPlayer = currentPlayer;

}


Game::~Game() {
  delete board;
  delete bag;
  for (int i = 0; i < numPlayers; ++i) {
    delete players[i];
  }
  delete[] players;
  delete currentPlayer;
}

void Game::launchGame() {
  // get the current status of the game once its launched
  std::cout << "DEBUG0" << std::endl;
  bool gameComplete = isGameComplete();
  std::cout << "DEBUG1" << std::endl;
  // run until the game is complete.
  while (!gameComplete) {
    // Show the current Game status at the start of the players turn
    displayGameStatus();

    // Start the current players turn.
    bool playerTurnComplete = false;
    while (!playerTurnComplete) {
      int menuChoice = getPlayerMenuSelection();

      if (menuChoice == 1) {  // Place tiles
                              // placeTiles();
        playerTurnComplete = placeTiles();
      } else if (menuChoice == 2) {
        if (currentPlayer->getHand()->getSize() < 6) {
          std::cout << "You have already placed a tile. You can not now replace a "
                  "tile"
               << std::endl;
          // return;
        } else {
          playerTurnComplete =
              replaceTile();  // Use the return value to determine if the turn
                              // is complete
        }
      } else if (menuChoice == 3) {
        saveGame();
      } else if (menuChoice == 4) {
        std::cout << "\nQuitting game..." << std::endl;
        return;
      } else {
        std::cout << "Invalid choice. Please enter a valid option." << std::endl;
      }
    }

    int currentPlayerIndex = 0;
    // find current player in array
    for (int i = 0; i < numPlayers; ++i) {
      if (players[i]->getName() == currentPlayer->getName()) {
        currentPlayerIndex = i;
      }
    }

    // switch to the next player
    currentPlayer = switchPlayer(currentPlayerIndex);

    //currentPlayer = switchPlayer();

    // Check if the game is complete
    gameComplete = isGameComplete();
  }
  declareWinner();
}

Player* Game::switchPlayer(int currentPlayerIndex) {
  // Increment the current player index
  currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
  // Return the next player
  return players[currentPlayerIndex];
}


// Check if any player has an empty hand
bool Game::isGameComplete() {
  for (int i = 0; i < numPlayers; ++i) {
    if (players[i]->getHand()->isEmpty()) {
      return true; // The game is complete if any player has an empty hand
    }
  }
  return false; // If no player has an empty hand, the game is not complete
}

void Game::displayGameStatus() {
  std::cout << "\n" << currentPlayer->getName() << ", it's your turn" << std::endl;

  // Iterate through all players to display their scores
  for (int i = 0; i < numPlayers; ++i) {
    std::cout << "Score for " << players[i]->getName() << ": " << players[i]->getScore() << std::endl;
  }

  // Display the board
  board->displayBoard();

  // Display the current player's hand
  std::cout << currentPlayer->getName() << " Your hand is " << std::endl;
  currentPlayer->getHand()->displayHand();
}

int Game::getPlayerMenuSelection() {
  int choice;
  bool validActionSelected = false;
  while (!validActionSelected) {
    std::cout << "\nSelect your action:\n";
    std::cout << "1. Place tiles\n";
    std::cout << "2. Replace a tile\n";
    std::cout << "3. Save game\n";
    std::cout << "4. Quit game\n";
    std::cout << "> ";
    // Read an integer or handle non-integer input
    // DO NOT DELETE THIS AS IT STOPS LOOPING
    if (std::cin >> choice) {
      if (std::cin.eof()) {
        std::cout << "\n\nGoodbye" << std::endl;
        exit(EXIT_SUCCESS);
      }
      std::cin.ignore();  // Clear the input buffer
      validActionSelected = true;
    } else {
      if (std::cin.eof()) {
        std::cout << "\n\nGoodbye" << std::endl;
        exit(EXIT_SUCCESS);
      }
      std::cout << "Invalid input. Please enter a valid option." << std::endl;
      std::cin.clear();  // Clear the error flag
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                 '\n');  // Discard invalid input
    }
  }
  return choice;
}

std::vector<std::string> Game::parsePlayerInput() {
  std::string command;
  getline(std::cin, command);
  if (std::cin.eof()) {
    std::cout << "\n\nGoodbye" << std::endl;
    exit(EXIT_SUCCESS);
  }

  // Split the command into words
  std::vector<std::string> words;
  size_t pos = 0;
  while ((pos = command.find(' ')) != std::string::npos) {
    words.push_back(command.substr(0, pos));
    command.erase(0, pos + 1);
  }
  words.push_back(command);

  return words;
}

bool Game::validateTilePlacement(std::vector<std::string>& words,
                                 std::vector<Tile*>& tilesToPlace,
                                 std::vector<std::pair<int, int>>& tilePositions) {
  // Parse the tile and location from the command
  std::string tile = words[1];
  std::string location = words[3];
  const int COLUMN_MAX = 26;
  // Convert the grid location to row and column
  char gridLetter = location[0];
  size_t row =
      (gridLetter >= 'A' && gridLetter <= 'Z') ? (gridLetter - 'A') : -1;
  size_t column = std::stoi(
      location.substr(1));  // Convert the rest of the string to a number

  // Check if the row and column are valid
  if (row == static_cast<size_t>(-1) ||
      row >= static_cast<size_t>(board->getSize()) || column >= COLUMN_MAX) {
    std::cout << "Invalid grid location. Please try again." << std::endl;
    return false;
  }

  std::string color = std::string(1, tile[0]);
  std::string shape = tile.substr(1);
  Tile* tileToCheck = new Tile(color[0], stoi(shape));

  if (!currentPlayer->getHand()->containsTile(tileToCheck)) {
    std::cout << "Tile not found in hand. Please try again." << std::endl;
    delete tileToCheck;  // Avoid memory leak
    return false;
  } else if (!board->checkSameTypeTiles(tilesToPlace, tilePositions)) {
    std::cout << "Invalid move. Tiles must have the same color, shape, and share "
            "the same column or row."
         << std::endl;
    return false;
  } else if (!board->checkSurroundingTilesMatch(row, column, tileToCheck)) {
    std::cout << "Surrounding tiles do not match. Please try again." << std::endl;
    delete tileToCheck;  // Avoid memory leak
    return false;
  }

  tilesToPlace.push_back(tileToCheck);
  tilePositions.push_back(std::make_pair(row, column));

  return true;
}

void Game::updateGameAfterTilePlacement(
    std::vector<Tile*>& tilesToPlace, std::vector<std::pair<int, int>>& tilePositions,
    int& numTiles) {
  // Check if the tiles being placed have the same color, shape, and share the
  // same column or row
  if (!board->checkSameTypeTiles(tilesToPlace, tilePositions)) {
    std::cout << "Invalid move. Tiles must have the same color, shape, and share "
            "the same column or row."
         << std::endl;
  } else {
    ++numTiles;
    int row = tilePositions.back().first;
    int col = tilePositions.back().second;
    board->setTileAtPosition(row, col, tilesToPlace.back());
    board->displayBoard();
  }

  // Remove the tile from the player's hand
  if (!currentPlayer->getHand()->removeTile(tilesToPlace.back())) {
    std::cout << "Error removing tile from hand. Please try again." << std::endl;
  }
}

bool Game::placeTiles() {
  int numTiles = 0;
  std::vector<Tile*> tilesToPlace;
  std::vector<std::pair<int, int>> tilePositions;
  bool activeTurn = false;

  while (!activeTurn && currentPlayer->getHand()->getSize() > 0) {
    currentPlayer->getHand()->displayHand();
    std::cout << "Place tile " << numTiles + 1
         << " using the format: place <tile> at <grid location>" << std::endl;
    std::cout << "Enter 'end' to end your turn or 'back' to return to previous menu"
         << std::endl;
    std::cout << "> ";

    std::vector<std::string> words = parsePlayerInput();

    // Check if the player wants to end their turn
    if (words.size() == 1 && words[0] == "end") {
      if (numTiles == 0) {
        std::cout << "You must place at least one tile." << std::endl;
        activeTurn = false;
      } else {
        std::cout << "Ending turn." << std::endl;
        activeTurn = true;
      }
    }
    // Check for the 'back' command first
    if (words.size() == 1 && words[0] == "back") {
      if (numTiles > 0) {
        std::cout << "You have already placed a tile. You must continue your move."
             << std::endl;
        // activeTurn = false;
      } else {
        std::cout << "Returning to the previous menu." << std::endl;
        return false;  // Directly exit the function, thereby exiting the loop
                       // and not ending the player's
      }

    } else {
      if (words.size() != 4 || words[0] != "place" || words[3].length() >= 4) {
        std::cout << "Invalid command. Please try again." << std::endl;
      } else {
        if (validateTilePlacement(words, tilesToPlace, tilePositions)) {
          updateGameAfterTilePlacement(tilesToPlace, tilePositions, numTiles);
        }
      }
    }
  }

  int score = board->calculateScore(tilesToPlace, tilePositions);

  // add the score to the player's score
  currentPlayer->addScore(score);
  int MAX_HAND_SIZE = 6;

  // Draw new tiles from the tile bag and add them to the player's hand
  for (int k = 0; k < numTiles && !bag->isEmpty() &&
                  currentPlayer->getHand()->getSize() < MAX_HAND_SIZE;
       ++k) {
    // Get the tile from the back of the bag
    Tile* tileFromBagPtr = bag->back();
    bag->remove_back();

    // Add the new tile to the player's hand
    currentPlayer->getHand()->addTile(tileFromBagPtr);
  }

  // output the player hand
  std::cout << "Player's hand after adding a new tile: ";
  currentPlayer->getHand()->displayHand();

  std::cout << "The size of the tile bag is now: " << bag->getSize() << std::endl;
  std::cout << "\n" << currentPlayer->getName() << "'s hand: ";
  currentPlayer->getHand()->displayHand();
  return true;
}

Tile* Game::createAndValidateTile(const std::string& tileStr) {
  try {
    std::string color = std::string(1, tileStr[0]);
    std::string shape = tileStr.substr(1);
    Tile* tileToReplace = new Tile(color[0], stoi(shape));

    if (!currentPlayer->getHand()->containsTile(tileToReplace)) {
      std::cout << "Tile not found in hand. Please try again." << std::endl;
      delete tileToReplace;
      return nullptr;
    }
    return tileToReplace;
  } catch (const std::invalid_argument&) {
    // Catch the exception if stoi fails (e.g., when the input is not a valid
    // integer)
    std::cout << "Invalid tile format. Please enter a valid tile." << std::endl;
    return nullptr;
  }
}

void Game::replaceTileAndUpdateHand(Tile* tileToReplace) {
  currentPlayer->getHand()->removeTile(tileToReplace);
  bag->push_back(tileToReplace);
  // bag->shuffle();

  Tile* tileFromBag = bag->back();
  bag->remove_back();
  currentPlayer->getHand()->addTile(tileFromBag);
}

bool Game::replaceTile() {
  std::cout << "Replace a tile using the format: replace <tile>" << std::endl;
  std::cout << "Enter 'back' to return to previous menu" << std::endl;

  bool validInput = false;
  while (!validInput) {
    std::cout << "> ";
    std::string command;
    getline(std::cin, command);
    // Check for the 'back' command first
    if (std::cin.eof()) {
      std::cout << "\n\nGoodbye" << std::endl;
      exit(EXIT_SUCCESS);
    }
    if (command == "back") {
      std::cout << "Returning to the previous menu." << std::endl;
      return false;  // Directly exit the function, thereby exiting the loop and
                     // not ending the player's turn
    } else {
      std::vector<std::string> words;
      size_t pos = 0;
      // Split the command into words based on spaces
      while ((pos = command.find(' ')) != std::string::npos) {
        words.push_back(command.substr(0, pos));
        command.erase(0, pos + 1);
      }
      words.push_back(command);  // Add the last (or only) word

      // Check the command format
      if (words.size() == 2 && words[0] == "replace") {
        Tile* tileToReplace = createAndValidateTile(words[1]);
        if (tileToReplace != nullptr) {
          // If the tile is valid, proceed with replacement and update the hand
          replaceTileAndUpdateHand(tileToReplace);
          std::cout << "Tile replaced. Proceeding with the game." << std::endl;
          validInput = true;  // Exit the loop
        } else {
          std::cout << "Invalid tile. Please try again." << std::endl;
        }
      } else {
        // If the command format is incorrect, inform the user and the loop will
        // repeat
        std::cout << "Invalid command. Please try again." << std::endl;
      }
    }
  }
  return true;
}

void Game::saveGame() {
  // Save game
  std::string filename;
  std::cout << "Enter the filename to save the game: ";
  getline(std::cin, filename);
  if (std::cin.eof()) {
    std::cout << "\n\nGoodbye" << std::endl;
    exit(EXIT_SUCCESS);
  }

  // Prepend the "tests/" folder to the filename
  std::string fullFilename = "tests/" + filename;

  SaveGame::saveGameState(fullFilename, player1, player2, board, bag,
                          currentPlayer);
  std::cout << "Game successfully saved" << std::endl;
}

void Game::declareWinner() {
  std::cout << "Game over" << std::endl;
  std::cout << "\nScore for " << player1->getName() << ": "
            << player1->getScore() << std::endl;
  std::cout << "Score for " << player2->getName() << ": " << player2->getScore()
            << std::endl;
  std::cout << "Player ";

  if (player1->getScore() > player2->getScore()) {
    std::cout << player1->getName() << " won!" << std::endl;
  } else if (player1->getScore() < player2->getScore()) {
    std::cout << player2->getName() << " won!" << std::endl;
  } else {
    std::cout << "It's a draw!" << std::endl;
  }
  std::cout << "\n\nGoodbye" << std::endl;
  exit(0);
}
