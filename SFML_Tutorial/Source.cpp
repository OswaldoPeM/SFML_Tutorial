//#include<SFML/Graphics.hpp>
//#include<iostream>
//#define SCREEN_WIDTH 1920
//#define SCREEN_HIGHT 1080
//
//int main() {
//	sf::RenderWindow window(sf::VideoMode( SCREEN_WIDTH,SCREEN_HIGHT), "SFML works!");
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Yellow);
//
//	sf::Vector2f shapePos=shape.getPosition();
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		shapePos.x++;
//		if (shapePos.x > SCREEN_WIDTH) {
//			shapePos.x = 1;
//			shapePos.y = shapePos.y + 10;
//		}
//		std::cout << shapePos.x<<std::endl;
//		shape.setPosition(shapePos);
//		window.clear();
//		window.draw(shape);
//		window.display();
//	}
//
//
//	return 0;
//}

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include"CTron.h"

int main() {
	CTron *tron;
	tron = new CTron(WIDTH, HEIGHT);
	tron->run();
	delete tron;
	return 0;
}

/*
int main()
{
	sf::TcpSocket socket;
	std::string consoleInput;
	std::cin >> consoleInput;
	if (consoleInput == "host")
	{
		sf::TcpListener listener;
		listener.listen(54000);
		std::cout << "Waiting for conneciont" << std::endl;
		if (listener.accept(socket) != sf::Socket::Done)
			return -1;
	}
	else
	{
		std::cout << "Trying to connect..." << std::endl;
		if (socket.connect(consoleInput, 54000, sf::seconds(10)) != sf::Socket::Done)
		{
			return -1;
		}
	}

	sf::RenderWindow window(sf::VideoMode(WIDTH, HIGHT), "NetWorking");
	socket.setBlocking(false);
	sf::Vector2f shapeSize(TILE_Size, TILE_Size);
	sf::RectangleShape localShape(shapeSize);
	sf::RectangleShape remoteShape(shapeSize);

	while (window.isOpen())
	{
		sf::Vector2i moveDir;
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::W)
					moveDir.y += -1;
				else if (event.key.code == sf::Keyboard::A)
					moveDir.x += -1;
				else if (event.key.code == sf::Keyboard::S)
					moveDir.y += 1;
				else if (event.key.code == sf::Keyboard::D)
					moveDir.x += 1;
				break;
			case sf::Event::Closed:
				window.close();
			default:
				break;
			}
		}

		//Check for new packets
		sf::Packet packet;
		if (socket.receive(packet) == sf::Socket::Done)
		{
			sf::Vector2f pos;
			packet >> pos.x >> pos.y;
			remoteShape.setPosition(pos);
		}

		//Update frame
		if (moveDir.x != 0 || moveDir.y != 0)
		{
			localShape.move(moveDir.x * TILE_Size, moveDir.y * TILE_Size);
			sf::Packet packet;
			packet << localShape.getPosition().x << localShape.getPosition().y;
			if (socket.send(packet) != sf::Socket::Done)
			{
				return -1;
			}
		}

		window.clear();
		window.draw(localShape);
		window.draw(remoteShape);
		window.display();
	}
}
*/
