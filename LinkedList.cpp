//345678911234567892123456789312345678941234567895123456789612345678971234567898
#include <iostream>

#include "Node.h"
#include "LinkedList.h"
#include "Tile.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   length = 0;
}

LinkedList::~LinkedList(){
   Node* currentNode = head;
   // Iterating through the list and deleting the previous node
   while (currentNode->rightNeighbour != nullptr){
      currentNode = currentNode->rightNeighbour;
      delete currentNode->leftNeighbour;
      currentNode->leftNeighbour = nullptr;
   }

   // Deleting final node and setting pointers to null
   delete currentNode;
   currentNode = nullptr;
   head = nullptr;
   tail = nullptr;
}

// Appends a Node to the end of the array
void LinkedList::append(Node* incomingNode){
   // If the list is empty
   if (tail == nullptr){

      // Set the tail and head to the node and ensure that its neighbour
      // pointers point to null
      head = incomingNode;
      tail = incomingNode;
      incomingNode->leftNeighbour = nullptr;
      incomingNode->rightNeighbour = nullptr;
   }

   // If the list is not empty
   else{

      // Insert the node at the back of the list and set it as the tail
      incomingNode->leftNeighbour = tail;
      incomingNode->rightNeighbour = nullptr;
      tail = incomingNode;
   }

   length++;
}

// Appends a Node to the end of the array
void LinkedList::append(string data){
   Node* incomingNode = new Node(data);
   // If the list is empty
   if (tail == nullptr){

      // Set the tail and head to the node and ensure that its neighbour
      // pointers point to null
      head = incomingNode;
      tail = incomingNode;
      incomingNode->leftNeighbour = nullptr;
      incomingNode->rightNeighbour = nullptr;
   }

   // If the list is not empty
   else{

      // Insert the node at the back of the list and set it as the tail
      incomingNode->leftNeighbour = tail;
      incomingNode->rightNeighbour = nullptr;
      tail = incomingNode;
   }
   incomingNode = nullptr;
   length++;
}

void LinkedList::printNodes(){
   if (head == nullptr){
      cout<< "The list is empty" << endl;
   }

   else{
      Node* currentNode = head;
      cout << currentNode->data << endl;
      while (currentNode->rightNeighbour != nullptr){
         cout << currentNode->rightNeighbour->data << endl;
         currentNode = currentNode->rightNeighbour;
      }
   }

}

// LinkedList::insert(Node* incomingNode, int index){

// }
