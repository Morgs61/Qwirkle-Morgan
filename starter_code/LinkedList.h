#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include "Tile.h"

class LinkedList {
 public:
  LinkedList();
  void initialize() {
    head = nullptr;
    tail = nullptr;
  }
  ~LinkedList();
  void addTile(Tile *tile);
  bool removeTile(Tile *tile);
  bool containsTile(Tile *tile) const;
  int getSize() const;
  bool isEmpty() const;
  void displayHand() const;

  // Add missing function declarations
  void initializeAndShuffleBag();
  void initializeLoadedBag();
  void shuffle();
  Node *begin();
  Node *end();
  Tile *back();
  void pop_back();
  void remove_back();
  void push_back(Tile *tile);
  Tile *getTile(int index);
  std::string toString();
  Node *getHead();  // Declaration of the getHead() method
 private:
  Node *head;
  Node *tail;
};

#endif  // ASSIGN2_LINKEDLIST_H