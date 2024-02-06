
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
#include <iomanip>
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

void Game::launchGame() {
    // get the current status of the game once its launched
    bool gameComplete = isGameComplete();

    // run until the game is complete.
    while (!gameComplete) {
        // Show the current Game status at the start of the players turn
        displayGameStatus();

        // Start the current players turn.
        bool playerTurnComplete = false;
        while (!playerTurnComplete) {
            int menuChoice = getPlayerMenuSelection();

            if (menuChoice == 1) { // Place tiles
               // placeTiles();
                playerTurnComplete = placeTiles();
            }
            else if (menuChoice == 2) {
                if (currentPlayer->getHand()->getSize() < 6) {
                    cout << "You have already placed a tile. You can not now replace a tile" << endl;
                    //return;
                }else {
                playerTurnComplete = replaceTile(); // Use the return value to determine if the turn is complete
}
            }
            else if (menuChoice == 3) {
                saveGame();
            }
            else if (menuChoice == 4) {
                cout << "Quitting game..." << endl;
                return;
            }
            else {
                cout << "Invalid choice. Please enter a valid option." << endl;
            }
        }
        // Switch players
        currentPlayer = (currentPlayer == player1) ? player2 : player1;

        // Check if the game is complete
        gameComplete = isGameComplete();
    }
	declareWinner();
}

// Check if any player has an empty hand
bool Game::isGameComplete() {
    // if either player has an empty hand, the game is complete.
    return player1->getHand()->isEmpty() || player2->getHand()->isEmpty();
}

void Game::displayGameStatus() {
    std::cout << "\n"
    << currentPlayer->getName() << ", it's your turn" << std::endl;
    std::cout << "Score for " << player1->getName() << ": " << player1->getScore() << std::endl;
    std::cout << "Score for " << player2->getName() << ": " << player2->getScore() << std::endl;
    board->displayBoard();
    std::cout << currentPlayer->getName() << " Your hand is " << std::endl;
    currentPlayer->getHand()->displayHand();
}

int Game::getPlayerMenuSelection() {
    int choice;
    bool validActionSelected = false;
    while (!validActionSelected) {
        cout << "\nSelect your action:\n";
        cout << "1. Place tiles\n";
        cout << "2. Replace a tile\n";
        cout << "3. Save game\n";
        cout << "4. Quit game\n";
        cout << "> ";
        // Read an integer or handle non-integer input
        // DO NOT DELETE THIS AS IT STOPS LOOPING
        if (cin >> choice) {
            cin.ignore(); // Clear the input buffer
            validActionSelected = true;
        } else {
            cout << "Invalid input. Please enter a valid option." << endl;
            cin.clear();                                                   // Clear the error flag
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    return choice;
}

vector<string> Game::parsePlayerInput() {
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

    return words;
}

bool Game::validateTilePlacement(vector<string>& words, vector<Tile*>& tilesToPlace, vector<std::pair<int, int>>& tilePositions) {
    // Parse the tile and location from the command
    string tile = words[1];
    string location = words[3];
    const int COLUMN_MAX = 26;
    // Convert the grid location to row and column
    char gridLetter = location[0];
    size_t row = (gridLetter >= 'A' && gridLetter <= 'Z') ? (gridLetter - 'A') : -1;
    size_t column = std::stoi(location.substr(1)); // Convert the rest of the string to a number

    // Check if the row and column are valid
    if (row == static_cast<size_t>(-1) || row >= static_cast<size_t>(board->getSize()) || column >= COLUMN_MAX) {
        cout << "Invalid grid location. Please try again." << endl;
        return false;
    }

    string color = string(1, tile[0]);
    string shape = tile.substr(1);
    Tile *tileToCheck = new Tile(color[0], stoi(shape));

    if (!currentPlayer->getHand()->containsTile(tileToCheck)) {
        cout << "Tile not found in hand. Please try again." << endl;
        delete tileToCheck; // Avoid memory leak
        return false;
    }
    else if (!board->checkSameTypeTiles(tilesToPlace, tilePositions)) {
        cout << "Invalid move. Tiles must have the same color, shape, and share the same column or row." << endl;
        return false;
    }
    else if (!board->checkSurroundingTilesMatch(row, column, tileToCheck)) {
        cout << "Surrounding tiles do not match. Please try again." << endl;
        delete tileToCheck; // Avoid memory leak
        return false;
    }

    tilesToPlace.push_back(tileToCheck);
    tilePositions.push_back(std::make_pair(row, column));

    return true;
}

void Game::updateGameAfterTilePlacement(vector<Tile*>& tilesToPlace, vector<std::pair<int, int>>& tilePositions, int& numTiles) {
    // Check if the tiles being placed have the same color, shape, and share the same column or row
    if (!board->checkSameTypeTiles(tilesToPlace, tilePositions)) {
        cout << "Invalid move. Tiles must have the same color, shape, and share the same column or row." << endl;
    }
    else {
        ++numTiles;
        int row = tilePositions.back().first;
        int col = tilePositions.back().second;
        board->setTileAtPosition(row, col, tilesToPlace.back());
        board->displayBoard();
    }

    // Remove the tile from the player's hand
    if (!currentPlayer->getHand()->removeTile(tilesToPlace.back())) {
        cout << "Error removing tile from hand. Please try again." << endl;
    }
}

bool Game::placeTiles() {
    int numTiles = 0;
    vector<Tile *> tilesToPlace;
    vector<std::pair<int, int>> tilePositions;
    bool activeTurn = false;

    while (!activeTurn && currentPlayer->getHand()->getSize() > 0) {
        currentPlayer->getHand()->displayHand();
        cout << "Place tile " << numTiles + 1 << " using the format: place <tile> at <grid location>" << endl;
        cout << "Enter 'end' to end your turn or 'back' to return to previous menu" << endl;
        cout << ">";

        vector<string> words = parsePlayerInput();

        // Check if the player wants to end their turn
        if (words.size() == 1 && words[0] == "end") {
            if (numTiles == 0) {
                cout << "You must place at least one tile." << endl;
                activeTurn = false;
            }
            else
            {
                cout << "Ending turn." << endl;
                activeTurn = true;
            }
        }
        // Check for the 'back' command first
        if (words.size() == 1 && words[0] == "back") {
            if (numTiles > 0) {
                cout << "You have already placed a tile. You must continue your move." << endl;
                //activeTurn = false;
            }
            else
            {
            cout << "Returning to the previous menu." << endl;
            return false; // Directly exit the function, thereby exiting the loop and not ending the player's
        }

        }
        else {
            if (words.size() != 4 || words[0] != "place" || words[3].length() >= 4) {
                cout << "Invalid command. Please try again." << endl;
            }
            else {
                if (validateTilePlacement(words, tilesToPlace, tilePositions)) {
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
    for (int k = 0; k < numTiles && !bag->isEmpty() && currentPlayer->getHand()->getSize() < MAX_HAND_SIZE; ++k) {
        // Get the tile from the back of the bag
        Tile *tileFromBagPtr = bag->back();
        bag->remove_back();

        // Add the new tile to the player's hand
        currentPlayer->getHand()->addTile(tileFromBagPtr);
    }

    // output the player hand
    cout << "Player's hand after adding a new tile: ";
    currentPlayer->getHand()->displayHand();

    cout << "The size of the tile bag is now: " << bag->getSize() << endl;
    cout << "\n"
         << currentPlayer->getName() << "'s hand: ";
    currentPlayer->getHand()->displayHand();
    return true;
}


Tile* Game::createAndValidateTile(const string& tileStr) {
    string color = string(1, tileStr[0]);
    string shape = tileStr.substr(1);
    Tile *tileToReplace = new Tile(color[0], stoi(shape));

    if (!currentPlayer->getHand()->containsTile(tileToReplace)) {
        cout << "Tile not found in hand. Please try again." << endl;
        delete tileToReplace;
        return nullptr;
    }
    return tileToReplace;
}

void Game::replaceTileAndUpdateHand(Tile* tileToReplace) {
    currentPlayer->getHand()->removeTile(tileToReplace);
    bag->push_back(tileToReplace);
    bag->shuffle();

    Tile *tileFromBag = bag->back();
    bag->remove_back();
    currentPlayer->getHand()->addTile(tileFromBag);
}

bool Game::replaceTile() {
    cout << "Replace a tile using the format: replace <tile>" << endl;
    cout << "Enter 'back' to return to previous menu" << endl;


    bool validInput = false;
    while (!validInput) {
        cout << "> ";
        string command;
        getline(cin, command);
     // Check for the 'back' command first
        if (command == "back") {
            cout << "Returning to the previous menu." << endl;
            return false; // Directly exit the function, thereby exiting the loop and not ending the player's turn

        }
        else{

        vector<string> words;
        size_t pos = 0;
        // Split the command into words based on spaces
        while ((pos = command.find(' ')) != string::npos) {
            words.push_back(command.substr(0, pos));
            command.erase(0, pos + 1);
        }
        words.push_back(command); // Add the last (or only) word

        // Check the command format
        if (words.size() == 2 && words[0] == "replace") {
            Tile* tileToReplace = createAndValidateTile(words[1]);
            if (tileToReplace != nullptr) {
                // If the tile is valid, proceed with replacement and update the hand
                replaceTileAndUpdateHand(tileToReplace);
                cout << "Tile replaced. Proceeding with the game." << endl;
                validInput = true; // Exit the loop
            }
        } else {
            // If the command format is incorrect, inform the user and the loop will repeat
            cout << "Invalid command. Please try again." << endl;
        }
        }
    } return true;
}

void Game::saveGame() {
    // Save game
    string filename;
    cout << "Enter the filename to save the game: ";
    getline(cin, filename);
    SaveGame::saveGameState(filename, player1, player2, board, bag, currentPlayer);
    cout << "Game successfully saved" << endl;
}

void Game::declareWinner() {
    std::cout << "Game over" << endl;
    std::cout << "\nScore for " << player1->getName() << ": " << player1->getScore() << std::endl;
    std::cout << "Score for " << player2->getName() << ": " << player2->getScore() << std::endl;
	std::cout << "Player ";

    if (player1->getScore() > player2->getScore()) {
        std::cout << player1->getName() << " won!" << std::endl;
    }
    else if (player1->getScore() < player2->getScore()) {
        std::cout << player2->getName() << " won!" << std::endl;
    }
    else {
        std::cout << "It's a draw!" << std::endl;
    }
    std::cout << "\nGoodbye" << std::endl;
	exit(0);
}



