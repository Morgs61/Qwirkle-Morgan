
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node
{
public:
   Node(Tile *tile, Node *next);
   Node(Node &other);
   ~Node();

   Tile *tile;
   Node *next;

private:
   // Private constructor and assignment operator to prevent copying
   Node(Node &other);
   Node &operator=(Node &other);
};

#endif // ASSIGN2_NODE_H