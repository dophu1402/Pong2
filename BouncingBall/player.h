#pragma once
#ifndef _palyer_h_
#define _player_h_
#include <SFML/Graphics.hpp>
#include <Windows.h>

class player
{
private:
	sf::RenderWindow *m_window;
	sf::RectangleShape m_bat;

	sf::Font m_font;
	sf::Text m_text;

	sf::Texture m_textureHeart;
	sf::Sprite m_spriteHeart;
	int countHeart;

	sf::Texture m_texture;
	sf::CircleShape people;

public:
	player(sf::RenderWindow *window, int, int);
	void update(int, int);
	void draw(int, int);
	sf::Vector2f getPosition();
	int& getCountHeart();
};

#endif
