#include "Game.h"
#include "Tile.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

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
    LinkedList *bag = new LinkedList(); // Bag initialized here

    // Read and store each line of the file
    string plyr1Name, plyr1Score, plyr1Hand, plyr2Name, plyr2Score, plyr2Hand, boardSize, boardState, bagContents, currentPlyr;
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

    // Output each line (for debugging purposes)
    cout << "Player 1 Name : " << plyr1Name << endl;
    cout << "Player 1 Score: " << plyr1Score << endl;
    cout << "Player 1 Hand: " << plyr1Hand << endl;
    cout << "Player 2 Name :" << plyr2Name << endl;
    cout << "Player 2 Score :" << plyr2Score << endl;
    cout << "Player 2 Hand :" << plyr2Hand << endl;
    cout << "Board Size :" << boardSize << endl;
    cout << "Board Positioning :" << boardState << endl;
    cout << "Bag Contents :" << bagContents << endl;
    cout << "Current Player :" << currentPlyr << endl;

    // Load tile bag contents
    loadBagContents(bag, bagContents);

    // Debugging output
    cout << "Bag Contents: " << bagContents << endl;

    vector<Player *> players;

    // Load player 1
    loadPlayer(bag, plyr1Name, stoi(plyr1Score), plyr1Hand, players);

    // Load player 2
    loadPlayer(bag, plyr2Name, stoi(plyr2Score), plyr2Hand, players);

    // Load board state
    board = loadBoardState(boardState);

    // Debugging output
    cout << "Board State: " << boardState << endl;

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
        cout << "Error: Current player not found." << endl;
        return nullptr;
    }

    // Debugging output
    cout << "Current Player: " << currentPlyr << endl;

    // Close the file
    file.close();

    // Create and return game object
    return new Game(players[0], players[1], bag, board, currentPlayer);
}

void LoadGame::loadPlayer(LinkedList *bag, string playerName, int playerScore, string playerHandStr, vector<Player *> &players)
{
    // Load player's hand
    LinkedList *playerHand = loadHand(playerHandStr, bag);

    // Create player object and add to vector
    players.push_back(new Player(playerName, playerScore, playerHand));
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
    // Load player's hand from string representation and return LinkedList object
    LinkedList *hand = new LinkedList();
    istringstream ss(handString);
    string token;
    while (getline(ss, token, ',')) // Assuming handString is comma-separated
    {
        char colour = token[0];
        int shape = stoi(token.substr(1)); // Assuming the shape is represented by the digits after the color

        // Create a Tile object with the specified color and shape
        Tile *tile = new Tile(colour, shape);

        // Attempt to remove the tile from the bag
        bool tileRemoved = bag->removeTile(tile);

        // Debugging output
        cout << "Removing tile: " << tile->toString() << " from bag... ";
        if (tileRemoved)
        {
            cout << "Successfully removed." << endl;
        }
        else
        {
            cout << "Tile not found in bag." << endl;
        }

        // Check if the tile was successfully removed
        if (tileRemoved)
        {
            // If the tile was removed from the bag, add it to the player's hand
            hand->push_back(tile);
        }
        else
        {
            // If the tile couldn't be added to the hand, delete it to avoid memory leaks
            cout << "Error: Invalid tile in player hand." << endl;
            delete tile;
        }
    }

    return hand;
}

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
        // Output the token for debugging
        cout << "Token: " << token << endl;

        // Find the '@' character to separate row and column indices
        size_t atPos = token.find('@');
        if (atPos != string::npos && atPos + 1 < token.size())
        {
            // Extract color, shape, row, and column information
            string colorShape = token.substr(0, atPos);
            char colour = colorShape[0];
            string shapeStr = colorShape.substr(1); // Remove the first character (color) to get the shape string

            // Extract only numeric part from the shape string
            string numericShape = shapeStr;
            numericShape.erase(remove_if(numericShape.begin(), numericShape.end(), [](char c)
                                         { return !isdigit(c); }),
                               numericShape.end());
            int shape = stoi(numericShape); // Convert numeric shape string to integer

            int row = token[atPos + 1] - 'A';
            int col = stoi(token.substr(atPos + 2)) - 1;

            // Output the extracted information for debugging
            cout << "Colour: " << colour << ", Shape: " << shape << ", Row: " << row << ", Col: " << col << endl;

            // Create a new tile object
            Tile *tile = new Tile(colour, shape);

            // Place the tile on the board
            board->placeTile(tile, row, col);
        }
        else
        {
            // Handle error case where '@' is not found
            cerr << "Error: Invalid token format" << endl;
        }
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