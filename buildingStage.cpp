#include "buildingStage.h"

buildingStage::buildingStage()
{
	colBrick = 0;
	rowBrick = 0;
}

buildingStage::~buildingStage()
{
	StageBrick.clear();
	colBrick = 0;
	rowBrick = 0;
}

void buildingStage::checkDataFile(string file_name)
{
	std::ifstream checkFile("Data");

	if (!checkFile) {
		std::ofstream saveFile("Data/" + file_name);
		saveFile << "--~-------~--\n";
		saveFile << "-----~-------\n";
		saveFile << "--------~----\n";
		saveFile << "---       ---\n";
		saveFile << "~--       -~-\n";
		saveFile << "---       ---\n";
		saveFile << "-----~-------\n";
		saveFile << "--~------~---\n";
		saveFile << "-~-----~-----\n";

		saveFile.close();
	}
	checkFile.close();
}

void buildingStage::loadLevelFromFile(string file_name)
{
	std::ifstream loadFile("Data/" + file_name);
	if (!loadFile.is_open()) {
		checkDataFile(file_name);
	}
	
	string line;
	unsigned long numBricksPerLines = 0;
	float brickWidth = 0;
	int row = 0;
	int col = 0;
	
	
	// lấy từng viên gạch từ file, kiểm tra có là gạch đặc biệt hay không
	while (getline(loadFile, line)) {
		
		//lấy số lượng gạch trên 1 dòng
		if (numBricksPerLines == 0)
		{
			numBricksPerLines = line.size();
		}

		for (int i = 0; i < line.size(); i++)
		{
			brick getBrick;

			getBrick.setSize({ BRICK_WIDTH,BRICK_HEIGHT });			
			char c = line[i];
			switch (c) {
			case '-': // gạch bình thường
				getBrick.Special = '\0'; 
				break;

			case '~': //gạch đặc biệt
				getBrick.Special = SPECIALS[rand() % (sizeof(SPECIALS) / sizeof(char))]; // Tạo ramdom gạch
				break;

			default:
				getBrick.Special = ' '; // không có gạch
				break;
			}
			StageBrick.push_back(getBrick);
		}
		++row;
	}

	this->colBrick = numBricksPerLines;
	this->rowBrick = row;

	loadFile.close();
}

vector<brick> buildingStage::getBrick(string file_name)
{
	loadLevelFromFile(file_name);
	return StageBrick;
}

int buildingStage::getNumOfCol()
{
	return colBrick;
}

int buildingStage::getNumOfRow()
{
	return rowBrick;
}

