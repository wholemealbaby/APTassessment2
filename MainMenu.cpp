#ifndef MAIN_MENU
#define MAIN_MENU

#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include <tuple>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctype.h>
#include "MainMenu.h"
#include "arrayFunctions.cpp"
#include "Player.h"
#include "Game.h"
#include "Board.h"
#include "split.h"




using std::string;
using std::array;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::tuple;
using std::make_tuple;
using std::stoi;
using std::getline;




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
    if (cin.eof()){
        cout << endl << "Goodbye!" << endl;
        exit(0);
    }

    while (arrayContains(expInputs, userInput) == -1){
        cout<<"Invalid Input"<<endl<<">"<<endl;
        cin>>userInput;

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

    for (int repeat = 1; repeat <= 2; repeat++){
        cout << "Enter a name for player ";
        cout << repeat;
        cout << " (uppercase characters only)" << endl;
        cout << "> ";
        cin >> username;

        // Checking for EOF
       if (cin.eof()){
            cout << endl << "Goodbye!" << endl;
            exit(0);
        }

        cout<<endl<<endl;
        usernames.at(repeat-1) = username;
    }
    cout << "Let's Play!" << endl << endl;

    Game game(usernames[0], usernames[1]);
    return;

}

void MainMenu::loadGame(){
    // The save file is as follows, line-by-line.

    // Player 1 name
    // Player 1 score
    // Player 1 hand
    // Player 2 name
    // Player 2 score
    // Player 2 hand
    // current player (playerturn)
    // Tile bag state
    // Board state

    // get save file name from user
    string fileName;
    cout << "Please enter save name" << endl;
    cin >> fileName;

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


    TileList player1Hand = TileList();
    for(int i = 0; i < (int)player1HandString.length(); i++){
        String tileLetter(1, player1HandString.at(i));
        tuple<string, int> data = make_tuple(tileLetter, getValue(tileLetter));
        player1Hand.append(data);
    }

    TileList player2Hand = TileList();
    for(int i = 0; i < (int)player2HandString.length(); i++){
        String tileLetter(1, player2HandString.at(i));
        tuple<string, int> data = make_tuple(tileLetter, getValue(tileLetter));
        player2Hand.append(data);
    }

    String tileBagState = info.at(7);
    TileList tileBag = TileList();
    for(int i = 0; i < (int)tileBagState.length(); i++){
        String tileLetter(1, tileBagState.at(i));
        tuple<string, int> data = make_tuple(tileLetter, getValue(tileLetter));
        tileBag.append(data);
    }




    Player* player1 = new Player(player1Name, stoi(player1Score), player1Hand);
    Player* player2 = new Player(player2Name, stoi(player2Score), player2Hand);


    TileList toPlace;
    int numTiles = 0;
    for(size_t i = 8; i < info.size(); i++){
        vector<string> words;
        split(info[i], ' ', words);

        
        tuple<string, int> data = make_tuple(words[0], getValue(words[0]));

        toPlace.append(data);

        Tile* tile = toPlace.get(numTiles);
        tile->posX = stoi(words[1]);
        tile->posY = stoi(words[2]);

        numTiles++;

    }




    // Now create a game and set the variable to what we have read from the file
    if(currentPlayerName == player1->name){
        Game game(player1, player2, tileBag, toPlace);
    }else{
        Game game(player2, player1, tileBag, toPlace);
    }


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



#endif
