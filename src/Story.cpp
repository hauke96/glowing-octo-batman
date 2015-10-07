#include <GameManager.h>
#include <stddef.h>
#include <sys/types.h>
#include <Story.h>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <regex>
#include <stdexcept>
#include <utility>

Story::Story(std::string storyName, std::string firstSentence, GameManager *gameManager)
{
	_currentSentence = firstSentence;
	_gameManager = gameManager;
	loadStory(storyName);
}

Story::~Story()
{
}

/**
 * Gets the next sentence.
 * @return The next gamescreen when the user presses ENTER. If he has to choose between answers, the reult will be the current sentence.
 */
std::string Story::getNextText()
{
	std::map<std::string, std::string> t;
	t[_currentSentence] = "0";
	if(_next[t] == "") return _currentSentence;
	return _next[t];
}

/**
 * This method will give you the next sentence depending on the users answer.
 * @param answer The answer of the user.
 * @return The name of the next sentence.
 */
std::string Story::answerChosen(std::string answer)
{
	std::vector<std::string> allKeys = getAllAnswerKeys(_currentSentence);
	if(std::find(allKeys.begin(), allKeys.end(), answer) == allKeys.end()) return _currentSentence; // if input is no answer

//	_gameManager->print(answer + "\n");
//	_gameManager->print(_currentSentence + "\n");
//	_gameManager->print(_answers[_currentSentence][answer] + "\n");
	std::map<std::string, std::string> t;
	t[_currentSentence] = answer;
//	_gameManager->print(_next[t] + "\n");
	return _next[t];
}

/**
 * This will set the new sentence.
 * @param nextSentence The new sentence.
 */
void Story::setNextText(std::string nextSentence)
{
	_currentSentence = nextSentence;
}
/**
 * Gets the current sentence of the story.
 * @return
 */
std::string Story::getCurrentSentence()
{
	return _currentSentence;
}
/**
 * Prints the message of the story.
 */
void Story::print()
{
	_gameManager->printText(_messages[_currentSentence] + std::string("\n\n"));
	std::vector<std::string> keys = getAllAnswerKeys(_currentSentence);
	if(keys.size() != 0)
	{
		for(int i = 0; i < keys.size(); i++)
		{
			_gameManager->printText("  (" + keys.at(i) + ") : " + _answers[_currentSentence].at(keys.at(i)) + "\n");
		}
		_gameManager->printText("\n");
	}
}
/**
 * Load a story. The story has to be a .txt file and the extension must not be part of the parameter.
 * @param storyName The name of the story.
 */
void Story::loadStory(std::string storyName)
{
	std::string line;
	std::ifstream file;
	file.open("stories/" + storyName + ".txt");
	std::regex emptyLine_expr("( *)");
	if(file.is_open())
	{
		std::string sentenceName = "";
		std::map<std::string, std::string> answerMap;
		std::map<std::string, std::string> nextMap;

		while(getline(file, line))
		{
			if(!std::regex_match(line, emptyLine_expr) && line.front() != '#' && line != "-")
			{
				// Replace all "\n" in the text by the real escape sequence.
				size_t pos = 0;
				const std::string old = "\\n";
				while((pos = line.find("\\n", pos)) <= line.size())
				{
					line.replace(pos, old.length(), "\n");
					pos += 1;
				}

				//Split by ':'
				std::vector<std::string> parsedLine = Story::splitString(line, ':');
				try // in the message can appear more ':' so repear these "errors":
				{
					if(parsedLine.at(0) == "SentenceMessage")
					{
						std::vector<std::string> temp(2);
						temp.at(0) = parsedLine.at(0);
						temp.at(1) = parsedLine.at(1);
						for(int i = 2; i < parsedLine.size(); i++)
						{
							temp.at(1) += ':' + parsedLine.at(i);
						}
						parsedLine = temp;
					}
				}
				catch(std::out_of_range) // happens when no ':' appeared in the line which can happen, so just do nothing
				{
				}
				if(parsedLine.at(0) == "SentenceName" && sentenceName == "")
				{
					_sentences.push_back(parsedLine.at(1));
					sentenceName = parsedLine.at(1);
				}
				else if(sentenceName != "")
				{
					if(parsedLine.at(0) == "SentenceName")
					{
						_gameManager->printText("\033[31mStructure of " + storyName + ".txt invalid!\033[0m" + "\n");
					}
					else if(parsedLine.at(0) == "SentenceMessage")
					{
						if(_messages.count(sentenceName) == 0)
						{
							_messages[sentenceName] = parsedLine.at(1);
						}
						else
						{
							_gameManager->printText(
								"\033[31mThere is more than one message in the \"" + sentenceName + std::string("\" sentence. This is not allowed!\033[0m\n\n"));
						}
					}
					else if(parsedLine.at(0) == "SentenceAnswer")
					{
						if(parsedLine.size() == 3)
						{
							answerMap[parsedLine.at(1)] = parsedLine.at(2);
							_answers[sentenceName] = answerMap;
						}
						else
						{
							_gameManager->printText(
								"\033[31mThere is a wrong amount of arguments in one answer block of the \"" + sentenceName
									+ std::string("\" sentence!\nThere must be 3 arguments (look into the \"storyExample.txt\" for help.\033[0m\n\n"));
						}
					}
					else if(parsedLine.at(0) == "SentenceNext")
					{
						if(parsedLine.size() == 3)
						{
							if(parsedLine.at(1) != "0")
							{
								nextMap[sentenceName] = parsedLine.at(1);
								_next[nextMap] = parsedLine.at(2);
							}
							else
							{
								_gameManager->printText(
									"\033[31mThe second argument in answer block must not be \"0\"! Have a look in the \"" + sentenceName
										+ std::string("\" sentence!\n\n"));
							}
						}
						else if(parsedLine.size() == 2)
						{
							nextMap[sentenceName] = "0";
							_next[nextMap] = parsedLine.at(1);
						}
						else
						{
							_gameManager->printText(
								"\033[31mA next block in the sentence \"" + sentenceName
									+ std::string(
										"\" has a wrong amount of arguments! There must be either 2 or 3 arguments (look into the \"storyExample.txt\" for help.\033[0m\n\n"));
						}
					}
					else
					{
						_gameManager->printText("\033[31mUnknown block: \"" + line + std::string("\"\033[0m\n\n"));
					}
				}
			}
			else if(line == "-")
			{
				sentenceName = "";
				if(answerMap.size() == 0)
				{
					answerMap[sentenceName] = "0";
					_answers[sentenceName] = answerMap;
				}
				if(nextMap.size() == 0)
				{
					nextMap[sentenceName] = "0";
					_next[nextMap] = "$exit";
				}
				answerMap.clear();
				nextMap.clear();
			}
		}
		file.close();
	}
	else
	{
		//system("Color 1A"); // WINDOWS
		_gameManager->printText("\033[31mError while reading file \033[0m\033[34m\"" + storyName + std::string(".txt\"\033[0m\033[31m. Make shure it exists!\033[0m"));
	}
	checkAnswers();
}

/**
 * Checks if every answer has its next block.
 */
void Story::checkAnswers()
{
	for(int i = 0; i < _sentences.size(); i++)
	{
		std::vector<std::string> allKeys = getAllAnswerKeys(_sentences.at(i));

		for(u_int i = 0; i < allKeys.size(); i++)
		{
			std::map<std::string, std::string> tempMap;
			tempMap[_sentences.at(1)] = allKeys.at(i); //build the map <sentence,answerNumber> for the _next map
			if(_next.count(tempMap) == 0) //if element does not exist -> element exists in the answers map but not in the next map -> error
			{
				_gameManager->printText("\033[31mThe answer \"" + allKeys.at(i) + "\" has no fitting next block!\033[0m" + "\n" + "\n");
			}
		}
	}
}
/**
 * Gets a list of all answer keys in the given sentence.
 * @param sentence The sentence which answers you want to know.
 * @return The list of answers.
 */
std::vector<std::string> Story::getAllAnswerKeys(std::string sentence)
{
	std::vector<std::string> allKeys;

	// Put all answer numbers of _sentences.at(...) into one list:
	for(auto entry : _answers) // go through all answers
	{
		if(entry.first != sentence) continue; // if not the wanted answer: ignore
		std::map<std::string, std::string> t;
		t = entry.second; // get the map with the numbers and texts for the answers of this sentence
		for(auto entry2 : t)
		{
			allKeys.push_back(entry2.first); // put them all into a list
		}
	}

	return allKeys;
}
/**
 * Splits a string by the given delimiter.
 * @param str The string.
 * @param delimiter The delimiter to split by.
 * @return All parts after splitting.
 */
std::vector<std::string> Story::splitString(std::string str, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream stream(str); // Turn the string into a stream.
	std::string temp;

	while(std::getline(stream, temp, delimiter))
	{
		result.push_back(temp);
	}

	return result;
}
