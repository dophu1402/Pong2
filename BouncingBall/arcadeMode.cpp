#include "Header.h"

/////////////////// auto generate
void generateBrick(std::vector<brick> &br)
{
	for (int i = 0; i < br.size(); i++)
	{
		sf::Vector2f vt;
		vt.x = 10 + ((i%9) * 60);
		vt.y = 30 + i/9 * 30;
		br[i].setPossition(vt);
	}
}

void arcadeMode()
{
	sf::RenderWindow ArcadeWindow(sf::VideoMode(550, 750), "Arcade Mode", sf::Style::Close);
	ArcadeWindow.setFramerateLimit(60);
	Ball ball(10);
	//ball.setPosition({ 270, 700 });
	ball.setPosition({ 235, 700 });
	sf::Event event;
	brick a;
	std::vector<brick> br;
	for (int i = 0; i < 50; i++)
	{
		br.push_back(a);
	}
	generateBrick(br);
	brick paddle({ 100, 10 });
	brick left({ 10, 700 }), right({ 10,700 }), top({550,10});
	left.setPossition({ 0, 10 });
	right.setPossition({ 540, 10 });

	paddle.setPossition({ 200, 700 });

	float ballSpeed = 5;

	ball.move({ 0, -ballSpeed });

	while (ArcadeWindow.isOpen())
	{
		float padSpeed = 5;
		float timeElapse = 1;

		static bool goingUp = true;
		static bool goingDown = false;
		static bool goingLeft = false;
		static bool goingRight = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle.getPosition().y > 650) {
			paddle.move({ 0, -padSpeed * timeElapse });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && paddle.getPosition().x < 430) {
			paddle.move({ padSpeed * timeElapse, 0 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddle.getPosition().y < 700) {
			paddle.move({ 0, padSpeed * timeElapse });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && paddle.getPosition().x > 20) {
			paddle.move({ -padSpeed * timeElapse, 0 });
		}

		sf::Event event;
		while (ArcadeWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				ArcadeWindow.close();
			}
		}

		for (int i = 0; i < br.size(); i++)
		{
			if (br[i].isHitBall(ball))
			{

				//system("pause");
				if (br[i].isHitSide(ball, goingUp))
				{
					goingLeft = !goingLeft;
					goingRight = !goingRight;
				}
				else
				{
					goingDown = !goingDown;
					goingUp = !goingUp;
				}

				br[i].setSize({ 0,0 });
				br[i].setPossition({ 0,0 });
		
			}
		}
		////////////
		if (paddle.isHitBall(ball))	{
			goingUp = true;
			goingDown = false;
		}

		if (left.isHitBall(ball)) {
			goingRight = true;
			goingLeft = false;
		}
		if (right.isHitBall(ball)) {
			goingRight = false;
			goingLeft = true;
		}
		if (top.isHitBall(ball)) {
			goingUp = false;
			goingDown = true;
		}
		//////////////
		if (goingDown == true){
			ball.move({ 0, ballSpeed });
		}
		if (goingUp == true)	{
			ball.move({ 0, -ballSpeed });
		}
		if (goingLeft == true)	{
			ball.move({ -ballSpeed, 0 });
		}
		if (goingRight == true){
			ball.move({ ballSpeed, 0 });
		}
		ArcadeWindow.clear();
		ball.drawTo(ArcadeWindow);
		for (int i = 0; i < br.size(); i++) {
			br[i].drawTo(ArcadeWindow);
		}
		left.drawTo(ArcadeWindow);
		right.drawTo(ArcadeWindow);
		paddle.drawTo(ArcadeWindow);
		ArcadeWindow.display();
	}
}