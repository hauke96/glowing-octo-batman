#include <Draw.h>
#include <GameManager.h>
#include <MapViewer.h>
#include <algorithm>
#include <iostream>
#include <regex>

/** \brief Creates the map viewer.
 *
 * \param drawer Draw The drawer reference.
 * \param gameManager GameManager* The pointer to a game manager.
 *
 */
MapViewer::MapViewer(Draw drawer, GameManager *gameManager) : GameScreen::GameScreen(*gameManager)
{
    _drawer = drawer;
    _gameManager = gameManager;
    _subMap = NULL;
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

/** \brief Updates the MapViewer.
 *          It gives an suitable output based on the users input, writes an title into the screen
 *          and executed the map render method.
 *          It also displays an description of the current map field, the player is standing on.
 *
 * \param input std::string The users input.
 * \return void
 *
 */
void MapViewer::update(std::string input)
{
	if(_subMap != NULL)
	{
		_subMap->update(input);
		return;
	}
    executeInput(input);

    std::cout << "╓────────────────────────────────────╖" << std::endl;
    std::cout << "║ THE HOLY KINGDOM \033[4m\033[1mMODGNI KYLOH EHT\033[0m: ║" << std:: endl;
    std::cout << "╙────────────────────────────────────╜" << std::endl;
    renderImage();
    std::cout << "You are " << getFieldDescription(_selectedFieldChar);
    std::cout << " You can E N T E R this area." << std::endl;
}

/** \brief Analyses the input of the user. If it matches with an RegEx, the fitting action will be executed.
 *
 * \param input std::string The users input.
 * \return bool True if something has been executed.
 *
 */
bool MapViewer::executeInput(std::string input)
{
    if(input == "") return false;

    std::regex walk_expr("(go|move|walk)( )(right|top|up|down|left|(w|W)est|(e|E)ast|(s|S)outh|(n|N)orth)");
    std::regex enter_expr("(e|E)nter|ENTER");

    if(std::regex_match(input, walk_expr))
    {
        if(input.find("left") != std::string::npos
            || input.find("west") != std::string::npos
            || input.find("West") != std::string::npos)
        {
            if(_selectedField % 10 != 0) _selectedField--;
        }
        else if(input.find("right") != std::string::npos
            || input.find("east") != std::string::npos
            || input.find("East") != std::string::npos)
        {
            if(_selectedField % 10 != 9) _selectedField++;
        }
        else if(input.find("top") != std::string::npos
            || input.find("up") != std::string::npos
            || input.find("north") != std::string::npos
            || input.find("North") != std::string::npos)
        {
            if(_selectedField >= 10) _selectedField -= 10;
        }
        else if(input.find("down") != std::string::npos
            || input.find("south") != std::string::npos
            || input.find("South") != std::string::npos)
        {
            if(_selectedField < 60) _selectedField += 10;
        }
        _selectedFieldChar = _drawer.getRawMap().at(_selectedField + (_selectedField / 10));
    }
    else if(std::regex_match(input, enter_expr))
    {
    	std::cout << "skdfg" << std::endl;
        _subMap = new SubMapViewer_Village(_drawer, _gameManager);
        _subMap->attach(this);
        _gameManager->changeGameScreen(_subMap);
    }
    return false;
}

/** \brief Renders the map with all its fanciness.
 *
 * \return void
 *
 */
void MapViewer::renderImage()
{
    // ─ ┘ ┐ ┌ └ │ ┬ ├ ┤ ┴ ┼

    // ━ ┛ ┓ ┏ ┗ ┃ ┳ ┣ ┫ ┻ ╋

    // ┡ ┢ ┩ ┪ ┱ ┲ ┹ ┺ ╃ ╄ ╅ ╆

    // UNDERLINE  : \033[4m
    // BOLD       : \033[1m
    // NOTHING    : \033[0m

	// DARK GREEN : \033[32m
    // LIGHT GREEN: \033[36m
	// BROWN      : \033[33m
	// BLUE       : \033[34m
	// GRAY       : \033[37m

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
                if((row / 4) * 10 + col == _selectedField || ((row / 4) * 10 + col - 1 == _selectedField && _selectedField % 10 != 9)) output += "\033[31m┃\033[0m"; // this or the previous row
                else output += "│";

            	// DARK GREEN : \033[32m
                // LIGHT GREEN: \033[36m
            	// BROWN      : \033[33m
            	// BLUE       : \033[34m
            	// GRAY       : \033[37m

                switch(rawRow.at(col))
                {
                case 'f':
                	output += "\033[32m";
                	break;
                case 'l':
                	output += "\033[1;32m";
                	break;
                case '1':
                case '2':
                case '3':
                	output += "\033[33m";
                	break;
                case 'w':
                	output += "\033[34m";
                	break;
                case 'm':
                	output += "\033[1;37m";
                }

                output += getRowOf(rawRow.at(col), row % 4 - 1);
                output += "\033[0m";

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

/** \brief Returns a specific row of an image (e.g. village or forest).
 *
 * \param field char The field char (v for village, f for forest, ...).
 * \param row int The row of the image (between 0 and 2).
 * \return std::string The row as string.
 *
 */
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
    case '1': // village
    case '2': // village
    case '3': // village
        return _mapGraphics[4][row];
    }
    return "     ";
}

/** \brief Returns an description of the field the player stand on.
 *
 * \param field char The field char (v, f, ...).
 * \return std::string The description.
 *
 */
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
    case '1': // village
    case '2': // village
    case '3': // village
        return "in a peaceful village.";
    }
    return "";
}

void MapViewer::notified()
{
	std::cout << "OK" << std::endl;
	_subMap = NULL;
	_gameManager->changeGameScreen(this);
}
