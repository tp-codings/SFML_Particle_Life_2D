#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class Particles
{
public:
	Particles(float x, float y, Color col);
	virtual ~ Particles();

	const Vector2f getPos() const;
	void setPos(Vector2f pos);
	const Vector2f getVel() const;
	void setVel(Vector2f vel);

	void update();
	void render(RenderTarget* target);
	float vx;
	float vy;
	float posX;
	float posY;

private:
	
	Color color;
	CircleShape shape;

	void initVariables(float x, float y, Color col);
	void initShape();
};

