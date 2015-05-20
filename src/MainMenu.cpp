#include <iostream>
#include "MainMenu.h"
#include <regex>
#include <GameScreen.h>
#include <GameManager.h>
#include <MapViewer.h>

MainMenu::MainMenu(Draw drawer, GameManager *gameManager) : GameScreen::GameScreen(*gameManager)
{
    _drawer = drawer;
    _drawer.printMainMenuImage();
    _drawer.printMainMenuText();
    _gameManager = gameManager;
}

MainMenu::~MainMenu()
{
    //dtor
}

void MainMenu::update(std::string input)
{
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
        MapViewer *mapView = new MapViewer(_drawer, _gameManager);
        _gameManager->changeGameScreen(mapView);
//        delete *mapView;
    }
    else if(std::regex_match(input, wtf_expr))
    {
        std::cout << "glowing-octo-batman is an ASCII based adventure game written in C++.\nYou have to do stuff in this game." << std::endl;
        executedInput = true;
    }

    return executedInput;
}
