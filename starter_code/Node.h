
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node
{
public:
   Node(Tile *tile, Node *next);
   Node(Node &other);
   ~Node();

   // Get the tile stored in the node
   Tile *getTile();

   // Get the next node in the linked list
   Node *getNext();

   Tile *tile;
   Node *next;
};

#endif // ASSIGN2_NODE_H