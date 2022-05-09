
#ifndef ASSIGN2_TILELIST_H
#define ASSIGN2_TILELIST_H

#include <tuple>
#include <memory>
#include "Tile.h"

using std::tuple;

//  Linked List of scrabble tiles
class TileList {
    public:
    TileList();
    ~TileList();

    void clear();
    // Appends a Node to the end of the list
    void append(tuple<string, int> incomingTileData);
    void append(Tile* incomingTile);

    // Inserts a node at the given index
    void insert(tuple<string, int> incomigTileData, int index);

    // Prints the tiles in the list
    void printTiles();

    // Deletes the contents of the list and copies the contents of the given list
    void copy(TileList* list);

    // Sort the list in descending order
    void sort();

    // Get the size of the list
    int size();

    Tile* operator[](int index);

    // Get the head of the list
    Tile* getHead();
    // Get the tail of the list
    Tile* getTail();

    // Get the element at the given index
    Tile* get(int index);

    // Searches for a tile with the given letter 
    // in the list and returns its pointer
    Tile* search(string letter);

    // Searches for a Tile with the given letter 
    // in the list and returns its index
    int index(string letter);

    // Searches for a matching tile in the list and
    // returns its index
    int index(Tile* target);

    // Pops the tile at the given index
    void pop(int index);
   
    // Pops the tile at the given index and stores it
    // at the given pointer
    void pop(int index, Tile*& returnPointer);
    
    private:
    Tile* head;
    Tile* tail;
    int length;
};

#endif // ASSIGN2_TILELIST_H
