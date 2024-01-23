
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

void LinkedList::addTileToHand(Tile *tile)
{
}