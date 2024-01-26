
#include "Node.h"

Node::Node(Tile *tile, Node *next)
{
   this->tile = tile;
   this->next = next;
}

Node::Node(Node &other)
{
   this->tile = other.tile;
   this->next = other.next;
}

Node::~Node()
{
   delete tile;
}

// Get the tile stored in the node
Tile *Node::getTile()
{
   return tile;
}

// Get the next node in the linked list
Node *Node::getNext()
{
   return next;
}