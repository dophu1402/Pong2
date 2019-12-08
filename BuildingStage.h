#pragma once
#include "Object.h"

class BuildingStage
{
	public:
		BuildingStage(std::vector<Object*>& objects, sf::Vector2f stageSize,
			sf::Vector2f origin, float brickHeight, float separation);

		bool getLevel(int level);

		void addSafetyBricks(int numBricks);

	private:
		std::vector<Object*>& objects_; ///< The stage builder needs access to the game's list of objects to add bricks
		sf::Vector2f stageSize_;
		sf::Vector2f origin_;
		float brickHeight_;
		float separation_;
		void checkDataFile();
		bool loadLevelFromFile(int level);
};


