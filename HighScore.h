#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#include <vector>
#include <fstream>
#include <string>
#include "DesignArcade.h"

class HighScore
{
private:
	vector<string> ScoreBoard;
public:
	HighScore();
	~HighScore();
	void saveHighScore(int, string file_name);
	void resize();
	void writeHighScores(string file_name);
	void loadHighScores(string file_name);
	vector<string> getHighScore();
	void sort();
};

