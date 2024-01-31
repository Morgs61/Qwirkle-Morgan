#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList()
{
   head = nullptr;
   tail = nullptr;

   // TODO
}

LinkedList::~LinkedList()
{
   // Destructor to free memory
   Node *current = head;
   while (current != nullptr)
   {
      Node *next = current->next;
      delete current->tile; // Free the memory for the tile
      delete current;       // Free the memory for the node
      current = next;
   }
}

// return size of linkedlist
int LinkedList::getSize()
{
   int size = 0;
   Node *current = head;
   while (current != nullptr)
   {
      size++;
      current = current->next;
   }
   return size;
}

// LinkedList.cpp

void LinkedList::addTile(Tile *tile)
{
   Node *newNode = new Node(tile, nullptr);
   if (head == nullptr)
   {
      head = newNode;
   }
   else
   {
      Node *current = head;
      while (current->next != nullptr)
      {
         current = current->next;
      }
      current->next = newNode;
   }
}

bool LinkedList::isEmpty() const
{
   return head == nullptr;
}

// Add a tile to the hand
void LinkedList::addTileToHand(Tile *tile)
{
   Node *newNode = new Node(tile, nullptr);
   if (head == nullptr)
   {
      head = newNode;
   }
   else
   {
      Node *current = head;
      while (current->next != nullptr)
      {
         current = current->next;
      }
      current->next = newNode;
   }
}

// Display the tiles in the hand
void LinkedList::displayHand()
{
   Node *current = head;
   while (current != nullptr)
   {
      std::cout << "[" << current->tile->colour << "" << current->tile->shape << "] ";
      current = current->next;
   }
   std::cout << std::endl;
}
bool LinkedList::containsTile(Tile *tile)
{
   Node *current = head;

   while (current != nullptr)
   {
      if (current->tile->colour == tile->colour && current->tile->shape == tile->shape)
      {
         // Found the tile
         std::cout << "Tile found: [" << current->tile->colour << ", " << current->tile->shape << "]" << std::endl;
         return true;
      }

      current = current->next;
   }

   // Tile not found
   return false;
}

bool LinkedList::removeTile(Tile *tile)
{
   Node *current = head;
   Node *previous = nullptr;

   while (current != nullptr)
   {
      if (current->tile->colour == tile->colour && current->tile->shape == tile->shape)
      {
         // Found the tile to remove
         if (previous == nullptr)
         {
            // The tile to remove is at the head of the list
            head = current->next;
         }
         else
         {
            // The tile to remove is somewhere else in the list
            previous->next = current->next;
         }

         // If the tile to remove is at the tail of the list
         if (current == tail)
         {
            tail = previous;
         }

         delete current;
         return true; // Tile found and removed
      }

      previous = current;
      current = current->next;
   }

   return false; // Tile not found
}

void LinkedList::initializeAndShuffleBag()
{
   // Get definitions from TileCodes.h
   char colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
   int shapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

   // Create all combinations of colours and shapes
   for (char colour : colours)
   {
      for (int shape : shapes)
      {
         // Add two tiles of each type to the tile bag
         addTile(new Tile(colour, shape));
         addTile(new Tile(colour, shape));
      }
   }

   // Shuffle the tile bag
   shuffle();
}

void LinkedList::shuffle()
{
   // Count the number of nodes in the list
   int count = getSize();

   // Create an array to hold pointers to all nodes
   Node **nodes = new Node *[count];

   // Traverse the list and store pointers to each node in the array
   Node *current = head;
   int i = 0;
   while (current != nullptr)
   {
      nodes[i++] = current;
      current = current->next;
   }

   // Shuffle the array of node pointers using the Fisher-Yates shuffle algorithm
   for (int i = count - 1; i > 0; --i)
   {
      int j = rand() % (i + 1); // Generate a random index between 0 and i
      if (i != j)
      {
         // Swap the pointers at indices i and j
         Node *temp = nodes[i];
         nodes[i] = nodes[j];
         nodes[j] = temp;
      }
   }

   // Reconstruct the list using the shuffled array
   head = nodes[0];
   tail = nodes[count - 1];
   for (int i = 0; i < count - 1; ++i)
   {
      nodes[i]->next = nodes[i + 1];
   }
   nodes[count - 1]->next = nullptr;

   // Clean up
   delete[] nodes;
}
