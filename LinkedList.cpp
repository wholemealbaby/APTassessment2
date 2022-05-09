//345678911234567892123456789312345678941234567895123456789612345678971234567898
#include <iostream>

#include "Node.h"
#include "LinkedList.h"


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
   if (length > 0){
      this->clear();
   }
}

void LinkedList::clear(){
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

   // Resetting length to 0
   length = 0;
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

int LinkedList::size(){
   return length;
}

//  Returns the head node of the list
Node* LinkedList::getHead(){
   return head;
}

// Returns the tail node of the list
Node* LinkedList::getTail(){
   return tail;
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

      prexisitngNode->prev->next = new Node 
      (incomingNodeData, prexisitngNode->prev, prexisitngNode);

      prexisitngNode->prev = prexisitngNode->prev->next;
   }
   length++;
}

// Deletes the contents of the list and copies the contents of the given list
void LinkedList::copy(LinkedList* list){
   // Clear this list
   this->clear();
   // Append the head of the given list
   append(list->getHead()->data);
   
   // Iterate through the given list starting at the head and appending 
   // each element to this list
   Node* currentNode = list->getHead();
   while (currentNode->next != nullptr){
      append(currentNode->next->data);
      currentNode = currentNode->next;
   }
}

Node* LinkedList::get(int index){
   return (*this)[index];
}

void LinkedList::sort(){
   LinkedList* sorted = new LinkedList();
   sorted->append(this->head->data);

   // For each element in unsorted (except for the first)
   for (int unsortedi = 1; unsortedi<this->length; unsortedi++){
      Node* unsortedNode = (*this)[unsortedi];

      // current index in sorted array
      int sortedi = 0;
      // flag indicated if the unsortedNode has been inserted into sorted
      bool inserted = false;
      // Iterate through sorted
      while(inserted == false && sortedi<sorted->length){
         Node* sortedNode = sorted->get(sortedi);
         // And insert the current unsortedNode at the point inhabbited
         // by the first sortedNode that is smalled than unsortedNode
         if (sortedNode->data < unsortedNode->data){
            sorted->insert(unsortedNode->data, sortedi);
            inserted = true;
         }
         sortedi++;
      }
      if (inserted == false){
         sorted->append(unsortedNode->data);
      }

   }

   copy(sorted);
   delete sorted;
}

// Searches for a Node with the given data 
// in the list and returns its pointer
Node* LinkedList::search(string data){
   bool found = false;
   Node* currentNode = head;
   while (found != true && currentNode != nullptr){
      if (currentNode->data == data){
         found = true;
      }
      else{
         currentNode = currentNode->next;
      }
   }
   return currentNode;
}

// Searches for a Node with the given letter 
// in the list and returns its index
int LinkedList::index(string data){

   // Flag for whether the tile has been found
   bool found = false;
   // The tile currently being examined
   Node* currentNode = head;
   // The index of the tile being examined
   int index = 0;
   while (found != true && currentNode != nullptr){
      // If the current tile's letter matches the target letter
      if (currentNode->data == data){
         found = true;
      }
      // Otherwise check the next tile
      else{
         currentNode = currentNode->next;
         index++;
      }
   }
   
   // If the tile was not found return -1 to indicate
   // that a tile with that letter does not exist within
   // this list
   if (found == false){
      index = -1;
   }
   // Return the index of the found tile
   return index;
}

// Searches for a Node with the given letter 
// in the list and returns its index
int LinkedList::index(Node* target){

   // Flag for whether the tile has been found
   bool found = false;
   // The tile currently being examined
   Node* currentNode = head;
   // The index of the tile being examined
   int index = 0;
   while (found != true && currentNode != nullptr){
      // If the current tile's letter matches the target letter
      if (currentNode->data == target->data){
         found = true;
      }
      // Otherwise check the next tile
      else{
         currentNode = currentNode->next;
         index++;
      }
   }
   
   // If the tile was not found return -1 to indicate
   // that a tile with that letter does not exist within
   // this list
   if (found == false){
      index = -1;
   }
   // Return the index of the found tile
   return index;
}

// Pops the tile at the given index
void LinkedList::pop(int index){
   Node* targetPtr;
   // Start case
   if (index == 0){
      // Returning the head
      targetPtr = head;
      // Setting the head to the next value
      head = head->next;

      // If the list is not empty
      if (head != nullptr){
         // Removing the old head from the list
         head->prev = nullptr;
      }
   }
   
   // End case
   else if (index == -1){
      // Returning the tail
      targetPtr = tail;
      // Setting the tail to the previous value;
      tail = tail->prev;
      // If the list is not empty
      if (tail != nullptr){
         // Removing the old tail from the list
         tail->next = nullptr;
      }
   }

   else {
      targetPtr = (*this)[index];
      // Setting the node behind the target node's next value
      // to the node in front of the target node
      targetPtr->prev->next = targetPtr->next;
      // Setting the node in front of the target node's prev value
      // to the node behind the target node
      targetPtr->next->prev = targetPtr->prev;
   }

   length--;
   delete targetPtr;
}

// Pops the tile at the given index and stores it
// at the given pointer
void LinkedList::pop(int index, Node*& returnPtr){
   // The pointer at the target index
   Node* targetPtr;
   // Start case
   if (index == 0){
      // Returning the head
      targetPtr = head;
      // Setting the head to the next value
      head = head->next;

      // If the list is not empty
      if (head != nullptr){
         // Removing the old head from the list
         head->prev = nullptr;
      }
   }
   
   // End case
   else if (index == -1){
      // Returning the tail
      targetPtr = tail;
      // Setting the tail to the previous value;
      tail = tail->prev;
      // If the list is not empty
      if (tail != nullptr){
         // Removing the old tail from the list
         tail->next = nullptr;
      }
   }

   else {
      targetPtr = (*this)[index];
      // Setting the node behind the target node's next value
      // to the node in front of the target node
      targetPtr->prev->next = targetPtr->next;
      // Setting the node in front of the target node's prev value
      // to the node behind the target node
      targetPtr->next->prev = targetPtr->prev;
   }
   // Copying returnPtr to targetPtr and deleting targetPtr
   returnPtr = new Node(targetPtr, nullptr, nullptr);
   delete targetPtr;
   length--;
}

   else {
      returnPointer = (*this)[index];
      // Setting the node behind the target node's next value
      // to the node in front of the target node
      returnPointer->prev->next = returnPointer->next;
      // Setting the node in front of the target node's prev value
      // to the node behind the target node
      returnPointer->next->prev = returnPointer->prev;
   }

   length--;
   return returnPointer;
}
