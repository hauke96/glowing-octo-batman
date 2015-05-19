#ifdef __WIN32__
    #define OS "MS Windows"
#elif __linux__
    #define OS "Linux"
#elif __APPLE__
    #define OS "Apple"
#elif __unix__
    #define OS "UNIX"
#endif
#include <iostream>
#include "MainMenu.h"
#include <regex>
#include <GameScreen.h>

MainMenu::MainMenu(Draw drawer)
{
    _drawer = drawer;
    _drawer.printMainMenuImage();
    _drawer.printMainMenuText();
}

MainMenu::~MainMenu()
{
    //dtor
}

void MainMenu::update(std::string input)
{
    if(OS == "Linux")system("clear");
    _drawer.printMainMenuImage();

    if(!executeInput(input)) _drawer.printMainMenuText();
    else std::cout << std::endl << "Type anything to go back ...";
}

bool MainMenu::executeInput(std::string input)
{
    bool executedInput = false;
    std::regex start_expr("((s|S)(tart))|(START)");
    std::regex wtf_expr("(wtf|WTF)");

    if(std::regex_match(input, start_expr))
    {
        std::cout << "Spiel startet ... 3 ... 2 ... 1 ... BRRRRR" << std::endl << "ERROR 0x00000000cafebabe" << std::endl;
        executedInput = true;
    }
    else if(std::regex_match(input, wtf_expr))
    {
        std::cout << "glowing-octo-batman is an ASCII based adventure game written in C++.\nYou have to do stuff in this game." << std::endl;
        executedInput = true;
    }

    return executedInput;
}
