#ifndef MAIN_MENU
#define MAIN_MENU

#include <string>
#include <iostream>
#include <array>
#include <cctype>
#include <clocale>
#include "MainMenu.h"
#include "arrayFunctions.cpp"
#include "Player.h"
#include "Game.h"
#include "Board.h"

#define NUM_PLAYERS 2


using std::string;
using std::array;
using std::cout;
using std::cin;
using std::endl;
using std::isupper;



MainMenu::MainMenu(){
    printOptions();

    // Recieving and validating user input

    // User Input
    string userInput;
    // Expected inputs for progression
    array<string, 4> expInputs = {"1", "2", "3", "4"};
    // Recieving user input
    cout<<"> ";
    std::getline(std::cin, userInput);

    // Checking for EOF
    if (cin.eof()){
        cout << endl << "Goodbye!" << endl;
        exit(0);
    }

    while (arrayContains(expInputs, userInput) == -1){
        cout<<"Invalid Input"<<endl<<">"<<endl;
        std::getline(std::cin, userInput);

        // Checking for EOF
        if (cin.eof()){
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

    int repeat = 1;
    while (repeat <= NUM_PLAYERS){
        cout << "Enter a name for player ";
        cout << repeat;
        cout << " (uppercase characters only)" << endl;
        cout << "> ";
        std::getline(std::cin, username);

        // Checking for EOF
       if (cin.eof()){
            cout << endl << "Goodbye!" << endl;
            exit(0);
        }

        // Verifying that username is uppercase
        else if (validateUsername(username) != true){
            cout << "Invalid Input" << endl;
        }

        else {
            cout<<endl<<endl;
            cout << " made game" << endl;
            usernames.at(repeat-1) = username;
            repeat++;
        }
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

    cout<<"----------------------------------"<<endl;
    cout<<"Name: Xander Broadbear"<<endl;
    cout<<"Student ID: s3902024"<<endl;
    cout<<"Email: s3902024@student.rmit.edu.au"<<endl;
    cout<<"----------------------------------"<<endl;
}

// Checks that the given username is all uppercase
bool MainMenu::validateUsername(String username){
    // Current index in username
    unsigned int index = 0;
    // flag indicating whether or not a lowercase has been found
    bool isUpper = true;
    while (isUpper == true && index < username.length()){
        if (isupper(username[index]) == false){
            isUpper = false;
        }
        index++;
    }
    return isUpper;
}

#endif
