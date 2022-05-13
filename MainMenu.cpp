#ifndef MAIN_MENU
#define MAIN_MENU

#include <string>
#include <iostream>
#include <array>
#include "main"
#include "arrayFunctions.cpp"
#include "Player.h"
#include "Game.h"
#include "Board.h"


using std::string;
using std::array;
using std::cout;
using std::cin;
using std::endl;



MainMenu::MainMenu(){
    printOptions();

    // Recieving and validating user input

    // User Input
    string userInput;
    // Expected inputs for progression
    array<string, 4> expInputs = {"1", "2", "3", "4"};
    // Recieving user input
    cout<<"> ";
    cin>>userInput;

    // Checking for EOF
    else if (cin.eof()){
        cout << endl << "Goodbye!" << endl;
        exit(0);
    }

    while (arrayContains(expInputs, userInput) == -1){
        cout<<"Invalid Input"<<endl<<">"<<endl;
        cin>>userInput;

        // Checking for EOF
        else if (cin.eof()){
            cout << endl << "Goodbye!" << endl;
            exit(0);
        }
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

void MainMenu::printOptions(){
    for (array<string, 2> option: options){
        
        cout<<option[0]<<". "<<option[1]<<endl;
    }
}

void MainMenu::newGame(){
    array<String, 2> usernames;
    String username;

    for (int repeat = 0; repeat < 2; repeat++){
        cout << "Enter a name for player ";
        cout << repeat;
        cout << " (uppercase characters only)" << endl;
        cout << "> ";
        cin >> username;

        // Checking for EOF
        else if (cin.eof()){
            cout << endl << "Goodbye!" << endl;
            exit(0);
        }

        cout<<endl<<endl;
        usernames.at(repeat) = username;
    }
    cout << "Let's Play!" << endl << endl;

    Game game(usernames[0], usernames[1]);
    return;

}


void MainMenu::loadGame(){
    cout<<"Loading New Game"<<endl;
    return;
}

void MainMenu::showCredits(){
    cout<<"----------------------------------"<<endl;
    cout<<"Name: Thomas Gosling"<<endl;
    cout<<"Student ID: s3850201"<<endl;
    cout<<"Email: s3850201@student.rmit.edu.au"<<endl;
    cout<<"----------------------------------"<<endl;
}

#endif
