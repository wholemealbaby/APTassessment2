#include <iostream>
#include <string>
#include <array>

using std::cin; 
using std::cout;
using std::endl;
using std::array;
using std::string;

template <typename T, std::size_t size> // Parameterise the element type and size
int arrayContains(const std::array<T, size>& expInputs, T userInput){
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