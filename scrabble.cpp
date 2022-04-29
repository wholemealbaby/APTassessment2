#include <iostream>
#include <string>
#include <array>

#include "LinkedList.h"
#include "Node.h"
#include "Tile.h"
#include "MainMenu.cpp"

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

   MainMenu menu;

   LinkedList list;
   list.append("pirrhannas");
   list.append("bears");
   list.append("cockraoches");


   return EXIT_SUCCESS;
}

