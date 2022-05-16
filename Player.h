
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <iostream>
#include "TileList.h"

using String = std::string;

// Scrabble game instance
class Player {
    public:
    Player();
    Player(Player* other);
    Player(string name);
    Player(String name, int score, TileList* list);
    String name;
    int score;
    TileList hand;
};

#endif // ASSIGN2_NODE_
