#include <iostream>
#include <tuple>
#include "Tile.h"

using std::string;
using std::tuple;
using std::get;

Tile::Tile(tuple<string, int> data){
    this->data = data;
    this->letter = get<0>(data);
    this->value = get<1>(data);
    posX = -1;
    posY = -1;
    next = nullptr;
    prev = nullptr;

}

Tile::Tile(tuple<string, int> data, Tile* prev, Tile* next){
    this->data = data;
    this->letter = get<0>(data);
    this->value = get<1>(data);
    posX = -1;
    posY = -1;
    this->next = next;
    this->prev = prev;
}
Tile::Tile(Tile* other){
    data = other->data;
    letter = other->letter;
    value = other->value;
    posX = other->posX;
    posY = other->posY;
    next = other->next;
    prev = other->prev;
}

Tile::Tile(Tile* other, Tile* prev, Tile* next){
    data = other->data;
    letter = get<0>(data);
    value = get<1>(data);
    posX = other->posX;
    posY = other->posY;
    this->next = next;
    this->prev = prev;
}

Tile::Tile(string letter, int value){
    data = make_tuple(letter, value);
    this->letter = letter;
    this->value = value;
    posX = -1;
    posY = -1;
    next = nullptr;
    prev = nullptr;
}

Tile::Tile(string letter, int value, Tile* prev, Tile* next){
    data = make_tuple(letter, value);
    this->letter = letter;
    this->value = value;
    posX = -1;
    posY = -1;
    this->next = next;
    this->prev = prev;
}

