#include "SubMapViewer_Village.h"
#include <iostream>

/** \brief Creates a SubMapViewer for the village
 *
 * \param drawer Draw The drawer reference.
 * \param gameManager GameManager* The pointer to a game manager.
 *
 */
SubMapViewer_Village::SubMapViewer_Village(Draw drawer, GameManager *gameManager) : GameScreen::GameScreen(*gameManager)
{
    _drawer = drawer;
    _gameManager = gameManager;
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

}

/** \brief Executes/interpretes the users input.
 *
 * \param input std::string The users input.
 * \return bool True when the input has been executed.
 *
 */
bool SubMapViewer_Village::executeInput(std::string input)
{

}
