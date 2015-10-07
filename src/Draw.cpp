#include <Draw.h>
#include <GameManager.h>
#include <fstream>
#include <iostream>

Draw::Draw(GameManager *gameManager)
{
	_gameManager = gameManager;
}

Draw::~Draw()
{
	//dtor
}

/** \brief Loads all image and map files.
 *
 * \return void
 *
 */
void Draw::loadAll()
{
	std::string line;
	std::ifstream file;
	file.open("title.img");
	if(file.is_open())
	{
		while(getline(file, line))
		{
			_titleImage += line + "\n";
		}
		file.close();
	}
	else
	{
		//system("Color 1A"); // WINDOWS
		std::cerr << "\033[1;31mError while reading file \033[0m"
				<< "\033[1;34m\"title.img\"\033[0m"
				<< "\033[1;31m. Make shure it exists!\033[0m";
	}
	file.clear();

	file.open("map.txt");
	if(file.is_open())
	{
		while(getline(file, line))
		{
			_map_raw += line + "\n";
		}
		file.close();
	}
	else
	{
		//system("Color 1A"); // WINDOWS
		std::cerr << "\033[1;31mError while reading file \033[0m"
				<< "\033[1;34m\"map.txt\"\033[0m"
				<< "\033[1;31m. Make shure it exists!\033[0m";
	}
}

/** \brief Prints the image of the main menu onto the screen.
 *
 * \return void
 *
 */
void Draw::printMainMenuImage()
{
	_gameManager->printText(_titleImage + "\n");
}

/** \brief Prints the text of the main menu.
 *
 * \return void
 *
 */
void Draw::printMainMenuText()
{
	_gameManager->printText("Type S T A R T to start the game.\nIf you want to know what glowing-octo-batman is type W T F.\n");
}

/** \brief Returns the raw map with its field chars.
 *
 * \return std::string The raw map.
 *
 */
std::string Draw::getRawMap()
{
	return _map_raw;
}
