#include "LinkedList.h"
#include "qwirkle.h"
#include "Tile.h"
#include "Node.h"
#include "Board.h"
#include "TileCodes.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
#define EXIT_SUCCESS 0

void displayMenu();
bool isValidPlayerName(const string &name);
void displayStudentInformation();
void loadGame();



int main(void)
{
    LinkedList *list = new LinkedList();
    delete list;

    // std::cout << "TODO: Implement Qwirkle!" << std::endl;
    // 2.1 Launch
    cout << "Welcome to Qwirkle!" << endl;
    cout << "-----------------------" << endl;

    int choice = 0;
    bool quit = false;

    while (!quit)
    {
        displayMenu();
        cout << "> ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "\nStarting a New Game" << endl;
            startNewGame();
            /**  Add code to proceed with normal gameplay
2.3.10 Special Operation: Starting a New Game
When a new game is started, a special sequence of operations must be conducted:
1. Create the ordering for the tile bag
2. Set up the initial player hands
3. Start with an empty board, with player 1 as the starting player
You will need to devise your own algorithm to “shuffle” the bag of tiles to create a “random” initial order. This
is left up to your own invention. The lectures will talk about randomness is C++ programs.
Then the initial tiles are added to the player’s hands. 6 tiles are drawn from the tile bag and placed in the 1st
player’s hand. Then 6 tiles are drawn from the tile bag and placed in the 2nd player’s hand.
Finally, the board starts with no tiles placed, so that when displayed, it should be empty.


            **/
        }
        else if (choice == 2)
        {
            cout << "Loading Game..." << endl;
            loadGame();
            // Add code for loading a game
        }
        else if (choice == 3)
        {

            displayStudentInformation();
        }
        else if (choice == 4)
        {
            cout << "Quitting the game. Goodbye!" << endl;
            quit = true;
        }
        else
        {
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return EXIT_SUCCESS;
}

void displayMenu()
{
    cout << "\nMenu" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Show student information)" << endl;
    cout << "4. Quit" << endl;
}

// Function to check if a player name is valid
bool isValidPlayerName(const string &name)
{
    for (char c : name)
    {
        // check if we can use this
        if (!isupper(c) || !isalpha(c))
        {
            cout << "Invalid name. Please enter uppercase letters only." << endl;
            return false;
        }
    }
    return true;
}

// 2.2.3 Credits - Need members to add their details
void displayStudentInformation()
{

    cout << "--------------------------------------" << endl;
    // Hardcoded information for 4 students
    cout << "\nName: Michael Moon" << endl;
    cout << "Student ID: s3523025" << endl;
    cout << "Email: s3523025@student.rmit.edu.au" << endl;

    cout << "\nName: Alexander Cowan" << endl;
    cout << "Student ID: s3863084" << endl;
    cout << "Email: s3863084@student.rmit.edu.au" << endl;

    cout << "\nName: Michael Whyte" << endl;
    cout << "Student ID: s3851481" << endl;
    cout << "Email: S3851481@student.rmit.edu.au" << endl;

    cout << "\nName: Morgan Cassar" << endl;
    cout << "Student ID: s3858530" << endl;
    cout << "Email: s3858530@student.rmit.edu.au" << endl;
    cout << "--------------------------------------" << endl;
    cout << "\n<Main Menu>" << endl;
}

void loadGame()
{
    cout << "\nEnter the filename from which to load a game:" << endl;
    string filename;
    cout << "> ";
    cin >> filename;

    // Attempt to open the file4
    std::ifstream file(filename);

    if (file.good() && file.is_open())
    {
        // File exists and is open

        // Add validation for the file format (replace with your actual format check logic)
        // For example, if you have a specific format, check if it matches
        // Here, we assume a simple check by reading a line from the file
        string line;
        if (getline(file, line))
        {
            cout << "\nQwirkle game successfully loaded." << endl;
            // Add code to load the game (replace with your actual game loading logic)
            // For example, you might read data from the file and restore the game state
            // ...

            // Continue with normal gameplay (replace with your actual gameplay logic)
            // ...
        }
        else
        {
            cout << "\nInvalid file format. Unable to load the game." << endl;
        }

        // Close the file
        file.close();
    }
    else
    {
        cout << "\nFile does not exist or could not be opened. Unable to load the game." << endl;
    }
}

void startNewGame()
{
    // Player 1
    string player1;
    do
    {
        cout << "\nEnter a name for player 1 (uppercase characters only): ";
        cin >> player1;
    } while (!isValidPlayerName(player1));

    // Player 2
    string player2;
    do
    {
        cout << "\nEnter a name for player 2 (uppercase characters only): ";
        cin >> player2;
    } while (!isValidPlayerName(player2));
    cin.ignore();
    cout << "\nLet's Play!" << endl;

    // Initialize and shuffle the tile bag
    std::vector<Tile> tileBag;
    initializeTileBag(tileBag);

    // Initialize player hands
    LinkedList player1Hand;
    LinkedList player2Hand;
    initializePlayerHands(player1Hand, player2Hand, tileBag);

    // Print the hands of each player
    void printTileBag(const std::vector<Tile>& tileBag);

    cout << "\n"
        << player1 << "'s hand: ";
    player1Hand.displayHand();

    cout << "\n"
        << player2 << "'s hand: ";
    player2Hand.displayHand();

    // Initialize the board
    std::vector<std::vector<Tile *>> board;
    initializeBoard(board);

    // Display the board
    displayBoard(board);
    printTileBag(tileBag);
    
    
//Player 1's turn
    while(!player1Hand.isEmpty() && !player2Hand.isEmpty())
{
    for (auto& player : {std::make_pair(player1, &player1Hand), std::make_pair(player2, &player2Hand)}) {
        cout << "\n" << player.first << "'s turn" << endl;
        cout << player.first << "'s hand`1: ";
        player.second->displayHand();

        cout << "Place a tile using the format: place <tile> at <grid location>" << endl;
        cout << ">";
        // Add this line to clear the input buffer
        
        string command;
        getline(cin, command);

    // Split the command into words
    vector<string> words;
    size_t pos = 0;
    while ((pos = command.find(' ')) != string::npos) {
        words.push_back(command.substr(0, pos));
        command.erase(0, pos + 1);
    }
    words.push_back(command);

    // Check that the command is correctly formatted
    if (words.size() != 4 || words[0] != "place" || words[3].length() != 2) {
        cout << "Invalid command. Please try again." << endl;
        continue;
    }

    // Parse the tile and location from the command
string tile = words[1];
string location = words[3];

// Convert the grid location to row and column
int row = location[0] - 'A';
int column = location[1] - '1';

// Place the tile onto the board
board[row][column] = new Tile(tile[0], tile[1]);

// Remove the tile from the player's hand
player.second->removeTile(new Tile(tile[0], tile[1]));

// Display an error message if the tile was not found in the player's hand
bool removed = true; 
if (!removed) {
    cout << "Tile not found in hand. Please try again." << endl;
    continue;
}

// Draw a new tile from the tile bag and add it to the player's hand
if (!tileBag.empty()) {
    // Get the tile from the back of the bag
    Tile tileFromBag = tileBag.back();
    tileBag.pop_back();

    // Create a new tile with the values from the tile drawn from the bag
    Tile* newTile = new Tile(tileFromBag.colour, tileFromBag.shape);

    // Add the new tile to the player's hand
    player.second->addTileToHand(newTile);
}

// Display the board and the player's hand
displayBoard(board);
cout << "\n" << player.first << "'s hand: ";
player.second->displayHand();

// Display the board and the player's hand
displayBoard(board);
        cout << "\n" << player.first << "'s hand: ";
        player.second->displayHand();
    }
}
}
void initializeTileBag(std::vector<Tile> &tileBag)
{
    // Get definitions from TileCodes.h
    char colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int shapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

    // Create all combinations of colours and shapes
    for (char colour : colours)
    {
        for (int shape : shapes)
        {
            // Add two tiles of each type to the tile bag
            tileBag.push_back({colour, shape});
            tileBag.push_back({colour, shape});
        }
    }

    // Shuffle the tile bag
    shuffleTileBag(tileBag);
}

void shuffleTileBag(std::vector<Tile> &tileBag)
{
    // Shuffle the tile bag
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(tileBag.begin(), tileBag.end(), rng);
}

void initializePlayerHands(LinkedList &player1Hand, LinkedList &player2Hand, std::vector<Tile> &tileBag)
{
    // Draw tiles from the tile bag and add them to player hands
    // Example
    for (int i = 0; i < 6; ++i)
    {
        player1Hand.addTileToHand(new Tile(tileBag.back()));
        tileBag.pop_back();
    }

    for (int i = 0; i < 6; ++i)
    {
        player2Hand.addTileToHand(new Tile(tileBag.back()));
        tileBag.pop_back();
    }
}