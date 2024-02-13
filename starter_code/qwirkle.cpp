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

int main(void)
{
  LinkedList *list = new LinkedList();
  delete list;

  // std::cout << "TODO: Implement Qwirkle!" << std::endl;
  // 2.1 Launch
  std::cout << "\nWelcome to Qwirkle!" << std::endl;
  std::cout << "-----------------------" << std::endl;

  int choice = 0;
  bool quit = false;
  std::string input;

  while (!quit)
  {
    displayMenu();
    std::cout << "> ";
    std::getline(std::cin, input);

    if (input == "help")
    {
      mainMenuHelp();
    }

    else if (std::cin.eof())
    {
      std::cout << "\n\nGoodbye" << std::endl;
      exit(EXIT_SUCCESS);
    }
    else if (std::cin.fail())
    {
      // Clear the error state
      std::cin.clear();

      // Ignore the rest of the line
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      std::cout << "Invalid choice. Please enter a valid option." << std::endl;
    }
    else
    {
      choice = std::stoi(input);
      if (choice == 1)
      {
        std::cout << "\nStarting a New Game" << std::endl;
        startNewGame();
      }
      else if (choice == 2)
      {
        loadGame();
        // Add code for loading a game
      }
      else if (choice == 3)
      {
        displayStudentInformation();
      }
      else if (choice == 4)
      {
        std::cout << "\nQuitting the game. Goodbye!" << std::endl;
        quit = true;
      }
      else
      {
        std::cout << "Invalid choice. Please enter a valid option." << std::endl;
      }
    }
  }
  return EXIT_SUCCESS;
}

void displayMenu()
{
  std::cout << "\nMenu" << std::endl;
  std::cout << "-----" << std::endl;
  std::cout << "1. New Game" << std::endl;
  std::cout << "2. Load Game" << std::endl;
  std::cout << "3. Credits (Show student information)" << std::endl;
  std::cout << "4. Quit" << std::endl;
  std::cout << "Type 'help' for help on using the menu" << std::endl;
}

// Function to check if a player name is valid
bool isValidPlayerName(const std::string &name)
{
  for (char c : name)
  {
    // check if we can use this
    if (!isupper(c) || !isalpha(c))
    {
      std::cout << "Invalid name. Please enter uppercase letters only." << std::endl;
      return false;
    }
  }
  return true;
}

// 2.2.3 Credits
void displayStudentInformation()
{
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

void loadGame()
{
  std::cout << "\nEnter the filename from which to load a game:" << std::endl;
  std::string filename;
  std::cout << "> ";

  std::cin >> filename;
  // Prepend the test folder path.
  filename = "tests/" + filename;

  if (std::cin.eof())
  {
    std::cout << "\n\nGoodbye" << std::endl;
    exit(EXIT_SUCCESS);
  }

  // Create an instance of LoadGame
  LoadGame loader;

  // Call the loadGame method with the filename
  Game *loadedGame = loader.loadGame(filename);

  // Check if the game is successfully loaded
  if (loadedGame != nullptr)
  {
    // File exists and is open

    // Open the file for reading
    ifstream file(filename);

    // Check if the file is open
    if (file.is_open())
    {
      // File is open, proceed with reading
      std::string line;
      if (getline(file, line))
      {
        std::cout << "\nQwirkle game successfully loaded." << std::endl;
        // Continue reading or processing the file content here
        loadedGame->launchGame();
      }
      else
      {
        std::cout << "\nInvalid file format. Unable to load the game." << std::endl;
      }

      // Close the file when done
      file.close();
    }
    else
    {
      cout << "\nError: Unable to open the file." << std::endl;
    }
  }
}

void startNewGame()
{
  // Initialize and shuffle the tile bag
  // cout << "making the bag" << std::endl;
  LinkedList *bag = new LinkedList(); // Instantiate LinkedList
  bag->initializeAndShuffleBag();     // Populate the bag

  // Create player names
  std::string playerName1, playerName2;
  do
  {
    cout << "\nEnter a name for player 1 (uppercase characters only): \n";
    cout << "> ";
    std::cin >> playerName1;

    if (std::cin.eof())
    {
      cout << "\n\nGoodbye" << std::endl;
      exit(EXIT_SUCCESS);
    }
  } while (!isValidPlayerName(playerName1));

  do
  {
    cout << "\nEnter a name for player 2 (uppercase characters only): \n";
    cout << "> ";
    std::cin >> playerName2;
    if (std::cin.eof())
    {
      cout << "\n\nGoodbye" << std::endl;
      exit(EXIT_SUCCESS);
    }
  } while (!isValidPlayerName(playerName2));

  // Create player hands
  LinkedList *playerHand1 = new LinkedList();
  initializePlayerHand(playerHand1, bag); // Pass the address of tileBag

  LinkedList *playerHand2 = new LinkedList();
  initializePlayerHand(playerHand2, bag); // Pass the address of tileBag

  // Create players
  Player *player1 = new Player(playerName1, 0, playerHand1);
  Player *player2 = new Player(playerName2, 0, playerHand2);

  std::cin.ignore();
  cout << "\nLet's Play!" << std::endl;

  // Initialize the board
  Board *board = new Board(); // Instantiate Board

  // This will find starting player by Qwirkle Rules
  // Player *startingPlayer = findStartingPlayer(player1, player2);
  // std::cout << "Starting player is: " << startingPlayer->getName() <<
  // std::endl;

  // Determine the starting player

  // Instantiate Game with the modified parameters
  Game *game =
      new Game(player1, player2, bag, board,
               player1); // Pass player1, player2, bag, and currentPlayer

  // Call the correct method
  game->launchGame();
}

void initializePlayerHand(LinkedList *playerHand, LinkedList *bag)
{
  // Draw tiles from the tile bag and add them to the player's hand until there
  // are 6 tiles
  while (playerHand->getSize() < 6 && !bag->isEmpty())
  {
    // Get the tile pointer from the back of the bag
    Tile *tileFromBagPtr = bag->back();

    bag->remove_back();

    // Add the tile pointer directly to the player's hand
    playerHand->addTile(tileFromBagPtr);
  }
}

// Function to find starting player by finding the most matching types of tiles
// in hand
Player *findStartingPlayer(Player *player1, Player *player2)
{
  Player *startingPlayer = nullptr;
  int maxMatchingTiles = 0;

  // Use unordered_map to track counts of color and shape for each player
  std::unordered_map<char, int> colorCount1, colorCount2;
  std::unordered_map<int, int> shapeCount1, shapeCount2;

  // Check player 1's hand for matching tiles
  for (int k = 0; k < player1->getHand()->getSize(); ++k)
  {
    Tile *currentTile = player1->getHand()->getTile(k);

    // Update color count
    if (colorCount1.find(currentTile->getColour()) == colorCount1.end())
    {
      colorCount1[currentTile->getColour()] = 1;
    }
    else
    {
      colorCount1[currentTile->getColour()]++;
    }

    // Update shape count
    if (shapeCount1.find(currentTile->getShape()) == shapeCount1.end())
    {
      shapeCount1[currentTile->getShape()] = 1;
    }
    else
    {
      shapeCount1[currentTile->getShape()]++;
    }
  }

  // Check player 2's hand for matching tiles
  for (int k = 0; k < player2->getHand()->getSize(); ++k)
  {
    Tile *currentTile = player2->getHand()->getTile(k);

    // Update color count
    if (colorCount2.find(currentTile->getColour()) == colorCount2.end())
    {
      colorCount2[currentTile->getColour()] = 1;
    }
    else
    {
      colorCount2[currentTile->getColour()]++;
    }

    // Update shape count
    if (shapeCount2.find(currentTile->getShape()) == shapeCount2.end())
    {
      shapeCount2[currentTile->getShape()] = 1;
    }
    else
    {
      shapeCount2[currentTile->getShape()]++;
    }
  }

  // Find the maximum count of matching tiles (color or shape) for player 1
  int matchingTiles1 = 0;
  for (const auto &pair : colorCount1)
  {
    matchingTiles1 = std::max(matchingTiles1, pair.second);
  }

  for (const auto &pair : shapeCount1)
  {
    matchingTiles1 = std::max(matchingTiles1, pair.second);
  }

  // Find the maximum count of matching tiles (color or shape) for player 2
  int matchingTiles2 = 0;
  for (const auto &pair : colorCount2)
  {
    matchingTiles2 = std::max(matchingTiles2, pair.second);
  }

  for (const auto &pair : shapeCount2)
  {
    matchingTiles2 = std::max(matchingTiles2, pair.second);
  }

  // Update startingPlayer based on the maximum count
  if (matchingTiles1 > maxMatchingTiles ||
      (matchingTiles1 == maxMatchingTiles &&
       player1->getName() < player2->getName()))
  {
    maxMatchingTiles = matchingTiles1;
    startingPlayer = player1;
  }

  if (matchingTiles2 > maxMatchingTiles ||
      (matchingTiles2 == maxMatchingTiles &&
       player2->getName() < player1->getName()))
  {
    maxMatchingTiles = matchingTiles2;
    startingPlayer = player2;
  }

  return startingPlayer;
}

void mainMenuHelp()
{
  std::cout << "=== Main Menu Help ===" << std::endl;
  std::cout << "To navigate the main menu, follow these steps:" << std::endl;
  std::cout << "1. Enter the number corresponding to your desired action." << std::endl;
  std::cout << "2. For each option:" << std::endl;
  std::cout << "   - New Game: Start a new game." << std::endl;
  std::cout << "   - Load Game: Load a previously saved game." << std::endl;
  std::cout << "   - Credits: Display information about the developers." << std::endl;
  std::cout << "   - Quit: Exit the game." << std::endl;
}