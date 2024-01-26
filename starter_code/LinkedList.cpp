#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList()
{
   head = nullptr;

   // TODO
}

LinkedList::~LinkedList()
{
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


void LinkedList::removeTile(Tile* tile) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->tile->colour == tile->colour && current->tile->shape == tile->shape) {
            // Found the tile to remove
            if (previous == nullptr) {
                // The tile to remove is at the head of the list
                head = current->next;
            } else {
                // The tile to remove is somewhere else in the list
                previous->next = current->next;
            }

            delete current;
            break;
        }

        previous = current;
        current = current->next;
    }
}