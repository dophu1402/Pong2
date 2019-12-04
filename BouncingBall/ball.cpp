#include "ball.h"



ball::ball(sf::RenderWindow *window)
{
	this->m_window = window;
	this->radius = 15;
	sf::CircleShape ball(this->radius);
	this->m_ball = ball;
	this->m_ball.setFillColor(sf::Color::Yellow);
	this->m_ball.setOrigin(this->m_ball.getRadius(), this->m_ball.getRadius());
	this->m_ball.setPosition(600, 275);

	this->speed = 0.03f;

	sf::Vector2f dir(12.f, 9.f);
	this->direction = dir;
	this->velocity = std::sqrt(direction.x * direction.x + direction.y * direction.y);

}

void ball::update(int left, int right)
{
	
	const sf::Time update_ms = sf::seconds(this->speed);
	const auto pos = this->m_ball.getPosition();
	const auto delta = update_ms.asSeconds() * this->velocity;
	sf::Vector2f new_pos(pos.x + this->direction.x * delta, pos.y + this->direction.y * delta);

	if (new_pos.x - this->radius < left) { // left window edge
		this->direction.x *= -1;
		this->speed += this->speed*0.1;
		new_pos.x = left + this->radius;
	}
	else if (new_pos.x + this->radius >= right) { // right window edge
		this->direction.x *= -1;
		this->speed += this->speed*0.1;
		new_pos.x = right - this->radius;
	}
	else if (new_pos.y - this->radius < 25) { // top of window
		this->direction.y *= -1;
		new_pos.y = 25 + this->radius;
	}
	else if (new_pos.y + this->radius >= 525) { // bottom of window
		this->direction.y *= -1;
		new_pos.y = 525 - this->radius;
	}
	this->m_ball.setPosition(new_pos);
}
void ball::draw()
{
	this->m_window->draw(this->m_ball);
}

sf::Vector2f ball::getPosition()
{
	return this->m_ball.getPosition();
}
float ball::getRadius()
{
	return this->radius;
}