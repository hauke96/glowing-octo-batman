#ifndef INCLUDE_STORYVIEW_H_
#define INCLUDE_STORYVIEW_H_

#include <GameScreen.h>
#include <Observable.h>
#include <map>
#include <string>
#include <Story.h>

class StoryView: public GameScreen, public Observable
{
		GameManager *gameManager;
		Story *_story;
	public:
		StoryView(std::string, std::string, GameManager*);
		virtual ~StoryView();
		void update(std::string);
	private:
		bool executeInput(std::string);
};

#endif /* INCLUDE_STORYVIEW_H_ */
