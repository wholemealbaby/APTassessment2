#ifndef MAIN_MENU
#define MAIN_MENU

#include <string>
#include <iostream>
#include <array>
//#include "arrayFunctions.cpp"
#include "Game.h"


using std::string;
using std::array;
using std::cout;
using std::cin;
using std::endl;

class MainMenu{
    private:
    array<array<string, 2>, 4> options = {{{"1", "New Game"}, {"2", "Load Game"}, {"3", "Credits (Show student information)"}, {"4", "Quit"}}};
    public:

    MainMenu(){
        printOptions();

        // Recieving and validating user input

        // User Input
        string userInput;
        // Expected inputs for progression
        array<string, 4> expInputs = {"1", "2", "3", "4"};
        // Recieving user input
        cout<<"> ";
        cin>>userInput;

        while (arrayContains(expInputs, userInput) == -1){
            cout<<"Invalid Input"<<endl<<">"<<endl;
            cin>>userInput;
        }

        if (userInput == "1"){
            newGame();
        }
        else if (userInput == "2"){
            loadGame();
        }
        else if (userInput == "3"){
            showCredits();
        }

    }

    void printOptions(){
        for (array<string, 2> option: options){
            
            cout<<option[0]<<". "<<option[1]<<endl;
        }
    }

    void newGame(){
        String p1name;
        String p2name;
        cout<<"Creating New Game"<<endl;
        cout<<"Player 1 name:"<<endl;
        cin >> p1name;
        cout<<"Player 2 name:"<<endl;
        cin >> p2name;

        Game newGame = Game(p1name, p2name);
        newGame.dealTiles((7 - newGame.player1->hand.size()), newGame.player1);
        newGame.dealTiles((7 - newGame.player2->hand.size()), newGame.player2);        
        
    }

    void loadGame(){
        cout<<"Loading New Game"<<endl;
        return;
    }

    void showCredits(){
        cout<<"----------------------------------"<<endl;
        cout<<"Name: Thomas Gosling"<<endl;
        cout<<"Student ID: s3850201"<<endl;
        cout<<"Email: s3850201@student.rmit.edu.au"<<endl;
        cout<<"----------------------------------"<<endl;

        cout<<"----------------------------------"<<endl;
        cout<<"Name: Xander Broadbear"<<endl;
        cout<<"Student ID: s3902024"<<endl;
        cout<<"Email: s3902024@student.rmit.edu.au"<<endl;
        cout<<"----------------------------------"<<endl;

        
    }
};
#endif
