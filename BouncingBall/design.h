#pragma once
#ifndef _design_h_
#define _design_h_
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <Windows.h>e
#include <iostream>
class design
{
private:
	sf::RenderWindow *m_window;
	//tgui::Gui *m_gui;
	sf::Font m_font;
	sf::Text m_text;
	sf::Texture m_textureLogo;
	sf::CircleShape m_logo;
	
	

public:
	design(sf::RenderWindow *window);
	void update();
	void draw();
};
#endif
