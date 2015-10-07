#ifndef SUBMAPVIEWER_VILLAGE_H
#define SUBMAPVIEWER_VILLAGE_H

#include <GameScreen.h>
#include <Observable.h>
#include <string>

class SubMapViewer_Village: public GameScreen, public Observable
{
		bool _isActive;
	public:
		SubMapViewer_Village(Draw *drawer, GameManager *gameManager);
		virtual ~SubMapViewer_Village();
		void update(std::string input);
	protected:
	private:
		bool executeInput(std::string input);
};

#endif // SUBMAPVIEWER_VILLAGE_H
