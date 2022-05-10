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
    main();
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
    player->hand.pop(player->hand.index(tile), tile);
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
    }

    void Game::main(){
        while (player1->hand.size() != 0 && player2->hand.size() != 0){
            // Printing current player and player scores
            cout << currentPlayer.name << ", it's your turn" <<endl;
            cout << "Score for " << player1.name << ": " << player1.score << endl;
            cout << "Score for " << player2.name << ": " << player2.score << endl<<endl;
            board.printBoard();
            cout<<endl;

            // Current player's hand
            cout << "Your hand is" << endl;
            currentPlayer->hand.printTiles2();
            cout << endl;

            // Current player's turn

            // Recieving inital command
            String playerMove = "";
            // While the users input is valid
            bool inputValid = true;
            while (inputValid ==true){
                cout << "> ";
                cin >> playerMove;
                // Checking for 'place' move
                if (playerMove.substr(0, 4) == "place"){
                    while (playerMove != "Place Done"){
                        try {
                            placeTile(
                                currentPlayer, currentPlayer->hand.index(playerMove[6]),
                                playerMove.substr(11, 12))
                            }
                        }
                        catch (...){
                            
                        }
                    }
                }
                // Checking for replace move
                else if (playerMove.substr(0, 6) == "replace"){

                }
                cout << endl;
            }
        }
    }

    void Game::getPlayerMove(){
        bool inputValid = false;
        while (inputValid == true){
            // Recieving inital command
            String playerMove = "";
            cout << "> ";
            cin >> playerMove;

/ 
            cout << playerMove.substr(0, 4) << endl;
            if (playerMove.substr(0, 4) == "place"){
                cout << playerMove.substr(8, 9) << endl;
                if (playerMove.substr(8, 9) == "at"){
                    // TODO 
                    // - Check if tile is players hand
                    // - Check if placement is free
                    // - Loop until placement is complete
                }
            }
            else if (playerMove.substr(0, 6) == "replace"){

            }
            else if (playerMove.substr(0, 3) == "pass"){
                validInput = true;
            }
        }


        while (inputValid ==true){
            cout << "> ";
            cin >> playerMove;
            // Checking for 'place' move
            try {
                if (playerMove.substr(0, 4) == "place"){
                    while (playerMove != "Place Done"){
                        placeTile(
                            currentPlayer, currentPlayer->hand.index(playerMove[6]),
                            playerMove.substr(11, 12))
                        }
                        
            
                    }
                }
                // Checking for replace move
                else if (playerMove.substr(0, 6) == "replace"){

                }
        }
        catch (...)
            cout << endl;
        }
    }
}