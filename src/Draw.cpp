#include "Draw.h"
#include <iostream>
#include <fstream>

Draw::Draw()
{
    //ctor
}

Draw::~Draw()
{
    //dtor
}

void Draw::loadAll()
{
    std::string line;
    std::ifstream file ("title.img");
    if (file.is_open())
    {
        while ( getline (file, line) )
        {
            _titleImage += line + "\n";
        }
        file.close();
    }
}

void Draw::printMainMenu()
{
    std::cout << _titleImage << std::endl;
    std::cout << "Type S T A R T to start the game." << std::endl;
}
