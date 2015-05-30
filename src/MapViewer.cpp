#include "MapViewer.h"
#include <Draw.h>
#include <iostream>

MapViewer::MapViewer(Draw drawer, GameManager *gameManager) : GameScreen::GameScreen(*gameManager)
{
    _drawer = drawer;
    _gameManager = gameManager;
}

MapViewer::~MapViewer()
{
    //dtor
}

void MapViewer::update(std::string input)
{
    _drawer.printMap();
}

bool MapViewer::executeInput(std::string input)
{

}
