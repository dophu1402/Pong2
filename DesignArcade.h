#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

const unsigned int WINDOW_WIDTH = 1300;

const unsigned int WINDOW_HEIGHT = 800;

const float PADDLE_WIDTH = 100;

const float PADDLE_HEIGHT = 13;

const float BARRIER_WIDTH = 5;                  

const float BARRIER_BUFFER = 5;                 

const float BANNER_HEIGHT = 30;

const float BRICK_HEIGHT = 10;

const char SPECIALS[] = { 'b', 'l' };

const sf::Color DEFAULT_COLOR = sf::Color(51, 51, 51);            

const sf::Color BACKGROUND_COLOR = sf::Color(245, 245, 245);

const sf::Color BALL_COLOR = sf::Color(122, 122, 122);

const sf::Color BRICK_COLOR = sf::Color(25, 130, 196);

const sf::Color LOSE_COLOR = sf::Color(255, 0, 0);                ///< Text color for failure messages

const sf::Color WIN_COLOR = sf::Color(138, 201, 38);              ///< Text color for failure messages




