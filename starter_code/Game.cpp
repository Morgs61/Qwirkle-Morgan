
#include "Game.h"
#include "SaveGame.h"
#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"
#include "Board.h"
#include "qwirkle.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

Game::Game(Player *player1, Player *player2, LinkedList *bag, Board *board, Player *currentPlayer)
{
    this->player1 = player1;
    this->player2 = player2;
    this->bag = bag;
    this->board = board;
    this->currentPlayer = currentPlayer;
    playerCount = 2;
}

Game::~Game()
{
    delete bag;
    delete player1;
    delete player2;
    delete board;
}

// ACTUAL RUNNING OF THE GAME STARTS HERE

void Game::launchGame()
{

    bool emptyHandExists = player1->getHand()->isEmpty() || player2->getHand()->isEmpty();

    // progress the game until at least one player has an empty hand.
    while (!emptyHandExists)
    {
        currentPlayer = findStartingPlayer(player1, player2);
        
        
        std::cout << "\n"
        // 1.    Display the current player's name
        << currentPlayer->getName() << ", it's your turn" << std::endl;
        // 2.    Display the Score of player A
        std::cout << "Score for " << player1->getName() << ": " << player1->getScore() << std::endl;
        // 2.    Display the Score of player B
        std::cout << "Score for " << player2->getName() << ": " << player2->getScore() << std::endl;
        // 3.    Display the board
        board->displayBoard();
        // 4.    Display the current player's hand
        std::cout << currentPlayer->getName() << " Your hand is " << std::endl;
        currentPlayer->getHand()->displayHand();

        // 5.    The user prompt
        bool validActionSelected = false;
        while (!validActionSelected)
        {
            cout << "\nSelect your action:\n";
            cout << "1. Place tiles\n";
            cout << "2. Replace a tile\n";
            cout << "3. Save game\n";
            cout << "4. Quit game\n";
            cout << "> ";

    int choice;
    // Read an integer or handle non-integer input
    //DO NOT DELETE THIS AS IT STOPS LOOPING
    if (cin >> choice)
    {
        cin.ignore(); // Clear the input buffer
        validActionSelected = true;
    }
    else
    {
        cout << "Invalid input. Please enter a valid option." << endl;
        cin.clear(); // Clear the error flag
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
    }

 if (choice == 1)
{
    int numTiles = 0;
    vector<Tile *> tilesToPlace;
    vector<std::pair<int, int>> tilePositions;
    int j = 0;
    bool activeTurn = false;

    while (!activeTurn && j < 6 && currentPlayer->getHand()->getSize() > 0)
    {
        currentPlayer->getHand()->displayHand();
        cout << "Place tile " << j + 1 << " using the format: place <tile> at <grid location>" << endl;
        cout << "Enter 'end' to end your turn." << endl;
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

        // Check if the player wants to end their turn
        if (words.size() == 1 && words[0] == "end")
        {
            cout << "Ending turn." << endl;
            activeTurn = true;
            currentPlayer = (currentPlayer == player1) ? player2 : player1;
        }
        else
        {
            // Check that the command is correctly formatted
            if (words.size() != 4 || words[0] != "place" || words[3].length() >= 4)
            {
                cout << "Invalid command. Please try again." << endl;
                cout << "\n"
                     << currentPlayer->getName() << "'s turn" << endl;
                cout << currentPlayer->getName() << "'s hand: ";
                currentPlayer->getHand()->displayHand();
                cout << "> ";
            }
            else
            {
                // Parse the tile and location from the command
                string tile = words[1];
                string location = words[3];
                const int COLUMN_MAX = 15;
                // Convert the grid location to row and column
                char gridLetter = location[0];
                size_t row = (gridLetter >= 'A' && gridLetter <= 'Z') ? (gridLetter - 'A') : -1;
                size_t column = std::stoi(location.substr(1)) - 1; // Convert the rest of the string to a number

                // Check if the row and column are valid
                if (activeTurn && (row == static_cast<size_t>(-1) || row >= static_cast<size_t>(board->getSize()) || column >= COLUMN_MAX))
                {
                    cout << "Invalid grid location. Please try again." << endl;
                }
                else
                {
                    string color = string(1, tile[0]);
                    string shape = tile.substr(1);
                    Tile *tileToCheck = new Tile(color[0], stoi(shape));

                    cout << "Debug Info: " << currentPlayer->getName() << "'s hand: ";
                    currentPlayer->getHand()->displayHand();
                    cout << "Debug Info: Tile to check: [" << tileToCheck->getColour() << "" << tileToCheck->getShape() << "]" << endl;

                    if (!currentPlayer->getHand()->containsTile(tileToCheck))
                    {
                        cout << "Tile not found in hand. Please try again." << endl;
                        delete tileToCheck; // Avoid memory leak
                    }
                    else if (!board->checkSameTypeTiles(tilesToPlace, tilePositions))
                    {
                        cout << "Invalid move. Tiles must have the same color, shape, and share the same column or row." << endl;
                    }
                    else if (!board->checkSurroundingTilesMatch(row, column, tileToCheck))
                    {
                        cout << "Surrounding tiles do not match. Please try again." << endl;
                        delete tileToCheck; // Avoid memory leak
                    }
                    else
                    {
                        cout << "Tile found in hand. Proceeding with the game." << endl;
                        
                        tilesToPlace.push_back(tileToCheck);
                        tilePositions.push_back(std::make_pair(row, column));
                        
                        // Check if the tiles being placed have the same color, shape, and share the same column or row
                        if (!board->checkSameTypeTiles(tilesToPlace, tilePositions))
                        {
                            cout << "Invalid move. Tiles must have the same color, shape, and share the same column or row." << endl;
                        }
                        else
                        {
                            ++numTiles;
                            board->setTileAtPosition(row, column, tileToCheck);
                            board->displayBoard();
                            
                        }
                    }

                    // Remove the tile from the player's hand
                    if (!currentPlayer->getHand()->removeTile(tileToCheck))
                    {
                        cout << "Error removing tile from hand. Please try again." << endl;
                    }
                }
            }
        }

        // Draw new tiles from the tile bag and add them to the player's hand
        for (int k = 0; k < numTiles && !bag->isEmpty(); ++k)
        {
            // Get the tile from the back of the bag
            Tile *tileFromBagPtr = bag->back();
            bag->remove_back();
            
            // Add the new tile to the player's hand
            currentPlayer->getHand()->addTile(tileFromBagPtr);
        }

        // TODO: update scoring methods
        int score = board->calculateScore(tilesToPlace, tilePositions);

        // add the score to the player's score
        currentPlayer->addScore(score);

        // output the player hand
        cout << "Player's hand after adding a new tile: ";
        currentPlayer->getHand()->displayHand();

        cout << "The size of the tile bag is now: " << bag->getSize() << endl;
        cout << "\n"
        << currentPlayer->getName() << "'s hand: ";
        currentPlayer->getHand()->displayHand();
    }
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
                    bool retry = false;
                    if (words.size() != 2 || words[0] != "replace")
                    {
                        cout << "Invalid command. Please try again." << endl;
                        cout << "\n"
                             << currentPlayer->getName() << "'s turn" << endl;
                        cout << currentPlayer->getName() << "'s hand: ";
                        currentPlayer->getHand()->displayHand();
                        cout << "Replace a tile using the format: replace <tile>" << endl;
                        cout << "> ";
                        retry = true;
                    }

                    if (!retry)
                    {
                        // Parse the tile from the command
                        string tile = words[1];

                        string color = string(1, tile[0]);
                        string shape = tile.substr(1);

                        try
                        {
                            // Attempt to create a tile with the provided color and shape
                            Tile *tileToReplace = new Tile(color[0], stoi(shape));

                            // Check if the tile to replace is in the player's hand
                            if (!currentPlayer->getHand()->containsTile(tileToReplace))
                            {
                                cout << "Tile not found in hand. Please try again." << endl;
                                delete tileToReplace; // Avoid memory leak
                                cout << "\n"
                                     << currentPlayer->getName() << "'s turn" << endl;
                                cout << currentPlayer->getName() << "'s hand: ";
                                currentPlayer->getHand()->displayHand();
                                cout << "> ";
                                retry = true;
                            }

                            if (!retry)
                            {
                                // Remove the tile from the player's hand
                                currentPlayer->getHand()->removeTile(tileToReplace);

                                // Add the replaced tile back to the tile bag
                                bag->push_back(tileToReplace);

                                // Print the tile bag before shuffling
                                cout << "Tile bag before shuffling: ";
                                for (Node *current = bag->begin(); current != bag->end(); current = current->next)
                                {
                                    cout << "[" << current->tile->getColour() << ", " << current->tile->getShape() << "] ";
                                }
                                cout << endl;

                                bag->shuffle();

                                // Print the tile bag after shuffling
                                cout << "Tile bag after shuffling: ";
                                for (Node *current = bag->begin(); current != bag->end(); current = current->next)
                                {
                                    cout << "[" << current->tile->getColour() << ", " << current->tile->getShape() << "] ";
                                }
                                cout << endl;

                                // Draw a new tile from the tile bag and add it to the player's hand
                                Tile *tileFromBag = bag->back();
                                // bag->pop_back();

                                currentPlayer->getHand()->addTile(tileFromBag); // Pass the Tile* directly

                                // Print the player's hand after a new tile is added
                                cout << "Player's hand after adding a new tile: ";
                                currentPlayer->getHand()->displayHand();
                                cout << endl;

                                cout << "Tile replaced. Proceeding with the game" << endl;
                                validInput = true;
                                currentPlayer = (currentPlayer == player1) ? player2 : player1;
                                cout << currentPlayer->getName() << "'s turn" << endl;
                                currentPlayer->getHand()->displayHand();
                            }
                        }
                        catch (const std::invalid_argument &e)
                        {
                            cout << "Invalid tile format. Please try again." << endl;
                            cout << "> ";
                        }
                        catch (const std::out_of_range &e)
                        {
                            cout << "Invalid tile format. Please try again." << endl;
                            cout << "> ";
                        }
                    }
                }
            }
            else if (choice == 3)
            {
                // Save game
                string filename;
                cout << "Enter the filename to save the game: ";
                getline(cin, filename);
                SaveGame::saveGameState(filename, player1, player2, board, bag, currentPlayer);
                cout << "Game successfully saved" << endl;
            }
            else if (choice == 4)
            {
                // Quit game
                cout << "Quitting game..." << endl;
                return;
            }
            else
            {
                cout << "Invalid choice. Please enter a valid option." << endl;
            }
        }

        // Switch players
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }

    // Check if any player has an empty hand
    emptyHandExists = player1->getHand()->isEmpty() || player2->getHand()->isEmpty();
}

// Helper function to check if any player has an empty hand

bool checkForEmptyPlayerHands(Player **players, int playerCount)
{
    for (int i = 0; i < playerCount; ++i)
    {
        if (players[i]->getHand()->isEmpty())
        {
            return true;
        }
    }
    return false;
}
