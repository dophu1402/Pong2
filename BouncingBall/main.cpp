#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "design.h"
#include "designGame.h"
#include "game.h"
#include "Header.h"
#include <iostream>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	sf::RenderWindow window(sf::VideoMode(500, 600), "Bouncing Ball", sf::Style::Close);
	window.setFramerateLimit(60);
	tgui::Gui gui;
	design des(&window);
	gui.setTarget(window);

	tgui::Button::Ptr newgame = tgui::Button::create("New Game");
	newgame->setSize(200, 50);
	newgame->setPosition(150, 170);

	tgui::Button::Ptr arcade = tgui::Button::create("Arcade Mode");
	arcade->setSize(200, 50);
	arcade->setPosition(150, 240);

	tgui::Button::Ptr quitgame = tgui::Button::create("Quit Game");
	quitgame->setSize(200, 50);
	quitgame->setPosition(150, 310);

	gui.add(newgame);
	gui.add(arcade);
	gui.add(quitgame);

	
	newgame->connect("pressed", [&]() {
		sf::RenderWindow MessWindow(sf::VideoMode(1200, 650), "MessageBox", sf::Style::Close);
		MessWindow.setFramerateLimit(60);
		designGame DG(&MessWindow);
		game Game(&MessWindow);
		while (MessWindow.isOpen())
		{
			sf::Event event;
			while (MessWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					MessWindow.close();

				}
			}

			MessWindow.clear(sf::Color::Transparent);
			DG.update();
			DG.draw();
			if (!Game.update())
				break;
			Game.draw();
			MessWindow.display();

		}

	});

	arcade->connect("pressed", [&]() {
		arcadeMode();
		/*sf::RenderWindow ArcadeWindow(sf::VideoMode(550, 750), "Arcade Mode", sf::Style::Close);
		ArcadeWindow.setFramerateLimit(60);
		Ball ball(10);
		brick a,c,d;
		std::vector<brick> br;
		for (int i = 0; i < 20; i++)
		{
			br.push_back(a);
		}
		c.setPossition({ 10,30 });
		d.setPossition({ 500,30 });
		generateBrick(br);

		while (ArcadeWindow.isOpen())
		{
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
					br[i].setSize({ 0,0 });
				}
			}
			ball.move({ 0, 5 });
			
			ArcadeWindow.clear();
			ball.drawTo(ArcadeWindow);
			for (int i = 0; i < br.size(); i++) {
				br[i].drawTo(ArcadeWindow);
			}

			ArcadeWindow.display();

		}*/
	});
	
	quitgame->connect("pressed", []() {
		exit(0);
	});

	bool checkChooseWindow = true;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::LostFocus)
				checkChooseWindow = false;
			if (event.type == sf::Event::GainedFocus)
				checkChooseWindow = true;
		}

		window.clear(sf::Color::Transparent);
		gui.handleEvent(event);
		des.update();
		des.draw();
		gui.draw();
		window.display();
	
	}

	return EXIT_SUCCESS;
}
