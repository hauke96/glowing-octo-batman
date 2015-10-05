#include <GameManager.h>
#include <StoryView.h>

StoryView::StoryView(std::string storyName, std::string firstSentence, GameManager *gameManager):GameScreen::GameScreen(*gameManager)
{
	_story = new Story(storyName, firstSentence);
	_story->answerChosen("4");
}
StoryView::~StoryView()
{

}
void StoryView::update(string input)
{

}
bool StoryView::executeInput(string input)
{

}
