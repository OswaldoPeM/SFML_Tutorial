#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

class CRenderer
{
public:
	sf::RenderWindow window;
	CRenderer();
	CRenderer(int width, int hight);
	void clear() { window.clear(); }
	void drawPlayer(std::vector<sf::RectangleShape> wall, sf::RectangleShape forma,sf::Sprite seven);
	void drawScore(sf::Text text1, sf::Text text2);
	void ToDisplay();
	~CRenderer();
};

