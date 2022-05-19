
#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "TileList.h"
#include "Player.h"
#include "Tile.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <tuple>

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

    // Deals each player a given number of random tiles from the tile bag
    void dealTiles(int numTiles);

     // Deals a given player a given number of random tiles from the tile bag
    void dealTiles(int numTiles, Player* player);

    // Reads in a place command from player and exectutes the move
    void place(String playerMove);

    // A player places a tile from their had on
    // the board. Returns false if the position
    // is unavailable
    bool placeTile(Player* player, String letter, string pos);
    bool placeTile(Tile tile);

    // Used in load game constructor
    // places a tile on the board without making
    // any validity checks
    void placeTile(Tile* tile, String pos);

    // A player swaps a tile from their hand
    // with a random tile from the tile bag
    bool replaceTile(Player* player, String letter);
    
    // A player passes their turn
    void passTurn(Player* player);

    // Checks if a given letter is in the palyer's hand
    // and that the given position is free
    bool validatePlacement(String pos, String letter);

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

    void saveGame(Player* player1, 
    Player* player2, String currentPlayer, TileList tileBag, TileList boardTiles);

    void loadGame(String fileName);

    // Recieves a vector containing the string positions of the tiles in
    // a word placed ny the player and indicates whether or not
    // they were placed consecutively in a straight line from
    // right to left or top to bottom
    bool tilePlacementIsConsecutive(std::vector<String> placedTiles);

    // Recieves a string position such as C6 and
    // converts it to an integer position (3, 6)
    std::tuple<int, int> convertStringPosToInt(String pos);

    // Converts a vector of string positions into 2
    // x and y integer vectors
    std::tuple<std::vector<int>, std::vector<int>> convertStringPositions(std::vector<String> stringPositions);
    
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
