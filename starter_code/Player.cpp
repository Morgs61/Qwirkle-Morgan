//
// Created by alex on 28/01/24.
//

#include "Player.h"

Player::Player(std::string &name, int score, LinkedList *hand) {
  this->name = name;
  this->score = score;
  this->hand = hand ? new LinkedList(*hand) : nullptr;
}

Player::~Player() { delete hand; }

std::string Player::getName() { return name; }

void Player::setName(std::string &newName) { name = newName; }

int Player::getScore() { return score; }

void Player::setScore(int newScore) { score = newScore; }

void Player::addScore(int points) { score += points; }

LinkedList *Player::getHand() { return hand; }
