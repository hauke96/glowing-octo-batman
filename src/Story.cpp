#include <Story.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <utility>

Story::Story(std::string storyName, std::string firstSentence)
{
	_currentSentence = firstSentence;
	loadStory(storyName);
}

Story::~Story()
{
}

std::string Story::getNextText()
{
	return "";
}

void Story::answerChosen(std::string answer)
{
	std::cout << answer << std::endl;
	std::cout << _currentSentence << std::endl;
	std::cout << _answers[_currentSentence][answer] << std::endl;
	std::map<std::string, std::string> t;
	t[_currentSentence] = answer;
	std::cout << _next[t] << std::endl;
}

void Story::loadStory(std::string storyName)
{
	std::string line;
	std::ifstream file;
	file.open(storyName + ".txt");
	std::regex emptyLine_expr("( *)");
	if(file.is_open())
	{
		std::string sentenceName = "";
		std::map<std::string, std::string> answerMap;
		while(getline(file, line))
		{
			if(!std::regex_match(line, emptyLine_expr) && line.front() != '#'
					&& line != "-")
			{
				std::vector<std::string> parsedLine = Story::splitString(line,
						':');
				if(parsedLine.at(0) == "SentenceName" && sentenceName == "")
				{
					_sentences.push_back(parsedLine.at(1));
					sentenceName = parsedLine.at(1);
				}
				else if(sentenceName != "")
				{
					if(parsedLine.at(0) == "SentenceName")
					{
						std::cout << "\033[31mStructure of " << storyName
								<< ".txt invalid!\033[0m" << std::endl;
					}
					else if(parsedLine.at(0) == "SentenceMessage")
					{
						if(_messages.count(sentenceName) == 0)
						{
							_messages[sentenceName] = parsedLine.at(1);
						}
						else
						{
							std::cout << "\033[31m"
									<< "There is more than one message in the \""
									<< sentenceName
									<< "\" sentence. This is not allowed!\033[0m"
									<< std::endl << std::endl;
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
							std::cout << "\033[31m"
									<< "There is a wrong amount of arguments in one answer block of the \""
									<< sentenceName << "\" sentence!"
									<< std::endl
									<< "There must be 3 arguments (look into the \"storyExample.txt\" for help.\033[0m"
									<< std::endl << std::endl;
						}
					}
					else if(parsedLine.at(0) == "SentenceNext")
					{
						if(parsedLine.size() == 3)
						{
							if(parsedLine.at(1) != "0")
							{
								std::map<std::string, std::string> nextMap;
								nextMap[sentenceName] = parsedLine.at(1);
								_next[nextMap] = parsedLine.at(2);
							}
							else
							{
								std::cout << "\033[31m"
										<< "The second argument in answer block must not be \"0\"! Have a look in the \""
										<< sentenceName << "\" sentence!"
										<< std::endl << std::endl;
							}
						}
						else if(parsedLine.size() == 2)
						{
							std::map<std::string, std::string> nextMap;
							nextMap[sentenceName] = parsedLine.at(1);
							_next[nextMap] = "";
						}
						else
						{
							std::cout << "\033[31m"
									<< "A next block in the sentence \""
									<< sentenceName << "\" has a wrong amount of arguments! There must be either 2 or 3 arguments (look into the \"storyExample.txt\" for help.\033[0m"
									<< std::endl << std::endl;
						}
					}
					else
					{
						std::cout << "\033[31m" << "Unknown block: \"" << line
								<< "\"\033[0m" << std::endl << std::endl;
					}
				}
			}
			else if(line == "-")
			{
				sentenceName = "";
				answerMap.clear();
			}
		}
		file.close();
	}
	else
	{
		//system("Color 1A"); // WINDOWS
		std::cout << "\033[31mError while reading file \033[0m"
				<< "\033[34m\"" << storyName << ".txt\"\033[0m"
				<< "\033[31m. Make shure it exists!\033[0m";
	}
	checkAnswers();
}

/**
 * Checks if every answer has its next block.
 */
void Story::checkAnswers()
{
	std::vector<std::string> allKeys;

	// Put all answer numbers of _sentences.at(...) into one list:
	for(auto entry : _answers) // go through all answers
	{
		if(entry.first != _sentences.at(1)) continue; // if not the wanted answer: ignore
		std::map<std::string, std::string> t;
		t = entry.second; // get the map with the numbers and texts for the answers of this sentence
		for(auto entry2 : t)
		{
			allKeys.push_back(entry2.first); // put them all into a list
		}
	}

	for(u_int i = 0; i < allKeys.size(); i++)
	{
		std::map<std::string, std::string> tempMap;
		tempMap[_sentences.at(1)] = allKeys.at(i); //build the map <sentence,answerNumber> for the _next map
		if(_next.count(tempMap) == 0) //if element does not exist -> element exists in the answers map but not in the next map -> error
		{
			std::cout << "\033[31mThe answer \""
					<< allKeys.at(i)
					<< "\" has no fitting next block!\033[0m"
					<< std::endl
					<< std::endl;
		}
	}
}

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
