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
    string spot = boardState[row][col];
    // If the specified postion is empty
    if (tiles.size() != 0 && spot != " ")
        return false;

    boardState[row][col] = tile->letter;
    tiles.append(tile);

    return true;
}

TileList Board::getTiles(){
    return tiles;
}

bool Board::validateBoard(){
    return true;
}

void Board::startNewMoves(){
    currMoves.clear();
}

bool Board::validateMoves() {
    // first move


}


// String Board::checkAdjacentTiles(Tile tile){
//     // int row = tile.posX;
//     // int col = tile.posY;
//     //if(tile.
 
// }

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
