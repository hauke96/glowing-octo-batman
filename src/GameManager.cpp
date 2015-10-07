#include <Draw.h>
#include <algorithm>
#include <vector>

#ifdef __WIN32__
#define OS "MS Windows"
#elif __linux__
#define OS "Linux"
#elif __APPLE__
#define OS "Apple"
#endif
#include <StoryView.h>
#include "iostream"
#include <cstdlib>
#include <string>
#include "GameManager.h"
#include <GameScreen.h>
#include <MainMenu.h>

#include <stddef.h>
#include <sys/types.h>
#include <Story.h>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <regex>
#include <stdexcept>
#include <utility>

GameManager::GameManager()
{
	// Resize console window:
	if(OS == "Linux") system("printf '\e[8;38;68t'");
	//TODO: Create console-rezizement for win and mac as well

	_output = "";
}

GameManager::~GameManager()
{
	//dtor
}

/** \brief Starts the game manager. This will also execute the main game loop.
 *          This method also deals with input and will pass it on to the game screens.
 *
 * \return void
 *
 */
void GameManager::start()
{
	_drawer = new Draw(this);
	_drawer->loadAll();
	_gameScreen = new MainMenu(_drawer, this);
	_newGameScreen = NULL;

	std::string input = "";
	fillScreen();

	while(input != "exit")
	{
		input = readLine();
		clearScreen();
		_gameScreen->update(input);
		fillScreen();
		if(_newGameScreen != NULL)
		{
			_gameScreen = _newGameScreen;
			_newGameScreen = NULL;
			clearScreen();
			_gameScreen->update("");
			fillScreen();
		}
	}
}

/** \brief This will display the "~$>" string for the console-like input and also will read it.
 *
 * \return std:: string The users input.
 *
 */
std::string GameManager::readLine()
{
	std::string str;
	_output += "\n~$> ";
	std::cout << _output;
	std::getline(std::cin, str);
	return str;
}

/** \brief Replaces the current game screen with a new one.
 *
 * \param newGameScreen GameScreen* The new game screen as pointer.
 * \return void
 *
 */
void GameManager::changeGameScreen(GameScreen *newGameScreen)
{
	_newGameScreen = newGameScreen;
}

/** \brief Will clear the buffer so the next draw (executing the readLine method) will clear the screen.
 *
 * \return void
 *
 */
void GameManager::clearScreen()
{
	_output = "";
//	if(OS == "Linux")
//	{
//		_gameManager->print(std::string(36,'\n');
//	}
//	if(OS == "MS Windows") system("cls");
	//TODO: also for mac
}
/**
 * Puts a text into the buffer.
 * @param output The text.
 */
void GameManager::print(std::string output)
{
	_output += output;
}
/**
 * Puts a text into the buffer and does automatic line breaks. This does not work with formatting stuff like \033[31m stuff and so on.
 * This method cuts the text by the '\n' character and calls the printPart() method for each part.
 * @param output The text.
 */
void GameManager::printText(std::string output)
{
	if(std::count(_output.begin(), _output.end(), '\n') != 0)
	{
		//Split into lines:
		std::vector<std::string> result;
		std::stringstream stream(output); // Turn the string into a stream.
		std::string temp;

		while(std::getline(stream, temp, '\n'))
		{
			result.push_back(temp);
		}
		std::vector<std::string> parsedLine = result;

		for(int i = 0; i < parsedLine.size(); i++)
		{
			printPart(parsedLine.at(i));
			_output += std::string("\n");
		}
	}
	else
	{
		_output += output;
	}
}
/**
 * This Method will make automatic line breaks into the text.
 * @param output The text.
 * @return Formatted line. If the line does not need any line breaks "" will be returned.
 */
std::string GameManager::printPart(std::string output)
{
	if(getLength(output) > 68)
	{
		//Split into words:
		std::vector<std::string> result;
		std::stringstream stream(output); // Turn the string into a stream.
		std::string temp;

		while(std::getline(stream, temp, ' '))
		{
			result.push_back(temp);
		}
		std::vector<std::string> parsedLine = result;

		//put words together to one line:
		std::string line;
		for(int i = 0; i <= parsedLine.size() && getLength(line) + getLength(parsedLine.at(i)) < 68; i++)
		{
			line += parsedLine.at(i) + std::string(" ");
		}
		line += "\n";
		_output += line;
		std::string(printPart(output.substr(getLength(line) - 2, getLength(output) - getLength(line) + getLength(parsedLine.at(parsedLine.size() - 1)))));
		return line;
	}
	else
	{
		_output += output;
	}
	return "";
}
/**
 * Calculates the length of a string considering formatting stuff like \033[31m.
 * @param str The string.
 * @return The amount of character (=length).
 */
int GameManager::getLength(std::string str)
{
	// Length of 6:
	// UNDERLINE  : \033[4m
	// BOLD       : \033[1m
	// NOTHING    : \033[0m

	// Length of 7:
	// ROT        : \033[31m
	// DARK GREEN : \033[32m
	// BROWN      : \033[33m
	// BLUE       : \033[34m
	// LIGHT GREEN: \033[36m
	// GRAY       : \033[37m

	int amount6 = 0;
	int amount7 = 0;
	amount6 += countSubstring(str, "\033[0m");
	amount6 += countSubstring(str, "\033[1m");
	amount6 += countSubstring(str, "\033[4m");

	amount7 += countSubstring(str, "\033[31m");
	amount7 += countSubstring(str, "\033[32m");
	amount7 += countSubstring(str, "\033[33m");
	amount7 += countSubstring(str, "\033[34m");
	amount7 += countSubstring(str, "\033[36m");
	amount7 += countSubstring(str, "\033[37m");

	return str.length() - amount6 * 6 - amount7 * 7 + 1;
}
/**
 * Count the amount of a specific substring in a text.
 * @param str The text.
 * @param sub The substring to count.
 * @return The amount of the substring.
 */
int GameManager::countSubstring(std::string str, std::string sub)
{
	if(sub.length() == 0) return 0;
	int count = 0;
	for(size_t offset = str.find(sub); offset != std::string::npos; offset = str.find(sub, offset + sub.length()))
	{
		++count;
	}
	return count;
}
/**
 * Fills the screen with '\n' characters so that the input line is at the very bottom and so that you can't see anything from the old screen.
 */
void GameManager::fillScreen()
{
	_output += "\n";
	if(36 - std::count(_output.begin(), _output.end(), '\n') - 1 < 0) return;
	std::string filler(36 - std::count(_output.begin(), _output.end(), '\n'), '\n');
	_output += filler;
}
