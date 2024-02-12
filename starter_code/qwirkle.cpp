#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <unordered_map>
#include <vector>

#include "Board.h"
#include "Game.h"
#include "LinkedList.h"
#include "LoadGame.h"
#include "Node.h"
#include "Player.h"
#include "Tile.h"
#include "TileCodes.h"
#include "qwirkle.h"

#define EXIT_SUCCESS 0

void displayMenu();
bool isValidPlayerName(const std::string &name);
void displayStudentInformation();
void loadGame();
bool checkSurroundingTilesMatch(const std::vector<std::vector<Tile *>> &board,
                                int row, int col, Tile *tile);
bool checkSameTypeTiles(const std::vector<Tile *> &tilesToPlace,
                        const std::vector<std::pair<int, int>> &positions);
Player *findStartingPlayer(Player *player1, Player *player2);

int main(void) {
  LinkedList *list = new LinkedList();
  delete list;

  // std::cout << "TODO: Implement Qwirkle!" << std::endl;
  // 2.1 Launch
  std::cout << "\nWelcome to Qwirkle!" << std::endl;
  std::cout << "-----------------------" << std::endl;

  int choice = 0;
  bool quit = false;

  while (!quit) {
    displayMenu();
    std::cout << "> ";
    std::cin >> choice;

    if (std::cin.eof()) {
      std::cout << "\n\nGoodbye" << std::endl;
      exit(EXIT_SUCCESS);
    } else if (std::cin.fail()) {
      // Clear the error state
      std::cin.clear();

      // Ignore the rest of the line
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      std::cout << "Invalid choice. Please enter a valid option." << std::endl;
    } else {
      if (choice == 1) {
        std::cout << "Welcome to QWIRKLE!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << "Welcome to QWIRKLE!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << "\nStarting a New Game" << std::endl;
        startNewGame();
      } else if (choice == 2) {
        loadGame();
        // Add code for loading a game
      } else if (choice == 3) {
        displayStudentInformation();
      } else if (choice == 4) {
        std::cout << "\nQuitting the game. Goodbye!" << std::endl;
        quit = true;
      } else {
        std::cout << "Invalid choice. Please enter a valid option." << std::endl;
      }
    }
  }

  return EXIT_SUCCESS;
}
void displayMenu() {
  std::cout << "\nMenu" << std::endl;
  std::cout << "-----" << std::endl;
  std::cout << "1. New Game" << std::endl;
  std::cout << "2. Load Game" << std::endl;
  std::cout << "3. Credits (Show student information)" << std::endl;
  std::cout << "4. Quit \n" << std::endl;
}

// Function to check if a player name is valid
bool isValidPlayerName(const std::string &name) {
  for (char c : name) {
    // check if we can use this
    if (!isupper(c) || !isalpha(c)) {
      std::cout << "Invalid name. Please enter uppercase letters only." << std::endl;
      return false;
    }
  }
  return true;
}

// 2.2.3 Credits
void displayStudentInformation() {
  std::cout << "\n--------------------------------------" << std::endl;
  // Hardcoded information for 4 students
  std::cout << "Name: Michael Moon" << std::endl;
  std::cout << "Student ID: s3523025" << std::endl;
  std::cout << "Email: s3523025@student.rmit.edu.au" << std::endl;

  std::cout << "\nName: Alexander Cowan" << std::endl;
  std::cout << "Student ID: s3863084" << std::endl;
  std::cout << "Email: s3863084@student.rmit.edu.au" << std::endl;

  std::cout << "\nName: Michael Whyte" << std::endl;
  std::cout << "Student ID: s3851481" << std::endl;
  std::cout << "Email: S3851481@student.rmit.edu.au" << std::endl;

  std::cout << "\nName: Morgan Cassar" << std::endl;
  std::cout << "Student ID: s3858530" << std::endl;
  std::cout << "Email: s3858530@student.rmit.edu.au" << std::endl;
  std::cout << "--------------------------------------" << std::endl;
}

void loadGame() {
  std::cout << "\nEnter the filename from which to load a game:" << std::endl;
  std::string filename;
  std::cout << "> ";

  std::cin >> filename;
  // Prepend the test folder path.
  filename = "tests/" + filename;

  if (std::cin.eof()) {
    std::cout << "\n\nGoodbye" << std::endl;
    exit(EXIT_SUCCESS);
  }

  // Create an instance of LoadGame
  LoadGame loader;

  // Call the loadGame method with the filename
  Game *loadedGame = loader.loadGame(filename);

  // Check if the game is successfully loaded
  if (loadedGame != nullptr) {
    // File exists and is open

    // Open the file for reading
    ifstream file(filename);

    // Check if the file is open
    if (file.is_open()) {
      // File is open, proceed with reading
      std::string line;
      if (getline(file, line)) {
        std::cout << "\nQwirkle game successfully loaded." << std::endl;
        // Continue reading or processing the file content here
        loadedGame->launchGame();
      } else {
        std::cout << "\nInvalid file format. Unable to load the game." << std::endl;
      }

      // Close the file when done
      file.close();
    } else {
      cout << "\nError: Unable to open the file." << std::endl;
    }
  }
}

void startNewGame() {

  //default game set to 2 players
  int numPlayers = 2;

  // Create Players
  Player** players = new Player*[numPlayers];
  // Initialize and shuffle the tile bag
  // cout << "making the bag" << std::endl;
  LinkedList *bag = new LinkedList();  // Instantiate LinkedList
  bag->initializeAndShuffleBag();      // Populate the bag

  for (int i = 0; i < numPlayers; ++i) {
    string playerName;
    do {
      std::cout << "\nEnter a name for player " << (i + 1) << " (uppercase characters only): " << std::endl;
      std::cout << "> ";
      std::cin >> playerName;

      if (std::cin.eof()) {
        cout << "\n\nGoodbye" << std::endl;
        exit(EXIT_SUCCESS);
      }
    } while (!isValidPlayerName(playerName));

    // create a new hand with 6 tiles in it from the tile bag
    LinkedList* playerHand = new LinkedList();
    initializePlayerHand(playerHand, bag);

    // create a new player with the name and hand
    players[i] = new Player(playerName, 0, playerHand);
  }

  std::cin.ignore();
  std::cout << "\nLet's Play!" << std::endl;

  // Initialize the board
  Board *board = new Board();  // Instantiate Board

  // This will find starting player by Qwirkle Rules
  int startingPlayerIndex = findStartingPlayer(players, numPlayers);
  std::rotate(players, players + startingPlayerIndex, players + numPlayers);
  //Player *startingPlayer = findStartingPlayer(players, numPlayers);
  std::cout << "Starting player is: " << players[0]->getName() << std::endl;

  // Determine the starting player

  // Instantiate Game with the modified parameters
  Game *game =
      new Game(players, numPlayers, bag, board, players[0]);  // Pass player1, player2, bag, and currentPlayer
  std::cout << "Game created" << std::endl;
  // Call the correct method
  game->launchGame();
}

void initializePlayerHand(LinkedList *playerHand, LinkedList *bag) {
  // Draw tiles from the tile bag and add them to the player's hand until there
  // are 6 tiles
  while (playerHand->getSize() < 6 && !bag->isEmpty()) {
    // Get the tile pointer from the back of the bag
    Tile *tileFromBagPtr = bag->back();

    bag->remove_back();

    // Add the tile pointer directly to the player's hand
    playerHand->addTile(tileFromBagPtr);
  }
}

// Function to find starting player by finding the most matching types of tiles in hand
int findStartingPlayer(Player** players, int numPlayers) {
    int maxMatchingTiles = 0;
    int startingPlayer = 0;

    // Loop through each player to find matching tiles
    for (int i = 0; i < numPlayers; ++i) {
        int matchingTiles = 0;

        // Use unordered_map to track counts of color and shape
        std::unordered_map<char, int> colorCount;
        std::unordered_map<int, int> shapeCount;

        // Check the current player's hand for matching tiles
        for (int k = 0; k < players[i]->getHand()->getSize(); ++k) {
            Tile* currentTile = players[i]->getHand()->getTile(k);

            // Update color count
            if (colorCount.find(currentTile->colour) == colorCount.end()) {
                colorCount[currentTile->colour] = 1;
            } else {
                colorCount[currentTile->colour]++;
            }

            // Update shape count
            if (shapeCount.find(currentTile->shape) == shapeCount.end()) {
                shapeCount[currentTile->shape] = 1;
            } else {
                shapeCount[currentTile->shape]++;
            }
        }

        // Find the maximum count of matching tiles (color or shape)
        for (const auto& pair : colorCount) {
            matchingTiles = std::max(matchingTiles, pair.second);
        }

        for (const auto& pair : shapeCount) {
            matchingTiles = std::max(matchingTiles, pair.second);
        }

        // Print the count for the current player
        std::cout << "Player " << players[i]->getName() << " has " << matchingTiles << " tiles able to be played." << std::endl;

        // Update startingPlayer based on the maximum count
        if (matchingTiles > maxMatchingTiles || (matchingTiles == maxMatchingTiles && players[i]->getName() < players[startingPlayer]->getName())) {
            maxMatchingTiles = matchingTiles;
            startingPlayer = i;
        }
    }

    return startingPlayer;
}
