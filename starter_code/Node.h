
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node
{
public:
   Node(Tile *tile, Node *nextNodePtr);
   Node(Tile *tile);
   Node(Node &other);
   ~Node();

   void clearNodeList();

   Tile *getTile();
   Node *getNextNodePtr();
   void setNextNodePtr(Node *nextNodePtr);
   void setNextNodePtrNullptr();

   Tile *tile;
   Node *nextNodePtr;
};

#endif // ASSIGN2_NODE_H