#include "LinkedList.h"
#include "qwirkle.h"
#include "Tile.h"
#include "Node.h"
#include "Board.h"
#include "TileCodes.h"
#include "Player.h"
#include "Game.h"
#include "LoadGame.h"
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
Player *findStartingPlayer(Player *player1, Player *player2);

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
        }
        else
        {
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
    cout << "4. Quit \n"
         << endl;
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

    // Create an instance of LoadGame
    LoadGame loader;

    // Call the loadGame method with the filename
    Game *loadedGame = loader.loadGame(filename);

    // Check if the game is successfully loaded
    if (loadedGame != nullptr)
    {
        // File exists and is open

        // Add validation for the file format (replace with your actual format check logic)
        // For example, if you have a specific format, check if it matches
        // Here, we assume a simple check by reading a line from the file
        // Open the file for reading
        ifstream file(filename);

        // Check if the file is open
        if (file.is_open())
        {
            // File is open, proceed with reading
            string line;
            if (getline(file, line))
            {
                cout << "\nQwirkle game successfully loaded." << endl;
                // Continue reading or processing the file content here
                loadedGame->launchGame();
            }
            else
            {
                cout << "\nInvalid file format. Unable to load the game." << endl;
            }

            // Close the file when done
            file.close();
        }
        else
        {
            cout << "\nError: Unable to open the file." << endl;
        }
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
    std::cout << playerName1 + "'s hand: ";
    playerHand1->displayHand();

    LinkedList *playerHand2 = new LinkedList();
    initializePlayerHand(playerHand2, bag); // Pass the address of tileBag

    // log the hand
    std::cout << playerName2 + "'s hand: ";
    playerHand2->displayHand();

    // Create players
    Player *player1 = new Player(playerName1, 0, playerHand1);
    Player *player2 = new Player(playerName2, 0, playerHand2);

    cin.ignore();
    cout << "\nLet's Play!" << endl;

    // Initialize the board
    Board *board = new Board(); // Instantiate Board

    Player *startingPlayer = findStartingPlayer(player1, player2);
    std::cout << "Starting player is: " << startingPlayer->getName() << std::endl;

    // Determine the starting player

    // Instantiate Game with the modified parameters
    Game *game = new Game(player1, player2, bag, board, player2); // Pass player1, player2, bag, and currentPlayer

    // Call the correct method
    game->launchGame();
}

void initializePlayerHand(LinkedList *playerHand, LinkedList *bag)
{
    // Draw tiles from the tile bag and add them to the player's hand until there are 6 tiles
    while (playerHand->getSize() < 6 && !bag->isEmpty())
    {
        // Get the tile pointer from the back of the bag
        Tile *tileFromBagPtr = bag->back();

        // bag->pop_back();
        // Replaced pop_back with function that preserves the tile at the pointer, instead of deleting it.
        bag->remove_back();

        // Add the tile pointer directly to the player's hand
        playerHand->addTile(tileFromBagPtr);
    }
}

// int main(void)
//{
//     LinkedList *list = new LinkedList();
//     delete list;
//
//     // std::cout << "TODO: Implement Qwirkle!" << std::endl;
//     // 2.1 Launch
//     cout << "Welcome to Qwirkle!" << endl;
//     cout << "-----------------------" << endl;
//
//     int choice = 0;
//     bool quit = false;
//
//     while (!quit)
//     {
//         displayMenu();
//         cout << "> ";
//         cin >> choice;
//
//         // If the extraction fails
//         if (cin.fail())
//         {
//             // Clear the error state
//             cin.clear();
//
//             // Ignore the rest of the line
//             cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//             cout << "Invalid choice. Please enter a valid option." << endl;
//             continue;
//         }
//
//         if (choice == 1)
//         {
//             cout << "\nStarting a New Game" << endl;
//             startNewGame();
//         }
//         else if (choice == 2)
//         {
//             cout << "Loading Game..." << endl;
//             loadGame();
//             // Add code for loading a game
//         }
//         else if (choice == 3)
//         {
//
//             displayStudentInformation();
//         }
//         else if (choice == 4)
//         {
//             cout << "Quitting the game. Goodbye!" << endl;
//             quit = true;
//         }
//         else
//         {
//             cout << "Invalid choice. Please enter a valid option." << endl;
//
//         }
//     }
//
//     return EXIT_SUCCESS;
// }
//
// void displayMenu()
//{
//     cout << "\nMenu" << endl;
//     cout << "1. New Game" << endl;
//     cout << "2. Load Game" << endl;
//     cout << "3. Credits (Show student information)" << endl;
//     cout << "4. Quit" << endl;
// }
//
//// Function to check if a player name is valid
// bool isValidPlayerName(const string &name)
//{
//     for (char c : name)
//     {
//         // check if we can use this
//         if (!isupper(c) || !isalpha(c))
//         {
//             cout << "Invalid name. Please enter uppercase letters only." << endl;
//             return false;
//         }
//     }
//     return true;
// }
//
//// 2.2.3 Credits - Need members to add their details
// void displayStudentInformation()
//{
//
//     cout << "--------------------------------------" << endl;
//     // Hardcoded information for 4 students
//     cout << "\nName: Michael Moon" << endl;
//     cout << "Student ID: s3523025" << endl;
//     cout << "Email: s3523025@student.rmit.edu.au" << endl;
//
//     cout << "\nName: Alexander Cowan" << endl;
//     cout << "Student ID: s3863084" << endl;
//     cout << "Email: s3863084@student.rmit.edu.au" << endl;
//
//     cout << "\nName: Michael Whyte" << endl;
//     cout << "Student ID: s3851481" << endl;
//     cout << "Email: S3851481@student.rmit.edu.au" << endl;
//
//     cout << "\nName: Morgan Cassar" << endl;
//     cout << "Student ID: s3858530" << endl;
//     cout << "Email: s3858530@student.rmit.edu.au" << endl;
//     cout << "--------------------------------------" << endl;
//     cout << "\n<Main Menu>" << endl;
// }
//
// void loadGame()
//{
//     cout << "\nEnter the filename from which to load a game:" << endl;
//     string filename;
//     cout << "> ";
//     cin >> filename;
//
//     // Attempt to open the file4
//     std::ifstream file(filename);
//
//     if (file.good() && file.is_open())
//     {
//         // File exists and is open
//
//         // Add validation for the file format (replace with your actual format check logic)
//         // For example, if you have a specific format, check if it matches
//         // Here, we assume a simple check by reading a line from the file
//         string line;
//         if (getline(file, line))
//         {
//             cout << "\nQwirkle game successfully loaded." << endl;
//             // Add code to load the game (replace with your actual game loading logic)
//             // For example, you might read data from the file and restore the game state
//             // ...
//
//             // Continue with normal gameplay (replace with your actual gameplay logic)
//             // ...
//         }
//         else
//         {
//             cout << "\nInvalid file format. Unable to load the game." << endl;
//         }
//
//         // Close the file
//         file.close();
//     }
//     else
//     {
//         cout << "\nFile does not exist or could not be opened. Unable to load the game." << endl;
//     }
// }
//
// void startNewGame()
//{
//     // Number of players
//     // int numPlayers = 2;
//
//     // Initialize and shuffle the tile bag
//     cout << "making the bag" << std::endl;
//     LinkedList *bag = new LinkedList(); // Instantiate LinkedList
//     bag->initializeAndShuffleBag();     // Populate the bag
//
//     // Create player names
//     string playerName1, playerName2;
//     do
//     {
//         cout << "\nEnter a name for player 1 (uppercase characters only): ";
//         cin >> playerName1;
//     } while (!isValidPlayerName(playerName1));
//
//     do
//     {
//         cout << "\nEnter a name for player 2 (uppercase characters only): ";
//         cin >> playerName2;
//     } while (!isValidPlayerName(playerName2));
//
//     // Create player hands
//     LinkedList *playerHand1 = new LinkedList();
//     initializePlayerHand(playerHand1, bag); // Pass the address of tileBag
//
//     // log the hand
//     std::cout << "Player 1's hand: ";
//     playerHand1->displayHand();
//
//     LinkedList *playerHand2 = new LinkedList();
//     initializePlayerHand(playerHand2, bag); // Pass the address of tileBag
//
//     // log the hand
//     std::cout << "Player 2's hand: ";
//     playerHand2->displayHand();
//
//     // Create players
//     Player *player1 = new Player(playerName1, 0, playerHand1);
//     Player *player2 = new Player(playerName2, 0, playerHand2);
//
//     cin.ignore();
//     cout << "\nLet's Play!" << endl;
//
//     // Initialize the board
//     Board *board = new Board(); // Instantiate Board
//
//     // Instantiate Game with the modified parameters
//     Game *game = new Game(player1, player2, bag, board, player1); // Pass player1, player2, bag, and currentPlayer
//
//     // Call the correct method
//     game->launchGame();
// }
//
// void initializePlayerHand(LinkedList *playerHand, LinkedList *bag)
//{
//             string color = string(1, tile[0]);
//             string shape = tile.substr(1);
//             Tile* tileToCheck = new Tile(color[0], stoi(shape));
//
//             cout << "Debug Info: " << players[i]->getName() << "'s hand: ";
//             players[i]->getHand()->displayHand();
//             cout << "Debug Info: Tile to check: [" << tileToCheck->getColour() << "" << tileToCheck->getShape() << "]" << endl;
//
//             if (!players[i]->getHand()->containsTile(tileToCheck)) {
//                 cout << "Tile not found in hand. Please try again." << endl;
//                 delete tileToCheck;  // Avoid memory leak
//                 //--j;  // Decrement j to repeat the input for the same tile
//                 continue;
//             } else {
//                 if (board[row][column] != nullptr) {
//                     cout << "There's already a tile at that location. Please try again." << endl;
//                     delete tileToCheck;  // Avoid memory leak
//                     //--j;  // Decrement j to repeat the input for the same tile
//                     continue;
//                 } else {
//                     cout << "Tile found in hand. Proceeding with the game." << endl;
//                     if (checkSurroundingTilesMatch(board, row, column, tileToCheck)) {
//                         cout << "Surrounding tiles match. Proceeding with the game." << endl;
//                     } else {
//                         cout << "Surrounding tiles do not match. Please try again." << endl;
//                         delete tileToCheck;  // Avoid memory leak
//                         //--j;  // Decrement i to repeat the input for the same tile
//                         continue;
//                     }
//                     tilesToPlace.push_back(tileToCheck);
//					tilePositions.push_back(std::make_pair(row, column));
//					// Check if the tiles being placed have the same color, shape, and share the same column or row
//					if (!checkSameTypeTiles(tilesToPlace, tilePositions)) {
//     					cout << "Invalid move. Tiles must have the same color, shape, and share the same column or row." << endl;
//						//--j;
//						continue;
//					}
//					++j;
//                     board[row][column] = tileToCheck;
//                     displayBoard(board);
//                 }
//             }
//             // Remove the tile from the player's hand
//             if (!players[i]->getHand()->removeTile(tileToCheck)) {
//                 cout << "Error removing tile from hand. Please try again." << endl;
//                 //--j;  // Decrement j to repeat the input for the same tile
//                 continue;
//             }
//         }
//
//         // Draw new tiles from the tile bag and add them to the player's hand
//         for (int n = 0; n < j && !tileBag.empty(); ++n) {
//             // Get the tile from the back of the bag
//             Tile tileFromBag = tileBag.back();
//             tileBag.pop_back();
//
//             // Create a new tile with the values from the tile drawn from the bag
//             Tile* newTile = new Tile(tileFromBag.colour, tileFromBag.shape);
//
//             // Add the new tile to the player's hand
//             players[i]->getHand()->addTileToHand(newTile);
//         }
//
//         cout << "The size of the tile bag is now: " << tileBag.size() << endl;
//         cout << "\n" << players[i]->getName() << "'s hand: ";
//         players[i]->getHand()->displayHand();
//         validActionSelected = true;
//     }
//     if (choice == 2) {
//         // Replacing a single tile
//         cout << "Replace a tile using the format: replace <tile>" << endl;
//         cout << ">";
//
//         bool validInput = false;
//         while (!validInput) {
//             string command;
//             getline(cin, command);
//
//             // Split the command into words
//             vector<string> words;
//             size_t pos = 0;
//             while ((pos = command.find(' ')) != string::npos) {
//                 words.push_back(command.substr(0, pos));
//                 command.erase(0, pos + 1);
//             }
//             words.push_back(command);
//
//             // Check that the command is correctly formatted
//             if (words.size() != 2 || words[0] != "replace") {
//                 cout << "Invalid command. Please try again." << endl;
//                 cout << "\n" << players[i]->getName() << "'s turn" << endl;
//                 cout << players[i]->getName() << "'s hand: ";
//                 players[i]->getHand()->displayHand();
//                 cout << "Replace a tile using the format: replace <tile>" << endl;
//                 cout << "> ";
//                 continue;
//             }
//
//             // Parse the tile from the command
//             string tile = words[1];
//
//             string color = string(1, tile[0]);
//             string shape = tile.substr(1);
//
//             try {
//                 // Attempt to create a tile with the provided color and shape
//                 Tile* tileToReplace = new Tile(color[0], stoi(shape));
//
//                 // Check if the tile to replace is in the player's hand
//                 if (!players[i]->getHand()->containsTile(tileToReplace)) {
//                     cout << "Tile not found in hand. Please try again." << endl;
//                     delete tileToReplace;  // Avoid memory leak
//                     cout << "\n" << players[i]->getName() << "'s turn" << endl;
//                     cout << players[i]->getName() << "'s hand: ";
//                     players[i]->getHand()->displayHand();
//                     cout << "> ";
//                     continue;
//                 }
//
//                 // Remove the tile from the player's hand
//                 players[i]->getHand()->removeTile(tileToReplace);
//
//                 // Add the replaced tile back to the tile bag
//                 tileBag.emplace_back(tileToReplace->getColour(), tileToReplace->getShape());
//
//                 // Print the tile bag before shuffling
//                 cout << "Tile bag before shuffling: ";
//                 for (const auto& tile : tileBag) {
//                     cout << "[" << tile.colour << ", " << tile.shape << "] ";
//                 }
//                 cout << endl;
//
//                 shuffleTileBag(tileBag);
//
//                 // Print the tile bag after shuffling
//                 cout << "Tile bag after shuffling: ";
//                 for (const auto& tile : tileBag) {
//                     cout << "[" << tile.colour << ", " << tile.shape << "] ";
//                 }
//                 cout << endl;
//
//                 // Draw a new tile from the tile bag and add it to the player's hand
//                 Tile tileFromBag = tileBag.back();
//                 tileBag.pop_back();
//
//                 Tile* newTile = new Tile(tileFromBag.colour, tileFromBag.shape);
//                 players[i]->getHand()->addTileToHand(newTile);
//
//                 // Print the player's hand after a new tile is added
//                 cout << "Player's hand after adding a new tile: ";
//                 players[i]->getHand()->displayHand();
//                 cout << endl;
//
//                 cout << "Tile replaced. Proceeding with the game." << endl;
//                 validInput = true;
//             } catch (const std::invalid_argument& e) {
//                 cout << "Invalid tile format. Please try again." << endl;
//                 cout << "> ";
//                 continue;
//             } catch (const std::out_of_range& e) {
//                 cout << "Invalid tile format. Please try again." << endl;
//                 cout << "> ";
//                 continue;
//             }
//         }
//     } else {
//                 cout << "Invalid choice. Please enter a valid option." << endl;
//             }
//         }
//     }
//     emptyHandExists = checkForEmptyPlayerHands(players, numPlayers);
// }
// }
//
//// Function to find starting player by finding the most matching types of tiles in hand
// int findStartingPlayer(Player** players, int numPlayers) {
//     int maxMatchingTiles = 0;
//     int startingPlayer = 0;
//
//     // Loop through each player to find matching tiles
//     for (int i = 0; i < numPlayers; ++i) {
//         int matchingTiles = 0;
//
//         // Use unordered_map to track counts of color and shape
//         std::unordered_map<char, int> colorCount;
//         std::unordered_map<int, int> shapeCount;
//
//         // Check the current player's hand for matching tiles
//         for (int k = 0; k < players[i]->getHand()->getSize(); ++k) {
//             Tile* currentTile = players[i]->getHand()->getTile(k);
//
//             // Update color count
//             if (colorCount.find(currentTile->getColour()) == colorCount.end()) {
//                 colorCount[currentTile->getColour()] = 1;
//             } else {
//                 colorCount[currentTile->getColour()]++;
//             }
//
//             // Update shape count
//             if (shapeCount.find(currentTile->getShape()) == shapeCount.end()) {
//                 shapeCount[currentTile->getShape()] = 1;
//             } else {
//                 shapeCount[currentTile->getShape()]++;
//             }
//         }
//
//         // Find the maximum count of matching tiles (color or shape)
//         for (const auto& pair : colorCount) {
//             matchingTiles = std::max(matchingTiles, pair.second);
//         }
//
//         for (const auto& pair : shapeCount) {
//             matchingTiles = std::max(matchingTiles, pair.second);
//         }
//
//         // Print the count for the current player
//         std::cout << "Player " << players[i]->getName() << " has " << matchingTiles << " tiles able to be played." << std::endl;
//
//         // Update startingPlayer based on the maximum count
//         if (matchingTiles > maxMatchingTiles || (matchingTiles == maxMatchingTiles && players[i]->getName() < players[startingPlayer]->getName())) {
//             maxMatchingTiles = matchingTiles;
//             startingPlayer = i;
//         }
//     }
//
//     return startingPlayer;
// }
//
//
//
//
//
//
// void initializeTileBag(std::vector<Tile> &tileBag)
//{
//     // Get definitions from TileCodes.h
//     char colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
//     int shapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
//
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
//
//     // Shuffle the tile bag
//     shuffleTileBag(tileBag);
// }
//
// void shuffleTileBag(std::vector<Tile> &tileBag)
//{
//     // Shuffle the tile bag
//     std::random_device rd;
//     std::default_random_engine rng(rd());
//     std::shuffle(tileBag.begin(), tileBag.end(), rng);
// }
//
// void initializePlayerHand(LinkedList& playerHand, std::vector<Tile> &tileBag)
//{
//     // Draw tiles from the tile bag and add them to the player's hand until there are 6 tiles
//     while (playerHand->getSize() < 6 && !bag->isEmpty())
//     {
//         // Get the tile pointer from the back of the bag
//         Tile* tileFromBagPtr = bag->back();
//
//         // bag->pop_back();
//         // Replaced pop_back with function that preserves the tile at the pointer, instead of deleting it.
//         bag->remove_back();
//
//         // Add the tile pointer directly to the player's hand
//         playerHand->addTile(tileFromBagPtr);
//     }
// }
// Function to find starting player by finding the most matching types of tiles in hand
Player *findStartingPlayer(Player *player1, Player *player2)
{
    Player *startingPlayer = nullptr;
    int maxMatchingTiles = 0;

    // Use unordered_map to track counts of color and shape for each player
    std::unordered_map<char, int> colorCount1, colorCount2;
    std::unordered_map<int, int> shapeCount1, shapeCount2;

    // Check player 1's hand for matching tiles
    for (int k = 0; k < player1->getHand()->getSize(); ++k)
    {
        Tile *currentTile = player1->getHand()->getTile(k);

        // Update color count
        if (colorCount1.find(currentTile->getColour()) == colorCount1.end())
        {
            colorCount1[currentTile->getColour()] = 1;
        }
        else
        {
            colorCount1[currentTile->getColour()]++;
        }

        // Update shape count
        if (shapeCount1.find(currentTile->getShape()) == shapeCount1.end())
        {
            shapeCount1[currentTile->getShape()] = 1;
        }
        else
        {
            shapeCount1[currentTile->getShape()]++;
        }
    }

    // Check player 2's hand for matching tiles
    for (int k = 0; k < player2->getHand()->getSize(); ++k)
    {
        Tile *currentTile = player2->getHand()->getTile(k);

        // Update color count
        if (colorCount2.find(currentTile->getColour()) == colorCount2.end())
        {
            colorCount2[currentTile->getColour()] = 1;
        }
        else
        {
            colorCount2[currentTile->getColour()]++;
        }

        // Update shape count
        if (shapeCount2.find(currentTile->getShape()) == shapeCount2.end())
        {
            shapeCount2[currentTile->getShape()] = 1;
        }
        else
        {
            shapeCount2[currentTile->getShape()]++;
        }
    }

    // Find the maximum count of matching tiles (color or shape) for player 1
    int matchingTiles1 = 0;
    for (const auto &pair : colorCount1)
    {
        matchingTiles1 = std::max(matchingTiles1, pair.second);
    }

    for (const auto &pair : shapeCount1)
    {
        matchingTiles1 = std::max(matchingTiles1, pair.second);
    }

    // Find the maximum count of matching tiles (color or shape) for player 2
    int matchingTiles2 = 0;
    for (const auto &pair : colorCount2)
    {
        matchingTiles2 = std::max(matchingTiles2, pair.second);
    }

    for (const auto &pair : shapeCount2)
    {
        matchingTiles2 = std::max(matchingTiles2, pair.second);
    }

    // Print the count for each player
    std::cout << player1->getName() << " has " << matchingTiles1 << " tiles able to be played." << std::endl;
    std::cout << player2->getName() << " has " << matchingTiles2 << " tiles able to be played." << std::endl;

    // Update startingPlayer based on the maximum count
    if (matchingTiles1 > maxMatchingTiles || (matchingTiles1 == maxMatchingTiles && player1->getName() < player2->getName()))
    {
        maxMatchingTiles = matchingTiles1;
        startingPlayer = player1;
    }

    if (matchingTiles2 > maxMatchingTiles || (matchingTiles2 == maxMatchingTiles && player2->getName() < player1->getName()))
    {
        maxMatchingTiles = matchingTiles2;
        startingPlayer = player2;
    }

    return startingPlayer;
}
