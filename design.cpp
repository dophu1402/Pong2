#include "design.h"



design::design(sf::RenderWindow* window)
{
	this->m_window = window;
	//this->m_gui = gui;

	this->m_font.loadFromFile("fonts/MarkerFelt.ttf");
	this->m_text.setFont(this->m_font);
	this->m_text.setString("Bouncing Ball");
	this->m_text.setCharacterSize(30);
	this->m_text.setFillColor(sf::Color::Green);


	this->m_textureLogo.loadFromFile("images/logo.png");
	this->m_textureLogo.setSmooth(true);
	sf::CircleShape logo(35);
	this->m_logo = logo;
	this->m_logo.setTexture(&m_textureLogo);
}

void design::update()
{
	this->m_logo.setPosition(215, 30);
	this->m_text.setPosition(170, 110);

}
void design::draw()
{
	this->m_window->draw(this->m_logo);
	this->m_window->draw(this->m_text);


}

