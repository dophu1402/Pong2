#include "game.h"

game::game(sf::RenderWindow* window)
{
	this->m_window = window;
	this->m_player1 = new player(this->m_window, 60, 350);
	this->m_player2 = new player(this->m_window, 1140, 350);
	this->m_ball = new Ball(this->m_window);
	sf::Vector2f pos;
	srand(time(NULL));
	pos.x = (rand() % 1000) + 100;
	pos.y = (rand() % 390) + 80;
	obstacle.setPossition(pos);
}

bool game::update()
{

	static bool player1 = false;
	static bool player2 = false;
	this->obstacle.setSize({ 30,50 });


	static sf::Vector2f pos;


	if (m_ball->getPosition().y + m_ball->getRadius() > obstacle.getPosition().y&& m_ball->getPosition().y - m_ball->getRadius() < obstacle.getPosition().y + obstacle.getSize().y) {
		if (m_ball->getPosition().x + m_ball->getRadius() > obstacle.getPosition().x&& m_ball->getPosition().x - m_ball->getRadius() < obstacle.getPosition().x + obstacle.getSize().x) {
			pos.x = rand() % 1000 + 100;
			pos.y = rand() % 390 + 80;
			obstacle.setPossition(pos);
			if (player1 == true)
			{
				this->m_player1->getCountHeart()--;
			}
			if (player2 == true)
			{
				this->m_player2->getCountHeart()--;
			}
		}
	}
	if (obstacle.isHitBall(*m_ball))
	{

	}

	this->m_player1->update(1, 2);
	this->m_player2->update(3, 4);
	this->m_ball->update(50, 1150);

	int x1 = std::abs(this->m_ball->getPosition().x - this->m_player1->getPosition().x);
	int x2 = std::abs(this->m_ball->getPosition().x - this->m_player2->getPosition().x);
	int y1 = std::abs(this->m_ball->getPosition().y - this->m_player1->getPosition().y);
	int y2 = std::abs(this->m_ball->getPosition().y - this->m_player2->getPosition().y);

	if (y1 <= 65 && x1 <= 20)
	{
		player1 = true;
		player2 = false;
		this->m_ball->update(70, 1150);
	}

	if (y2 <= 65 && x2 <= 20)
	{
		player2 = true;
		player1 = false;
		this->m_ball->update(50, 1130);
	}

	int a = this->m_ball->getPosition().x - this->m_ball->getRadius();
	int b = this->m_ball->getPosition().x + this->m_ball->getRadius();
	sf::Event event;
	if (a <= 50) {
		this->m_player1->getCountHeart()--;
		m_window->waitEvent(event);
		this->m_ball->update(600, 275);
		this->m_ball->resetSpeed();
		player1 = false;
		player2 = false;

	}
	if (b >= 1150) {
		this->m_player2->getCountHeart()--;
		m_window->waitEvent(event);
		this->m_ball->update(600, 275);
		this->m_ball->resetSpeed();
		player1 = false;
		player2 = false;
	}
	if (this->m_player2->getCountHeart() >= 0 && this->m_player1->getCountHeart() >= 0)
		return true;
	else {
		if (this->m_player2->getCountHeart() < 0) {
			if (MessageBox(NULL, L"PlayerI Win!", L"Game Over", MB_OK) == IDOK)
				return false;
		}
		if (this->m_player1->getCountHeart() < 0) {
			if (MessageBox(NULL, L"PlayerII Win!", L"Game Over", MB_OK) == IDOK)
				return false;
		}
	}
}
void game::draw()
{
	this->m_player1->draw(1, 2);
	this->m_player2->draw(3, 4);
	this->m_ball->draw();
	this->obstacle.draw(*this->m_window);
}
