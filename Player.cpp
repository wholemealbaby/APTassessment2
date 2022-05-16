#include <iostream>
#include "Player.h"

using String = std::string;

Player::Player(){
    name = "";
    score = 0;
}

Player::Player(String name){
    this->name = name;
    score = 0;
}

Player::Player(String name, int score, TileList list){
    this->name = name;
    this->score = score;
    while(list.size() > 0){
        Tile* tile = list.getHead(); 
        list.pop(0);
        this->hand.insert(tile->data, -1);
    }
}