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

        // Derives the integer x value buy substracting the ascii value 
        // of 'A' from the character in the pos string
        int posX = pos[0]-65; 
        int posY = stoi(pos.substr(1, 3));

        // Checking that the position values
        // are not out of range
        if (posX < 15 && posY < 15){

            // Removing the tile from the player's hand
            Tile* tile;
            player->hand.pop(player->hand.index(letter), tile);

            // Updating the tile's position
            tile->posX = posX;
            tile->posY = posY;

            // Placing tile on the board and recording
            // placement success in a flag
            placementValid = board.placeTile(tile, tile->posX, tile->posY);
            if (placementValid == true){
                currentPlayer->score = currentPlayer->score + tile->value;
            }
            delete tile;
        }
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

void Game::saveGame(Player player1, Player player2, String currentPlayer, String tileBag,  Board boardSave){
    String fileName = player1.name + "-VS-" + player2.name + ".txt";
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

    while(player2.hand.size() > 0){
        player2hand += player2.hand.get(0)->letter;
        player2.hand.pop(0);
    }

    saveFile << currentPlayer << endl;
    saveFile << tileBag << endl;
    
    // write the board state to game file
    //fix magic number

    for(int i = 0; i <= boardTiles.size(); i++){
                saveFile << boardTiles.get(i);
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
    string gameSave;
    int boardSize = 15;
    vector<string> info;
    vector<string> line;
    TileList boardList = TileList();

    // Read from the text file
    std::ifstream ReadFile(fileName);

    // Use a while loop together with the getline() function to read the file line by line
    while (std::getline (ReadFile, gameSave)) {
        info.push_back(gameSave);
    }
    // set the variables based on each line from the file
    String player1Name = info.at(0);
    int player1Score = stoi(info.at(1));
    String player1HandString = info.at(2);

    String player2Name = info.at(3);
    int player2Score = stoi(info.at(4));
    String player2HandString = info.at(5);

    String currentPlayerName = info.at(6);
    Player* currentPlayer = new Player(currentPlayerName);

    TileList player1Hand = TileList();
    for(int i = 0; i <= (int)player1HandString.length(); i++){
        String tileLetter(1, player1HandString.at(i));
        tuple<string, int> data = make_tuple(tileLetter, getValue(tileLetter));
        player1Hand.append(data);
    }

    TileList player2Hand = TileList();
    for(int i = 0; i <= (int)player2HandString.length(); i++){
        String tileLetter(1, player2HandString.at(i));
        tuple<string, int> data = make_tuple(tileLetter, getValue(tileLetter));
        player2Hand.append(data);
    }

    String tileBagState = info.at(7);
    TileList tileBag = TileList();
    for(int i = 0; i <= (int)tileBagState.length(); i++){
        String tileLetter(1, tileBagState.at(i));
        tuple<string, int> data = make_tuple(tileLetter, getValue(tileLetter));
        player1Hand.append(data);
    }

    line.push_back(info.at(8));


    for(int i = 0; i <= boardSize; i++){
        Tile *tile = new Tile(line.at(i), getValue(line.at(i)));
        boardList.append(tile);
    }

    // Now create a game and set the variable to what we have read from the file
    Game* game = new Game(player1Name, player2Name);
    game->currentPlayer = currentPlayer;
    game->player1->score = player1Score;
    game->player2->score = player2Score;
    game->player1->hand = player1Hand;
    game->player2->hand = player2Hand;
    game->board.tiles = boardList;
    game->tileBag = tileBag;
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

                        // checking to see if the player has placed
                        // their entire hand
                        if (tilesPlaced == 6){
                            
                            // Performing bingo special operation
                            cout << endl << "BINGO!!!" << endl<< endl;;
                            
                            // Giving the player the chance to read the
                            // bingo message before continuing
                            do {
                            cout << '\n' << "Press Enter to continue...";
                            } while (cin.get() != '\n');

                            currentPlayer->score = currentPlayer->score + 50;

                            // Forcing move exit
                            playerMove = "Place Done";
                        }

                        else{
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

    if (currentPlayer->hand.size() < 7){
        dealTiles(7 - currentPlayer->hand.size(), currentPlayer);
    }
}

