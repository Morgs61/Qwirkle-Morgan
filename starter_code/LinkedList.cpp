#include <iostream>
#include <vector>
#include "LinkedList.h"
#include "Node.h"

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

int LinkedList::size()
{
   int count = 0;

   if (head != nullptr)
   {
      Node *currentNode = head;

      // Traverse the linked list and count nodes
      while (currentNode->getNext() != nullptr)
      {
         count++;
         currentNode = currentNode->getNext();
      }
      count++;
   }

   return count;
}

// Implementation of get function
Tile *LinkedList::get(int index)
{
   Tile *rTile = nullptr;

   // Check if the index is valid and the linked list is not empty
   if (index >= 0 && index < size() && head != nullptr)
   {
      Node *currentNode = head;

      // Traverse the linked list to the specified index
      for (int i = 0; i < index; i++)
      {
         currentNode = currentNode->getNext();
      }

      // Get the tile at the specified index
      rTile = currentNode->getTile();
   }

   return rTile;
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

// Convert the linked list to a string representation
std::string LinkedList::toString()
{
   std::string linkedListString = "";
   if (head != nullptr)
   {
      Node *currentNode = head;
      bool cont = true;
      while (cont)
      {
         linkedListString = linkedListString + currentNode->getTile()->toString();

         if (currentNode->getNext() == nullptr)
         {
            cont = false;
         }
         else
         {
            linkedListString = linkedListString + ",";
            currentNode = currentNode->getNext();
         }
      }
   }

   return linkedListString;
}

std::vector<Tile *> LinkedList::getAllTiles()
{
   std::vector<Tile *> tiles;
   int listSize = size();

   for (int i = 0; i < listSize; ++i)
   {
      Tile *tile = get(i);
      tiles.push_back(tile);
   }

   return tiles;
}