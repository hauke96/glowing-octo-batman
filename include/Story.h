#ifndef STORY_H_
#define STORY_H_

#include <map>
#include <string>
#include <vector>

class Story
{
		std::map<std::map<std::string, std::string>, std::string> _next; //<<sentenceName, answerNumber>, nextSentence>
		std::map<std::string, std::map<std::string, std::string>> _answers; // <sentenceName,<answerNumber, answerText>>
		std::map<std::string, std::string> _messages;
		std::vector<std::string> _sentences;
		std::string _currentSentence;
	public:
		Story(std::string, std::string);
		virtual ~Story();
		std::string getNextText();
		void answerChosen(std::string);
	private:
		void loadStory(std::string);
		std::vector<std::string> splitString(std::string, char);
		void checkAnswers();
};

#endif /* STORY_H_ */
