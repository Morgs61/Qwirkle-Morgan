
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <cctype>
#include <sstream>

#include "Board.h"
#include "Game.h"
#include "LinkedList.h"
#include "Player.h"
#include "SaveGame.h"
#include "Tile.h"
#include "qwirkle.h"

Game::Game(Player *player1, Player *player2, LinkedList *bag, Board *board,
           Player *currentPlayer)
{
  this->player1 = player1;
  this->player2 = player2;
  this->bag = bag;
  this->board = board;
  this->currentPlayer = currentPlayer;
  playerCount = 2;
}

// Constructor for starting a new game with a vector of players
Game::Game(std::vector<Player *> &players, LinkedList *bag, Board *board,
           Player *currentPlayer)
{
  if (players.size() == 2)
  {
    // Use the original constructor if there are only two players
    this->player1 = players[0];
    this->player2 = players[1];
    this->bag = bag;
    this->board = board;
    this->currentPlayer = currentPlayer;
    playerCount = 2;
  }
  else if (players.size() >= 3 && players.size() <= 4)
  {
    // Handle cases with 3 or 4 players
    // Assign players from the vector to the appropriate player variables
    this->player1 = players[0];
    this->player2 = players[1];
    this->player3 = players[2]; // For 3 players
    if (players.size() == 4)
    {
      this->player4 = players[3]; // For 4 players
    }
    else
    {
      this->player4 = nullptr; // Set player4 to nullptr if there are only 3 players
    }

    // Initialize other game components
    this->bag = bag;
    this->board = board;
    this->currentPlayer = currentPlayer;
    playerCount = players.size();
  }
  else
  {
    // Handle cases with invalid number of players
    throw std::invalid_argument("Invalid number of players for starting a new game.");
  }
}

Game::~Game()
{
  delete bag;
  delete player1;
  delete player2;
  delete board;
}

void Game::launchGame()
{
  // get the current status of the game once its launched
  bool gameComplete = isGameComplete();

  // run until the game is complete.
  while (!gameComplete)
  {
    // Show the current Game status at the start of the players turn
    displayGameStatus();

    // Start the current players turn.
    bool playerTurnComplete = false;
    while (!playerTurnComplete)
    {
      int menuChoice = getPlayerMenuSelection();

      if (menuChoice == 1)
      { // Place tiles
        // placeTiles();
        playerTurnComplete = placeTiles();
      }
      else if (menuChoice == 2)
      {
        if (currentPlayer->getHand()->getSize() < 6)
        {
          std::cout << "You have already placed a tile. You can not now replace a "
                       "tile"
                    << std::endl;
          // return;
        }
        else
        {
          playerTurnComplete =
              replaceTile(); // Use the return value to determine if the turn
                             // is complete
        }
      }
      else if (menuChoice == 3)
      {
        saveGame();
      }
      else if (menuChoice == 4)
      {
        std::cout << "\nQuitting game..." << std::endl;
        return;
      }
      else
      {
        std::cout << "Invalid choice. Please enter a valid option." << std::endl;
      }
    }
    // Switch players
    switchPlayer();

    // Check if the game is complete
    gameComplete = isGameComplete();
  }
  declareWinner();
}

// Check if any player has an empty hand
bool Game::isGameComplete()
{
  // if either player has an empty hand, the game is complete.
  return player1->getHand()->isEmpty() || player2->getHand()->isEmpty();
}

void Game::displayGameStatus()
{
  std::cout << "\n"
            << currentPlayer->getName() << std::endl;
  std::cout << "It's your turn!" << std::endl;
  std::cout << "Score for " << player1->getName()
            << std::endl;
  std::cout << player1->getScore() << std::endl;
  std::cout << "Score for " << player2->getName()
            << std::endl;
  std::cout << player2->getScore() << std::endl;

  if (playerCount >= 3)
  {
    std::cout << "Score for " << player3->getName()
              << std::endl;
    std::cout << player3->getScore() << std::endl;
  }

  if (playerCount == 4)
  {
    std::cout << "Score for " << player4->getName()
              << std::endl;
    std::cout << player4->getScore() << std::endl;
  }

  board->displayBoard();
  std::cout << "\n"
            << currentPlayer->getName() << std::endl;
  std::cout << "Your hand: ";
  currentPlayer->getHand()->displayHand();
}

void Game::switchPlayer()
{
  if (currentPlayer == player1)
  {
    currentPlayer = player2;
  }
  else if (currentPlayer == player2)
  {
    if (playerCount == 3)
    {
      currentPlayer = player3;
    }
    else if (playerCount == 4)
    {
      currentPlayer = player4;
    }
    else
    {
      currentPlayer = player1; // In case of unexpected number of players
    }
  }
  else if (currentPlayer == player3)
  {
    if (playerCount == 4)
    {
      currentPlayer = player4;
    }
    else
    {
      currentPlayer = player1; // In case of unexpected number of players
    }
  }
  else if (currentPlayer == player4)
  {
    currentPlayer = player1;
  }
}

int Game::getPlayerMenuSelection()
{
  std::string input;
  int choice = 0;
  bool validActionSelected = false;

  while (!validActionSelected)
  {
    std::cout << "\nSelect your action:\n";
    std::cout << "1. Place tiles\n";
    std::cout << "2. Replace a tile\n";
    std::cout << "3. Save game\n";
    std::cout << "4. Quit game\n";
    std::cout << "type 'help' for more information\n";
    std::cout << "> ";

    std::getline(std::cin, input);

    // Convert input to lowercase for case-insensitive comparison
    input = toLower(input);

    std::istringstream iss(input);

    if (input == "help")
    {
      displayHelpMessageGameMenu();
      continue; // Skip the rest of the loop and restart
    }
    else if (iss >> choice)
    {
      if (std::cin.eof())
      {
        std::cout << "\n\nGoodbye" << std::endl;
        exit(EXIT_SUCCESS);
      }
      validActionSelected = true;
    }
    else
    {
      if (std::cin.eof())
      {
        std::cout << "\n\nGoodbye" << std::endl;
        exit(EXIT_SUCCESS);
      }
      std::cout << "Invalid input. Please enter a valid option. Enter an option between 1 & 4, or type 'help' for more information" << std::endl;
      std::cin.clear();                                                   // Clear the error flag
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
    }
  }

  return choice;
}

std::vector<std::string> Game::parsePlayerInput()
{
  std::string command;
  getline(std::cin, command);

  // Remove the newline character if it exists
  if (!command.empty() && command[command.size() - 1] == '\n')
  {
    command.erase(command.size() - 1);
  }

  if (std::cin.eof())
  {
    std::cout << "\n\nGoodbye" << std::endl;
    exit(EXIT_SUCCESS);
  }

  // Split the command into words
  std::vector<std::string> words;
  size_t pos = 0;
  while ((pos = command.find(' ')) != std::string::npos)
  {
    words.push_back(command.substr(0, pos));
    command.erase(0, pos + 1);
  }
  words.push_back(command);

  return words;
}

bool Game::validateTilePlacement(std::vector<std::string> &words,
                                 std::vector<Tile *> &tilesToPlace,
                                 std::vector<std::pair<int, int>> &tilePositions)
{
  // Parse the tile and location from the command
  std::string tile = words[1];
  std::string location = words[3];
  const int COLUMN_MAX = 26;
  // Convert the grid location to row and column
  char gridLetter = location[0];
  size_t row =
      (gridLetter >= 'A' && gridLetter <= 'Z') ? (gridLetter - 'A') : -1;
  size_t column = std::stoi(
      location.substr(1)); // Convert the rest of the string to a number

  // Check if the row and column are valid
  if (row == static_cast<size_t>(-1) ||
      row >= static_cast<size_t>(board->getSize()) || column >= COLUMN_MAX)
  {
    std::cout << "Invalid grid location. Please try again." << std::endl;
    return false;
  }

  std::string color = std::string(1, tile[0]);
  std::string shape = tile.substr(1);

  std::cout << "Color: " << color << ", Shape: " << shape << ", Row: " << row << ", Column: " << column << std::endl; // Debug output

  Tile *tileToCheck = new Tile(color[0], stoi(shape));

  if (!currentPlayer->getHand()->containsTile(tileToCheck))
  {
    std::cout << "Tile not found in hand. Please try again." << std::endl;
    delete tileToCheck; // Avoid memory leak
    return false;
  }
  else if (!board->checkSameTypeTiles(tilesToPlace, tilePositions))
  {
    std::cout << "Invalid move. Tiles must have the same color, shape, and share "
                 "the same column or row."
              << std::endl;
    return false;
  }
  else if (!board->checkSurroundingTilesMatch(row, column, tileToCheck))
  {
    std::cout << "Surrounding tiles do not match. Please try again." << std::endl;
    delete tileToCheck; // Avoid memory leak
    return false;
  }

  tilesToPlace.push_back(tileToCheck);
  tilePositions.push_back(std::make_pair(row, column));

  return true;
}

void Game::updateGameAfterTilePlacement(
    std::vector<Tile *> &tilesToPlace, std::vector<std::pair<int, int>> &tilePositions,
    int &numTiles)
{
  // Check if the tiles being placed have the same color, shape, and share the
  // same column or row
  if (!board->checkSameTypeTiles(tilesToPlace, tilePositions))
  {
    std::cout << "Invalid move. Tiles must have the same color, shape, and share "
                 "the same column or row."
              << std::endl;
  }
  else
  {
    ++numTiles;
    int row = tilePositions.back().first;
    int col = tilePositions.back().second;
    board->setTileAtPosition(row, col, tilesToPlace.back());
    board->displayBoard();
  }

  // Remove the tile from the player's hand
  if (!currentPlayer->getHand()->removeTile(tilesToPlace.back()))
  {
    std::cout << "Error removing tile from hand. Please try again." << std::endl;
  }
}

bool Game::placeTiles()
{
  int numTiles = 0;
  std::vector<Tile *> tilesToPlace;
  std::vector<std::pair<int, int>> tilePositions;
  bool activeTurn = false;

  while (!activeTurn && currentPlayer->getHand()->getSize() > 0)
  {
    currentPlayer->getHand()->displayHand();
    std::cout << "Place tile " << numTiles + 1
              << " using the format: place <tile> at <grid location>" << std::endl;
    std::cout << "Enter 'end' to end your turn or 'back' to return to previous menu"
              << std::endl;
    std::cout << "Type 'help' for help on placing tiles" << std::endl; // Added help message
    std::cout << "> ";

    std::vector<std::string> words = parsePlayerInput();

    // Check if the player wants to end their turn
    if (words.size() == 1 && words[0] == "end")
    {
      if (numTiles == 0)
      {
        std::cout << "You must place at least one tile." << std::endl;
        activeTurn = false;
      }
      else
      {
        std::cout << "Ending turn." << std::endl;
        activeTurn = true;
      }
    }
    // Check for the 'back' command first
    if (words.size() == 1 && words[0] == "back")
    {
      if (numTiles > 0)
      {
        std::cout << "You have already placed a tile. You must continue your move."
                  << std::endl;
        // activeTurn = false;
      }
      else
      {
        std::cout << "Returning to the previous menu." << std::endl;
        return false; // Directly exit the function, thereby exiting the loop
                      // and not ending the player's
      }
    }
    else
    {
      if (words[0] == "help")
      {
        placeTileHelp();
      }
      else if (words.size() != 4 || words[0] != "place" || words[3].length() >= 4)
      {
        std::cout << "Invalid command. Please try again." << std::endl;
      }
      else
      {
        if (validateTilePlacement(words, tilesToPlace, tilePositions))
        {
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
       ++k)
  {
    // Get the tile from the back of the bag
    Tile *tileFromBagPtr = bag->back();
    bag->remove_back();

    // Add the new tile to the player's hand
    currentPlayer->getHand()->addTile(tileFromBagPtr);
  }

  // output the player hand
  std::cout << "Player's hand after adding a new tile: ";
  currentPlayer->getHand()->displayHand();

  std::cout << "The size of the tile bag is now: " << bag->getSize() << std::endl;
  std::cout << "\n"
            << currentPlayer->getName() << "'s hand: ";
  currentPlayer->getHand()->displayHand();
  return true;
}

Tile *Game::createAndValidateTile(const std::string &tileStr)
{
  try
  {
    std::string color = std::string(1, tileStr[0]);
    std::string shape = tileStr.substr(1);
    Tile *tileToReplace = new Tile(color[0], stoi(shape));

    if (!currentPlayer->getHand()->containsTile(tileToReplace))
    {
      std::cout << "Tile not found in hand. Please try again." << std::endl;
      delete tileToReplace;
      return nullptr;
    }
    return tileToReplace;
  }
  catch (const std::invalid_argument &)
  {
    // Catch the exception if stoi fails (e.g., when the input is not a valid
    // integer)
    std::cout << "Invalid tile format. Please enter a valid tile." << std::endl;
    return nullptr;
  }
}

void Game::replaceTileAndUpdateHand(Tile *tileToReplace)
{
  currentPlayer->getHand()->removeTile(tileToReplace);
  bag->push_back(tileToReplace);
  // bag->shuffle();

  Tile *tileFromBag = bag->back();
  bag->remove_back();
  currentPlayer->getHand()->addTile(tileFromBag);
}

bool Game::replaceTile()
{
  std::cout << "Replace a tile using the format: replace <tile>" << std::endl;
  std::cout << "Enter 'back' to return to the previous menu" << std::endl;
  std::cout << "Type 'help' for help on replacing a tile" << std::endl;

  bool validInput = false;
  while (!validInput)
  {
    std::cout << "> ";
    std::string command;
    getline(std::cin, command);
    // Check for the 'back' command first
    if (std::cin.eof())
    {
      std::cout << "\n\nGoodbye" << std::endl;
      exit(EXIT_SUCCESS);
    }
    if (command == "back")
    {
      std::cout << "Returning to the previous menu." << std::endl;
      return false; // Directly exit the function, thereby exiting the loop and
                    // not ending the player's turn
    }
    else if (command == "help")
    {
      replaceTileHelp();
    }
    else
    {
      std::vector<std::string> words;
      size_t pos = 0;
      // Split the command into words based on spaces
      while ((pos = command.find(' ')) != std::string::npos)
      {
        words.push_back(command.substr(0, pos));
        command.erase(0, pos + 1);
      }
      words.push_back(command); // Add the last (or only) word

      // Check the command format
      if (words.size() == 2 && words[0] == "replace")
      {
        Tile *tileToReplace = createAndValidateTile(words[1]);
        if (tileToReplace != nullptr)
        {
          // If the tile is valid, proceed with replacement and update the hand
          replaceTileAndUpdateHand(tileToReplace);
          std::cout << "Tile replaced. Proceeding with the game." << std::endl;
          validInput = true; // Exit the loop
        }
        else
        {
          std::cout << "Invalid tile. Please try again." << std::endl;
        }
      }
      else
      {
        // If the command format is incorrect, inform the user and the loop will
        // repeat
        std::cout << "Invalid command. Please try again." << std::endl;
      }
    }
  }
  return true;
}

void Game::saveGame()
{
  // Save game
  std::string filename;
  std::cout << "\ntype 'help' for assistance";
  std::cout << "\nEnter the filename to save the game: ";
  std::getline(std::cin, filename);

  if (std::cin.eof())
  {
    std::cout << "\n\nGoodbye" << std::endl;
    exit(EXIT_SUCCESS);
  }

  if (filename == "help")
  {
    saveGameHelp();
    return;
  }

  // Prepend the "tests/" folder to the filename
  std::string fullFilename = "tests/" + filename;

  if (playerCount == 2)
  {
    // If there are only two players, pass them to saveGameState
    SaveGame::saveGameState(fullFilename, player1, player2, board, bag, currentPlayer);
  }
  else if (playerCount >= 3 && playerCount <= 4)
  {
    // If there are three or four players, create a vector of players and pass them
    std::vector<Player *> players;
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3); // Add player3
    if (playerCount == 4)
    {
      players.push_back(player4); // Add player4 if it exists
    }
    SaveGame::saveGameStateMultiplayer(fullFilename, players, board, bag, currentPlayer);
  }
  else
  {
    std::cout << "Invalid number of players. Cannot save game." << std::endl;
    return;
  }

  std::cout << "Game successfully saved" << std::endl;
}

void Game::declareWinner()
{
  std::cout << "Game over" << std::endl;
  std::cout << "\nScore for " << player1->getName() << ": "
            << player1->getScore() << std::endl;
  std::cout << "Score for " << player2->getName() << ": " << player2->getScore()
            << std::endl;
  std::cout << "Player ";

  if (player1->getScore() > player2->getScore())
  {
    std::cout << player1->getName() << " won!" << std::endl;
  }
  else if (player1->getScore() < player2->getScore())
  {
    std::cout << player2->getName() << " won!" << std::endl;
  }
  else
  {
    std::cout << "It's a draw!" << std::endl;
  }
  std::cout << "\n\nGoodbye" << std::endl;
  exit(0);
}

void Game::displayHelpMessageGameMenu()
{
  std::cout << "\nType 'help' for more information.\n";
  std::cout << "1. Place tiles: Allows you to place tiles on the board.\n";
  std::cout << "2. Replace a tile: Allows you to replace a tile in your hand.\n";
  std::cout << "3. Save game: Saves the current game state.\n";
  std::cout << "4. Quit game: Quits the game.\n";
}

void Game::placeTileHelp()
{
  std::cout << "\n=== Place Tiles Help ===\n";
  std::cout << "To place tiles on the board, follow these steps:\n";
  std::cout << "1. Enter the command in the format: place <tile> <position>\n";
  std::cout << "   - <tile>: The tile you want to place on the board.\n";
  std::cout << "             - the colour of the tile is determined by the letter\n";
  std::cout << "                  - R: Red\n";
  std::cout << "                  - O: Orange\n";
  std::cout << "                  - Y: Yellow\n";
  std::cout << "                  - G: Green\n";
  std::cout << "                  - B: Blue\n";
  std::cout << "                  - P: Purple\n";
  std::cout << "             - the shape of the tile is determined by the number\n";
  std::cout << "                  - 1: Circle\n";
  std::cout << "                  - 2: 4 Point Star\n";
  std::cout << "                  - 3: Diamond\n";
  std::cout << "                  - 4: Square\n";
  std::cout << "                  - 5: 6 Point Star\n";
  std::cout << "                  - 6: Clover\n";
  std::cout << "   - <position>: The position on the board where you want to place the tile.\n";
  std::cout << "2. The <tile> should be a valid tile from your hand.\n";
  std::cout << "3. The <position> are the coordinates on the board.\n";
  std::cout << "   Example - place A6 at B6\n";
  std::cout << "4. After placing the tile, the game will proceed.\n";
  std::cout << "   - If the placement is valid, your hand will be updated.\n";
  std::cout << "   - If the placement is invalid, an error message will be displayed.\n";
  std::cout << "5. Repeat the steps to place more tiles or choose another action.\n";
  std::cout << "   - back: return to previous menu.\n";
  std::cout << "   - end : end your turn, after placing a tile.\n";
  std::cout << "\n";
}

void Game::replaceTileHelp()
{
  std::cout << "\n=== Replace Tile Help ===\n";
  std::cout << "To replace a tile in your hand, follow these steps:\n";
  std::cout << "1. Enter the command in the format: replace <tile>\n";
  std::cout << "   - <tile>: The tile you want to replace in your hand.\n";
  std::cout << "2. The <tile> should be a valid tile from your hand.\n";
  std::cout << "3. After replacing the tile, a new tile will be drawn from the bag.\n";
  std::cout << "4. Repeat the steps to replace more tiles or choose another action.\n";
  std::cout << "   - back: return to previous menu.\n";
  std::cout << "\n";
}

void Game::saveGameHelp()
{
  std::cout << "\n=== Save Game Help ===" << std::endl;
  std::cout << "To save the current game state, follow these steps:" << std::endl;
  std::cout << "1. Enter the filename you want to save the game with." << std::endl;
  std::cout << "2. The game state will be saved with the specified filename." << std::endl;
  std::cout << "3. You can load the saved game later using the 'Load Game' option from the main menu." << std::endl;
  std::cout << std::endl;
}

// Function to convert a string to lowercase
std::string Game::toLower(std::string &str)
{
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
                 { return std::tolower(c); });
  return result;
}
