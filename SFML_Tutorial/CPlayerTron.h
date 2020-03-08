#pragma once
#include<SFML/Graphics.hpp>
#include<bitset>
#define SPEED 1.0f

using namespace sf;

class CPlayerTron
{
	int m_direccion;
	float velocidad;
	Vector2f posicion;
	RectangleShape forma;
	Color m_color;
	std::vector<RectangleShape> wall;
	bool isCrashed = false;
	
	

public:
	CPlayerTron();
	CPlayerTron(Vector2f shapeSize);
	CPlayerTron(float X,float Y,int direccion,Color color);

	void createPlayer(int X, int Y, int direccion, Color color);
	void createRemote(Color color);


	int getDireccion();
	Vector2f getPos();
	RectangleShape getForma();
	Color getColor();
	std::vector<RectangleShape> getWall();
	bool getCrash();

	void setTEX(bool host);
	void crash();
	void setPos(Vector2f pos);
	void direccionar(int i);
	void mover();
	void reset();
	
	void update(bool local);

	~CPlayerTron();
};

