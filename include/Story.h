#ifndef STORY_H_
#define STORY_H_

#include <map>
#include <string>
#include <vector>

class GameManager;

class Story
{
		std::map<std::map<std::string, std::string>, std::string> _next; //+sentenceName, answerNumber>, nextSentence>
		std::map<std::string, std::map<std::string, std::string>> _answers; // <sentenceName,<answerNumber, answerText>>
		std::map<std::string, std::string> _messages; // <sentenceName, message>
		std::vector<std::string> _sentences;
		std::string _currentSentence;
		GameManager *_gameManager;
	public:
		Story(std::string, std::string, GameManager*);
		virtual ~Story();
		std::string getNextText();
		std::string answerChosen(std::string);
		void setNextText(std::string);
		std::string getCurrentSentence();
		void print();
	private:
		void loadStory(std::string);
		std::vector<std::string> splitString(std::string, char);
		void checkAnswers();
		std::vector<std::string> getAllAnswerKeys(std::string);
};

#endif /* STORY_H_ */
