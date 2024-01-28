//
// Created by alex on 28/01/24.
//

#include "Player.h"

Player::Player(const std::string& name, int score, LinkedList* hand) {
    this->name = name;
    this->score = score;
    this->hand = hand ? new LinkedList(*hand) : nullptr;
}

Player::~Player() {
    delete hand;
}

std::string Player::getName() const {
    return name;
}

void Player::setName(const std::string& newName) {
    name = newName;
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int newScore) {
    score = newScore;
}

void Player::addScore(int points) {
    score += points;
}

LinkedList* Player::getHand() const {
    return hand;
}

