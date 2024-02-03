#include <fstream>
#include <sstream>
#include <iomanip>
#include "Game.h"

void Game::loadGame(std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    std::string playerName;
    int playerScore;
    std::string playerHand;
    std::string boardShape;
    std::string boardState;
    std::string tileBagContents;
    std::string currentPlayerName;

    // Read player 1
    if (!std::getline(file, playerName) ||
        !file >> playerScore || file.get() != '\n' ||
        !std::getline(file, playerHand))
    {
        std::cerr << "Error: Invalid file format" << std::endl;
        return;
    }
    Player *player1 = new Player(playerName, playerScore, playerHand);

    // Read player 2
    if (!std::getline(file, playerName) ||
        !file >> playerScore || file.get() != '\n' ||
        !std::getline(file, playerHand))
    {
        delete player1;
        std::cerr << "Error: Invalid file format" << std::endl;
        return;
    }
    Player *player2 = new Player(playerName, playerScore, playerHand);

    // Read board
    if (!std::getline(file, boardShape) ||
        !std::getline(file, boardState))
    {
        delete player1;
        delete player2;
        std::cerr << "Error: Invalid file format" << std::endl;
        return;
    }
    Board *board = new Board(boardShape, boardState);

    // Read tile bag contents
    if (!std::getline(file, tileBagContents))
    {
        delete player1;
        delete player2;
        delete board;
        std::cerr << "Error: Invalid file format" << std::endl;
        return;
    }
    LinkedList *bag = new LinkedList();
    std::istringstream iss(tileBagContents);
    std::string tileStr;
    while (iss >> tileStr)
    {
        Tile *tile = parseTile(tileStr); // Implement parseTile to convert string to Tile
        bag->push_back(tile);
    }

    // Read current player name
    if (!std::getline(file, currentPlayerName))
    {
        delete player1;
        delete player2;
        delete board;
        delete bag;
        std::cerr << "Error: Invalid file format" << std::endl;
        return;
    }

    // Construct the current player pointer based on the name read
    Player *currentPlayer = (currentPlayerName == player1->getName()) ? player1 : player2;

    // Close the file
    file.close();

    // Update game state with loaded data
    // Assuming you have appropriate setter functions in your Game class
    setPlayer1(player1);
    setPlayer2(player2);
    setBag(bag);
    setBoard(board);
    setCurrentPlayer(currentPlayer);

    // Continue with normal gameplay
    launchGame();
}
