#include "Player.h"

// Constructor: Initializes a player with a unique name, an initial score, and an empty hand
Player::Player(std::string playerName, int initialScore, LinkedList *initialHand)
    : name(playerName), score(initialScore), hand(initialHand) {}

// Destructor: Deallocates the memory used by the player's hand
Player::~Player()
{
    delete hand;
}

// Retrieves the name of the player
std::string Player::getName()
{
    return name;
}

// Retrieves the current score of the player
int Player::getScore()
{
    return score;
}

// Retrieves the player's hand represented by a linked list
LinkedList *Player::getHand()
{
    return hand;
}

// Checks if two players refer to the same object in memory
bool Player::isSamePlayer(Player *otherPlayer)
{
    return this == otherPlayer;
}

// Increases the player's score by a specified amount
void Player::addPoints(int pointsToAdd)
{
    score += pointsToAdd;
}

bool Player::equals(Player *other)
{
    // Check if the pointers are equal
    if (this == other)
        return true;

    // Check if the other pointer is null
    if (!other)
        return false;

    // Check if the name, score, and hand are equal
    return (name == other->getName()) &&
           (score == other->getScore()) &&
           (hand->equals(other->getHand())); 
}