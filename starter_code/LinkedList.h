
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

private:
   Node *head;
};

#endif // ASSIGN2_LINKEDLIST_H