#include "Barrier.h"

Barrier::Barrier()
{
	left.setSize({ BARRIER_WIDTH,WINDOW_HEIGHT - 160 });
	left.setPossition({ 60, 140 });

	right.setSize({ BARRIER_WIDTH,WINDOW_HEIGHT - 160 });
	right.setPossition({ WINDOW_WIDTH - 60, 140 });

	top.setSize({ WINDOW_WIDTH - 110,BARRIER_WIDTH });
	top.setPossition({ 60, 130 });

	bottom.setSize({ WINDOW_WIDTH - 110,BARRIER_WIDTH });
	bottom.setPossition({ 60, WINDOW_HEIGHT - 20 });
	//bottom.setColor(sf::Color::Black);
}

bool Barrier::isHitBall(Ball ball, bool& goingUp, bool& goingDown, bool& goingLeft, bool& goingRight)
{
	sf::SoundBuffer buffer_paddle;
	if (!buffer_paddle.loadFromFile("audios/click.wav"))
	{
	}
	sf::Sound sound_paddle;
	sound_paddle.setBuffer(buffer_paddle);
	if (left.isHitBall(ball)) {
		goingRight = true;
		goingLeft = false;
		sound_paddle.play();
		return true;
	}
	if (right.isHitBall(ball)) {
		goingRight = false;
		goingLeft = true;
		sound_paddle.play();
		return true;
	}
	if (top.isHitBall(ball)) {
		goingUp = false;
		goingDown = true;
		sound_paddle.play();
		return true;
	}
	if (bottom.isHitBall(ball))
	{
		return false;
	}
	return true;
}

void Barrier::drawTo(sf::RenderWindow& window)
{
	left.drawTo(window);
	right.drawTo(window);
	top.drawTo(window);
	bottom.drawTo(window);
}

void Barrier::setTexture(vector<sf::Texture> T)
{
	m_Texture = T;

	left.setTexture(m_Texture[0]);
	right.setTexture(m_Texture[0]);
	top.setTexture(m_Texture[1]);
	bottom.setTexture(m_Texture[1]);
}