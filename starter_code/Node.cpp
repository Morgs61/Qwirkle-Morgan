
#include "Node.h"

Node::Node(Tile *tile, Node *nextNodePtr) {
  this->tile = tile;
  this->nextNodePtr = nextNodePtr;
}

Node::Node(Tile *tile) {
  this->tile = tile;
  this->nextNodePtr = nullptr;
}

Node::Node(Node &other) {
  this->tile = other.tile;
  this->nextNodePtr = other.nextNodePtr;
}

Node::~Node() {
  if (tile != nullptr) {
    delete tile;
  }
}

void Node::clearNodeList() {
  if (nextNodePtr != nullptr) {
    nextNodePtr->~Node();
  }
}

Tile *Node::getTile() { return tile; }
Node *Node::getNext() { return nextNodePtr; }

void Node::setNext(Node *nextNodePtr) { this->nextNodePtr = nextNodePtr; }

void Node::setNextNullptr() { this->nextNodePtr = nullptr; }