#include "Game.h"
#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"
#include "Board.h"
#include <iostream>
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

Game::Game(){
    this->player1 = new Player("Player1");
    this->player2 = new Player("Player2");
    currentPlayer = player1;
    fillTileBag();
    cout<<"bagfilled" <<endl;
    tileBag.printTiles();
}

Game::Game(string player1Name, string player2Name){
    this->player1 = new Player(player1Name);
    this->player2 = new Player(player2Name);
    currentPlayer = player1;
    fillTileBag();
    cout<<"bagfilled" <<endl;
    tileBag.printTiles();
}

Game::~Game(){
    delete player1;
    delete player2;
    player1 = nullptr;
    player2 = nullptr;
}

void Game::placeTile(Player* player, Tile* tile, string pos){
    tile->posX = pos[0]-65;
    tile->posY = stoi(pos.substr(1, pos.size()-1));
    board.placeTile(tile, tile->posX, tile->posY);
}

// Reads the tiles from tile set file and populates
// the tile bag
void Game::fillTileBag(){
    string line;
    vector<string> tiles;

    while(std::getline(cin, line)){
        tiles.push_back(line);
    }
    cout << endl << endl;
    
    tiles.erase(tiles.begin());
    for (string tile: tiles){
        string letter(1, tile[0]);
        int value = stoi(tile.substr(2, tile.size()-1));
        tuple<string, int> tileData = make_tuple(letter, value);
        tileBag.append(tileData);
    }
}

// Deals each player 7 random tiles from the tile bag
void Game::dealTiles(){
    for (int i = 0; i < 7; i++){
        Tile* tile1 = tileBag.pop(rand() % tileBag.size());
        Tile* tile2 = tileBag.pop(rand() % tileBag.size());
        player1->hand.append(tile1);
        player2->hand.append(tile2);
    }
}