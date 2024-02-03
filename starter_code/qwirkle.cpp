#include "LinkedList.h"
#include "qwirkle.h"
#include "Tile.h"
#include "Node.h"
#include "Board.h"
#include "TileCodes.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <limits>
#include <unordered_map>
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
bool checkSurroundingTilesMatch(const std::vector<std::vector<Tile *>> &board, int row, int col, Tile *tile);
bool checkSameTypeTiles(const std::vector<Tile *> &tilesToPlace, const std::vector<std::pair<int, int>> &positions);


int main(void)
{
    LinkedList *list = new LinkedList();
    delete list;

    // std::cout << "TODO: Implement Qwirkle!" << std::endl;
    // 2.1 Launch
    cout << "\n Welcome to Qwirkle!" << endl;
    cout << "-----------------------" << endl;

    int choice = 0;
    bool quit = false;

    while (!quit)
    {
        displayMenu();
        cout << "> ";
        cin >> choice;

        // If the extraction fails
        if (cin.fail())
        {
            // Clear the error state
            cin.clear();

            // Ignore the rest of the line
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Invalid choice. Please enter a valid option." << endl;
            continue;
        }

        if (choice == 1)
        {
            cout << "\nStarting a New Game" << endl;
            startNewGame();
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
    cout << "-----" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Show student information)" << endl;
    cout << "4. Quit \n" << endl;
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
    cout << "Name: Michael Moon" << endl;
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
    // Number of players
    // int numPlayers = 2;

    // Initialize and shuffle the tile bag
    cout << "making the bag" << std::endl;
    LinkedList *bag = new LinkedList(); // Instantiate LinkedList
    bag->initializeAndShuffleBag();     // Populate the bag

    // Create player names
    string playerName1, playerName2;
    do
    {
        cout << "\nEnter a name for player 1 (uppercase characters only): \n";
        cout << "> ";
        cin >> playerName1;
    } while (!isValidPlayerName(playerName1));

    do
    {
        cout << "\nEnter a name for player 2 (uppercase characters only): \n";
        cout << "> ";
        cin >> playerName2;
    } while (!isValidPlayerName(playerName2));

    // Create player hands
    LinkedList *playerHand1 = new LinkedList();
    initializePlayerHand(playerHand1, bag); // Pass the address of tileBag

    // log the hand
    std::cout << "Player 1's hand: ";
    playerHand1->displayHand();

    LinkedList *playerHand2 = new LinkedList();
    initializePlayerHand(playerHand2, bag); // Pass the address of tileBag

    // log the hand
    std::cout << "Player 2's hand: ";
    playerHand2->displayHand();

    // Create players
    Player *player1 = new Player(playerName1, 0, playerHand1);
    Player *player2 = new Player(playerName2, 0, playerHand2);

    cin.ignore();
    cout << "\nLet's Play!" << endl;

    // Initialize the board
    Board *board = new Board(); // Instantiate Board

    // ADD MOTOMICHI'S CODE HERE to determine the starting player
    //TODO: MIC ADD IT HERE


    // Instantiate Game with the modified parameters
    Game *game = new Game(player1, player2, bag, board, player1); // Pass player1, player2, bag, and currentPlayer

    // Call the correct method
    game->launchGame();
}

void initializePlayerHand(LinkedList *playerHand, LinkedList *bag)
{
    // Draw tiles from the tile bag and add them to the player's hand until there are 6 tiles
    while (playerHand->getSize() < 6 && !bag->isEmpty())
    {
        // Get the tile pointer from the back of the bag
        Tile* tileFromBagPtr = bag->back();

        // bag->pop_back();
        // Replaced pop_back with function that preserves the tile at the pointer, instead of deleting it.
        bag->remove_back();

        // Add the tile pointer directly to the player's hand
        playerHand->addTile(tileFromBagPtr);
    }
}
