#include "HighScore.h"

HighScore::HighScore()
{
}

HighScore::~HighScore()
{
	this->ScoreBoard.clear();
}

void HighScore::saveHighScore(int score, string file_name)
{
	loadHighScores(file_name);
	ScoreBoard.push_back(to_string(score));
	sort();
	resize();
	writeHighScores(file_name);
}

void HighScore::resize()
{
	//kiem tra lai neu bang diem qua 10 thi xoa bot
	while (this->ScoreBoard.size() > 10)
	{
		ScoreBoard.pop_back();
	}
}

void HighScore::writeHighScores(string file_name)
{
	ofstream scoresFile(file_name);
	//Xoa file cu
	if (scoresFile.is_open())
		scoresFile.clear();

	//Viet diem vao file
	for (int i = 0; i < ScoreBoard.size(); i++)
	{
		scoresFile << ScoreBoard[i] << endl;
	}

	scoresFile.close();
}

void HighScore::loadHighScores(string file_name)
{
	ifstream scoresFile(file_name);

	//Lay diem tu file
	if (scoresFile.is_open()) {
		string line;
		while (getline(scoresFile, line))
			ScoreBoard.push_back(line);
	}

	scoresFile.close();
}

vector<string> HighScore::getHighScore()
{
	return ScoreBoard;
}

void HighScore::sort()
{
	for (int i = 0; i < this->ScoreBoard.size() - 1; i++)
	{
		for (int j = i + 1; j < this->ScoreBoard.size(); j++)
		{
			if (stoi(ScoreBoard[j]) > stoi(ScoreBoard[i]))
			{
				swap(ScoreBoard[j], ScoreBoard[i]);
			}
		}
	}
}
