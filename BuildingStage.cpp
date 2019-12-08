#include "BuildingStage.h"
#include <sys/stat.h>
#include <fstream>
#include "Brick.h"


BuildingStage::BuildingStage(std::vector<Object*>& objects, sf::Vector2f stageSize,
	sf::Vector2f origin, float brickHeight, float separation)
	: objects_(objects),
	stageSize_(stageSize),
	origin_(origin),
	brickHeight_(brickHeight),
	separation_(separation)
{
	checkDataFile();
}

bool BuildingStage::getLevel(int level) {
	if (level == 1) {
		// Xep gach vao vi tri da danh dau
		float brickWidth = ((stageSize_.x - separation_) / NUM_BRICKS_PER_LINE);
		srand(time(NULL));

		// cai dat gach dac biet 
		int specials[NUM_SPECIAL_BRICKS];
		for (int i = 0; i < NUM_SPECIAL_BRICKS; ++i) {
			specials[i] = rand() % (NUM_BRICKS_PER_LINE * NUM_BRICK_ROWS);
		}

		for (int row = 0; row < NUM_BRICK_ROWS; ++row) {
			for (int col = 0; col < NUM_BRICKS_PER_LINE; ++col) {

				//neu la gach dac biet
				int k = 0;
				for (; k < NUM_SPECIAL_BRICKS; k++) {
					if (specials[k] == row * NUM_BRICKS_PER_LINE + col) {
						objects_.push_back(
							new brick(origin_.x + separation_ + brickWidth * col,
								origin_.y + separation_ + (NUM_EMPTY_ROWS + row) *
								(brickHeight_ + separation_),
								brickWidth - separation_,
								brickHeight_,
								SPECIALS[rand() % (sizeof(SPECIALS) / sizeof(char))] 
							)
						);
						break;
					}
				}
				// Neu la gach thuong
				if (k == NUM_SPECIAL_BRICKS) {
					objects_.push_back(
						new brick(origin_.x + separation_ + brickWidth * col,
							origin_.y + separation_ + (NUM_EMPTY_ROWS + row) *
							(brickHeight_ + separation_),
							brickWidth - separation_,
							brickHeight_
						)
					);
				}
			}
		}
	}

	// Tu level 2 tro len se load tu file
	else {
		return loadLevelFromFile(level);
	}

	return true;
}

void BuildingStage::addSafetyBricks(int numBricks) {
	float brickWidth = (stageSize_.x - 2 * separation_) / numBricks;

	// Cai dat gach an toan
	for (int col = 0; col < numBricks; ++col) {
		objects_.push_back(
			new brick(2 * separation_ + origin_.x + brickWidth * col,
				origin_.y + stageSize_.y - brickHeight_ * .5f - separation_,
				brickWidth - 2 * separation_,
				brickHeight_ * .5f,
				's'
			)
		);
	}
}

void BuildingStage::checkDataFile() {
	std::ifstream mkdir("Data");

	if (!mkdir) {
		std::ofstream levelTwoFile("Data/levels/2.txt");
		levelTwoFile << "~                  ~\n";
		levelTwoFile << "~                  ~\n";
		levelTwoFile << "~                  ~\n";
		levelTwoFile << "--------------------\n";
		levelTwoFile << "--------------------\n";

		levelTwoFile.close();
	}
	mkdir.close();
}

bool BuildingStage::loadLevelFromFile(int level) {
	// Load file
	std::ifstream levelFile("Data/levels/" + std::to_string(level) + ".txt");
	if (!levelFile.is_open()) {
		return false;
	}

	std::string line;
	char special = '\0';
	unsigned long numBricksPerLines = 0;
	float brickWidth = 0;
	int row = 0;
	int col = 0;

	while (getline(levelFile, line)) {
		col = 0;
		// dong dau la kich thuoc gach cua brick
		if (numBricksPerLines == 0) {
			numBricksPerLines = line.size();
			brickWidth = ((stageSize_.x - separation_) / numBricksPerLines);
		}

		// sua lai kich thuoc neu qua dai hoac qua ngan
		if (line.size() > numBricksPerLines) {
			line.resize(numBricksPerLines, ' ');
		}

		for (char c : line) {
			// Lay gach tu file
			switch (c) {
			case '-': special = '\0';
				break;

			case '~': special = SPECIALS[rand() % (sizeof(SPECIALS) / sizeof(char))]; // Tao ngau nhien ki tu dac biet
				break;

			default: c = ' '; // Vi tri k co gach
			}

			if (c != ' ') {
				objects_.push_back(
					new brick(origin_.x + separation_ + brickWidth * col,
						origin_.y + separation_ + row * (brickHeight_ + separation_),
						brickWidth - separation_,
						brickHeight_,
						special
					)
				);
			}
			++col;
		}
		++row;
	}

	levelFile.close();
	return true;
}

