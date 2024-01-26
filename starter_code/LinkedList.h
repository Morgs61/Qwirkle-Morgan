
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

   std::string toString();

private:
   Node *head;
   Node *tail;
};

#endif // ASSIGN2_LINKEDLIST_H