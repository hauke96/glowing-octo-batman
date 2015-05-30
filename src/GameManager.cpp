#ifdef __WIN32__
    #define OS "MS Windows"
#elif __linux__
    #define OS "Linux"
#elif __APPLE__
    #define OS "Apple"
#endif
#include "iostream"
#include "GameManager.h"
#include <GameScreen.h>
#include <MainMenu.h>

GameManager::GameManager()
{
    // Resize console window:
    if(OS == "Linux") system("printf '\e[8;38;68t'");
    //TODO: Create console-rezizement for win and mac as well

    _drawer.loadAll();
    _gameScreen = new MainMenu(_drawer, this);
    _newGameScreen = NULL;
}

GameManager::~GameManager()
{
    //dtor
}

void GameManager::start()
{
    std::string input = "";

    while(input != "exit")
    {
        input = readLine();
        clearScreen();
        _gameScreen->update(input);
        if(_newGameScreen != NULL)
        {
            _gameScreen = _newGameScreen;
            _newGameScreen = NULL;
            clearScreen();
            _gameScreen->update("");
        }
    }
}

std:: string GameManager::readLine()
{
    std::string str;
    std::cout << std::endl << "~$> ";
    std::getline(std::cin, str);
    //std::cin >> str;
    return str;
}

void GameManager::changeGameScreen(GameScreen *newGameScreen)
{
    _newGameScreen = newGameScreen;
}

void GameManager::clearScreen()
{
    if(OS == "Linux")system("clear");
    if(OS == "MS Windows")system("cls");
    //TODO: also for mac
}
