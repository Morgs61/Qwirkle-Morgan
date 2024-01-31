//
// Created by alex on 30/01/24.
//

#include "Game.h"
#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"
#include "Board.h"

#include <iostream>
#include <algorithm>
#include <random>
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

void Game::launchGame()
{
    // Print the hands of each player
    std::cout << "\n"
              << player1->getName() << "'s hand: ";
    player1->getHand()->displayHand();
    std::cout << "\n"
              << player2->getName() << "'s hand: ";
    player2->getHand()->displayHand();

    bool emptyHandExists = player1->getHand()->isEmpty() || player2->getHand()->isEmpty();

    // continue the game until at least one player has an empty hand.
    while (!emptyHandExists)
    {
        std::cout << "\n"
                  << currentPlayer->getName() << "'s turn" << std::endl;
        std::cout << currentPlayer->getName() << "'s hand: ";
        currentPlayer->getHand()->displayHand();

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
                cout << "\n"
                     << currentPlayer->getName() << "'s turn" << endl;
                cout << currentPlayer->getName() << "'s hand: ";
                currentPlayer->getHand()->displayHand();
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
                    currentPlayer->getHand()->displayHand();
                    continue;
                }
                cin.ignore();

                // Initialize a vector to store tiles to be placed
                vector<Tile *> tilesToPlace;

                // Input each tile one by one
                for (int j = 0; j < numTiles; ++j)
                {
                    board->displayBoard();
                    currentPlayer->getHand()->displayHand();
                    cout << "Place tile " << j + 1 << " using the format: place <tile> at <grid location>" << endl;
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
                        currentPlayer->getHand()->displayHand();
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
                    if (row == static_cast<size_t>(-1) || row >= board->size() || column == static_cast<size_t>(-1) || column >= board[0].size())
                    {
                        cout << "Invalid grid location. Please try again." << endl;
                        --j; // Decrement j to repeat the input for the same tile
                        continue;
                    }

                    string color = string(1, tile[0]);
                    string shape = tile.substr(1);
                    Tile *tileToCheck = new Tile(color[0], stoi(shape));

                    cout << "Debug Info: " << currentPlayer->getName() << "'s hand: ";
                    currentPlayer->getHand()->displayHand();
                    cout << "Debug Info: Tile to check: [" << tileToCheck->colour << "" << tileToCheck->shape << "]" << endl;

                    if (!currentPlayer->getHand()->containsTile(tileToCheck))
                    {
                        cout << "Tile not found in hand. Please try again." << endl;
                        delete tileToCheck; // Avoid memory leak
                        --j;                // Decrement j to repeat the input for the same tile
                        continue;
                    }
                    else
                    {
                        if (board[row][column] != nullptr)
                        {
                            cout << "There's already a tile at that location. Please try again." << endl;
                            delete tileToCheck; // Avoid memory leak
                            --j;                // Decrement j to repeat the input for the same tile
                            continue;
                        }
                        else
                        {
                            cout << "Tile found in hand. Proceeding with the game." << endl;
                            board[row][column] = tileToCheck;
                            board->displayBoard();
                            tilesToPlace.push_back(tileToCheck);
                        }
                    }

                    // Remove the tile from the player's hand
                    if (!currentPlayer->getHand()->removeTile(tileToCheck))
                    {
                        cout << "Error removing tile from hand. Please try again." << endl;
                        --j; // Decrement j to repeat the input for the same tile
                        continue;
                    }
                }

                // Draw new tiles from the tile bag and add them to the player's hand
                for (int j = 0; j < numTiles && !bag->isEmpty(); ++j)
                {
                    // Get the tile pointer from the back of the bag
                    Tile *tileFromBagPtr = bag->back();
                    bag->pop_back();

                    // Add the tile pointer directly to the player's hand
                    currentPlayer->getHand()->addTileToHand(tileFromBagPtr);
                }

                cout << "The size of the tile bag is now: " << bag->getSize() << endl;
                cout << "\n"
                     << currentPlayer->getName() << "'s hand: ";
                currentPlayer->getHand()->displayHand();
                validActionSelected = true;
            }
            if (choice == 2)
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
                        currentPlayer->getHand()->displayHand();
                        cout << "Replace a tile using the format: replace <tile>" << endl;
                        cout << "> ";
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
                        if (!currentPlayer->getHand()->containsTile(tileToReplace))
                        {
                            cout << "Tile not found in hand. Please try again." << endl;
                            delete tileToReplace; // Avoid memory leak
                            cout << "\n"
                                 << currentPlayer->getName() << "'s turn" << endl;
                            cout << currentPlayer->getName() << "'s hand: ";
                            currentPlayer->getHand()->displayHand();
                            cout << "> ";
                            continue;
                        }

                        // Remove the tile from the player's hand
                        currentPlayer->getHand()->removeTile(tileToReplace);

                        // Add the replaced tile back to the tile bag
                        bag->push_back(tileToReplace);

                        // Print the tile bag before shuffling
                        cout << "Tile bag before shuffling: ";
                        for (Node *current = bag->begin(); current != bag->end(); current = current->next)
                        {
                            cout << "[" << current->tile->colour << ", " << current->tile->shape << "] ";
                        }
                        cout << endl;

                        bag->shuffle();

                        // Print the tile bag after shuffling
                        cout << "Tile bag after shuffling: ";
                        for (Node *current = bag->begin(); current != bag->end(); current = current->next)
                        {
                            cout << "[" << current->tile->colour << ", " << current->tile->shape << "] ";
                        }
                        cout << endl;

                        // Draw a new tile from the tile bag and add it to the player's hand
                        Tile *tileFromBag = bag->back();
                        bag->pop_back();

                        currentPlayer->getHand()->addTileToHand(tileFromBag); // Pass the Tile* directly

                        // Print the player's hand after a new tile is added
                        cout << "Player's hand after adding a new tile: ";
                        currentPlayer->getHand()->displayHand();
                        cout << endl;

                        cout << "Tile replaced. Proceeding with the game." << endl;
                        validInput = true;
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

// void initializeTileBag(std::vector<Tile> &tileBag)
// {
//     // Get definitions from TileCodes.h
//     char colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
//     int shapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

//     // Create all combinations of colours and shapes
//     for (char colour : colours)
//     {
//         for (int shape : shapes)
//         {
//             // Add two tiles of each type to the tile bag
//             tileBag.push_back({colour, shape});
//             tileBag.push_back({colour, shape});
//         }
//     }

//     // Shuffle the tile bag
//     shuffleTileBag(tileBag);
// }

void shuffleTileBag(std::vector<Tile> &tileBag)
{
    // Shuffle the tile bag
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(tileBag.begin(), tileBag.end(), rng);
}

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
