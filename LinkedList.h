
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   // Appends a Node to the end of the array
   void append(Node* incomingNode);
   void append(string incomingNodeData);

   // Inserts a Node at the specified index
   void insert(Node* incomingNode, int index);
   void insert(string incomingNodeData, int index);
   // Returns the size of the list
   int size();

   void clear();

   void printNodes();

   void sort();

   Node* operator[](int index);

   Node* getHead();
   Node* getTail();

   void copy(LinkedList* list);

   Node* get(int index);



private:
   Node* head;
   Node* tail;
   int length;

};

#endif // ASSIGN2_LINKEDLIST_H
