
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
   Node(string data, Node* leftNeighbour, Node* rightNeighbour);
   Node(Node& other);

   // Scrabble tile value of the Node
   string data;

   // Left and right neighbour pointers
   Node* leftNeighbour;
   Node* rightNeighbour;
};

#endif // ASSIGN2_NODE_H
