#include <iostream>
#include "TileCodes.h"
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
      std::cout << "Node: " << current << ", Tile: " << current->tile;
      if (current->tile != nullptr)
      {
         std::cout << " [" << current->tile->colour << "" << current->tile->shape << "] ";
      }
      else
      {
         std::cout << " [nullptr] ";
      }
      std::cout << std::endl;
      current = current->next;
   }
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
         // Add two pointers to each type of tile to the tile bag
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

Node *LinkedList::begin()
{
   return head;
}

Node *LinkedList::end()
{
   return nullptr;
}

Tile *LinkedList::back()
{
   if (tail != nullptr)
   {
      return tail->tile;
   }
   else
   {
      return nullptr; // Return nullptr if the list is empty
   }
}

void LinkedList::pop_back()
{
   if (head == nullptr)
   {
      // The list is empty, nothing to pop
      return;
   }
   if (head == tail)
   {
      // Only one node in the list
      delete head;
      head = tail = nullptr;
      return;
   }
   // Traverse the list to find the second-to-last node
   Node *current = head;
   while (current->next != tail)
   {
      current = current->next;
   }
   // Remove the last node
   delete tail;
   tail = current;
   tail->next = nullptr;
}

void LinkedList::push_back(Tile *tile)
{
   Node *newNode = new Node(tile, nullptr);
   if (head == nullptr)
   {
      head = newNode;
      tail = newNode;
   }
   else
   {
      tail->next = newNode;
      tail = newNode;
   }
}