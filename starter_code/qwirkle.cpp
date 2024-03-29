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
  bool loaded = false;
  while (!loaded)
  {
    std::cout << "\nType 'help' for assistance or 'exit' to return to the main menu." << std::endl;
    std::cout << "Enter the filename from which to load a game:" << std::endl;
    std::string filename;
    std::cout << "> ";

    std::getline(std::cin, filename);
    // Prepend the test folder path.
    filename = "tests/" + filename;

    if (filename == "tests/help")
    {
      loadGameHelp();
    }
    else if (filename == "tests/exit")
    {
      std::cout << "\nReturning to the main menu." << std::endl;
      return; // Return to the main menu
    }
    else
    {
      // Create an instance of LoadGame
      LoadGame loader;

      // Get the number of players from the file
      int numPlayers = loader.getNumPlayers(filename);

      // Check the number of players and choose the appropriate loader
      if (numPlayers == 2)
      {
        // Call the loadGame method with the filename
        Game *loadedGame = loader.loadGame(filename);
        if (loadedGame != nullptr)
        {
          std::cout << "\nQwirkle game successfully loaded." << std::endl;
          std::cout << "Launching the game..." << std::endl;
          // Continue reading or processing the file content here
          loadedGame->launchGame();
          loaded = true;
        }
        else
        {
          std::cout << "\nInvalid filename. Please try again or enter 'help' for assistance." << std::endl;
        }
      }
      else if (numPlayers == 3)
      {
        // Call the loadMultiplayerGame method with the filename
        Game *loadedGame = loader.loadMultiplayerGame(filename, numPlayers);
        if (loadedGame != nullptr)
        {
          std::cout << "\nQwirkle multiplayer game successfully loaded." << std::endl;
          std::cout << "Launching the game..." << std::endl;
          // Continue reading or processing the file content here
          loadedGame->launchGame();
          loaded = true;
        }
        else
        {
          std::cout << "\nInvalid filename. Please try again or enter 'help' for assistance." << std::endl;
        }
      }
      else if (numPlayers == 4)
      {
        // Call the loadFourPlayerGame method with the filename
        Game *loadedGame = loader.loadMultiplayerGame(filename, numPlayers);
        if (loadedGame != nullptr)
        {
          std::cout << "\nQwirkle four-player game successfully loaded." << std::endl;
          std::cout << "Launching the game..." << std::endl;
          // Continue reading or processing the file content here
          loadedGame->launchGame();
          loaded = true;
        }
        else
        {
          std::cout << "\nInvalid filename. Please try again or enter 'help' for assistance." << std::endl;
        }
      }
      else
      {
        std::cout << "\nUnsupported number of players in the game file." << std::endl;
      }
    }
  }
}

void startNewGame()
{
  // Prompt the user to select the number of players
  int numPlayers;
  do
  {
    std::cout << "Enter the number of players (2-4): ";
    std::cin >> numPlayers;
  } while (numPlayers < 2 || numPlayers > 4);

  // Initialize and shuffle the tile bag
  LinkedList *bag = new LinkedList();
  bag->initializeAndShuffleBag();

  // Create the game object based on the number of players
  Game *game;
  if (numPlayers == 2)
  {
    // Create player names for 2 players
    std::string playerName1, playerName2;
    do
    {
      std::cout << "\nEnter a name for player 1 (uppercase characters only): ";
      std::cin >> playerName1;
    } while (!isValidPlayerName(playerName1));
    do
    {
      std::cout << "\nEnter a name for player 2 (uppercase characters only): ";
      std::cin >> playerName2;
    } while (!isValidPlayerName(playerName2));

    // Create player hands for 2 players
    LinkedList *playerHand1 = new LinkedList();
    initializePlayerHand(playerHand1, bag);
    LinkedList *playerHand2 = new LinkedList();
    initializePlayerHand(playerHand2, bag);

    // Create players for 2 players
    Player *player1 = new Player(playerName1, 0, playerHand1);
    Player *player2 = new Player(playerName2, 0, playerHand2);

    // Initialize the board
    Board *board = new Board();

    // Set starting player as player1
    Player *startingPlayer = player1;

    // Instantiate Game for 2 players
    game = new Game(player1, player2, bag, board, startingPlayer);
  }
  else
  {
    // Create players for 3 or 4 players
    std::vector<Player *> players;
    for (int i = 0; i < numPlayers; ++i)
    {
      std::string playerName;
      do
      {
        std::cout << "\nEnter a name for player " << i + 1 << " (uppercase characters only): ";
        std::cin >> playerName;
      } while (!isValidPlayerName(playerName));

      LinkedList *playerHand = new LinkedList();
      initializePlayerHand(playerHand, bag);
      players.push_back(new Player(playerName, 0, playerHand));
    }

    // Initialize the board
    Board *board = new Board();

    // Set starting player as the first player
    Player *startingPlayer = players[0];

    // Instantiate Game for 3 or 4 players
    game = new Game(players, bag, board, startingPlayer);
  }

  std::cout << "\nLet's Play!" << std::endl;

  // Launch the game
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

void loadGameHelp()
{
  std::cout << "=== Load Game Help ===" << std::endl;
  std::cout << "To load a game, follow these steps:" << std::endl;
  std::cout << "1. Enter the filename of the game you want to load." << std::endl;
  std::cout << "2. The game will be loaded and you can continue playing." << std::endl;
  std::cout << "3. If the file does not exist or is invalid, an error message will be displayed." << std::endl;
  std::cout << "4. Type 'exit' to exit the game." << std::endl;
}
