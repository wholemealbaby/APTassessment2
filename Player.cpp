#include <iostream>
#include "Player.h"

using String = std::string;

Player::Player(){
    name = "";
    score = 0;
}

Player::Player(Player* other){
    name = other->name;
    score = other->score;
    hand.copy(&other->hand);
}

Player::Player(String name){
    this->name = name;
    score = 0;
}

Player::Player(String name, int score, TileList* hand){
    this->name = name;
    this->score = score;
    this->hand.copy(hand);
}