#include <Draw.h>
#include <GameManager.h>
#include <SubMapViewer_Village.h>
#include <iostream>
#include <regex>

/** \brief Creates a SubMapViewer for the village
 *
 * \param drawer Draw The drawer reference.
 * \param gameManager GameManager* The pointer to a game manager.
 *
 */
SubMapViewer_Village::SubMapViewer_Village(Draw drawer, GameManager *gameManager)
{
    _drawer = drawer;
    _gameManager = gameManager;
    _isActive = true;
}

SubMapViewer_Village::~SubMapViewer_Village()
{
    //dtor
}


/** \brief Updates the MapViewer.
 *          It gives an suitable output based on the users input, writes an title into the screen
 *          and executed the submap render method.
 *
 * \param input std::string The users input.
 * \return void
 *
 */
void SubMapViewer_Village::update(std::string input)
{
	executeInput(input);
}

/** \brief Executes/interpretes the users input.
 *
 * \param input std::string The users input.
 * \return bool True when the input has been executed.
 *
 */
bool SubMapViewer_Village::executeInput(std::string input)
{
    if(input == "") return false;

    std::regex leave_expr("((l|L)eave)|(go back)");

    if(std::regex_match(input, leave_expr))
    {
    	Observable::notify();
    }

    return true;
}
