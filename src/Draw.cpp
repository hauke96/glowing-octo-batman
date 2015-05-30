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
    std::ifstream file;
    file.open("title.img");
    if (file.is_open())
    {
        while ( getline (file, line) )
        {
            _titleImage += line + "\n";
        }
        file.close();
    }
    else
    {
        //system("Color 1A"); // WINDOWS
        std::cerr << "\033[1;31mError while reading file \033[0m" << "\033[1;34m\"title.img\"\033[0m" << "\033[1;31m. Make shure it exists!\033[0m";
    }
    file.clear();

    file.open("map.txt");
    if (file.is_open())
    {
        while ( getline (file, line) )
        {
            _map_raw += line + "\n";
        }
        file.close();
    }
    else
    {
        //system("Color 1A"); // WINDOWS
        std::cerr << "\033[1;31mError while reading file \033[0m" << "\033[1;34m\"map.txt\"\033[0m" << "\033[1;31m. Make shure it exists!\033[0m";
    }
}

void Draw::printMainMenuImage()
{
    std::cout << _titleImage << std::endl;
}

void Draw::printMainMenuText()
{
    std::cout << "Type S T A R T to start the game." << std::endl << "If you want to know what glowing-octo-batman is type W T F." << std::endl;
}

std::string Draw::getRawMap()
{
    return _map_raw;
}
