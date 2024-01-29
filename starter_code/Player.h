//
// Created by alex on 28/01/24.
//

#ifndef APT2023_A2_PLAYER_H
#define APT2023_A2_PLAYER_H

#include <string>
#include "LinkedList.h"

class Player {
private:
    std::string name;
    int score;
    LinkedList* hand;

public:
    Player() : name(""), score(0), hand(nullptr) {}  // Default constructor

    Player(const std::string& name, int score, LinkedList* hand) {
        this->name = name;
        this->score = score;
        this->hand = hand ? new LinkedList(*hand) : nullptr;
    }

    ~Player() {
        delete hand;
    }

    std::string getName() const {
        return name;
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    int getScore() const {
        return score;
    }

    void setScore(int newScore) {
        score = newScore;
    }

    void addScore(int points) {
        score += points;
    }

    LinkedList* getHand() const {
        return hand;
    }

    LinkedList* setHand(LinkedList* newHand) {
        LinkedList* oldHand = hand;
        hand = newHand;
        return oldHand;
    }
};

#endif //APT2023_A2_PLAYER_H