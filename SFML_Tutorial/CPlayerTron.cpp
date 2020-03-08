#include "CPlayerTron.h"



CPlayerTron::~CPlayerTron()
{

}

CPlayerTron::CPlayerTron()
{
}

CPlayerTron::CPlayerTron(Vector2f shapeSize) :
	forma(shapeSize)
{
	
}

CPlayerTron::CPlayerTron(float X, float Y, int direccion, Color color)
{

	forma.setPosition(X*10, Y*10);
	forma.setFillColor(color);
	m_direccion = direccion;
}

void CPlayerTron::createPlayer(int X, int Y, int direccion, Color color)
{
	posicion.x = X;
	posicion.y = Y;

	forma.setPosition(X, Y);
	forma.setFillColor(color);

	m_direccion = direccion;
}

void CPlayerTron::createRemote(Color color)
{
	m_color = color;
	forma.setFillColor(m_color);
}

int CPlayerTron::getDireccion()
{
	return m_direccion;
}

Vector2f CPlayerTron::getPos()
{
	return posicion;
}

RectangleShape CPlayerTron::getForma()
{
	return forma;
}

Color CPlayerTron::getColor()
{
	return m_color;
}


std::vector<RectangleShape> CPlayerTron::getWall()
{
	return wall;
}

bool CPlayerTron::getCrash()
{
	return isCrashed;
}

void CPlayerTron::setTEX(bool host)
{
	 Texture tex;
	if (host) {
		if (!tex.loadFromFile("rj45.png"))
		{
			// Si hay un error salimos
			return;
		}
	}
	else {
		if (!tex.loadFromFile("rj45_red.png"))
		{
			// Si hay ->n error salimos
			return;
		}
	}
	return;
}

void CPlayerTron::crash()
{
	isCrashed = true;
}

void CPlayerTron::setPos(Vector2f pos)
{ 
	if (pos.x > 0) {
		if (!wall.empty())
		{
			if (pos == wall[wall.size() - 1].getPosition()) {
				return;
			}
		}
		wall.push_back(forma);
		posicion.x = pos.x;
		posicion.y = pos.y;
		forma.setPosition(pos);

	}
}

void CPlayerTron::direccionar(int i)
{
	// left =0, right=1, up = 2, down 3

	if (m_direccion = 0 && 1 != i) {
		m_direccion = i;
	}
	else if (m_direccion = 1 && 0 != i) {
		m_direccion = i;
	}
	else if (m_direccion = 2 && 3 != i) {
		m_direccion = i;
	}
	else if (m_direccion = 3 && 2 != i) {
		m_direccion = i;
	}
	
}

void CPlayerTron::mover()
{
	wall.push_back(forma);
	switch (m_direccion)
	{
		case 0:
			posicion.x -= 10*SPEED;
			break;
		case 1:
			posicion.x += 10*SPEED;
			break;
		case 2:
			posicion.y -= 10*SPEED;
			break;
		case 3:
			posicion.y += 10*SPEED;
			break;
	default:
		break;
	}
	forma.setPosition(posicion.x, posicion.y);
}

void CPlayerTron::reset()
{	
	if (!wall.empty()) {
		forma = wall[0];
	}
	posicion = forma.getPosition();
	wall.clear();
	isCrashed = false;

}

void CPlayerTron::update(bool local)
{
	if (!isCrashed) {
		mover();
	}

}
