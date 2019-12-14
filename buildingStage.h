#pragma once
#include "brick.h"
#include <iostream>
using namespace std;
#include <vector>
#include <fstream>
#include <string>
#include "DesignArcade.h"

class buildingStage
{
private:
	vector<brick> StageBrick;
	int colBrick, rowBrick;
public:
	buildingStage();
	~buildingStage();
	void checkDataFile(string);
	void loadLevelFromFile(string);
	vector<brick> getBrick(string);
	int getNumOfCol();
	int getNumOfRow();
};

