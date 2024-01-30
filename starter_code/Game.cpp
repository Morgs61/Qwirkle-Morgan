//
// Created by alex on 30/01/24.
//

#include "Game.h"
#include <iostream>
#include <algorithm>
#include <random>

Game::Game(std::vector<Player*> players, LinkedList *bag, Board *board, int currentPlayerTurn)
{
    this->players = players;
    this->bag = bag;
    this->board = board;
    this->currentPlayerTurn = currentPlayerTurn;
    playerCount = players.size();
}

Game::~Game()
{
    delete board;
    delete bag;
    for (int i = 0; i < playerCount; i++)
    {
        delete players[i];
    }
}