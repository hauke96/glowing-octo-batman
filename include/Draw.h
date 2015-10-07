#ifndef DRAW_H
#define DRAW_H

#include <string>

class GameManager;

class Draw
{
		std::string _titleImage, _map_raw, _map_processed;
		GameManager *_gameManager;
	public:
		Draw(GameManager*);
		virtual ~Draw();
		void loadAll();
		void printMainMenuImage();
		void printMainMenuText();
		std::string getRawMap();
	protected:
	private:
};

#endif // DRAW_H
