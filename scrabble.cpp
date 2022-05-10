#include <iostream>
#include <string>
#include <array>

#include "Player.h"
#include "Board.h"
#include "MainMenu.cpp"
#include "Game.h"

using std::cin; 
using std::cout;
using std::endl;
using std::array;
using std::string;

#define EXIT_SUCCESS    0

int main(void) {
   cout<<endl;
   cout<<"Welcome to Scrabble!"<<endl;
   cout<<"--------------------"<<endl<<endl;

   Game game;

   game.dealTiles(7);
   game.placeTile(game.currentPlayer, game.currentPlayer->hand[0], "C1");


   return EXIT_SUCCESS;
}

