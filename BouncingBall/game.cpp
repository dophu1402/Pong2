#include "game.h"

game::game(sf::RenderWindow *window)
{
	this->m_window = window;
	this->m_player1 = new player(this->m_window, 60, 350);
	this->m_player2 = new player(this->m_window, 1140, 350);
	this->m_ball = new ball(this->m_window);
}

bool game::update()
{
	this->m_player1->update(1, 2);
	this->m_player2->update(3, 4);
	this->m_ball->update(50, 1150);

	int x1 = std::abs(this->m_ball->getPosition().x - this->m_player1->getPosition().x);
	int x2 = std::abs(this->m_ball->getPosition().x - this->m_player2->getPosition().x);
	int y1 = std::abs(this->m_ball->getPosition().y - this->m_player1->getPosition().y);
	int y2 = std::abs(this->m_ball->getPosition().y - this->m_player2->getPosition().y);

	if (y1 <= 65 && x1 <= 20)
		this->m_ball->update(70,1150);
	if (y2 <= 65 && x2 <= 20)
		this->m_ball->update(50,1130);
	int a = this->m_ball->getPosition().x - this->m_ball->getRadius();
	int b = this->m_ball->getPosition().x + this->m_ball->getRadius();
	if (a == 50) {
		this->m_player1->getCountHeart()--;
	}
	if (b >= 1150) {
		this->m_player2->getCountHeart()--;
	}
	if (this->m_player2->getCountHeart() >= 0 && this->m_player1->getCountHeart() >= 0)
		return true;
	else {
		if (this->m_player2->getCountHeart() < 0) {
			if (MessageBox(NULL, "PlayerI Win!", "Game Over", MB_OK) == IDOK)
				return false;
		}
		if (this->m_player1->getCountHeart() < 0) {
			if (MessageBox(NULL, "PlayerII Win!", "Game Over", MB_OK) == IDOK)
				return false;
		}
	}
}
void game::draw()
{
	this->m_player1->draw(1, 2);
	this->m_player2->draw(3, 4);
	this->m_ball->draw();
}
