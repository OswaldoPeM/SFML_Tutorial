#include "CNetworkMNG.h"



bool CNetworkMNG::menu()
{
	std::string input;
	bool done = false;
	while (!done) {
		std::cout << "Introdusca '1' para ser Host, introdusca '2' para conectarte a un host." << std::endl;
		getline(std::cin, input, '\n');
		switch (input[0])
		{
		case'1':
			if (!setHost()) {
				std::cout << "\nNo se ha enlazado correctamente\n";
			}
			else {
				done = true;	
				std::cout << "\nSe ha enlazado correctamente\n";
				return true;
				break;
			}
		case'2':
			if (!conectTo()) {
				std::cout << "\nNo se ha enlazado correctamente\n";
			}
			else {
				done = true;
				std::cout << "\nSe ha enlazado correctamente\n";
				return false;
			}
			break;
		default:
			break;
		}
	}
	return false;
}

bool CNetworkMNG::setHost()
{
	sf::TcpListener listener;
	listener.listen(54000);
	std::cout << "Esperando una coneccion..." << std::endl;
	if (listener.accept(socket) != sf::Socket::Done) return false;
	return true;
}

bool CNetworkMNG::conectTo()
{
	std::string input;
	bool done = false;
	while (!done)
	{
		std::cout << "\nIngresa direccion a la que te quieres conectar: ";
		std::getline(std::cin, input, '\n');

		std::cout << "Trying to connect..." << std::endl;
		if (!socket.connect(input, 54000, sf::seconds(10)) != sf::Socket::Done)
		{
			system("cls");
			return true;
		}
		system("cls");
		std::cout << "\nNo es posible estalecer comunicacion a la direccion, Si quieres reintentar presione 'r', si quieres abandonar presione 'x'\n";
		std::getline(std::cin, input, '\n');
		switch (input[0])
		{
		case'r':
		case'R':
			system("cls");
			break;
		case'x':
		case'X':
			return false;
		default:
			break;
		}
	}
	return false;
}

sf::Vector2f CNetworkMNG::listen()
{
	sf::Packet paquete;
	sf::Vector2f pos;
	if (socket.receive(paquete) == sf::Socket::Done)
	{
		paquete >> pos.x >> pos.y;
		return pos;
	}
	pos.x = -1;
	return pos;
}

void CNetworkMNG::sendPack(sf::Vector2f pos)
{
	sf::Packet packet;
	packet << pos.x << pos.y;
	if (socket.send(packet) != sf::Socket::Done){}

}

CNetworkMNG::CNetworkMNG()
{
}


CNetworkMNG::~CNetworkMNG()
{
}
