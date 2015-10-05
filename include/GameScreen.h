#ifdef __WIN32__
#define OS "MS Windows"
#elif __linux__
#define OS "Linux"
#elif __APPLE__
#define OS "Apple"
#endif
#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include <string>
#include <Draw.h>
#include <GameManager.h>

class GameManager;
class GameScreen
{
	public:
		virtual void update(std::string input) = 0;
		Draw _drawer;
	protected:
		GameManager *_gameManager;
		void clearScreen()
		{
			if(OS == "Linux") system("clear");
			if(OS == "MS Windows") system("cls");
			//TODO also for mac
		}
	private:
		virtual bool executeInput(std::string input) = 0;
};

#endif // GAMESCREEN_H
