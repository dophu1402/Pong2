#include "ball.h"


Ball::Ball(float rad)
{
	this->m_ball.setRadius(rad);
}
Ball::Ball(sf::RenderWindow* window)
{
	this->m_window = window;
	this->radius = 15;
	sf::CircleShape Ball(this->radius);
	this->m_ball = Ball;
	this->m_ball.setFillColor(sf::Color::Yellow);
	this->m_ball.setOrigin(this->m_ball.getRadius(), this->m_ball.getRadius());
	this->m_ball.setPosition(600, 275);

	this->speed = 0.03f;

	sf::Vector2f dir(12.f, 9.f);
	this->direction = dir;
	this->velocity = std::sqrt(direction.x * direction.x + direction.y * direction.y);

}

void Ball::update(int left, int right)
{

	const sf::Time update_ms = sf::seconds(this->speed);
	const auto pos = this->m_ball.getPosition();
	const auto delta = update_ms.asSeconds() * this->velocity;
	sf::Vector2f new_pos(pos.x + this->direction.x * delta, pos.y + this->direction.y * delta);

	if (new_pos.x - this->radius < left) { // left window edge
		this->direction.x *= -1;
		this->speed += this->speed * 0.1;
		new_pos.x = left + this->radius;
	}
	else if (new_pos.x + this->radius >= right) { // right window edge
		this->direction.x *= -1;
		this->speed += this->speed * 0.1;
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
void Ball::draw()
{
	this->m_window->draw(this->m_ball);
}

sf::Vector2f Ball::getPosition()
{
	return this->m_ball.getPosition();
}
float Ball::getRadius()
{
	return m_ball.getRadius();
	//return this->radius;
}

void Ball::resetSpeed()
{
	this->speed = 0.03f;
}


void Ball::drawTo(sf::RenderWindow& window)
{
	window.draw(m_ball);
}

void Ball::move(sf::Vector2f distance) {
	m_ball.move(distance);
}

void Ball::setPosition(sf::Vector2f pos) {
	m_ball.setPosition(pos);
}
