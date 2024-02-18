#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Game.h"
#include "LoadGame.h"
#include "Tile.h"

Game *LoadGame::loadGame(std::string filename)
{
#include <fstream>

  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cout << "Error: File '" << filename << "' not found." << std::endl;
    return nullptr;
  }

  // Check if the file is empty
  if (file.peek() == std::ifstream::traits_type::eof())
  {
    std::cout << "Error: File '" << filename << "' is empty." << std::endl;
    return nullptr;
  }

  std::cout << "\nLoading Game..." << std::endl;

  std::string line;

  // Initialize game components
  Board *board = new Board();
  LinkedList *bag = new LinkedList(); // Bag initialized here
  bag->initializeAndShuffleBag();     // Reset the linked list

  // Read and store each line of the file
  std::string plyr1Name, plyr1Score, plyr1Hand, plyr2Name, plyr2Score, plyr2Hand,
      boardSize, boardState, bagContents, currentPlyr;
  getline(file, plyr1Name);
  getline(file, plyr1Score);
  getline(file, plyr1Hand);
  getline(file, plyr2Name);
  getline(file, plyr2Score);
  getline(file, plyr2Hand);
  getline(file, boardSize);
  getline(file, boardState);
  getline(file, bagContents);
  getline(file, currentPlyr);

  // Load tile bag contents
  loadBagContents(bag, bagContents);
  // bag = loadTileBag(bagContents);

  // Initialize vector to store players
  std::vector<Player *> players;

  // Load player 1
  loadPlayer(bag, plyr1Name, stoi(plyr1Score), plyr1Hand, players);

  // Load player 2
  loadPlayer(bag, plyr2Name, stoi(plyr2Score), plyr2Hand, players);

  // Load board state
  board = loadBoardState(boardState);
  bag = loadTileBag(bagContents);

  // Load current player
  Player *currentPlayer = nullptr;
  for (Player *player : players)
  {
    if (player->getName() == currentPlyr)
    {
      currentPlayer = player;
      break;
    }
  }
  if (currentPlayer == nullptr)
  {
    std::cout << "Error: Current player not found." << std::endl;
    return nullptr;
  }

  // Close the file
  file.close();

  // Create and return game object
  return new Game(players[0], players[1], bag, board, currentPlayer);
}

void LoadGame::loadPlayer(LinkedList *bag, std::string playerName, int playerScore,
                          std::string playerHandStr, std::vector<Player *> &players)
{
  // Load player's hand
  LinkedList *playerHand = loadHand(playerHandStr, bag);

  // Create player object and add to vector
  players.push_back(new Player(playerName, playerScore, playerHand));
}

LinkedList *LoadGame::loadTileBag(std::string bagContents)
{
  // Load tile bag from string representation and return LinkedList object

  LinkedList *bag = new LinkedList();
  std::istringstream ss(bagContents);

  char delimiter = ','; // Define the delimiter as a comma
  std::string token;
  while (getline(ss, token, delimiter)) // Use getline with the comma delimiter
  {
    char colour;
    int shape;

    // Extract color and shape information from the token
    std::istringstream tokenStream(token);
    tokenStream >> colour >> shape;

    // Create a new tile object
    Tile *tile = new Tile(colour, shape);

    // Add the tile to the bag
    bag->push_back(tile);
  }
  return bag;
}

LinkedList *LoadGame::loadHand(std::string handString, LinkedList *bag)
{
  // Load player's hand from string representation and return LinkedList object
  LinkedList *hand = new LinkedList();
  std::istringstream ss(handString);
  std::string token;
  while (getline(ss, token, ',')) // Assuming handString is comma-separated
  {
    char colour = token[0];
    int shape = stoi(token.substr(
        1)); // Assuming the shape is represented by the digits after the color

    // Create a Tile object with the specified color and shape
    Tile *tile = new Tile(colour, shape);

    // Attempt to remove the tile from the bag
    bool tileRemoved = bag->removeTile(tile);

    // Check if the tile was successfully removed
    if (tileRemoved)
    {
      // If the tile was removed from the bag, add it to the player's hand
      hand->push_back(tile);
    }
    else
    {
      // If the tile couldn't be added to the hand, delete it to avoid memory
      // leaks
      std::cout << "Error: Invalid tile in player hand." << std::endl;
      delete tile;
    }
  }

  return hand;
}

Board *LoadGame::loadBoardState(std::string boardState)
{
  // Create a new Board object
  Board *board = new Board();

  // Parse the board state string and update the board object accordingly
  std::stringstream ss(boardState);
  std::string token;

  // Iterate through each token separated by comma
  while (getline(ss, token, ','))
  {
    // Find the '@' character to separate row and column indices
    size_t atPos = token.find('@');
    if (atPos != std::string::npos && atPos + 1 < token.size())
    {
      // Extract color, shape, row, and column information
      std::string colorShape = token.substr(0, atPos);
      char colour = ' '; // Initialize colour with a default value

      bool colorFound = false;
      // Extract the color part from the colorShape string
      for (char c : colorShape)
      {
        if (isalpha(c)) // Check if the character is alphabetic (a letter)
        {
          colour = c;        // Set the colour if the character is a letter
          colorFound = true; // Set the flag to indicate that color is found
        }
      }

      if (!colorFound) // Check if the colour is still the default value
      {
        // Handle error case where no color is found
        std::cerr << "Error: No color found in token: " << token << std::endl;
      }

      // Extract the shape part from the colorShape string
      std::string shapeStr = "";
      bool foundAtSymbol = false; // Flag to track if '@' symbol is found

      for (char c : colorShape)
      {
        if (isdigit(c)) // Check if the character is a digit
        {
          if (!foundAtSymbol) // Check if '@' symbol is not found yet
          {
            shapeStr +=
                c; // Append the character to the shape string if it's a digit
          }
        }
        else if (c == '@') // Handle '@' symbol
        {
          foundAtSymbol = true; // Set flag to true when '@' symbol is found
        }
      }
      // Convert shape string to integer
      int shape;

      // Check if the shape string is not empty
      bool shapeFound = false;
      try
      {
        shape = stoi(shapeStr);
        shapeFound = true;
      }
      catch (const std::invalid_argument &ia)
      {
        std::cerr << "Error: Invalid shape value in token: " << token << std::endl;
      }

      // Extract row and column indices
      if (shapeFound)
      {
        int row = token[atPos + 1] - 'A';
        int col = stoi(token.substr(atPos + 2));

        // Create a new tile object
        Tile *tile = new Tile(colour, shape);

        // Place the tile on the board
        board->placeTile(tile, row, col);
      }
      else
      {
        std::cerr << "Error: Invalid shape" << std::endl;
      }
    }
    else
    {
      // Handle error case where '@' is not found
      std::cerr << "Error: Invalid token format" << std::endl;
    }
  }

  // Return the updated board object
  return board;
}

// Load bag contents from string representation and update the bag object
void LoadGame::loadBagContents(LinkedList *bag, std::string bagContents)
{
  // Check if the bag pointer is null
  if (bag == nullptr)
  {
    std::cerr << "Error: Bag pointer is null." << std::endl;
    return;
  }

  // Parse the bag contents string and update the bag object accordingly
  std::stringstream ss(bagContents);
  std::string token;

  // Iterate through each token separated by comma
  while (getline(ss, token, ','))
  {
    // Extract tile information from the token
    char colour = token[0];
    int shape = token[1] - '0';

    // Create a new tile object
    Tile *tile = new Tile(colour, shape);

    // Add the tile to the bag
    bag->push_back(tile);
  }
}

Game *LoadGame::loadMultiplayerGame(std::string filename)
{
  // Open the file
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cout << "Error: File '" << filename << "' not found." << std::endl;
    return nullptr;
  }

  // Check if the file is empty
  if (file.peek() == std::ifstream::traits_type::eof())
  {
    std::cout << "Error: File '" << filename << "' is empty." << std::endl;
    return nullptr;
  }

  std::cout << "\nLoading Game..." << std::endl;

  // Initialize game components
  Board *board = new Board();
  LinkedList *bag = new LinkedList(); // Bag initialized here
  bag->initializeAndShuffleBag();     // Reset the linked list

  // Read and store each line of the file
  std::string playerName, playerScore, playerHand, boardSize, boardState, bagContents, currentPlayer;
  std::vector<Player *> players;

  while (getline(file, playerName))
  {
    // Read player details
    getline(file, playerScore);
    getline(file, playerHand);
    // Load player
    loadPlayer(bag, playerName, std::stoi(playerScore), playerHand, players);
  }

  // Read remaining game state
  getline(file, boardSize);
  getline(file, boardState);
  getline(file, bagContents);
  getline(file, currentPlayer);

  // Load board state
  board = loadBoardState(boardState);
  bag = loadTileBag(bagContents);

  // Find current player
  Player *currentPlayerPtr = nullptr;
  for (Player *player : players)
  {
    if (player->getName() == currentPlayer)
    {
      currentPlayerPtr = player;
      break;
    }
  }

  if (currentPlayerPtr == nullptr)
  {
    std::cerr << "Error: Current player not found." << std::endl;
    return nullptr;
  }

  // Close the file
  file.close();

  // Create and return game object
  return new Game(players, bag, board, currentPlayerPtr);
}
