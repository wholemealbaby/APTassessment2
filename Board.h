
#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#define BOARD_DIM   15;

#include "TileList.h"
#include "Player.h"
#include <iostream>
#include <vector>

using String = std::string;
using std::array;
// Scrabble game instance
class Board {
    public:
    Board();
    Board(const Board& rhs)
    {
        *this = rhs;
    }

    // Allows us to copy a board (so we can create backups incase of illegal moves)
    Board& operator=(const Board& rhs)
    {
        boardState = rhs.boardState;
        tiles.copy((TileList*)&rhs);

        return *this;
    }


    // Prints the current state of the board
    void printBoard();
    
    // Places a tile on the board and returns
    // a  truth value indicating the placement success
    bool placeTile(Tile* tile, int row, int col);





    // begins a new curr word
    void startNewMoves();

    TileList getTiles();

    // Tiles that are current placed on the board
    TileList tiles;

    // Represents the board and letters on it.
    // Used to identify if a position is free.
    // Positions on the board that do not have a tile on them
    array<array<String, 15>, 15> boardState;

private:
    static int board_length;



};

#endif // ASSIGN2_NODE_
