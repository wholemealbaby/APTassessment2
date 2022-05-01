
#include "Node.h"
#include <iostream>

using string = std::string;

Node::Node(string data){
   this->data = data;
   this->prev = nullptr;
   this->next = nullptr;
}

Node::Node(string data, Node* prev, Node* next){
   this->data = data;
   this->prev = prev;
   this->next = next;
}

Node::Node(Node& other, Node* prev, Node* next){
   this->data = other.data;
   this->prev = other.prev;
   this->next = other.next;
}

Node::Node(Node& other){
   this->data = other.data;
   this->prev = other.prev;
   this->next = other.next;
}
