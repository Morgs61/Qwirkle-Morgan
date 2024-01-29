#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <vector>
#include <string>

class LinkedList
{
public:
   LinkedList();
   ~LinkedList();

   // Get the size of the linked list
   int size();

   // Add a tile to the linked list
   void addTile(Tile *tile);

   // Add a tile to the hand
   void addTileToHand(Tile *tile);

   // Check if the linked list is empty
   bool isEmpty() const;

   // Display the contents of the hand
   void displayHand();

   // Check if the linked list contains a specific tile
   bool containsTile(Tile *tile);

   // Remove a specific tile from the linked list
   bool removeTile(Tile *tile);

   // Convert the linked list to a string representation
   std::string toString();

   // Get all tiles in the linked list
   std::vector<Tile *> getAllTiles();

   // Get a tile at a specific index
   Tile *get(int index);

   // Comparison
   bool equals(LinkedList& other);

private:
   Node *head;
   Node *tail;
};

#endif // ASSIGN2_LINKEDLIST_H
