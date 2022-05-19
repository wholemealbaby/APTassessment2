#include "Game.h"
#include "Player.h"
#include "Tile.h"
#include "Board.h"
#include "MainMenu.h"
#include "split.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <regex>

#define PLAYER_HAND_SIZE 7
#define MIDDLE 7

using std::string;
using std::tuple;
using std::vector;
using std::cin;
using std::endl;
using std::cout;
using std::make_tuple;
using std::get;
using std::stoi;
using std::ifstream;
using std::ofstream;
using std::abs;

Game::Game(){
    this->player1 = new Player("Player1");
    this->player2 = new Player("Player2");
    currentPlayer = player1;
    fillTileBag();
    dealTiles(PLAYER_HAND_SIZE);
    consecutivePasses = 0;
    cout << "Please make your first move across H7" << endl;
    main();
}


Game::Game(string player1Name, string player2Name){
    this->player1 = new Player(player1Name);
    this->player2 = new Player(player2Name);
    currentPlayer = player1;
    fillTileBag();
    dealTiles(PLAYER_HAND_SIZE);
    consecutivePasses = 0;
    cout << "Please make your first move across H7" << endl;
    main();
}

// Load game constructor
Game::Game(Player* player1, Player* player2, String boardStateStr){
    // Performing normal construction
    this->player1 = new Player(player1);
    this->player2 = new Player(player2);
    currentPlayer = player1;
    consecutivePasses = 0;
    fillTileBag();

    // Popping tiles in player1's hand from tileBag
    for(int i = 0; i<player1->hand.size(); i++){
        String tileLetter = player1->hand.get(i)->letter;
        tileBag.pop(tileBag.index(tileLetter));
    }

    // Popping tiles in player2's hand from tileBag
    for(int i = 0; i<player2->hand.size(); i++){
        String tileLetter = player2->hand.get(i)->letter;
        tileBag.pop(tileBag.index(tileLetter));
    }

    // Placing board state tiles on the board
    vector<String> boardState;
    // Seperating boardStateStr
    split(boardStateStr, " ", boardState, true);

    for (String tileInfo: boardState){
        Tile* tileOnBoard;
        // Popping tile from tile bag
        String letter(1, tileInfo[0]);
        tileBag.pop(tileBag.index(letter), tileOnBoard);
        // Placing tile on the board
        placeTile(tileOnBoard, tileInfo.substr(2,2));
        delete tileOnBoard;
        tileOnBoard = nullptr;
    }

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
            std::srand(0);
            tileBag.pop(std::rand() % tileBag.size(), tile);
            // Adding tile to hand
            player->hand.append(tile);
            delete tile;

            // Sort the player's new hand
            currentPlayer->hand.sort();

            // Giving the player the chance to read their new
            // hand by waiting for user to press enter 
            // before continuing

        }
    }
    return replacementValid;
}

bool Game::placeTile(Player* player, String letter, string pos){

    bool placementValid = false;
    // Get Tile from players hand   
    int tileIndex = player->hand.index(letter);
    cout << letter << tileIndex << endl;
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

void Game::placeTile(Tile* tile, string pos){
    cout << "Called placetile 1"<< endl;
    // Derives the integer x value buy substracting the ascii value 
    // of 'A' from the character in the pos string
    int posX = pos[0]-65; 
    int posY = stoi(pos.substr(1, 3));

    // Updating the tile's position
    tile->posX = posX;
    tile->posY = posY;

    board.placeTile(tile, posX, posY);
}

bool Game::placeTile(Tile tile){
    cout << "Called placetile 1"<< endl;
    bool placementValid = false;
        placementValid = board.placeTile(&tile, tile.posX, tile.posY);
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

void Game::saveGame(Player* player1, Player* player2, String currentPlayer, TileList tileBag,  TileList boardTiles){
    // Create save file name string
    String fileName = player1->name + "-VS-" + player2->name + ".txt";
    cout << "Saving game as: " << fileName << endl;

    // Strings containing the contents of the
    // player's hands and the tileBag 
    // TileList objects
    String player1Hand;
    String player2Hand;
    String tileBagString;    

    // Save File stream
    ofstream saveFile (fileName);

    // Writing player1 name and score to save file
    saveFile << player1->name << endl;
    saveFile << player1->score << endl;

    // Building player1's hand string and 
    // writing it to the save file
    while(player1->hand.size() > 0){
        // Adding letter-value to the hand string
        player1Hand += player1->hand.get(0)->letter + "-";
        player1Hand += std::to_string(player1->hand.get(0)->value);
        if (player1->hand.size() != 1){
            player1Hand += ", ";
        }

        player1->hand.pop(0);
    }
    saveFile << player1Hand << endl;

    // Writing player2 name and score to save file
    saveFile << player2->name << endl;
    saveFile << player2->score << endl;

    // Building player2's hand string and 
    // writing it to the save file
    while(player2->hand.size() > 0){
        // Adding letter-value to the hand string
        player2Hand += player2->hand.get(0)->letter + "-";
        player2Hand += std::to_string(player2->hand.get(0)->value);
        if (player2->hand.size() != 1){
            player2Hand += ", ";
        }

        player2->hand.pop(0);
    }
    saveFile << player2Hand << endl;

    // Recording current player
    saveFile << currentPlayer << endl;

    
    while(tileBag.size() > 0){
        tileBagString += tileBag.get(0)->letter;
        tileBag.pop(0);
    }
    saveFile << tileBagString << endl;

    // Writing info of tiles on the board
    // to the save file
    while(boardTiles.size() > 0){
        saveFile << boardTiles.getHead()->letter;
        saveFile << "@";
        char pos_letter = 'A' + boardTiles.getHead()->posX;
        saveFile << pos_letter;
        saveFile << boardTiles.getHead()->posY;
        boardTiles.pop(0);
        saveFile << " ";
    }
}


// Deals each player a given number of tiles
void Game::dealTiles(int numTiles){
    if (numTiles < tileBag.size()){
            // For each tile to be dealt
        for (int i = 0; i < numTiles; i++){
            // Pop two random tiles from the tile bag
            Tile* tile1; 
            std::srand(0);
            tileBag.pop(std::rand() % tileBag.size(), tile1);
            Tile* tile2; 
            std::srand(0);
            tileBag.pop(std::rand() % tileBag.size(), tile2);

            // Insert them into the players hands
            player1->hand.insert(tile1->data, -1);
            player2->hand.insert(tile2->data, -1);

            // Clean up the transfer pointers
            delete tile1;
            delete tile2;
        }
    }
}

// Deals the specified player a given number of tiles
void Game::dealTiles(int numTiles, Player* player){
    if (numTiles < tileBag.size()){
        // For each tile to be dealt
        for (int i = 0; i < numTiles; i++){
            // Pop a random tile from the tile bag
            Tile* tile; 
            std::srand(0);
            tileBag.pop(std::rand() % tileBag.size(), tile);
            currentPlayer->hand.insert(tile->data, -1);
            delete tile;
        }
    }
}

void Game::switchCurrentPlayer(){
    // If the current player is player1 set the current player
    // to player2
    if (currentPlayer->name == player1->name){
        currentPlayer = player2;
    }
    // Otherwise set the current player to player1
    else{
        currentPlayer = player1;
    }
}

void Game::main(){
    // Each iteration of this loop represents a turn
    while (player1->hand.size() != 0 && player2->hand.size() != 0 && consecutivePasses < 4){
        // print game info at the start of a turn
        printGameInfo();

        // Process the player's move from input
        getPlayerMove();

        // Switch the players for the next turn
        switchCurrentPlayer();
    }

    if (player1->hand.size() == 0){
        cout<< player1->name << " WINS!" << endl;
    }
    else if (player2->hand.size() == 0){
        cout<< player1->name << " WINS!" << endl << endl;;
    }
    else {
        cout << "Stalemate."<<endl << endl;
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
        cout << endl;
        playerMove = std::regex_replace(playerMove, std::regex("\\r\\n|\\r|\\n"), "");
        // Checking for placement
    
        if (playerMove.substr(0, 5) == "Place"){
            // Recieving player's word placement
            place(playerMove);
            inputValid = true;
            consecutivePasses = 0;
        }
        // Checking for replacement
        else if (playerMove.substr(0, 7) == "Replace"){
            // Extracting tile letter from command string
            String letter(1, playerMove[8]);
            replaceTile(currentPlayer, letter);
            inputValid = true;
            consecutivePasses = 0;
        }

        // Checking for pass
        else if (playerMove == "pass"){
            inputValid = true;
            consecutivePasses++;
        }

        else if (playerMove == "save game" || playerMove == "Save Game"){
            inputValid = false;
            
            TileList boardTiles = board.getTiles();

            saveGame(player1, player2, currentPlayer->name, tileBag, boardTiles);

            exit(EXIT_SUCCESS);
        }

        // Checking for EOF
        else if (cin.eof()){
            cout << endl << "Goodbye!" << endl;
            exit(0);
        }

        // Printing invalid input if the input is still invalid
        if (inputValid == false){
            cout << "Invalid Input"<< endl;
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
    vector<String> placedTilesPositions;
    vector<String> placedLetters;

    // back up boardState and playerHand in case move is illegal
    backupHand.copy(&currentPlayer->hand);
    backupBoard = board;

    int numTilesPlaced = 0;

    // while the move has not been finished
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
                    // pos is the coordinates of the move
                    String pos = playerMove.substr(11, 3);

                    // Place the specified tile at the position specified at index 11
                    // of the command if the placement succeeds, the input is valid.
                    if (validatePlacement(pos, commandLetter) == true){
                        inputValid = true;
                        placedTilesPositions.push_back(pos);
                        placedLetters.push_back(commandLetter);

                        // Forcing player to follow through with place move
                        cout << "> Place ";
                        std::getline(std::cin, playerMove);
                        cout << endl;
                        playerMove = std::regex_replace( playerMove, std::regex("\\r\\n|\\r|\\n"), "");
                        // Adding place to the beginning of player command
                        playerMove = "Place " + playerMove;
                        numTilesPlaced++;
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
            cout << endl;
            playerMove = std::regex_replace( playerMove, std::regex("\\r\\n|\\r|\\n"), "");
            // Adding place to the beginning of player command
            playerMove = "Place " + playerMove;
        }
    }

    bool legalPlacement = true;
    int i =0;
   while (i < numTilesPlaced && legalPlacement == true){
        if (tilePlacementIsConsecutive(placedTilesPositions) == true){
            placeTile(currentPlayer,
            placedLetters[i],
            placedTilesPositions[i]);
        }
        else{
            legalPlacement = false;
            cout << "Invalid Input. Please ensure that you the enter word ";
            cout << "start to finish and that your placements are ";
            cout << "in a horizontal or vertical straight line ";
            cout << "with no gaps." << endl;
            // Forcing player to follow through with place move
            cout << "> Place ";
            std::getline(std::cin, playerMove);
            cout << endl;
            playerMove = std::regex_replace( playerMove, std::regex("\\r\\n|\\r|\\n"), "");
            // Adding place to the beginning of player command
            playerMove = "Place " + playerMove;
            place(playerMove);
        }
        i++;
    }
}

// Checks if a given letter is in the palyer's hand
// and that the given position is free
bool Game::validatePlacement(String pos, String letter){
    bool placementValid = false;
    // Get Tile from players hand   
    int tileIndex = currentPlayer->hand.index(letter);
    if (tileIndex != -1){
        if (board.validatePos(pos) == true){
            placementValid = true;
        }
    }

    return placementValid;
}

// Recieves a vector containing the string positions of the tiles in
// a word placed ny the player and indicates whether or not
// they were placed consecutively in a straight line from
// right to left or top to bottom
bool Game::tilePlacementIsConsecutive(vector<String> placedTilesPositions){

    // Flags to indicate if consecutive flow of tiles
    // has been broken
    bool verticallyConsecutive = true;
    bool horizontallyConsecutive = true;

    // Converting string positions
    // into 2 vectors of coordinates
    tuple<vector<int>, vector<int>> convertedPositions;
    convertedPositions = convertStringPositions(placedTilesPositions);
    vector<int> xVals = std::get<0>(convertedPositions);
    vector<int> yVals = std::get<1>(convertedPositions);

    // Position of the first tile in the word
    int posX1 = xVals[0];
    int posY1 = yVals[0];
    
    // Iterating through tiles to test consecutiveness

    {
        // Iterator index. Starting at 1 as the front
        // element has already been stored.
        int i = 1;

        // Checking vertical consecutiveness
        while (i < (int)xVals.size() && verticallyConsecutive == true){
            // Checking that the current x value
            // matches the first x value

            if (xVals[i] != posX1){
                verticallyConsecutive = false;
            }

            // Checking that the current y value
            // i spaces below the original y
            // value

            if (yVals[i] != posY1+i){
                // // Iterating through positions between yVals[i-1]
                // // and yVals[i] to see whether or not they are
                // // already occupied by other tiles
                // for (int j = yVals[i-1]; j < yVals[i]; j++){
                //     // If the space between the two tiles is empty
                //     if(board.validateCoords(xVals[i], yVals[j]) == true){
                //         verticallyConsecutive = false;
                //     }
                // }
                verticallyConsecutive = false;
            }

            i++;
        }
    }

    {
        // Iterator index. Starting at 1 as the front
        // element has already been stored.
        int i = 1;

        // Checking horizontal consecutiveness
        while (i < (int)xVals.size() && horizontallyConsecutive == true){
            // Checking that the current y value
            // matches the first y value

            if (yVals[i] != posY1){
                horizontallyConsecutive = false;
            }

            // Checking that the current x value
            // i spaces to the right the original x
            // value

            if (xVals[i] != posX1+i){
                // // Iterating through positions between yVals[i-1]
                // // and yVals[i] to see whether or not they are
                // // already occupied by other tiles
                // for (int j = xVals[i-1]; j < xVals[i]; j++){
                //     // If the space between the two tiles is empty
                //     cout << board.validateCoords(j, yVals[i]) << endl;
                //     if(board.validateCoords(j, yVals[i]) == true){
                //         horizontallyConsecutive = false;
                //     }
                // }
                horizontallyConsecutive = false;
            }

            i++;
        }
    }
    
    bool returnVal;
    
    if (verticallyConsecutive == true){
        cout << "using vert" << endl;
        returnVal = verticallyConsecutive;
    }
    else{
        cout << horizontallyConsecutive << endl;
        returnVal = horizontallyConsecutive;
    }

    return returnVal;
}


// Recieves a string position such as C6 and
// converts it to an integer position (3, 6)
std::tuple<int, int> Game::convertStringPosToInt(String pos){
    int posX = pos[0]-65; 
    int posY = stoi(pos.substr(1, 3));
    return make_tuple(posX, posY);
}

// Converts a vector of string positions into 2
// x and y integer vectors
std::tuple<std::vector<int>, std::vector<int>> Game::convertStringPositions(vector<String> stringPositions){
    vector<int> xVals;
    vector<int> yVals;

    // Iterating through string positions
    // to convert them
    int posX;
    int posY;
    for (String pos: stringPositions){
        // Converting the string pos to integer
        posX = pos[0]-65; 
        posY = stoi(pos.substr(1, 3));
        // Storing resulting coordinates in
        // appropriate vectors
        xVals.push_back(posX);
        yVals.push_back(posY);
    }

    return make_tuple(xVals, yVals);
}