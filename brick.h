#pragma once
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "math.h"
#include "DesignArcade.h"
#include <iostream>
#include <fstream>
using namespace std;

class brick
{
private:
	sf::RectangleShape paddle;
	sf::Texture m_Texture;
public:
	char Special;

	sf::Texture image;

	brick();
	brick(sf::Vector2f size);
	~brick();
	void clear();
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	void draw(sf::RenderWindow& window);
	void setPossition(sf::Vector2f);
	bool isHitBall(Ball ball);
	void setSize(sf::Vector2f size);
	virtual void drawTo(sf::RenderWindow& window);
	void move(sf::Vector2f distance);
	virtual bool isHitSide(Ball ball, bool goingUp);

	void setColor(sf::Color);
	virtual void setTexture(sf::Texture);
	void setIntRect(sf::IntRect);
	
};

