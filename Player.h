
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <iostream>
#include "TileList.h"

using String = std::string;

// Scrabble game instance
class Player {
    public:
    Player();
    Player(string name);
    String name;
    int score;
    TileList hand;
};

#endif // ASSIGN2_NODE_
