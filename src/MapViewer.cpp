#include "MapViewer.h"
#include <Draw.h>
#include <iostream>
#include <algorithm>
#include <regex>

MapViewer::MapViewer(Draw drawer, GameManager *gameManager) : GameScreen::GameScreen(*gameManager)
{
    _drawer = drawer;
    _gameManager = gameManager;
    _selectedField = 49; // 0,1,2 \n 4,5,6 \n ...
    _selectedFieldChar = _drawer.getRawMap().at(_selectedField + (_selectedField / 10));

    _mapGraphics[0][0] = " ~~~ ";
    _mapGraphics[0][1] = " ~~~ ";
    _mapGraphics[0][2] = " ~~~ ";

    _mapGraphics[1][0] = "   ` ";
    _mapGraphics[1][1] = " '   ";
    _mapGraphics[1][2] = "  .  ";

    _mapGraphics[2][0] = "  ʌ  ";
    _mapGraphics[2][1] = " /ʌ\\ ";
    _mapGraphics[2][2] = " / \\ ";

    _mapGraphics[3][0] = " ↟↟  ";
    _mapGraphics[3][1] = " ↟ ↟ ";
    _mapGraphics[3][2] = " ↟↟↟ ";

    _mapGraphics[4][0] = " ⌂⌂  ";
    _mapGraphics[4][1] = " ⌂⤊⌂ ";
    _mapGraphics[4][2] = "  ⌂  ";
}

MapViewer::~MapViewer()
{
    //dtor
}

void MapViewer::update(std::string input)
{
    executeInput(input);
    std::cout << "OK" << std::endl;
    //_drawer.printMap();
    std::cout << "╓────────────────────────────────────╖" << std::endl;
    std::cout << "║ THE HOLY KINGDOM \033[4m\033[1mMODGNI KYLOH EHT\033[0m: ║" << std:: endl;
    std::cout << "╙────────────────────────────────────╜" << std::endl;
    renderImage();
    std::cout << "You are " << getFieldDescription(_selectedFieldChar) << std::endl;
}

bool MapViewer::executeInput(std::string input)
{
    bool executedInput = false;
    std::regex walk_expr("((go|move)|walk)( )((((right|top)|up)|down)|left)");

    if(std::regex_match(input, walk_expr))
    {
        if(input.find("left") != std::string::npos)
        {
            if(_selectedField % 10 != 0) _selectedField--;
        }
        else if(input.find("right") != std::string::npos)
        {
            if(_selectedField % 10 != 9) _selectedField++;
        }
        else if(input.find("top") != std::string::npos
            || input.find("up") != std::string::npos)
        {
            if(_selectedField >= 10) _selectedField -= 10;
        }
        else if(input.find("down") != std::string::npos)
        {
            if(_selectedField < 60) _selectedField += 10;
        }
        _selectedFieldChar = _drawer.getRawMap().at(_selectedField + (_selectedField / 10));
    }
    return false;
}

void MapViewer::renderImage()
{
    // ─ ┘ ┐ ┌ └ │ ┬ ├ ┤ ┴ ┼

    // ━ ┛ ┓ ┏ ┗ ┃ ┳ ┣ ┫ ┻ ╋

    // ┡ ┢ ┩ ┪ ┱ ┲ ┹ ┺ ╃ ╄ ╅ ╆

    //UNDERLINE: \033[4m
    //BOLD:      \033[1m
    //NOTHING:   \033[0m

    std::string output = "",
        rawMap = _drawer.getRawMap(),
        rawRow = _drawer.getRawMap().substr(0, _drawer.getRawMap().find('\n')); // get first row of map.txt
    int amountRows = (std::count(rawMap.begin(), rawMap.end(), '\n')) * 4 + 1,
        amountCols = rawRow.size();

    for(int row = 0; row < amountRows; row++)
    {
        if(row % 4 == 0)
        {
            rawRow = _drawer.getRawMap().substr((row / 4) * (amountCols + 1) , amountCols); // get first row of map.txt
        }
        for(int col = 0; col < amountCols; col++)
        {
            //if((row - 1) / 5 == _selectedField)
            if(row % 4 == 0) // lines between fields
            {
                if(col == 0) // first col
                {
                    if(((row - 4)/ 4) * 10 + col == _selectedField) // if field is selected
                    {
                        if(row == 0) output +="\033[31m┏\033[0m";
                        else if(row == amountRows - 1) output += "\033[31m┗\033[0m";
                        else output += "\033[31m┡\033[0m";
                    }
                    else if((row / 4) * 10 + col == _selectedField) // if field is selected
                    {
                        if(row == 0) output +="\033[31m┏\033[0m";
                        else if(row == amountRows - 1) output += "\033[31m┗\033[0m";
                        else output += "\033[31m┢\033[0m";
                    }
                    else
                    {
                        if(row == 0) output +="┌";
                        else if(row == amountRows - 1) output += "└";
                        else output += "├";
                    }
                }

                if((row / 4) * 10 + col == _selectedField || ((row - 4) / 4) * 10 + col == _selectedField) output += "\033[31m━━━━━\033[0m"; // this or the previous row
                else output += "─────";

                if(col == amountCols - 1) // last col
                {
                    if(row == 0)
                    {
                        if((row/ 4) * 10 + col == _selectedField) output += "\033[31m┓\033[0m";
                        else output += "┐";
                    }
                    else if(row == amountRows - 1)
                    {
                        if(((row - 4)/ 4) * 10 + col == _selectedField) output += "\033[31m┛\033[0m";
                        else output += "┘";
                    }
                    else
                    {
                        if((row/ 4) * 10 + col == _selectedField) output += "\033[31m┪\033[0m";
                        else if(((row - 4) / 4) * 10 + col == _selectedField) output += "\033[31m┩\033[0m";
                        else output += "┤";
                    }
                }
                else
                {
                    if(((row - 4)/ 4) * 10 + col == _selectedField) // if field is selected at any col
                    {
                        if(row == 0) output += "\033[31m┱\033[0m";
                        else if(row == amountRows - 1) output += "\033[31m┹\033[0m";
                        else output += "\033[31m╃\033[0m";
                    }
                    else if((row/ 4) * 10 + col == _selectedField) // if field is selected at any col
                    {
                        if(row == 0) output += "\033[31m┱\033[0m";
                        else if(row == amountRows - 1) output += "\033[31m┹\033[0m";
                        else output += "\033[31m╅\033[0m";
                    }
                    else if(((row - 4)/ 4) * 10 + col + 1 == _selectedField) // if field is selected at any col
                    {
                        if(row == 0) output += "\033[31m┲\033[0m";
                        else if(row == amountRows - 1) output += "\033[31m┺\033[0m";
                        else output += "\033[31m╄\033[0m";
                    }
                    else if((row/ 4) * 10 + col + 1 == _selectedField) // if field is selected at any col
                    {
                        if(row == 0) output += "\033[31m┲\033[0m";
                        else if(row == amountRows - 1) output += "\033[31m┺\033[0m";
                        else output += "\033[31m╆\033[0m";
                    }
                    else // any col
                    {
                        if(row == 0) output += "┬";
                        else if(row == amountRows - 1) output += "┴";
                        else output += "┼";
                    }
                }
            }
            else
            {
                if((row / 4) * 10 + col == _selectedField || (row / 4) * 10 + col - 1 == _selectedField && _selectedField % 10 != 9) output += "\033[31m┃\033[0m"; // this or the previous row
                else output += "│";

                output += getRowOf(rawRow.at(col), row % 4 - 1);

                if(col == amountCols - 1)
                {
                    if((row / 4) * 10 + col == _selectedField) output += "\033[31m┃\033[0m"; // this or the previous row
                    else output += "│";
                }
            }
        }
        output += "\n";
    }

    std::cout << output;
}

std::string MapViewer::getRowOf(char field, int row)
{
    if(row < 0 || row > 2) return "     ";
    switch(field)
    {
    case 'w': // water
        return _mapGraphics[0][row];
    case 'l': // land
        return _mapGraphics[1][row];
    case 'm': // mountain
        return _mapGraphics[2][row];
    case 'f': // forest
        return _mapGraphics[3][row];
    case 'v': // village
        return _mapGraphics[4][row];
    }
    return "     ";
}

std::string MapViewer::getFieldDescription(char field)
{
    switch(field)
    {
    case 'w': // water
        return "swimming in the wide an dangerous Ocean.";
    case 'l': // land
        return "walking on beautiful grasland.";
    case 'm': // mountain
        return "climbing on breathtaking mountains.";
    case 'f': // forest
        return "walking through a dark forest.";
    case 'v': // village
        return "in a peaceful village.";
    }
    return "";
}
