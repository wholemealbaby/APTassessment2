#include "TileList.h"
#include "Board.h"
#include "Player.h"
#include <array>
#include <iostream>

using std::array;
using std::cout;
using std::endl;

Board::Board(){
    // Filling board state with empty spaces
    for (int i = 0; i < board_length; i ++){
        boardState[i].fill({" "});
    }
}

int Board::board_length = 15;

// Places a tile on the board and returns
// a  truth value indicating the placement success
bool Board::placeTile(Tile* tile, int row, int col){
    bool placementValid = false;
    if (boardState[row][col] == " "){

        boardState[row][col] = tile->letter;
        tiles.append(tile);
        placementValid = true;
    }

    return placementValid;
}

// Checks that the given coordinates is free on the board
bool Board::validateCoords(int row, int col){
    bool placementValid = false;
    if (boardState[row][col] == " "){
        placementValid = true;
    }

    return placementValid;    
}

// Checks that the given string position is free on the board
bool Board::validatePos(String pos){
    // converting pos to integers
    int posX = pos[0]-65; 
    int posY = stoi(pos.substr(1, 3));

    bool placementValid = false;
    if (boardState[posX][posY] == " "){
        placementValid = true;
    }

    return placementValid;    
}





TileList Board::getTiles(){
    return tiles;
}


void Board::printBoard(){
    array<string, 15> rows = 
    {"A", "B", "C", "D", "E", "F","G", "H", "I", "J", "K", "L", "M", "N", "O"};
    cout<<"    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14";
    cout << endl;
    cout<<"  -------------------------------------------------------------";
    cout << endl;
    
    for (int row = 0; row < board_length; row++){
        // Print row character
        cout<<rows[row]<<" ";
        // Print row contents
        for(int col = 0; col < board_length; col++){
            cout << "| " << boardState[row][col] << " ";
        }
        cout<<"|"<<endl;
    }
}
