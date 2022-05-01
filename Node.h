
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"
#include <iostream>

using std::string;

// Scrabble double linked list node
class Node {
   public:
   // Default constructor
   Node(string data);
   // Constructor, recieves tile value, left and right neighbour pointers
   Node(string data, Node* prev, Node* next);
   Node(Node& other, Node* prev, Node* next);
   Node(Node& other);

   // Scrabble tile value of the Node
   string data;

   // Left and right neighbour pointers
   Node* prev;
   Node* next;
};

#endif // ASSIGN2_NODE_H
