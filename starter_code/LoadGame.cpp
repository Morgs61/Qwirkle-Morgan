#include "Game.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "LoadGame.h"

using std::getline;
using std::ifstream;
using std::istringstream;
using std::stoi;
using std::string;
using std::vector;

Game *LoadGame::loadGame(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: File '" << filename << "' not found." << endl;
        return nullptr;
    }

    // Check if the file is empty
    if (file.peek() == ifstream::traits_type::eof())
    {
        cout << "Error: File '" << filename << "' is empty." << endl;
        return nullptr;
    }

    cout << "Loading Game..." << endl;

    string line;

    // Initialize game components
    Board *board = new Board();
    LinkedList *bag = new LinkedList();

    int playerCount = 2; // Default player count

    vector<Player *> players;
    for (int i = 0; i < playerCount; i++)
    {
        string playerName, playerHand;
        int playerScore;

        // Read player details
        if (!getline(file, playerName) || !getline(file, line) || !getline(file, playerHand))
        {
            cout << "Error: Invalid file format." << endl;
            return nullptr;
        }
        playerScore = stoi(line);

        // Debugging output
        cout << "Player Name: " << playerName << ", Score: " << playerScore << ", Hand: " << playerHand << endl;

        // Load player's hand
        LinkedList *hand = loadHand(playerHand, bag);

        // Create player object and add to vector
        players.push_back(new Player(playerName, playerScore, hand));
    }

    // Load board state
    if (!getline(file, line))
    {
        cout << "Error: Invalid file format." << endl;
        return nullptr;
    }
    board = loadBoardState(line);

    // Debugging output
    cout << "Board State: " << line << endl;

    // Load tile bag contents
    if (!getline(file, line))
    {
        cout << "Error: Invalid file format." << endl;
        return nullptr;
    }
    loadBagContents(bag, line);

    // Debugging output
    cout << "Bag Contents: " << line << endl;

    // Load current player
    string currentPlayerName;
    if (!getline(file, currentPlayerName))
    {
        cout << "Error: Invalid file format." << endl;
        return nullptr;
    }
    Player *currentPlayer = nullptr;
    for (Player *player : players)
    {
        if (player->getName() == currentPlayerName)
        {
            currentPlayer = player;
            break;
        }
    }
    if (currentPlayer == nullptr)
    {
        cout << "Error: Current player not found." << endl;
        return nullptr;
    }

    // Debugging output
    cout << "Current Player: " << currentPlayerName << endl;

    // Close the file
    file.close();

    // Create and return game object
    return new Game(players[0], players[1], bag, board, currentPlayer);
}

LinkedList *LoadGame::loadTileBag(ifstream &file)
{
    // Load tile bag from file and return LinkedList object
    string line;         // Declare the variable to store the line from the file
    getline(file, line); // Read a line from the file
    istringstream ss(line);
    LinkedList *bag = new LinkedList();
    char colour;
    int shape;
    while (ss >> colour >> shape)
    {
        bag->push_back(new Tile(colour, shape));
    }
    return bag;
}

LinkedList *LoadGame::loadHand(string handString, LinkedList *bag)
{
    cout << "Hand String: " << handString << endl;

    // Load player's hand from string representation and return LinkedList object
    LinkedList *hand = new LinkedList();
    istringstream ss(handString);
    char colour;
    int shape;
    while (ss >> colour >> shape)
    {
        // Create a Tile object with the specified color and shape
        Tile *tile = new Tile(colour, shape);

        // Attempt to remove the tile from the bag
        bool tileRemoved = bag->removeTile(tile);

        // Check if the tile was successfully removed
        if (tileRemoved)
        {
            hand->push_back(tile);
        }
        else
        {
            cout << "Error: Invalid tile in player hand." << endl;
            delete tile; // Since the tile couldn't be added to the hand, we need to delete it to avoid memory leaks
        }
    }
    return hand;
}

// Load board state from string representation and update the board object
Board *LoadGame::loadBoardState(string boardState)
{
    // Create a new Board object
    Board *board = new Board();

    // Parse the board state string and update the board object accordingly
    stringstream ss(boardState);
    string token;

    // Iterate through each token separated by comma
    while (getline(ss, token, ','))
    {
        // Extract tile information from the token
        char colour = token[0];
        int shape = token[1] - '0';
        int row = token[3] - 'A';
        int col = stoi(token.substr(4)) - 1;

        // Create a new tile object
        Tile *tile = new Tile(colour, shape);

        // Place the tile on the board
        board->placeTile(tile, row, col);
    }

    // Return the updated board object
    return board;
}

// Load bag contents from string representation and update the bag object
void LoadGame::loadBagContents(LinkedList *bag, string bagContents)
{
    // Parse the bag contents string and update the bag object accordingly
    stringstream ss(bagContents);
    string token;

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