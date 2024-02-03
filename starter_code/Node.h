
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node
{
public:
   Node(Tile *tile, Node *next);
   Node(Tile *tile);
   Node(Node &other);

   ~Node();

   void clearNodeList();

   Tile *getTile();
   Tile *getData();
   Node *getNext();
   void setNext(Node *next);
   void setNextNullptr();

   Tile *tile;
   Node *next;
   Tile *data; // Member to hold the tile data
};

#endif // ASSIGN2_NODE_H