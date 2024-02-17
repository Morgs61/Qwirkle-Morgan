#include "AIPlayer.h"
#include "Board.h"
#include <iostream>

// Constructor
AIPlayer::AIPlayer(std::string name, int score, LinkedList *hand) : Player(name, score, hand)
{
    // Initialize any AI-specific variables here
}

// Function to make a move
void AIPlayer::makeMove(Board *board)
{
    // Generate all possible moves
    std::vector<std::pair<int, int>> possibleMoves = generatePossibleMoves(board);

    // Evaluate each move and select the best move
    std::pair<int, int> bestMove;
    int bestScore = 0;

    for (const auto &move : possibleMoves)
    {
        // Evaluate the move and calculate its score
        int moveScore = evaluateMove(move, board);

        // Update the best move if the current move has a higher score
        if (moveScore > bestScore)
        {
            bestMove = move;
            bestScore = moveScore;
        }
    }

    // Make the best move on the board
    placeTilesOnBoard(bestMove, board);

    // Other necessary actions after making the move
}

// Function to generate all possible moves for the AI
std::vector<std::pair<int, int>> AIPlayer::generatePossibleMoves(Board *board)
{
    std::vector<std::pair<int, int>> possibleMoves;
    // Implement the logic to generate possible moves here
    // This function should return a vector of pairs representing possible moves on the board
    return possibleMoves;
}

// Function to evaluate a move
int AIPlayer::evaluateMove(std::pair<int, int> move, Board *board)
{
    int moveScore = 0;

    // Retrieve the coordinates of the move
    int row = move.first;
    int col = move.second;

    // Check if the move is valid (for example, not out of bounds)
    if (row >= 0 && row < board->getHeight() && col >= 0 && col < board->getWidth())
    {
        // Check if the move creates a horizontal or vertical pattern
        int horizontalScore = board->calculatePatternScore(row, col, 1, 0); // Check horizontal pattern
        int verticalScore = board->calculatePatternScore(row, col, 0, 1);   // Check vertical pattern

        // Calculate the total score for the move
        moveScore = horizontalScore + verticalScore;
    }

    return moveScore;
}

// Function to place tiles on the board
void AIPlayer::placeTilesOnBoard(std::pair<int, int> move, Board *board)
{
    // Retrieve the coordinates of the move
    int row = move.first;
    int col = move.second;

    Tile *tile = getTileFromHand(); // function to get a tile from the AI player's hand

    // Place the tile on the board
    if (tile && board)
    {
        board->placeTile(tile, row, col); // function to place the tile on the board
        removeTileFromHand(tile);         // function to remove the tile from the AI player's hand
        delete tile;                      // Remember to delete the tile since it's dynamically allocated
    }
    else
    {
        // Handle the case where the tile retrieved from the hand is not valid
        std::cout << "Error: Invalid tile retrieved from hand!" << std::endl;
    }
}

// Function to remove a tile from the player's hand
void AIPlayer::removeTileFromHand(Tile *tile)
{
    bool removed = getHand()->removeTile(tile);
    if (!removed)
    {
        std::cout << "Error: Tile not found in the hand!" << std::endl;
    }
}

// Function to get a tile from the player's hand
Tile *AIPlayer::getTileFromHand()
{
    LinkedList *hand = getHand();
    if (hand && !hand->isEmpty())
    {
        // Assuming hand is a linked list of tiles
        // You can traverse the linked list to get the first tile in the hand
        return hand->getHead()->getTile();
    }
    else
    {
        std::cerr << "Error: Hand is empty!" << std::endl;
        return nullptr;
    }
}
