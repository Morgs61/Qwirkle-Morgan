
#include <vector>
#include "Player.h"
#include "Tile.h"
#include "Board.h"

class AIPlayer : public Player
{
private:
    // Private member variables and functions for the AI

public:
    // Constructor
    AIPlayer(std::string name, int score, LinkedList *hand) : Player(name, score, hand) {}

    // Destructor
    ~AIPlayer() {}

    // Function to make a move
    void makeMove(Board *board);

    // Function to generate all possible moves for the AI
    std::vector<std::pair<int, int>> generatePossibleMoves(Board *board);

    int evaluateMove(std::pair<int, int> move, Board *board);

    void placeTilesOnBoard(std::pair<int, int> move, Board *board);

    void removeTileFromHand(Tile *tile);

    Tile *getTileFromHand();
};