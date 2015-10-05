#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <GameScreen.h>
#include <string>

class GameScreen;
class GameManager
{
		Draw _drawer;
		GameScreen *_gameScreen, *_newGameScreen;
	public:
		GameManager();
		virtual ~GameManager();
		void start();
		void changeGameScreen(GameScreen *newScreen);
	protected:
	private:
		std::string readLine();
		void clearScreen();
};

#endif // GAMEMANAGER_H
