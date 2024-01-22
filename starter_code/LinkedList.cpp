
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;

   // TODO
}

LinkedList::~LinkedList() {

}

//return size of linkedlist
int LinkedList::getSize() {
   int size = 0;
   Node* current = head;
   while (current != nullptr) {
      size++;
      current = current->next;
   }
   return size;
}

