#include "Game.h"
#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <fstream>
#include <string>

using std::string;
using std::tuple;
using std::vector;
using std::cin;
using std::endl;
using std::cout;
using std::make_tuple;
using std::stoi;
using std::ifstream;
using std::ofstream;


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
}

void Game::saveGame(Player player1, Player player2, String currentPlayer, String tileBag,  Board boardSave){
    String fileName = player1.name + player2.name + ".txt";
    String player1hand;
    String player2hand;
    array <string, 15> boardLine;
    
    ofstream saveFile (fileName);
    TileList boardTiles = boardSave.getTiles();
    saveFile << player1.name << endl;
    saveFile << player1.score << endl;

    while(player1.hand.size() > 0){
        player1hand += player1.hand.get(0)->letter;
        player1.hand.pop(0);
    }

    saveFile << player2.name << endl;
    saveFile << player2.score << endl;

    while(player1.hand.size() > 0){
        player1hand += player1.hand.get(0)->letter;
        player1.hand.pop(0);
    }

    saveFile << currentPlayer << endl;
    saveFile << tileBag << endl;
    
    // write the board state to game file
    //fix magic number

    for(int n = 0; n <= boardTiles.size(); n++){
                saveFile << boardTiles.get(n);
    }
}

void Game::loadGame(String fileName){
    // The save file is as follows, line-by-line.

    // Player 1 name
    // Player 1 score
    // Player 1 hand
    // Player 2 name
    // Player 2 score
    // Player 2 hand
    // current player (playerturn)
    // Tile bag state
    // Board state

    // Create a text string, which is used to output the text file
    // string gameSave;
    // int boardSize = 15;
    // vector<string> info;
    // vector<string> line;
    // TileList* boardList = new TileList();

    // // Read from the text file
    // std::ifstream ReadFile(fileName);

    // // Use a while loop together with the getline() function to read the file line by line
    // while (std::getline (ReadFile, gameSave)) {
    //     info.push_back(gameSave);
    // }
    // set the variables based on each line from the file
    // String player1Name = info.at(0);
    // int player1Score = stoi(info.at(1));
    // String player1Hand = info.at(2);

    // String player2Name = info.at(3);
    // int player2Score = stoi(info.at(4));
    // String player2Hand = info.at(5);

    // String currentPlayer = info.at(6);
    // String tileBagState = info.at(7);

    // line.push_back(info.at(8));


    // for(int j = 0; j <= boardSize; j++){
    //     Tile* tile = new Tile(line.at(j), getValue(line.at(j)));
    //     boardList->append(tile);
    // }



    //Need To Initiate a new game here
    }

int Game::getValue(String letter){
    // returns the score of a given letter
    const char* cha = letter.c_str();
    // atoi converts char to int precisely
    int letterNum = atoi(cha) - 65;
        
        switch(letterNum) {
        case 0: return 1;
        case 1: return 3;
        case 2: return 3;
        case 3: return 2;
        case 4: return 1;
        case 5: return 4;
        case 6: return 2;
        case 7: return 4;
        case 8: return 1;
        case 9: return 8;
        case 10: return 5;
        case 11: return 1;
        case 12: return 3;
        case 13: return 1;
        case 14: return 1;
        case 15: return 3;
        case 16: return 10;
        case 17: return 1;
        case 18: return 1;
        case 19: return 1;
        case 20: return 1;
        case 21: return 4;
        case 22: return 4;
        case 23: return 8;
        case 24: return 4;
        case 25: return 10;
        default: return -1;    
        }
    }


