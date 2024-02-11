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
#include "Help.h"
#include "HighScoreManager.h"

using std::cout;


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
void displayMenuSelection();
void displayMenuBasic();
void displayMenuEnhanced();

int main(void) {




  LinkedList *list = new LinkedList();
  delete list;

  // 2.1 Launch
  std::cout << "\nWelcome to Qwirkle!" << std::endl;
  std::cout << "-----------------------" << std::endl;


  bool quit = false;
  bool isEnhancedMenu = false; // Initially, assume basic menu

while (!quit) {    
    if (isEnhancedMenu) {
        displayMenuEnhanced();
    } else {
        displayMenuBasic(); // Assuming this is the function for the basic menu
    }
    
    std::string userInput;
    std::cin >> userInput;

    if (userInput == "help" && isEnhancedMenu) {
        Help::displayMainMenuHelp();
    } else {
        // Convert userInput to integer if it's not "help"
        try {
            int choice = std::stoi(userInput);

            if (choice == 1) {
                std::cout << "How many players?" << std::endl;
                int playerCount; 
                std::cin >> playerCount;
                 // Assuming playerCount is an integer variable
                startNewGame(playerCount);
            } 
            else if (choice == 2) {
                loadGame();
            } 
            else if (choice == 3) {
                displayStudentInformation();
            } else if (choice == 4) {
                std::cout << "\nQuitting the game. Goodbye!" << std::endl;
                quit = true;
            } else if (isEnhancedMenu && choice == 5) {
                std::cout << "\nHigh Scores!" << std::endl;
                HighScoreManager highScoreManager("highscores.txt");
                highScoreManager.displayHighScores(); // Assuming you have a function to display high scores
            } else if (choice == 5) {
                std::cout << "Toggling to " << (isEnhancedMenu ? "basic" : "enhanced") << " menu." << std::endl;
                isEnhancedMenu = !isEnhancedMenu; // Toggle menu mode 
            } else {
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
            }
        } catch (...) {
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }
}

return 0;
}
void displayMenuBasic() {
  std::cout << "\nMenu" << std::endl;
  std::cout << "-----" << std::endl;
  std::cout << "1. New Game" << std::endl;
  std::cout << "2. Load Game" << std::endl;
  std::cout << "3. Credits (Show student information)" << std::endl;
  std::cout << "4. Quit" << std::endl;
  std::cout << "5. Toggle Enhanced Menu" << std::endl;
  std::cout << "> ";


}

void displayMenuEnhanced() {
  std::cout << "\nMenu" << std::endl;
  std::cout << "-----" << std::endl;
  std::cout << "1. New Game" << std::endl;
  std::cout << "2. Load Game" << std::endl;
  std::cout << "3. Credits (Show student information)" << std::endl;
  std::cout << "4. Quit" << std::endl;
  std::cout << "5. High Scores \n" << std::endl;
  std::cout << "If you need help with this menu type, help" << std::endl;
  std::cout << "> ";


}

void displayMenuSelection() {
    std::cout << "Which menu would you like to use? (Enter 'basic' or 'enhanced'): ";
    std::string menuChoice;
    std::cin >> menuChoice;
    
    if (menuChoice == "basic") {
        displayMenuBasic();
    } else if (menuChoice == "enhanced") {
        displayMenuEnhanced();
    } else {
        std::cout << "Invalid choice. Please enter 'basic' or 'enhanced'." << std::endl;
        displayMenuSelection();
    }
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
  if (filename == "help") {
    Help::displayLoadGameHelp();
    loadGame();
  }
  else if (filename == "back") {
    std::cout << "\n\return" << std::endl;
    return;
  }
  else {
  // Prepend the test folder path.
  filename = filename;

  if (std::cin.eof()) {
    std::cout << "\n\nGoodbye" << std::endl;
    exit(EXIT_SUCCESS);
  }

  //Create an instance of LoadGame
  LoadGame loader;

  //Call the loadGame method with the filename
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
}
void startNewGame(int playerCount) {
    // Initialize and shuffle the tile bag
    LinkedList* bag = new LinkedList();
    bag->initializeAndShuffleBag();

    // Create player names
    Player** players = new Player*[playerCount];
    for (int i = 0; i < playerCount; ++i) {
        std::string playerName;
        bool invalidName = true;
        while (invalidName) {
            // Prompt user for player name
            std::cout << "\nEnter a name for player " << i + 1 << " (uppercase characters only):\n> ";
            std::cin >> playerName;
            if (std::cin.eof()) {
                std::cout << "\n\nGoodbye" << std::endl;
                exit(EXIT_SUCCESS);
            } else if (playerName == "help") {
                Help::displayNamingHelp();
            } else if (isValidPlayerName(playerName)) {
                invalidName = false;
            } else {
                std::cout << "Invalid player name. Please enter uppercase characters only." << std::endl;
            }
        }
        // Create player hands
        LinkedList* playerHand = new LinkedList();
        initializePlayerHand(playerHand, bag);

        // Create players
        players[i] = new Player(playerName, 0, playerHand);

        // Print player's hand
        std::cout << "Player " << playerName << "'s hand:" << std::endl;
        playerHand->displayHand(); // Assuming there's a function to display a player's hand
    }

    std::cin.ignore();
    std::cout << "\nLet's Play!" << std::endl;

    // Initialize the board
    Board* board = new Board();

    // Instantiate Game with the modified parameters
    Game* game = new Game(players, playerCount, bag, board, players[0]);

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

// Function to find starting player by finding the most matching types of tiles
// in hand
Player *findStartingPlayer(Player *player1, Player *player2) {
  Player *startingPlayer = nullptr;
  int maxMatchingTiles = 0;

  // Use unordered_map to track counts of color and shape for each player
  std::unordered_map<char, int> colorCount1, colorCount2;
  std::unordered_map<int, int> shapeCount1, shapeCount2;

  // Check player 1's hand for matching tiles
  for (int k = 0; k < player1->getHand()->getSize(); ++k) {
    Tile *currentTile = player1->getHand()->getTile(k);

    // Update color count
    if (colorCount1.find(currentTile->getColour()) == colorCount1.end()) {
      colorCount1[currentTile->getColour()] = 1;
    } else {
      colorCount1[currentTile->getColour()]++;
    }

    // Update shape count
    if (shapeCount1.find(currentTile->getShape()) == shapeCount1.end()) {
      shapeCount1[currentTile->getShape()] = 1;
    } else {
      shapeCount1[currentTile->getShape()]++;
    }
  }

  // Check player 2's hand for matching tiles
  for (int k = 0; k < player2->getHand()->getSize(); ++k) {
    Tile *currentTile = player2->getHand()->getTile(k);

    // Update color count
    if (colorCount2.find(currentTile->getColour()) == colorCount2.end()) {
      colorCount2[currentTile->getColour()] = 1;
    } else {
      colorCount2[currentTile->getColour()]++;
    }

    // Update shape count
    if (shapeCount2.find(currentTile->getShape()) == shapeCount2.end()) {
      shapeCount2[currentTile->getShape()] = 1;
    } else {
      shapeCount2[currentTile->getShape()]++;
    }
  }

  // Find the maximum count of matching tiles (color or shape) for player 1
  int matchingTiles1 = 0;
  for (const auto &pair : colorCount1) {
    matchingTiles1 = std::max(matchingTiles1, pair.second);
  }

  for (const auto &pair : shapeCount1) {
    matchingTiles1 = std::max(matchingTiles1, pair.second);
  }

  // Find the maximum count of matching tiles (color or shape) for player 2
  int matchingTiles2 = 0;
  for (const auto &pair : colorCount2) {
    matchingTiles2 = std::max(matchingTiles2, pair.second);
  }

  for (const auto &pair : shapeCount2) {
    matchingTiles2 = std::max(matchingTiles2, pair.second);
  }

  // Update startingPlayer based on the maximum count
  if (matchingTiles1 > maxMatchingTiles ||
      (matchingTiles1 == maxMatchingTiles &&
       player1->getName() < player2->getName())) {
    maxMatchingTiles = matchingTiles1;
    startingPlayer = player1;
  }

  if (matchingTiles2 > maxMatchingTiles ||
      (matchingTiles2 == maxMatchingTiles &&
       player2->getName() < player1->getName())) {
    maxMatchingTiles = matchingTiles2;
    startingPlayer = player2;
  }

  return startingPlayer;
}


