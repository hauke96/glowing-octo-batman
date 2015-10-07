#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>

class Draw;

class GameScreen;
class GameManager
{
		Draw *_drawer;
		GameScreen *_gameScreen, *_newGameScreen;
		std::string _output;
	public:
		GameManager();
		virtual ~GameManager();
		void start();
		void changeGameScreen(GameScreen *newScreen);
		void clearScreen();
		void print(std::string);
		void printText(std::string);
	protected:
	private:
		std::string readLine();
		void fillScreen();
		std::string printPart(std::string);
		int getLength(std::string);
		int countSubstring(std::string, std::string);
};

#endif // GAMEMANAGER_H
