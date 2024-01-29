#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "LinkedList.h"

class Player
{
public:
    // Constructor: Initializes a player with a unique name, an initial score, and an empty hand
    Player(std::string playerName, int initialScore, LinkedList *initialHand);

    // Destructor
    ~Player();

    // Retrieves the name of the player
    std::string getName();

    // Retrieves the current score of the player
    int getScore();

    // Retrieves the player's hand represented by a linked list
    LinkedList *getHand();

    // Checks if two players refer to the same object in memory
    bool isSamePlayer(Player *otherPlayer);

    // Increases the player's score by a specified amount
    void addPoints(int pointsToAdd);

    // Comparison
    bool equals(Player &other);

private:
    std::string name;
    int score;
    LinkedList *hand;
};

// Implement the << operator for Player
std::ostream &operator<<(std::ostream &os, Player &player)
{
    // Output the details of the player to the stream
    os << "Player Name: " << player.getName() << ", Score: " << player.getScore() << ", Hand: " << player.getHand();
    return os;
}

#endif // PLAYER_H
