
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList
{
public:
   LinkedList();
   ~LinkedList();

   int getSize();

   void addTile(Tile *tile);

   void addTileToHand(Tile *tile);

   bool isEmpty() const;

   void displayHand();

   bool containsTile(Tile *tile);

   bool removeTile(Tile *tile);

   void initializeAndShuffleBag();

   void shuffle();

   void pop_back();

   void push_back(Tile *tile);

   std::string toString();

   Node *begin();
   Node *end();
   Tile *back();

private:
   Node *head;
   Node *tail;
};

#endif // ASSIGN2_LINKEDLIST_H