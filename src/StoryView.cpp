#include <GameManager.h>
#include <StoryView.h>
#include <iostream>

/**
 * Creates a new view for a story.
 * @param storyName The name of the story (=name of the file with the story)
 * @param firstSentence The name of the first sentence.
 * @param gameManager The game manager.
 */
StoryView::StoryView(std::string storyName, std::string firstSentence, GameManager *gameManager)
{
	_story = new Story(storyName, firstSentence, gameManager);
	_story->print();
}
StoryView::~StoryView()
{

}
void StoryView::update(string input)
{
	executeInput(input);
	_story->print();
}
bool StoryView::executeInput(string input)
{
	std::string next = "";
	if(input != "")
	{
		next = _story->answerChosen(input);
	}
	else
	{
		next = _story->getNextText();
	}
	if(next == "")
	{
		notify(); //exit
	}
	else if(_story->getCurrentSentence() != next) _story->setNextText(next);
}
std::string StoryView::getCurrentSentence()
{
	return _story->getCurrentSentence();
}
