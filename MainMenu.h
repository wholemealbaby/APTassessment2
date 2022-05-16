#include <string>
#include <array>

using std::string;
using std::array;

class MainMenu{
    private:
    // Menu progression options
    array<array<string, 2>, 4> options = {{{"1", "New Game"}, {"2", "Load Game"}, {"3", "Credits (Show student information)"}, {"4", "Quit"}}};
    public:
    MainMenu();
    
    // Prints the menu options
    void printOptions();

    // Runs a new instance of Game
    void newGame();

    // Loads a game instance from a save file
    void loadGame();

    //get score of a letter
    static int getValue(string letter){
        // returns the score of a given letter
        const char* cha = letter.c_str();
        // atoi converts char to int precisely
        int letterNum = atoi(cha) - 65;
        
        switch(letterNum) {
        case 0: return 1;
        case 1: return 3;
        case 2: return 3;
        case 3: return 2;
        case 4: return 1;
        case 5: return 4;
        case 6: return 2;
        case 7: return 4;
        case 8: return 1;
        case 9: return 8;
        case 10: return 5;
        case 11: return 1;
        case 12: return 3;
        case 13: return 1;
        case 14: return 1;
        case 15: return 3;
        case 16: return 10;
        case 17: return 1;
        case 18: return 1;
        case 19: return 1;
        case 20: return 1;
        case 21: return 4;
        case 22: return 4;
        case 23: return 8;
        case 24: return 4;
        case 25: return 10;
        default: return -1;    
            }
    }
    // Shows developer student IDs
    void showCredits();

    // Checks that the given username is all uppercase
    bool validateUsername(string username);
};