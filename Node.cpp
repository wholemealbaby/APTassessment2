
#include "Node.h"
#include <iostream>

using string = std::string;

Node::Node(string data){
   this->data = data;
   this->leftNeighbour = nullptr;
   this->rightNeighbour = nullptr;
}

Node::Node(string data, Node* leftNeighbour, Node* rightNeighbour){
   this->data = data;
   this->leftNeighbour = leftNeighbour;
   this->rightNeighbour = rightNeighbour;
}
Node::Node(Node& other){
   this->data = other.data;
   this->leftNeighbour = other.leftNeighbour;
   this->rightNeighbour = other.rightNeighbour;
}
