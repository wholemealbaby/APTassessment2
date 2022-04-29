
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   // Appends a Node to the end of the array
   void append(Node* incomingNode);
   void append(string data);

   // Inserts a Node at the specified index
   void insert(Node* incomingNode, int index);

   // Returns the size of the list
   int size();

   void printNodes();


private:
   Node* head;
   Node* tail;
   int length;

};

#endif // ASSIGN2_LINKEDLIST_H
