//
// Created by alex on 28/01/24.
//

#ifndef APT2023_A2_PLAYER_H
#define APT2023_A2_PLAYER_H

#include <string>
#include "LinkedList.h"

class Player
{
private:
    std::string name;
    int score;
    LinkedList *hand;

public:
    Player() : name(""), score(0), hand(nullptr) {} // Default constructor

    Player(std::string &name, int score, LinkedList *hand)
    {
        this->name = name;
        this->score = score;
        this->hand = hand ? new LinkedList(*hand) : nullptr;
    }

    ~Player()
    {
        delete hand;
    }

    std::string getName()
    {
        return name;
    }

    void setName(std::string &newName)
    {
        name = newName;
    }

    int getScore()
    {
        return score;
    }

    void setScore(int newScore)
    {
        score = newScore;
    }

    void addScore(int points)
    {
        score += points;
    }

    LinkedList *getHand()
    {
        return hand;
    }

    LinkedList *setHand(LinkedList *newHand)
    {
        LinkedList *oldHand = hand;
        hand = newHand;
        return oldHand;
    }
    //Player* findStartingPlayer(Player* player1, Player* player2);

};

#endif // APT2023_A2_PLAYER_H