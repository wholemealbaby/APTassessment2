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
    dealTiles(7);
    main();
}

Game::Game(string player1Name, string player2Name){
    this->player1 = new Player(player1Name);
    this->player2 = new Player(player2Name);
    currentPlayer = player1;
    fillTileBag();
    dealTiles(7);
    main();
}

Game::~Game(){
    delete player1;
    delete player2;
    player1 = nullptr;
    player2 = nullptr;
}

bool Game::replaceTile(Player* player, String letter){
    bool replacementValid = false;
    // Removing tile from player's hand
    int tileIndex = player->hand.index(letter);
    if (tileIndex != -1){
        if (tileBag.size() > 0){
            replacementValid = true;
            player->hand.pop(tileIndex);
            // Getting a random tile from tile bag
            Tile* tile;
    
            tileBag.pop(std::rand() % tileBag.size(), tile);
            // Adding tile to hand
            player->hand.append(tile); 

            // Print the player's new hand
            cout << endl << "Your new hand:" << endl;
            currentPlayer->hand.sort();
            currentPlayer->hand.printTiles2();

            // Giving the player the chance to read their new
            // hand by waiting for user to press enter 
            // before continuing
            do {
            cout << '\n' << "Press Enter to continue...";
            } while (cin.get() != '\n');

        }
    }
    return replacementValid;
}

bool Game::placeTile(Player* player, String letter, string pos){
    bool placementValid = false;
    // Get Tile from players hand   
    int tileIndex = player->hand.index(letter);
    if (tileIndex != -1){
        // Removing the tile from the player's hand
        Tile* tile;
        player->hand.pop(player->hand.index(letter), tile);

        // Derives the integer x value buy substracting the ascii value 
        // of 'A' from the character in the pos string
        tile->posX = pos[0]-65; 
        tile->posY = stoi(pos.substr(1, 3));

        // Flag to indicate if the placement succeeded
        // Placing the tile on the board
        placementValid = board.placeTile(tile, tile->posX, tile->posY);
        if (placementValid == true){
            currentPlayer->score = currentPlayer->score + tile->value;
        }
        delete tile;
    }

    
    return placementValid;
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

// Deals each player a given number of tiles
void Game::dealTiles(int numTiles){
    // For each tile to be dealt
    for (int i = 0; i < numTiles; i++){
        // Pop two random tiles from the tile bag
        Tile* tile1; 
        tileBag.pop(std::rand() % tileBag.size(), tile1);
        Tile* tile2; 
        tileBag.pop(std::rand() % tileBag.size(), tile2);

        // Insert them into the players hands
        player1->hand.insert(tile1->data, -1);
        player2->hand.insert(tile2->data, -1);

        // Clean up the transfer pointers
        delete tile1;
        delete tile2;
    }
}

// Deals the specified player a given number of tiles
void Game::dealTiles(int numTiles, Player* player){
    // For each tile to be dealt
    for (int i = 0; i < numTiles; i++){
        // Pop a random tile from the tile bag
        Tile* tile; 
        tileBag.pop(std::rand() % tileBag.size(), tile);
        currentPlayer->hand.insert(tile->data, -1);
        delete tile;
    }
}

void Game::switchCurrentPlayer(){
    // If the current player is player1 set the current player
    // to player2
    if (currentPlayer == player1){
        currentPlayer = player2;
    }
    // Otherwise set the current player to player1
    else{
        currentPlayer = player1;
    }
}

void Game::main(){
    // Each iteration of this loop represents a turn
    while (player1->hand.size() != 0 && player2->hand.size() != 0){
        // print game info at the start of a turn
        printGameInfo();

        // Process the player's move from input
        getPlayerMove();

        // Switch the players for the next turn
        switchCurrentPlayer();
    }
}

void Game::getPlayerMove(){
    // String containing player's move
    String playerMove = "";

    // While the users input is valid
    bool inputValid = false;
    while (inputValid == false){
        // Recieivng input
        cout << "> ";
        std::getline(std::cin, playerMove);

        // Checking for placement
    
        if (playerMove.substr(0, 5) == "Place"){
            // Recieving player's word placement
            place(playerMove);
            inputValid = true;
        }
        // Checking for replacement
        else if (playerMove.substr(0, 7) == "Replace"){
            // Extracting tile letter from command string
            String letter(1, playerMove[8]);
            replaceTile(currentPlayer, letter);
            inputValid = true;
        }

        // Checking for pass
        else if (playerMove == "pass"){
            inputValid = true;
        }

        // Checking for EOF
        else if (cin.eof()){
            cout << endl << "Goodbye!" << endl;
            exit(0);
        }

    }
    cout << endl;
}


void Game::printGameInfo(){
    // Printing current player and player scores
    cout << currentPlayer->name << ", it's your turn" <<endl;
    cout << "Score for " << player1->name << ": " << player1->score << endl;
    cout << "Score for " << player2->name << ": " << player2->score << endl<<endl;
    board.printBoard();
    cout<<endl;

    // Current player's hand
    cout << "Your hand is" << endl;
    currentPlayer->hand.sort();
    currentPlayer->hand.printTiles2();
    cout << endl;
}


void Game::place(String playerMove){
    int tilesPlaced = 0;
    // // while the move has not been finished
    while (playerMove != "Place Done"){
        bool inputValid = false;

        // Checking for EOF
        if (cin.eof()){
            cout << endl << "Goodbye!" << endl;
            exit(0);
        }

        // Check that the length of the arguments is valid
        if (playerMove.size() == MIN_PLACE_ARG_LENGTH || playerMove.size() == MAX_PLACE_ARG_LENGTH){
            // Check that arguments follow the correct syntax
            if (playerMove.substr(8, 2) == "at"){

                // Check that the specified letter is in the player's hand
                String commandLetter(1, playerMove[6]);
                int indexOfTile = currentPlayer->hand.index(commandLetter);
                if (indexOfTile != -1){

                    // Place the specified tile at the position specied at index 11
                    // if the placement succeeds, the input is valid.
                    if (placeTile(currentPlayer, commandLetter, playerMove.substr(11, 3)) == true){
                        inputValid = true;
                        // Forcing player to follow through with place move
                        cout << "> Place ";
                        std::getline(std::cin, playerMove);
                        // Adding place to the beginning of player command
                        playerMove = "Place " + playerMove;
                        tilesPlaced++;
                    }
                }
            }
        }

        // Input was invalid
        if (inputValid == false) {
            cout << "Invalid Input" << endl;
            // Forcing player to follow through with place move
            cout << "> Place ";
            std::getline(std::cin, playerMove);
            // Adding place to the beginning of player command
            playerMove = "Place " + playerMove;
        }
    }
}

