#ifndef MAINMENU_H
#define MAINMENU_H
#include <GameScreen.h>
#include <Draw.h>
#include <string>

class MainMenu: public GameScreen
{
	public:
		MainMenu(Draw drawer, GameManager *gameManager);
		virtual ~MainMenu();
		void update(std::string input);
	protected:
	private:
		bool executeInput(std::string input);
};

#endif // MAINMENU_H
