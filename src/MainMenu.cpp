#include <Draw.h>
#include <GameManager.h>
#include <GameScreen.h>
#include <MainMenu.h>
#include <MapViewer.h>
#include <iostream>
#include <regex>

/** \brief Creates the main menu.
 *
 * \param drawer Draw The drawer reference.
 * \param gameManager GameManager* The pointer to a game manager.
 *
 */
MainMenu::MainMenu(Draw *drawer, GameManager *gameManager)
{
	_drawer = drawer;
	_drawer->printMainMenuImage();
	_drawer->printMainMenuText();
	_gameManager = gameManager;
	_introView = NULL;
}

MainMenu::~MainMenu()
{
	//dtor
}
/** \brief The update method for the MainMenu.
 *          This method prints the main menu image onto the screen and creates an output based on the users input.
 *
 * \param input std::string The input from the user.
 * \return void
 *
 */
void MainMenu::update(std::string input)
{
	_drawer->printMainMenuImage();
	if(_introView != NULL)
	{
		_introView->update(input);
	}

	if(!executeInput(input) && _introView == NULL) _drawer->printMainMenuText();
	else if(_introView == NULL) _gameManager->printText("\nType anything to go back ...");
}

/** \brief The given input will be analysed. If the input is usable (matching to an RegEx), a fitting operation will be executed.
 *
 * \param input std::string The users inout.
 * \return bool True if an action has been executed.
 *
 */
bool MainMenu::executeInput(std::string input)
{
	bool executedInput = false;
	std::regex start_expr("((s|S)(tart))|(START)");
	std::regex wtf_expr("(wtf|WTF)");

	if(std::regex_match(input, start_expr))
	{
		_introView = new StoryView("intro", "text1", _gameManager);
		executedInput = true;
	}
	else if(std::regex_match(input, wtf_expr))
	{
		_gameManager->clearScreen();
		StoryView wtfStory("wtf", "wtf", _gameManager);
		wtfStory.update("");
		_gameManager->printText("glowing-octo-batman is an ASCII based adventure game written in C++.\nYou have to do stuff in this game.\n");
		executedInput = true;
	}
	else if(_introView != NULL && _introView->getCurrentSentence() == "$exit"
			&& input == "")
	{
		MapViewer *mapView = new MapViewer(_drawer, _gameManager);
		_gameManager->changeGameScreen(mapView);
	}

	return executedInput;
}
