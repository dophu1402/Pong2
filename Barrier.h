#pragma once
#include "brick.h"
#include <SFML/Audio.hpp>

class Barrier:public brick
{
public: 
	Barrier();
	virtual bool isHitBall(Ball, bool&, bool& , bool& , bool&);
	virtual void drawTo(sf::RenderWindow& window);
	virtual void setTexture(vector<sf::Texture>);
private:
	brick left, right, top, bottom;
	vector<sf::Texture> m_Texture;
};

