#include "designGame.h"



designGame::designGame(sf::RenderWindow *window)
{
	this->m_window = window;
	sf::RectangleShape station(sf::Vector2f(1100, 500));
	this->m_station = station;
	this->m_station.setFillColor(sf::Color::Black);
	this->m_station.setOutlineThickness(4);
	this->m_station.setOutlineColor(sf::Color::Green);

	sf::RectangleShape line(sf::Vector2f(500, 4));
	this->m_line = line;
	this->m_line.setFillColor(sf::Color::Green);
	this->m_line.setOrigin(this->m_line.getSize().x / 2, this->m_line.getSize().y / 2);

	sf::CircleShape circle(100);
	this->m_circle = circle;
	this->m_circle.setFillColor(sf::Color::Black);
	this->m_circle.setOutlineThickness(4);
	this->m_circle.setOutlineColor(sf::Color::Green);
	this->m_circle.setOrigin(this->m_circle.getRadius(), this->m_circle.getRadius());

	sf::CircleShape ball(10);
	this->m_ball = ball;
	this->m_ball.setFillColor(sf::Color::Green);
	this->m_ball.setOrigin(this->m_ball.getRadius(), this->m_ball.getRadius());
}

void designGame::update()
{
	this->m_station.setPosition(50, 25);

	this->m_line.setPosition(this->m_station.getSize().x / 2+50,this->m_station.getSize().y/2+ 25);
	this->m_line.setRotation(90);

	this->m_circle.setPosition(this->m_station.getSize().x / 2 + 50, this->m_station.getSize().y / 2 + 25);

	this->m_ball.setPosition(this->m_station.getSize().x / 2 + 50, this->m_station.getSize().y / 2 + 25);

}

void designGame::draw()
{
	this->m_window->draw(this->m_station);
	this->m_window->draw(this->m_circle);
	this->m_window->draw(this->m_line);
	this->m_window->draw(this->m_ball);
	
}

