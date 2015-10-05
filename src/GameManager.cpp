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
#include "GameManager.h"
#include <GameScreen.h>
#include <MainMenu.h>

GameManager::GameManager()
{
	// Resize console window:
	if(OS == "Linux") system("printf '\e[8;38;68t'");
	//TODO: Create console-rezizement for win and mac as well

	_drawer.loadAll();
//	_gameScreen = new MainMenu(_drawer, this);
	_gameScreen = new StoryView("storyExample", "optionalAnswers", this);
	_newGameScreen = NULL;
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

/** \brief This will display the "~$>" string for the console-like input and also will read it.
 *
 * \return std:: string The users input.
 *
 */
std::string GameManager::readLine()
{
	std::string str;
	std::cout << std::endl << "~$> ";
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

/** \brief Will clear the screen.
 *
 * \return void
 *
 */
void GameManager::clearScreen()
{
	if(OS == "Linux") system("clear");
	if(OS == "MS Windows") system("cls");
	//TODO: also for mac
}
