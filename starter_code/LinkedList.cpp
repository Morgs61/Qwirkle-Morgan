#include <iostream>
#include "LinkedList.h"
#include <ctime>
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
        Node *nextNodePtr = current->nextNodePtr;
        delete current->tile; // Free the memory for the tile
        delete current;       // Free the memory for the node
        current = nextNodePtr;
    }
}

// return tile at index
Tile *LinkedList::getTile(int index)
{
    Node *current = head;
    int count = 0;
    while (current != nullptr)
    {
        if (count == index)
        {
            return current->tile;
        }
        count++;
        current = current->nextNodePtr;
    }
    return nullptr;
}

// return size of linkedlist
int LinkedList::getSize() const
{
    int size = 0;
    Node *current = head;
    while (current != nullptr)
    {
        size++;
        current = current->nextNodePtr;
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
        tail = newNode;
    }
    else
    {
        tail->nextNodePtr = newNode;
        tail = newNode;
    }
}

bool LinkedList::isEmpty() const
{
    return head == nullptr;
}

void LinkedList::displayHand() const
{
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << "[" << current->tile->getColour() << "" << current->tile->getShape() << "] ";
        current = current->nextNodePtr;
    }
    std::cout << std::endl;
}

bool LinkedList::containsTile(Tile *tile) const
{
    Node *current = head;

    while (current != nullptr)
    {
        if (current->tile->getColour() == tile->getColour() && current->tile->getShape() == tile->getShape())
        {
            // Found the tile
            std::cout << "Tile found: [" << current->tile->getColour() << ", " << current->tile->getShape() << "]" << std::endl;
            return true;
        }

        current = current->nextNodePtr;
    }

    // Tile not found
    return false;
}

bool LinkedList::removeTile(Tile *tile)
{
    if (head != nullptr)
    {
        Node *current = head;
        Node *previous = nullptr;

        while (current != nullptr)
        {

            if (current->tile != nullptr && current->tile->getColour() == tile->getColour() && current->tile->getShape() == tile->getShape())
            {
                if (previous == nullptr)
                {
                    head = current->nextNodePtr;
                }
                else
                {
                    previous->nextNodePtr = current->nextNodePtr;
                }

                if (current == tail)
                {
                    tail = previous;
                }

                delete current;
                return true;
            }

            previous = current;
            current = current->nextNodePtr;
        }
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
            // log the tile being added
            // std::cout << "Adding tile: [" << colour << ", " << shape << "]" << std::endl;
            // Add two pointers to each type of tile to the tile bag
            addTile(new Tile(colour, shape));
            addTile(new Tile(colour, shape));
        }
    }
    // // Print the contents of the bag
    // std::cout << "Tile Bag Contents: ";
    // displayHand(); // Display the contents of the tile bag
    // // Shuffle the tile bag
    shuffle();
    // // Print the contents of the bag
    // std::cout << " after shuffle Tile Bag Contents: ";
    // displayHand(); // Display the contents of the tile bag
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
        current = current->nextNodePtr;
    }
    srand(static_cast<unsigned int>(time(nullptr)));
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
        nodes[i]->nextNodePtr = nodes[i + 1];
    }
    nodes[count - 1]->nextNodePtr = nullptr;

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

Node *LinkedList::getHead()
{
    return head;
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
    while (current->nextNodePtr != tail)
    {
        current = current->nextNodePtr;
    }
    // Remove the last node
    delete tail;
    tail = current;
    tail->nextNodePtr = nullptr;
}

// removes the last tile in the linked list but preserves the tile object.
void LinkedList::remove_back()
{
    if (head == nullptr)
    {
        // The list is empty, nothing to remove
        return;
    }
    if (head == tail)
    {
        // Only one node in the list
        head = tail = nullptr;
        return;
    }
    // Traverse the list to find the second-to-last node
    Node *current = head;
    while (current->nextNodePtr != tail)
    {
        current = current->nextNodePtr;
    }
    // Remove the last node
    tail = current;
    tail->nextNodePtr = nullptr;
}

void LinkedList::push_back(Tile *tile)
{
    Node *newNode = new Node(tile); // Create a new node with the given tile
    if (head == nullptr)             // If the list is empty, set the new node as the head and tail
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->setNext(newNode); // Set the next pointer of the last node to the new node
        tail = newNode; // Update the tail to the new node
    }
}

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