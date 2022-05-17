
#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "TileList.h"
#include "Player.h"
#include "Tile.h"
#include "Board.h"
#include <iostream>

#define MIN_PLACE_ARG_LENGTH    13
#define MAX_PLACE_ARG_LENGTH   14

using std::string;

// Scrabble game instance
class Game {
    public:
    Game();
    Game(string player1Name, string player2Name);
    // Load Game Constructor
    Game(Player* player1, Player* player2, String boardStateString);
    ~Game();

    // A player places a tile from their had on
    // the board. Returns false if the position
    // is unavailable
    bool placeTile(Player* player, String letter, string pos);
    bool placeTile(Tile tile);

    // Used in load game constructor
    // places a tile on the board without making
    // any validity checks
    void placeTile(Tile* tile, String pos);

    //checks if the move is going down or right
    bool isStraight(int x1, int y1, int x2, int y2);

        // A player swaps a tile from their hand
    // with a random tile from the tile bag
    bool replaceTile(Player* player, String letter);
    
    // A player passes their turn
    void passTurn(Player* player);

    // Deals each player a given number of random tiles from the tile bag
    void dealTiles(int numTiles);

     // Deals a given player a given number of random tiles from the tile bag
    void dealTiles(int numTiles, Player* player);

    // Reads in a place command from player and exectutes the move
    void place(String playerMove);

    // Reads the tiles from tile set file and populates
    // the tile bag
    void fillTileBag();

    // Main method for gameplay
    void main();

    // Prints current player, scores and the player's hand
    void printGameInfo();

    // Recieves the palyer's move as input and executes the
    // appropriate move function
    void getPlayerMove();

    // Switches the currentPlayer
    void switchCurrentPlayer();

    void resetMove();

    void saveGame(Player* player1, Player* player2, String currentPlayer, TileList tileBag, TileList boardTiles);

    void loadGame(String fileName);

    //checks if move intersects with a word or the middle of the board
    bool isAdjacent(int x, int y);

    //check if moves are consecutive
    bool isConsecutive(int x, int y, int numTiles);



        Player* player1;
    Player* player2;
    Player* currentPlayer;
    
    TileList backupHand;
    TileList tileBag;
    Board board;
    Board backupBoard;
    
    private:
    // Current count of consecutive passes
    int consecutivePasses;
};

#endif // ASSIGN2_NODE_
