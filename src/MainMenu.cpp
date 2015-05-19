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

MainMenu::MainMenu(Draw drawer)
{
    _drawer = drawer;
    _drawer.printMainMenu();
}

MainMenu::~MainMenu()
{
    //dtor
}

void MainMenu::update(std::string input)
{
    if(OS == "Linux")system("clear");
    _drawer.printMainMenu();

    executeInput(input);
}

void MainMenu::executeInput(std::string input)
{
    std::regex start_expr("((s|S)(tart))|(START)");
    if(std::regex_match(input, start_expr))
    {
        std::cout << std::endl << "Spiel startet ... 3 ... 2 ... 1 ... BRRRRR" << std::endl << "ERROR 0x00000000cafebabe" << std::endl;
    }
}
