#include "player.h"



player::player(sf::RenderWindow *window, int a, int b)
{
	this->m_window = window;

	sf::RectangleShape bat(sf::Vector2f(100, 10));
	this->m_bat = bat;
	this->m_bat.setFillColor(sf::Color::Cyan);
	this->m_bat.setOrigin(this->m_bat.getSize().x / 2, this->m_bat.getSize().y / 2);
	this->m_bat.setRotation(90);
	this->m_bat.setPosition(a, b);

	this->countHeart = 5;
	this->m_textureHeart.loadFromFile("images/heart.png");
	this->m_textureHeart.setSmooth(true);
	this->m_spriteHeart.setTexture(this->m_textureHeart);

	this->m_texture.loadFromFile("images/man.png");
	this->m_texture.setSmooth(true);
	sf::CircleShape sh(25);
	this->people = sh;
	this->people.setTexture(&this->m_texture);


	this->m_font.loadFromFile("fonts/MarkerFelt.ttf");
	this->m_text.setFont(this->m_font);
	this->m_text.setCharacterSize(18);
	this->m_text.setFillColor(sf::Color::White);


}


void player::update(int a, int b)
{
	sf::Vector2f bat_postition = this->m_bat.getPosition();
	if (a == 1 && b == 2) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			bat_postition.y -= 10;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			bat_postition.y += 10;
		if (bat_postition.y <= 75)
			bat_postition.y = 75;
		if (bat_postition.y >= 475)
			bat_postition.y = 475;
		this->m_bat.setPosition(bat_postition.x, bat_postition.y);
		this->people.setPosition(180, 550);
		this->m_text.setString("Player I");
		this->m_text.setPosition(250, 550);
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			bat_postition.y -= 10;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			bat_postition.y += 10;
		if (bat_postition.y <= 75)
			bat_postition.y = 75;
		if (bat_postition.y >= 475)
			bat_postition.y = 475;
		this->m_bat.setPosition(bat_postition.x, bat_postition.y);
		this->people.setPosition(970, 550);
		this->m_text.setString("Player II");
		this->m_text.setPosition(900, 550);
	}
}
void player::draw(int a, int b)
{
	this->m_window->draw(this->people);
	this->m_window->draw(this->m_text);
	if (a == 1 && b == 2) {
		for (int i = 0; i < this->countHeart; i++)
		{
			this->m_spriteHeart.setPosition(250 + i * 15, 580);
			this->m_window->draw(this->m_spriteHeart);
		}
	}
	else {
		for (int i = 0; i < this->countHeart; i++)
		{
			this->m_spriteHeart.setPosition(950 - i * 15, 580);
			this->m_window->draw(this->m_spriteHeart);
		}
	}
	this->m_window->draw(this->m_bat);
}
sf::Vector2f player::getPosition()
{
	return this->m_bat.getPosition();
}
int& player::getCountHeart()
{
	return this->countHeart;
}