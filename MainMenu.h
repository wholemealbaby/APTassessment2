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

    // Shows developer student IDs
    void showCredits();
};