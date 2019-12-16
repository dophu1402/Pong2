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
	tgui::Gui gui, arcadegui;
	design des(&window);
	gui.setTarget(window);

	tgui::Theme black{ "interface/Black.txt" };
	///Thiet ke main menu
	tgui::Button::Ptr newgame = tgui::Button::create("Pong Game");
	newgame->setRenderer(black.getRenderer("Button"));
	newgame->setSize(200, 50);
	newgame->setPosition(150, 170);

	tgui::Button::Ptr arcade = tgui::Button::create("Brick Breaker");
	arcade->setRenderer(black.getRenderer("Button"));
	arcade->setSize(200, 50);
	arcade->setPosition(150, 240);

	tgui::Button::Ptr arcade1 = tgui::Button::create("Speed Mode");
	arcade1->setRenderer(black.getRenderer("Button"));
	arcade1->setSize(200, 50);
	arcade1->setPosition(150, 30);

	tgui::Button::Ptr arcade2 = tgui::Button::create("Level Mode");
	arcade2->setRenderer(black.getRenderer("Button"));
	arcade2->setSize(200, 50);
	arcade2->setPosition(150, 100);

	tgui::Button::Ptr demo = tgui::Button::create("Demo");
	demo->setRenderer(black.getRenderer("Button"));
	demo->setSize(200, 50);
	demo->setPosition(150, 170);

	tgui::Button::Ptr quitgame = tgui::Button::create("Quit Game");
	quitgame->setRenderer(black.getRenderer("Button"));
	quitgame->setSize(200, 50);
	quitgame->setPosition(150, 310);

	auto checkbox = tgui::CheckBox::create();
	checkbox->setRenderer(black.getRenderer("CheckBox"));
	checkbox->setPosition(300, 550);
	checkbox->setText("Background Music");
	checkbox->setSize(25, 25);
	
	////add button vao gui
	gui.add(checkbox);
	gui.add(newgame);
	gui.add(arcade);
	gui.add(quitgame);

	arcadegui.add(arcade1);
	arcadegui.add(arcade2);
	arcadegui.add(demo);

	sf::Music theme;
	if (!theme.openFromFile("audios/maintheme.ogg"))
	{
	}
	sf::Music backGround;
	if (!backGround.openFromFile("audios/ingame.ogg"))
	{
	}
	theme.setLoop(true);
	backGround.setLoop(true);

	bool playMusic = true;
	checkbox->setChecked(true);
	theme.play();

	checkbox->connect("checked", [&]() {
		playMusic = true;
		theme.play();
		});

	checkbox->connect("unchecked", [&]() {
		playMusic = false;
		theme.stop();
		});
	backGround.setVolume(30);

	//////Classic pong game
	newgame->connect("pressed", [&]() {
		theme.pause();
		if (playMusic)
		{
			checkbox->setChecked(true);
			backGround.play();
		}
		else {
			checkbox->setChecked(false);
			backGround.stop();
		}
		window.setVisible(false);
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
		window.setVisible(true);
		//Music
		backGround.stop();
		if (playMusic)
		{
			checkbox->setChecked(true);
			theme.play();
		}
		else {
			checkbox->setChecked(false);
			theme.stop();
		}
		
		});


	//////Arcade window
	arcade->connect("pressed", [&]() {
		/*
		 mode 0: Demo
		 mode 1: tăng ball speed
		 mode 2: level
		*/
		window.setVisible(false);
		int switch_mode;// = 1;

		//subwindow
		sf::RenderWindow Arcade(sf::VideoMode(500, 250), "Arcade", sf::Style::Close);
		Arcade.setFramerateLimit(60);
		arcadegui.setTarget(Arcade);
		arcade1->connect("pressed", [&]() {
			switch_mode = 1;
			Arcade.close();
			});
		arcade2->connect("pressed", [&]() {
			switch_mode = 2;
			Arcade.close();
			});
		demo->connect("pressed", [&]() {
			switch_mode = 0;
			Arcade.close();
			});

		theme.pause();
		if (playMusic)
		{
			checkbox->setChecked(true);
			backGround.play();
		}
		else {
			checkbox->setChecked(false);
			backGround.stop();
		}
		/////select screen
		while (Arcade.isOpen())
		{
			bool check = true;
			sf::Event event;
			while (Arcade.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					Arcade.close();
				if (event.type == sf::Event::LostFocus)
					check = false;
				if (event.type == sf::Event::GainedFocus)
					check = true;
			}

			Arcade.clear(sf::Color::Transparent);
			arcadegui.handleEvent(event);
			arcadegui.draw();
			Arcade.display();

		}
		if (switch_mode == 1 || switch_mode == 2 || switch_mode == 0)
		{
			arcadeMode(switch_mode);
		}
		window.setVisible(true);

		////Music
		backGround.stop();
		if (playMusic)
		{
			checkbox->setChecked(true);
			theme.play();
		}
		else {
			checkbox->setChecked(false);
			theme.stop();
		}

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
