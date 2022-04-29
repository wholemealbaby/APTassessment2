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
   while (currentNode->next != nullptr){
      currentNode = currentNode->next;
      delete currentNode->prev;
      currentNode->prev = nullptr;
   }

   // Deleting final node and setting pointers to null
   delete currentNode;
   currentNode = nullptr;
   head = nullptr;
   tail = nullptr;
}

 Node* LinkedList::operator[](int index){
   Node* currentNode;
   if (index == -1){
      currentNode = tail;
   }

   else{
      currentNode = head;
      for (int i = 0; i<index; i++){
         currentNode = currentNode->next;
      }
   }
   return currentNode;
 }

// Appends a Node to the end of the array
void LinkedList::append(Node* incomingNode){
   // If the list is empty
   if (tail == nullptr){

      // Set the tail and head to the node and ensure that its neighbour
      // pointers point to null
      head = incomingNode;
      tail = incomingNode;
      incomingNode->prev = nullptr;
      incomingNode->next = nullptr;
   }

   // If the list is not empty
   else{

      // Insert the node at the back of the list and set it as the tail
      incomingNode->prev = tail;
      incomingNode->next = nullptr;
      tail = incomingNode;
   }

   length++;
}

// Appends a Node to the end of the array
void LinkedList::append(string incomingNodeData){;
   // If the list is empty
   if (head == nullptr){

      // Set the tail and head to a Node with the given data and
      head = new Node(incomingNodeData);
      tail = head;
   }

   // If the list is not empty
   else{
      // Insert the node at the back of the list and set it as the tail
      tail = new Node(incomingNodeData, tail, nullptr);
      tail->prev->next = tail;
   }
   length++;
}

void LinkedList::printNodes(){
   if (head == nullptr){
      cout<< "The list is empty" << endl;
   }

   else{
      Node* currentNode = head;
      while (currentNode != nullptr){
         cout << currentNode->data << endl;
         currentNode = currentNode->next;
      }
      currentNode = nullptr;
   }
}

void LinkedList::insert(string incomingNodeData, int index){
   if (index == 0) {
      head->prev = new Node(incomingNodeData, nullptr, head);
      head = head->prev;
   }

   else if (index == length){
      tail->next = new Node(incomingNodeData, tail, nullptr);
      tail = tail->next;
   }

   else{
      // Node that already exists at the index
      Node* prexisitngNode = (*this)[index];
      prexisitngNode->prev->next = new Node(incomingNodeData, prexisitngNode->prev, prexisitngNode);
      prexisitngNode->prev = prexisitngNode->prev->next;
   }
}
