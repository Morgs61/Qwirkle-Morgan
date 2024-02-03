#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "LinkedList.h"
#include "Board.h"

class Game
{
private:
    Player *player1;
    Player *player2;
    LinkedList *bag;
    Board *board;
    Player *currentPlayer;

public:
    Game(Player *player1, Player *player2, LinkedList *bag, Board *board, Player *currentPlayer);
    ~Game();
    void launchGame();
    void loadGame(std::string &filename); // Declaration of loadGame function

    // Add other member functions as needed

    // Getters and setters
    void setPlayer1(Player *player1) { this->player1 = player1; }
    Player *getPlayer1() { return player1; }

    void setPlayer2(Player *player2) { this->player2 = player2; }
    Player *getPlayer2() { return player2; }

    void setBag(LinkedList *bag) { this->bag = bag; }
    LinkedList *getBag() { return bag; }

    void setBoard(Board *board) { this->board = board; }
    Board *getBoard() { return board; }

    void setCurrentPlayer(Player *currentPlayer) { this->currentPlayer = currentPlayer; }
    Player *getCurrentPlayer() { return currentPlayer; }
};

#endif // GAME_H
