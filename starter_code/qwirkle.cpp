#include "LinkedList.h"
#include "qwirkle.h"
#include "Tile.h"
#include "Node.h"
#include "Board.h"
#include "TileCodes.h"
#include "GameSave.h"
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
    string player1Name;
    do
    {
        cout << "\nEnter a name for player 1 (uppercase characters only): ";
        cin >> player1Name;
    } while (!isValidPlayerName(player1Name));

    // Player 2
    string player2Name;
    do
    {
        cout << "\nEnter a name for player 2 (uppercase characters only): ";
        cin >> player2Name;
    } while (!isValidPlayerName(player2Name));
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
    void printTileBag(std::vector<Tile> & tileBag);

    cout << "\n"
         << player1Name << "'s hand: ";
    player1Hand.displayHand();

    cout << "\n"
         << player2Name << "'s hand: ";
    player2Hand.displayHand();

    // Initialize the board
    std::vector<std::vector<Tile *>> board;
    initializeBoard(board);

    // Display the board
    displayBoard(board);
    printTileBag(tileBag);

    // Initialize the current player
    Player player1(player1Name, 0, &player1Hand);
    Player player2(player2Name, 0, &player2Hand);
    Player *currentPlayer = &player1; // Start with Player 1

    while (!player1Hand.isEmpty() && !player2Hand.isEmpty())
    {
        cout << "\n"
             << currentPlayer->getName() << "'s turn" << endl;
        cout << currentPlayer->getName() << "'s hand: ";
        (currentPlayer == &player1) ? player1Hand.displayHand() : player2Hand.displayHand();

        bool validActionSelected = false;
        while (!validActionSelected)
        {
            cout << "Select your action:\n";
            cout << "1. Place tiles\n";
            cout << "2. Replace a tile\n";
            cout << "> ";

            int choice;
            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number." << endl;
                continue;
            }
            cin.ignore();

            if (choice == 1)
            {
                // Placing tiles
                cout << "How many tiles do you want to place? ";
                int numTiles;
                if (!(cin >> numTiles))
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                    cout << "\n"
                         << currentPlayer->getName() << "'s turn" << endl;
                    cout << currentPlayer->getName() << "'s hand: ";
                    (currentPlayer == &player1) ? player1Hand.displayHand() : player2Hand.displayHand();
                    continue;
                }
                cin.ignore();

                // Initialize a vector to store tiles to be placed
                vector<Tile *> tilesToPlace;

                // Input each tile one by one
                for (int i = 0; i < numTiles; ++i)
                {
                    displayBoard(board);
                    (currentPlayer == &player1) ? player1Hand.displayHand() : player2Hand.displayHand();
                    cout << "Place tile " << i + 1 << " using the format: place <tile> at <grid location>" << endl;
                    cout << ">";

                    string command;
                    getline(cin, command);

                    // Split the command into words
                    vector<string> words;
                    size_t pos = 0;
                    while ((pos = command.find(' ')) != string::npos)
                    {
                        words.push_back(command.substr(0, pos));
                        command.erase(0, pos + 1);
                    }
                    words.push_back(command);

                    // Check that the command is correctly formatted
                    if (words.size() != 4 || words[0] != "place" || words[3].length() != 2)
                    {
                        cout << "Invalid command. Please try again." << endl;
                        cout << "\n"
                             << currentPlayer->getName() << "'s turn" << endl;
                        cout << currentPlayer->getName() << "'s hand: ";
                        (currentPlayer == &player1) ? player1Hand.displayHand() : player2Hand.displayHand();
                        cout << "> ";
                        continue;
                    }

                    // Parse the tile and location from the command
                    string tile = words[1];
                    string location = words[3];

                    // Convert the grid location to row and column
                    char gridLetter = location[0];
                    size_t row = (gridLetter >= 'A' && gridLetter <= 'Z') ? (gridLetter - 'A') : -1;
                    size_t column = (location[1] >= '1' && location[1] <= '9') ? (location[1] - '1') : -1;

                    // Check if the row and column are valid
                    if (row == static_cast<size_t>(-1) || row >= board.size() || column == static_cast<size_t>(-1) || column >= board[0].size())
                    {
                        cout << "Invalid grid location. Please try again." << endl;
                        --i; // Decrement i to repeat the input for the same tile
                        continue;
                    }

                    string color = string(1, tile[0]);
                    string shape = tile.substr(1);
                    Tile *tileToCheck = new Tile(color[0], stoi(shape));

                    cout << "Debug Info: " << currentPlayer->getName() << "'s hand: ";
                    (currentPlayer == &player1) ? player1Hand.displayHand() : player2Hand.displayHand();
                    cout << "Debug Info: Tile to check: [" << tileToCheck->colour << "" << tileToCheck->shape << "]" << endl;

                    if (!(currentPlayer == &player1 ? &player1Hand : &player2Hand)->containsTile(tileToCheck))
                    {
                        cout << "Tile not found in hand. Please try again." << endl;
                        delete tileToCheck; // Avoid memory leak
                        --i;                // Decrement i to repeat the input for the same tile
                        continue;
                    }
                    else
                    {
                        if (board[row][column] != nullptr)
                        {
                            cout << "There's already a tile at that location. Please try again." << endl;
                            delete tileToCheck; // Avoid memory leak
                            --i;                // Decrement i to repeat the input for the same tile
                            continue;
                        }
                        else
                        {
                            cout << "Tile found in hand. Proceeding with the game." << endl;
                            board[row][column] = tileToCheck;
                            displayBoard(board);
                            tilesToPlace.push_back(tileToCheck);
                        }
                    }

                    // Remove the tile from the player's hand
                    if (!(currentPlayer == &player1 ? &player1Hand : &player2Hand)->removeTile(tileToCheck))
                    {
                        cout << "Error removing tile from hand. Please try again." << endl;
                        --i; // Decrement i to repeat the input for the same tile
                        continue;
                    }
                }

                // Draw new tiles from the tile bag and add them to the player's hand
                for (int i = 0; i < numTiles && !tileBag.empty(); ++i)
                {
                    // Get the tile from the back of the bag
                    Tile tileFromBag = tileBag.back();
                    tileBag.pop_back();

                    // Create a new tile with the values from the tile drawn from the bag
                    Tile *newTile = new Tile(tileFromBag.colour, tileFromBag.shape);

                    // Add the new tile to the player's hand
                    (currentPlayer == &player1 ? &player1Hand : &player2Hand)->addTileToHand(newTile);
                }

                cout << "The size of the tile bag is now: " << tileBag.size() << endl;
                cout << "\n"
                     << currentPlayer->getName() << "'s hand: ";
                (currentPlayer == &player1) ? player1Hand.displayHand() : player2Hand.displayHand();
                validActionSelected = true;
            }
            else if (choice == 2)
            {
                // Replacing a single tile
                cout << "Replace a tile using the format: replace <tile>" << endl;
                cout << ">";

                bool validInput = false;
                while (!validInput)
                {
                    string command;
                    getline(cin, command);

                    // Split the command into words
                    vector<string> words;
                    size_t pos = 0;
                    while ((pos = command.find(' ')) != string::npos)
                    {
                        words.push_back(command.substr(0, pos));
                        command.erase(0, pos + 1);
                    }
                    words.push_back(command);

                    // Check that the command is correctly formatted
                    if (words.size() != 2 || words[0] != "replace")
                    {
                        cout << "Invalid command. Please try again." << endl;
                        cout << "\n"
                             << currentPlayer->getName() << "'s turn" << endl;
                        cout << currentPlayer->getName() << "'s hand: ";
                        (currentPlayer == &player1) ? player1Hand.displayHand() : player2Hand.displayHand();
                        cout << "Replace a tile using the format: replace <tile>" << endl;
                        cout << ">";
                        continue;
                    }

                    // Parse the tile from the command
                    string tile = words[1];

                    string color = string(1, tile[0]);
                    string shape = tile.substr(1);

                    try
                    {
                        // Attempt to create a tile with the provided color and shape
                        Tile *tileToReplace = new Tile(color[0], stoi(shape));

                        // Check if the tile to replace is in the player's hand
                        if (!(currentPlayer == &player1 ? &player1Hand : &player2Hand)->containsTile(tileToReplace))
                        {
                            cout << "Tile not found in hand. Please try again." << endl;
                            delete tileToReplace; // Avoid memory leak
                            cout << "\n"
                                 << currentPlayer->getName() << "'s turn" << endl;
                            cout << currentPlayer->getName() << "'s hand: ";
                            (currentPlayer == &player1) ? player1Hand.displayHand() : player2Hand.displayHand();
                            cout << "> ";
                            continue;
                        }

                        // Remove the tile from the player's hand
                        (currentPlayer == &player1 ? &player1Hand : &player2Hand)->removeTile(tileToReplace);

                        // Add the replaced tile back to the tile bag
                        tileBag.emplace_back(tileToReplace->colour, tileToReplace->shape);

                        // Print the tile bag before shuffling
                        cout << "Tile bag before shuffling: ";
                        for (const auto &tile : tileBag)
                        {
                            cout << "[" << tile.colour << ", " << tile.shape << "] ";
                        }
                        cout << endl;

                        shuffleTileBag(tileBag);

                        // Print the tile bag after shuffling
                        cout << "Tile bag after shuffling: ";
                        for (const auto &tile : tileBag)
                        {
                            cout << "[" << tile.colour << ", " << tile.shape << "] ";
                        }
                        cout << endl;

                        // Draw a new tile from the tile bag and add it to the player's hand
                        Tile tileFromBag = tileBag.back();
                        tileBag.pop_back();

                        Tile *newTile = new Tile(tileFromBag.colour, tileFromBag.shape);
                        (currentPlayer == &player1 ? &player1Hand : &player2Hand)->addTileToHand(newTile);

                        // Print the player's hand after a new tile is added
                        cout << "Player's hand after adding a new tile: ";
                        (currentPlayer == &player1) ? player1Hand.displayHand() : player2Hand.displayHand();
                        cout << endl;

                        cout << "Tile replaced. Proceeding with the game." << endl;
                        validInput = true;
                        validActionSelected = true; // Exit the loop
                    }
                    catch (const std::invalid_argument &e)
                    {
                        cout << "Invalid tile format. Please try again." << endl;
                        cout << "> ";
                        continue;
                    }
                    catch (const std::out_of_range &e)
                    {
                        cout << "Invalid tile format. Please try again." << endl;
                        cout << "> ";
                        continue;
                    }
                }
            }
            // else if (choice == 3)
            // {
            //     std::string outputFileName;

            //     // Ask the user to enter a name for the output file
            //     std::cout << "Enter a name for the output file: ";
            //     std::cin >> outputFileName;

            //     GameSave gs(player1, player2, board, &tileBag, currentPlayer, outputFileName); // Pass pointer to tileBag

            //     // Don't switch player turn when saving
            //     returnVal = false;
            //     std::cout << std::endl
            //               << "Game successfully saved" << std::endl
            //               << std::endl;
            // }
            else
            {

                cout << "Invalid choice. Please enter a valid option." << endl;
            }
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

void switchPlayer(Player *&currentPlayer, Player *player1, Player *player2)
{
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}