//345678911234567892123456789312345678941234567895123456789612345678971234567898
#include <iostream>
#include <tuple>
#include "Tile.h"
#include "TileList.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::tuple;
using std::get;

TileList::TileList(){
   head = nullptr;
   tail = nullptr;
   length = 0;
}

TileList::~TileList(){
   
   this->clear();
}

void TileList::clear(){
   if (length > 0){
      Tile* currentTile = head;
      // Iterating through the list and deleting the previous Tile
      int count = 0;
      while (currentTile->next != nullptr){
         currentTile = currentTile->next;
         delete currentTile->prev;
         currentTile->prev = nullptr;
         count++;
      }

      // Deleting final Tile and setting pointers to null
      delete currentTile;
      currentTile = nullptr;
      head = nullptr;
      tail = nullptr;

      // Resetting length to 0
      length = 0;      
   }

}

// Get the size of the list
int TileList::size(){
   return length;
}

Tile* TileList::operator[](int index){
   Tile* currentTile;

   // If the index given is -1 then return the tail
   if (index == -1){
      currentTile = tail;
   }

   // Otherwise iterate through the elements until the index
   // is reached and return the node at that index
   else{
      currentTile = head;
      for (int i = 0; i<index; i++){
         currentTile = currentTile->next;
      }
   }
   return currentTile;
}

// Searches for a tile with the given letter 
// in the list and returns its pointer
Tile* TileList::search(string letter){
   bool found = false;
   Tile* currentTile = head;
   while (found != true && currentTile != nullptr){
      if (currentTile->letter == letter){
         found = true;
      }
      else{
         currentTile = currentTile->next;
      }
   }
   return currentTile;
}

// Get an element at the given index
Tile* TileList::get(int index){
   return (*this)[index];
}

//  Returns the head Tile of the list
Tile* TileList::getHead(){
   return head;
}

// Returns the tail Tile of the list
Tile* TileList::getTail(){
   return tail;
}

// Appends a new tile with the given data to the end of the list
void TileList::append(tuple<string, int> incomingTileData){;
   // If the list is empty
   if (head == nullptr){

      // Set the tail and head to a Tile with the given data and
      head = new Tile(incomingTileData);
      tail = head;
   }

   // If the list is not empty
   else{
      // Insert the Tile at the back of the list and set it as the tail
      tail = new Tile(incomingTileData, tail, nullptr);
      tail->prev->next = tail;
   }
   length++;
}

// Appends a Tile to the end of the list
void TileList::append(Tile* incomingTile){;
   // If the list is empty
   if (head == nullptr){

      // Set the tail and head to a Tile with the given data and
      head = new Tile(incomingTile, nullptr, nullptr);
      tail = head;
   }

   // If the list is not empty
   else{
      // Insert the Tile at t he back of the list and set it as the tail
      tail = new Tile(incomingTile, tail, nullptr);
      if (length == 1){
         head->next = tail;
      }
      tail->prev->next = tail;
   }
   length++;
}

// Inserts a Tile at the given index
void TileList::insert(tuple<string, int> incomingTileData, int index){
   if (length == 0){
      head = new Tile(incomingTileData);
      tail = head;
   }

   // First element case
   else if (index == 0) {
      head->prev = new Tile(incomingTileData, nullptr, head);
      head = head->prev;
   }

   // Last element case
   else if (index == length || index == -1){
      tail->next = new Tile(incomingTileData, tail, nullptr);
      tail = tail->next;
   }

   // Average case
   else{
      // Tile that already exists at the index
      Tile* prexisitngTile = (*this)[index];

      prexisitngTile->prev->next = new Tile 
      (incomingTileData, prexisitngTile->prev, prexisitngTile);

      prexisitngTile->prev = prexisitngTile->prev->next;
   }

   length++;
}

// Print all the tiles in the list
void TileList::printTiles(){
   if (head == nullptr){
      cout<< "The list is empty" << endl;
   }

   else{
      Tile* currentTile = head;
      while (currentTile != nullptr){
         cout << currentTile->letter << currentTile->value << endl;
         currentTile = currentTile->next;
      }
      currentTile = nullptr;
   }
}

// Deletes the contents of the list and copies the contents of the given list
void TileList::copy(TileList* list){
   // Clear this list
   this->clear();
   // Append the head of the given list
   append(list->getHead()->data);
   
   // Iterate through the given list starting at the head and appending 
   // each element to this list
   Tile* currentTile = list->getHead();
   while (currentTile->next != nullptr){
      append(currentTile->next->data);
      currentTile = currentTile->next;
   }
}

void TileList::sort(){
   TileList* sorted = new TileList();
   sorted->append(this->head->data);

   // For each element in unsorted (except for the first)
   for (int unsortedi = 1; unsortedi<this->length; unsortedi++){
      Tile* unsortedTile = (*this)[unsortedi];

      // current index in sorted list
      int sortedi = 0;
      // flag indicated if the unsortedTile has been inserted into sorted
      bool inserted = false;
      // Iterate through sorted
      while(inserted == false && sortedi<sorted->length){
         Tile* sortedTile = sorted->get(sortedi);

         // Insert the current unsortedTile at the point inhabbited
         // by the first sortedTile that has a smaller value than 
         // unsortedTile
         if (sortedTile->value < unsortedTile->value){
            sorted->insert(unsortedTile->data, sortedi);
            inserted = true;
         }
         
         sortedi++;
      }
      if (inserted == false){
         sorted->append(unsortedTile->data);
      }

   }

   copy(sorted);
   delete sorted;
}

// Pops the tile at the given index
void TileList::pop(int index){
   Tile* targetPtr;
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
void TileList::pop(int index, Tile*& returnPtr){
   // The pointer at the target index
   Tile* targetPtr;
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
   returnPtr = new Tile(targetPtr, nullptr, nullptr);
   delete targetPtr;
   length--;
}

// Searches for a Tile with the given letter 
// in the list and returns its index
int TileList::index(string letter){

   // Flag for whether the tile has been found
   bool found = false;
   // The tile currently being examined
   Tile* currentTile = head;
   // The index of the tile being examined
   int index = 0;
   while (found != true && currentTile != nullptr){
      // If the current tile's letter matches the target letter
      if (currentTile->letter == letter){
         found = true;
      }
      // Otherwise check the next tile
      else{
         currentTile = currentTile->next;
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

// Searches for a matching tile in the list and
// returns its index
int TileList::index(Tile* target){

   // Flag for whether the tile has been found
   bool found = false;
   // The tile currently being examined
   Tile* currentTile = head;
   // The index of the tile being examined
   int index = 0;
   while (found != true && currentTile != nullptr){
      // If the current tile's letter matches the target letter
      if (currentTile->data == target->data){
         found = true;
      }
      // Otherwise check the next tile
      else{
         currentTile = currentTile->next;
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
