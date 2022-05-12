
#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "TileList.h"
#include "Player.h"
#include "Tile.h"
#include "Board.h"
#include <iostream>

using std::string;

// Scrabble game instance
class Game {
    public:
    Game();
    Game(string player1Name, string player2Name);
    ~Game();

    // A player places a tile from their had on
    // the board. Returns false if the position
    // is unavailable
    void placeTile(Player* player, Tile* tile, string pos);

    // A player swaps a tile from their hand
    // with a random tile from the tile bag
    void replaceTile(Player* player, Tile* tile);
    
    // A player passes their turn
    void passTurn(Player* player);

    // Deals each player a defined number of random tiles from the tile bag
    void dealTiles(int numTiles);

    void saveGame(Player player1, Player player2, String currentPlayer, String tileBag, Board boardState);


    void loadGame(String fileName);

    int getValue(String letter);


    Player* player1;
    Player* player2;
    Player* currentPlayer;
    private:
    TileList tileBag;
    Board board;

    // Reads the tiles from tile set file and populates
    // the tile bag
    void fillTileBag();

};

#endif // ASSIGN2_NODE_
