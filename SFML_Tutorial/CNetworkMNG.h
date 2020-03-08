#pragma once
#include <SFML/Network.hpp>
#include <iostream>

class CNetworkMNG
{
public:
	sf::TcpSocket socket;
	sf::Packet packet;
	bool menu();
	bool setHost();
	bool conectTo();
	sf::Vector2f listen();
	void sendPack(sf::Vector2f pos);
	
	CNetworkMNG();
	~CNetworkMNG();
};

