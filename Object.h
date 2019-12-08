#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <SFML/Graphics/RenderWindow.hpp>

class Object
{
public:
	Object() = default;

	virtual ~Object() = default;

	virtual void draw(sf::RenderWindow & window) const = 0;

	virtual void move() {};

	 /* \returns One of the following characters:
	 *      'n' : Khong va cham
	 *      'y' : va cham
	 *      'v' : va cham tren hoac duoi
	 *      'h' : va cham trai hoac phai
	 *      'c' : va cham goc
	 */
	virtual const char collision(sf::FloatRect & boundingBox) const = 0;

	bool delete_ = false;
};

