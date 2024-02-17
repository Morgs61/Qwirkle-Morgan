#include "AIPlayer.h"
#include "Board.h"
#include "Player.h"
#include <iostream>
#include "LinkedList.h"
#include <set>

// Constructor definition
AIPlayer::AIPlayer(std::string name, int score, LinkedList *hand) : Player(name, score, hand) {}

// Destructor definition
AIPlayer::~AIPlayer() {}

// Function to make a move
void AIPlayer::makeMove(Board *board)
{
    // Get a tile from the AI player's hand
    Tile *tile = getBestTileFromHand(board);

    // // Get the colour and shape of the tile
    // Colour colour = tile->getColour();
    // Shape shape = tile->getShape();

    // Generate all possible moves for the selected tile
    std::vector<std::pair<int, int>> possibleMoves = generatePossibleMoves(board, tile);

    // Evaluate each move and select the best move
    std::pair<int, int> bestMove;
    int bestScore = 0;

    for (const auto &move : possibleMoves)
    {
        // Check if the tile can be placed at the current move position
        if (board->canPlaceTile(tile, move.first, move.second))
        {
            // Evaluate the move and calculate its score
            int moveScore = evaluateMove(board, tile, move.first, move.second);

            // Update the best move if the current move has a higher score
            if (moveScore > bestScore)
            {
                bestMove = move;
                bestScore = moveScore;
            }
        }
    }
    // Make the best move on the board
    placeTilesOnBoard(bestMove, board);

    // Other necessary actions after making the move
}

// Generate possible moves considering the color and shape of the tile
std::vector<std::pair<int, int>> AIPlayer::generatePossibleMoves(Board *board, Tile *tile)
{
    std::vector<std::pair<int, int>> moves;

    // Iterate over all positions on the board
    for (int row = 0; row < board->getHeight(); ++row)
    {
        for (int col = 0; col < board->getWidth(); ++col)
        {
            // Check if the tile can be placed at this position
            if (board->canPlaceTile(tile, row, col))
            {
                moves.push_back(std::make_pair(row, col));
            }
        }
    }

    return moves;
}

// Function to get the set of occupied positions on the board
std::set<std::pair<int, int>> AIPlayer::getOccupiedPositions(Board *board)
{
    std::set<std::pair<int, int>> occupiedPositions;

    // Iterate over all positions on the board
    for (int row = 0; row < board->getHeight(); ++row)
    {
        for (int col = 0; col < board->getWidth(); ++col)
        {
            // Check if the position is occupied by a tile
            if (board->getTileAt(row, col) != nullptr)
            {
                // Add the position to the set of occupied positions
                occupiedPositions.insert({row, col});
            }
        }
    }

    return occupiedPositions;
}

// Function to evaluate a move
int AIPlayer::evaluateMove(Board *board, Tile *tile, int row, int col)
{
    int moveScore = 0;

    // Check if the move is valid (for example, not out of bounds)
    if (row >= 0 && row < board->getHeight() && col >= 0 && col < board->getWidth())
    {
        // Get the tile at the specified position
        Tile *boardTile = board->getTileAt(row, col);

        // Check if the position is occupied and the tile matches the adjacent tile
        if (boardTile && (boardTile->getColour() == tile->getColour() || boardTile->getShape() == tile->getShape()))
        {
            // Calculate the score for the move based on some criteria
            // Example: count the number of adjacent tiles with matching colour or shape
            moveScore = 1; // Example score calculation
        }
    }

    return moveScore;
}

// Function to place tiles on the board
void AIPlayer::placeTilesOnBoard(std::pair<int, int> move, Board *board)
{
    // Retrieve the coordinates of the move
    int row = move.first;
    int col = move.second;

    Tile *tile = getBestTileFromHand(board); // function to get a tile from the AI player's hand

    // Place the tile on the board
    if (tile && board)
    {
        board->placeTile(tile, row, col); // function to place the tile on the board
        removeTileFromHand(tile);         // function to remove the tile from the AI player's hand
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

Tile *AIPlayer::getBestTileFromHand(Board *board)
{
    LinkedList *hand = getHand();
    Tile *bestTile = nullptr;
    int bestScore = -1;

    if (hand && !hand->isEmpty())
    {
        // Iterate over all tiles in the hand
        for (Node *node = hand->getHead(); node != nullptr; node = node->getNext())
        {
            Tile *tile = node->getTile();
            int tileScore = 0;

            // Generate possible moves for this tile
            std::vector<std::pair<int, int>> moves = generatePossibleMoves(board, tile);

            // Evaluate these moves and select the best one
            for (auto &move : moves)
            {
                int score = evaluateMove(board, tile, move.first, move.second);
                tileScore += score; // Accumulate the score for all possible moves
            }

            // Update bestTile if the current tile has a higher total score
            if (tileScore > bestScore)
            {
                bestScore = tileScore;
                bestTile = tile;
            }
        }

        // Debugging: print out the state of the hand and the tile that is being returned
        std::cout << "Hand size: " << hand->getSize() << std::endl;
        if (bestTile)
        {
            std::cout << "Returning tile with color: " << bestTile->getColour() << " and shape: " << bestTile->getShape() << std::endl;
        }
        else
        {
            std::cout << "No valid moves found!" << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Hand is empty!" << std::endl;
    }

    return bestTile;
}
