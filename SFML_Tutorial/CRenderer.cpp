#include "CRenderer.h"





CRenderer::CRenderer()
{
}

CRenderer::CRenderer(int width, int hight):
	window(sf::VideoMode(width, hight), "SFML works!")
{
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	clear();
}

void CRenderer::drawPlayer(std::vector<sf::RectangleShape> wall, sf::RectangleShape forma, sf::Sprite seven)
{
	for (unsigned int i = 0; i < wall.size(); i++)
	{
		window.draw(wall[i]);
	}
	window.draw(forma);
	seven.setPosition(forma.getPosition());

	if (!wall.empty()) {
		if (forma.getPosition().y < wall[wall.size()-1].getPosition().y) {
			seven.setRotation(0);
		}
		else if (forma.getPosition().y > wall[wall.size() - 1].getPosition().y) {
			seven.setRotation(180);
		}
		else if (forma.getPosition().x < wall[wall.size() - 1].getPosition().x) {
			seven.setRotation(270);
		}
		else if (forma.getPosition().x > wall[wall.size() - 1].getPosition().x) {
			seven.setRotation(90);
		}
	}
	window.draw(seven);
}

void CRenderer::drawScore(sf::Text text1, sf::Text text2)
{
	window.draw(text1);
	window.draw(text2);
}

void CRenderer::ToDisplay()
{
	window.display();
}



CRenderer::~CRenderer()
{
}
