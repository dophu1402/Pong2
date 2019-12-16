#include "brick.h"

brick::brick()
{
	paddle.setSize({ BRICK_WIDTH, BRICK_HEIGHT });
	//paddle.setTexture(&norBrick);
	//paddle.setFillColor(sf::Color::Yellow);
}

brick::brick(sf::Vector2f size)
{
	paddle.setSize(size);
	//paddle.setFillColor(sf::Color::Yellow);
}

brick::~brick()
{
	//auto destruct....
}


void brick::clear()
{
	Special = ' ';
	this->setSize({ 0, 0 });
	this->setPossition({ 0, 0 });
}

sf::Vector2f brick::getSize()
{
	return paddle.getSize();
}

sf::Vector2f brick::getPosition()
{
	return paddle.getPosition();
}
void brick::draw(sf::RenderWindow& window)
{
	window.draw(paddle);
}

void brick::setPossition(sf::Vector2f Pos)
{
	paddle.setPosition(Pos);
}

bool brick::isHitBall(Ball ball)
{
	if (ball.getPosition().y + ball.getRadius() * 2 > paddle.getPosition().y&& ball.getPosition().y < paddle.getPosition().y + paddle.getSize().y) {
		if (ball.getPosition().x + ball.getRadius() * 2 > paddle.getPosition().x&& ball.getPosition().x < paddle.getPosition().x + paddle.getSize().x) {
			return true;
		}
	}
	return false;
}

void brick::setSize(sf::Vector2f size) {
	paddle.setSize(size);
}

void brick::drawTo(sf::RenderWindow& window) {
	window.draw(paddle);
}

void brick::move(sf::Vector2f distance)
{
	paddle.move(distance);
}

bool brick::isHitSide(Ball ball, bool goingUp)
{
	sf::Vector2f A, B, C, D, O;
	O.x = ball.getPosition().x + ball.getRadius();
	O.y = ball.getPosition().y + ball.getRadius();

	A.x = this->getPosition().x;
	A.y = this->getPosition().y;

	B.x = A.x + this->getSize().x;
	B.y = A.y;

	C.x = A.x + this->getSize().x;
	C.y = A.y + this->getSize().y;

	D.x = A.x;
	D.y = C.y;

	if (O.y > D.y&& O.x + ball.getRadius() >= D.x && O.x - ball.getRadius() <= C.x && goingUp == true)
	{
		return false;
	}
	if (O.y < A.y && O.x + ball.getRadius() >= A.x && O.x - ball.getRadius() <= B.x && goingUp == false)
	{
		return false;
	}
	/*if ((abs(D.y - O.y) <= abs(D.x - O.x) && abs(D.y - O.y) <= abs(C.x - O.x)) && goingUp == true)
	{
		return false;
	}
	if ((abs(A.y - O.y) <= abs(A.x - O.x) && abs(A.y - O.y) <= abs(B.x - O.x)) && goingUp == false)
	{
		return false;
	}*/
	return true;
}

void brick::setColor(sf::Color color)
{
	paddle.setFillColor(color);
}

void brick::setTexture(sf::Texture T)
{
	m_Texture = T;
	paddle.setTexture(&m_Texture);
}

void brick::setIntRect(sf::IntRect I)
{
	paddle.setTextureRect(I);
}

