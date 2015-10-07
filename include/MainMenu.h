#ifndef MAINMENU_H
#define MAINMENU_H

#include <StoryView.h>
#include <string>

class MainMenu: public GameScreen
{
	public:
		MainMenu(Draw *drawer, GameManager *gameManager);
		virtual ~MainMenu();
		void update(std::string input);
	protected:
	private:
		bool executeInput(std::string input);
		StoryView *_introView;
};

#endif // MAINMENU_H
