#include "Game.h"
#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

using std::string;
using std::tuple;
using std::vector;
using std::cin;
using std::endl;
using std::cout;
using std::make_tuple;
using std::stoi;
using std::ifstream;

Game::Game(){
    this->player1 = new Player("Player1");
    this->player2 = new Player("Player2");
    currentPlayer = player1;
    fillTileBag();
}

Game::Game(string player1Name, string player2Name){
    this->player1 = new Player(player1Name);
    this->player2 = new Player(player2Name);
    currentPlayer = player1;
    fillTileBag();
}

Game::~Game(){
    delete player1;
    delete player2;
    player1 = nullptr;
    player2 = nullptr;
}

void Game::placeTile(Player* player, Tile* tile, string pos){
    // Derives the integer x value buy substracting the ascii value 
    // of 'A' from the character in the pos string
    tile->posX = pos[0]-65; 
    tile->posY = stoi(pos.substr(1, pos.size()-1));
    // Removing the tile from the player's hand
    player->hand.pop(player->hand.index(tile));
    // Placing the tile on the board
    board.placeTile(tile, tile->posX, tile->posY);
    delete tile;
    board.printBoard();
}

// Reads the tiles from tile set file and populates
// the tile bag
void Game::fillTileBag(){
    // Current line of file
    string line;
    // tile info string that have already been read from
    // the file
    vector<string> tiles;

    // Iterate through tiles file and append each tile to
    // tiles vector
    ifstream myfile ("ScrabbleTiles.txt");
    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            tiles.push_back(line);
        }
        myfile.close();
    }

    // If the file doesn't exist
    else cout << "Unable to open ScrabbleTiles.txt"; 


    // For each tile read from, append its data to the tileBag
    for (string tile: tiles){
        string letter(1, tile[0]);
        
        int value = stoi(tile.substr(2, tile.size()-1));
        tuple<string, int> tileData = make_tuple(letter, value);
        tileBag.append(tileData);
    }
}

// Deals each player enough random tiles from the tile bag to result in them having 7 tiles total
void Game::dealTiles(int numTiles){
    for (int i = 0; i < numTiles; i++){
        Tile* tile1; 
        tileBag.pop(std::rand() % tileBag.size(), tile1);
        Tile* tile2; 
        tileBag.pop(std::rand() % tileBag.size(), tile2);
        player1->hand.insert(tile1->data, -1);
        player2->hand.insert(tile2->data, -1);
        delete tile1;
        delete tile2;
    }
    //player1->hand.printTiles();
};