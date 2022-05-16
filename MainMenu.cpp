#ifndef MAIN_MENU
#define MAIN_MENU

#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include <cctype>
#include <clocale>
#include <tuple>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctype.h>
#include "MainMenu.h"
#include "Player.h"
#include "Game.h"
#include "Board.h"
#include "split.h"



#define NUM_PLAYERS 2


using std::string;
using std::array;
using std::cout;
using std::cin;
using std::endl;
using std::isupper;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::tuple;
using std::make_tuple;
using std::stoi;
using std::getline;

template <typename T, std::size_t size>
static int arrayContains(const array<T, size>& expInputs, T userInput);

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
            usernames.at(repeat-1) = username;
            repeat++;
        }
    }
    cout << "Let's Play!" << endl << endl;
    Game game(usernames[0], usernames[1]);
    return;

}

void MainMenu::loadGame(){
/* 

    The save file is as follows, line-by-line.

    Player 1 name
    Player 1 score
    Player 1 hand
    Player 2 name
    Player 2 score
    Player 2 hand
    current player (playerturn)
    Tile bag state
    Board state

*/

    // get save file name from user
    string fileName;
    cout << "Please enter save name" << endl;
    getline(cin, fileName);

    // Create a text string, which is used to output the text file
    string gameSave;
    vector<string> info;
    TileList boardList = TileList();

    // Read from the text file
    ifstream ReadFile(fileName);
    if(!ReadFile){
        cout << "cannot open file." << endl;
        EXIT_FAILURE;
    }

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (ReadFile, gameSave)) {
        info.push_back(gameSave);
    }
    // set the variables based on each line from the file
    String player1Name = info[0];
    String player1Score = info[1];
    String player1HandString = info[2];

    String player2Name = info[3];
    String player2Score = info[4];
    String player2HandString = info[5];

    String currentPlayerName = info[6];

    String boardStateString = info[8];


    TileList* player1Hand = new TileList();

    vector<std::string> player1HandTiles;
     split(player1HandString, ", ", player1HandTiles, true);
    for(String tileInfo: player1HandTiles){
        String letter(1, tileInfo[0]);
        int value = stoi(tileInfo.substr(2, 2));
        tuple<string, int> data = make_tuple(letter, value);
        player1Hand->append(data);
    }

    TileList* player2Hand = new TileList();

    vector<std::string> player2HandTiles;
    split(player2HandString, ", ", player2HandTiles, true);
    for(String tileInfo: player2HandTiles){
        String letter(1, tileInfo[0]);
        int value = stoi(tileInfo.substr(2, 2));
        tuple<string, int> data = make_tuple(letter, value);
        player2Hand->append(data);
    }

    Player* player1 = new Player(player1Name, stoi(player1Score), player1Hand);
    Player* player2 = new Player(player2Name, stoi(player2Score), player2Hand);

    delete player1Hand;
    delete player2Hand;
    player1Hand = nullptr;
    player2Hand = nullptr;

    // Now create a game and set the variable to what we have read from the file
    if(currentPlayerName == player1->name){
        Game game(player1, player2, boardStateString);
    }else{
        Game game(player2, player1, boardStateString);
    }

    delete player1;
    delete player2;
    player1 = nullptr;
    player2 = nullptr;


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

template <typename T, std::size_t size>
static int arrayContains(const std::array<T, size>& expInputs, T userInput){
    bool validInput = false;
    int i = 0;
    while (validInput == false && i < int(size)){
        if (expInputs[i] == userInput){
            validInput = true;
        }
        i++;
    }
    if (validInput == false){
        i = -1;
    }
    return i;
}

#endif
