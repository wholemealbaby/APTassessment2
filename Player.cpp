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
