#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

const unsigned int WINDOW_WIDTH = 1200;

const unsigned int WINDOW_HEIGHT = 900;

const float PADDLE_WIDTH = 150;

const float PADDLE_HEIGHT = 15;

const float BARRIER_WIDTH = 10;                  

const float DEFAULT_PADDLE_SPEED = 8;

const float DEFAULT_BALL_SPEED = 5;

const float BALL_SPEED_MAX = 10;

const float BRICK_HEIGHT = 35;

const float BRICK_WIDTH = 78;

const sf::Vector2f DEFAULT_BALL_POSITION = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 70);

const sf::Vector2f DEFAULT_PADDLE_POSITION = sf::Vector2f(WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2 + 15, WINDOW_HEIGHT - 45);

/*
	p tăng 50% số điểm nhận được
	m trừ 50% số điểm nhận được
	l paddle dài 
	i paddle ngắn
	a tốc độ paddle tăng
	b tốc độ paddle giảm
	s biên dưới an toàn
	o vật cản
*/
const char SPECIALS[] = { 'p', 'm', 'l', 'i', 'a', 'b', 's', 'o' };

const sf::Color DEFAULT_COLOR = sf::Color(51, 51, 51); 

const sf::Color PADDLE_COLOR = sf::Color(221, 221, 221);

const sf::Color BACKGROUND_COLOR = sf::Color(245, 245, 245);

const sf::Color BALL_COLOR = sf::Color(122, 122, 122);

const sf::Color BRICK_COLOR = sf::Color(25, 130, 196);

const sf::Color LOSE_COLOR = sf::Color(255, 0, 0);     

const sf::Color WIN_COLOR = sf::Color(138, 201, 38);    

const sf::Color HIGHSCORE_COLOR = sf::Color(255, 0, 0);

const sf::Color RANK1_COLOR = sf::Color(255, 240, 100);

const sf::Color RANK2_COLOR = sf::Color(250, 255, 250);

const sf::Color RANK3_COLOR = sf::Color(225, 160, 90);

const sf::Color OTHER_RANK_COLOR = sf::Color(190, 190, 190);

const sf::Color SCORE_COLOR = sf::Color(210, 210, 210);

const sf::Color GOOD_EFFECT_COLOR = sf::Color(138, 201, 38);

const sf::Color BAD_EFFECT_COLOR = sf::Color(255, 0, 0);

const sf::Color SAFE_BARRIER_COLOR = sf::Color(255, 240, 100);
