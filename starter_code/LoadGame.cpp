#include "Game.h"
#include "Tile.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

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

    cout << "\nLoading Game..." << endl;

    string line;

    // Initialize game components
    Board *board = new Board();
    LinkedList *bag = new LinkedList(); // Bag initialized here
    bag->initializeAndShuffleBag();     // Reset the linked list

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

    // Load tile bag contents
    loadBagContents(bag, bagContents);
    //bag = loadTileBag(bagContents);

    // Initialize vector to store players
    vector<Player *> players;

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
        cout << "Error: Current player not found." << endl;
        return nullptr;
    }

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

LinkedList *LoadGame::loadTileBag(string bagContents)
{
    // Load tile bag from string representation and return LinkedList object
    LinkedList *bag = new LinkedList();
    istringstream ss(bagContents);

    char delimiter = ','; // Define the delimiter as a comma
    string token;
    while (getline(ss, token, delimiter)) // Use getline with the comma delimiter
    {
        char colour;
        int shape;

        // Extract color and shape information from the token
        istringstream tokenStream(token);
        tokenStream >> colour >> shape;

        // Create a new tile object
        Tile *tile = new Tile(colour, shape);

        // Add the tile to the bag
        bag->push_back(tile);
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
        // Find the '@' character to separate row and column indices
        size_t atPos = token.find('@');
        if (atPos != string::npos && atPos + 1 < token.size())
        {
            // Extract color, shape, row, and column information
            string colorShape = token.substr(0, atPos);
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
                cerr << "Error: No color found in token: " << token << endl;
            }

            // Extract the shape part from the colorShape string
            string shapeStr = "";
            bool foundAtSymbol = false; // Flag to track if '@' symbol is found

            for (char c : colorShape)
            {
                if (isdigit(c)) // Check if the character is a digit
                {
                    if (!foundAtSymbol) // Check if '@' symbol is not found yet
                    {
                        shapeStr += c; // Append the character to the shape string if it's a digit
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
                cerr << "Error: Invalid shape value in token: " << token << endl;
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
                cerr << "Error: Invalid shape" << endl;
            }
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
    // Check if the bag pointer is null
    if (bag == nullptr)
    {
        cerr << "Error: Bag pointer is null." << endl;
        return;
    }

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