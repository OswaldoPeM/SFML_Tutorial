#include "CTron.h"


void CTron::run()
{


	reset();

	host = NetworkManager.menu();
	int midWidth = WIDTH / 2, midHight = HEIGHT/2;
	setText();
	if (host) {
		localPlayer.createPlayer(midWidth, midHight + midHight / 2, 2, sf::Color::Blue);
		remotePlayer.createRemote(sf::Color::Red);
	}
	else {
		localPlayer.createPlayer(midWidth, midHight-midHight/2, 3, sf::Color::Blue);
		remotePlayer.createRemote(sf::Color::Red);
		
	}

	renderer = new CRenderer(WIDTH, HEIGHT);

	if (!fuente.loadFromFile("arial.ttf"))
	{
		printf("Error: Loading a font\n");
	}

	text1.setFont(fuente);
	text2.setFont(fuente);

	text1.setString(std::to_string(score1));
	text2.setString(std::to_string(score2));

	text1.setCharacterSize(50);
	text2.setCharacterSize(50);

	text1.setFillColor(sf::Color::Blue);
	text2.setFillColor(remotePlayer.getColor());

	sf::FloatRect textBox1 = text1.getLocalBounds();
	sf::FloatRect textBox2 = text2.getLocalBounds();

	text1.setOrigin(textBox1.left + textBox1.width / 2, textBox1.top + textBox1.height / 2);
	text2.setOrigin(textBox2.left + textBox2.width / 2, textBox2.top + textBox2.height / 2);

	text1.setPosition(sf::Vector2f(WIDTH / 10, HEIGHT / 20));
	text2.setPosition(sf::Vector2f((WIDTH * 9) / 10, HEIGHT / 20));





	NetworkManager.socket.setBlocking(false);
	NetworkManager.sendPack(localPlayer.getPos());
	remotePlayer.setPos(NetworkManager.listen());

	gameLoop();
}

void CTron::render()
{
	renderer->clear();
	renderer->drawPlayer(localPlayer.getWall(), localPlayer.getForma(),seven);
	renderer->drawPlayer(remotePlayer.getWall(), remotePlayer.getForma(),Up);
	renderer->drawScore(text1, text2);
	renderer->ToDisplay();
}

void CTron::gameLoop()
{
	while (renderer->window.isOpen())
	{
		sf::Vector2i moveDir;
		sf::Event event;
		while (renderer->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::W) {
					localPlayer.direccionar(2);
					seven.setRotation(0);
				}
				else if (event.key.code == sf::Keyboard::A) {
					localPlayer.direccionar(0);
					seven.setRotation(270);
				}

				else if (event.key.code == sf::Keyboard::S) {
					localPlayer.direccionar(3);
					seven.setRotation(180);

				}
				else if (event.key.code == sf::Keyboard::D) {
					seven.setRotation(90);
					localPlayer.direccionar(1);
				}
				else if (event.key.code == sf::Keyboard::Escape)
					renderer->window.close();
				else if (event.key.code == sf::Keyboard::Up)
					moveDir.y += -1;
				else if (event.key.code == sf::Keyboard::Left)
					moveDir.x += -1;
				else if (event.key.code == sf::Keyboard::Down)
					moveDir.y += 1;
				else if (event.key.code == sf::Keyboard::Right)
					moveDir.x += 1;
				break;
			case sf::Event::Closed:
				renderer->window.close();
			default:
				break;
			}
		}
		if (moveDir.x != 0 || moveDir.y != 0)
		{
			localPlayer.getForma().move(moveDir.x * TILE_Size, moveDir.y * TILE_Size);
			localPlayer.setPos(Vector2f(localPlayer.getPos().x + (moveDir.x*TILE_Size), localPlayer.getPos().y + (moveDir.y*TILE_Size)));
		}

		remotePlayer.setPos(NetworkManager.listen());
		localPlayer.update(true);

		NetworkManager.sendPack(localPlayer.getPos());

		checkForCrash();
		donalTrump();

		render();
	}
}

void CTron::update()
{
	localPlayer.update(host);
	
}

void CTron::donalTrump()
{
	if (!localPlayer.getCrash()) {
		wall[(int)(localPlayer.getPos().x) / 10][(int)(localPlayer.getPos().y) / 10] = true;
		wall[(int)(remotePlayer.getPos().x) / 10][(int)(remotePlayer.getPos().y) / 10] = true;
	}
}

void CTron::checkForCrash()
{
	if (localPlayer.getPos().x > WIDTH || localPlayer.getPos().y > HEIGHT) {
		localPlayer.crash();
	}
	if (localPlayer.getPos().x < 0 || localPlayer.getPos().y < 0) {
		localPlayer.crash();
	}
	if (wall[(int)(localPlayer.getPos().x) / 10][(int)(localPlayer.getPos().y) / 10]) {
		localPlayer.crash();
	}
	if (localPlayer.getCrash()) {
		score1++;
		reset();
	}
	if (remotePlayer.getPos().x > WIDTH || remotePlayer.getPos().y > HEIGHT) {
		remotePlayer.crash();
	}
	if (remotePlayer.getPos().x < 0 || remotePlayer.getPos().y < 0) {
		remotePlayer.crash();
	}
	if (wall[(int)(remotePlayer.getPos().x) / 10][(int)(remotePlayer.getPos().y) / 10]) {
		remotePlayer.crash();
	}
	if (remotePlayer.getCrash()) {
		score2++;
		reset();
	}
}

void CTron::reset()
{

	int Width = WIDTH / 10;
	int Hight = HEIGHT / 10;
	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Hight; j++)
		{
			wall[i][j] = false;
		}
	}
	localPlayer.reset();
	remotePlayer.reset();
	text1.setString(std::to_string(score1));
	text2.setString(std::to_string(score2));
}

void CTron::setText()
{
	if (!tex.loadFromFile("rj45.png"))
	{
		// Si hay un error salimos
		return;
	}

	seven.setTexture(tex);

	// Cambiamos el origen al centro del sprite
	sf::Vector2f tamanio;
	tamanio.x = seven.getTextureRect().width;
	tamanio.y = seven.getTextureRect().height;
	seven.setTextureRect(sf::IntRect(0, 0, tamanio.x, tamanio.y));
	seven.setScale(0.2, 0.2);

	sf::Vector2f centro;
	centro.x = seven.getTextureRect().width / 2.f;
	centro.y = seven.getTextureRect().height / 2.f;
	seven.setOrigin(centro);
	

	if (!tex2.loadFromFile("rj45_red.png"))
	{
		// Si hay ->n error salimos
		return;
	}
	Up.setTexture(tex2);
	tamanio.x = Up.getTextureRect().width;
	tamanio.y = Up.getTextureRect().height;
	Up.setTextureRect(sf::IntRect(0, 0, tamanio.x, tamanio.y));
	Up.setScale(0.2, 0.2);

	centro.x = Up.getTextureRect().width / 2.f;
	centro.y = Up.getTextureRect().height / 2.f;
	Up.setOrigin(centro);
	return;
}

CTron::CTron()
{
}

CTron::CTron(int Width, int Hight):
	localPlayer(sf::Vector2f(TILE_Size,TILE_Size)),
	remotePlayer(sf::Vector2f(TILE_Size,TILE_Size))
{
	
}


CTron::~CTron()
{
	if (renderer != nullptr) {
		delete renderer;
	}
}
