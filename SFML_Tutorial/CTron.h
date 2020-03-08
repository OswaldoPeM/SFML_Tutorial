#pragma once
#include <SFML/Graphics.hpp>
#include"CNetworkMNG.h"
#include"CPlayerTron.h"
#include"CRenderer.h"
#define TILE_Size 10.f
#define WIDTH 980
#define HEIGHT 1080

class CTron
{
	CPlayerTron localPlayer, remotePlayer;
	sf::Vector2f shapeSize=sf::Vector2f(TILE_Size, TILE_Size);
	sf::Font fuente;
	sf::Text text1, text2;
	int score1 = 0, score2 = 0;
	CNetworkMNG NetworkManager;
	CRenderer *renderer=nullptr;
	Sprite seven, Up;
	Texture tex, tex2;
	bool host;
	bool wall[WIDTH / 10][HEIGHT / 10];

public:
	void run();
	void render();
	void gameLoop();
	void update();
	//Because he gonna build a WALL
	void donalTrump();
	void checkForCrash();
	void reset();
	void setText();

	CTron();
	CTron(int Width, int Hight);
	~CTron();
};

