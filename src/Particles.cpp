#include "Particles.h"

Particles::Particles(float x, float y, Color col)
{
	this->initVariables(x, y, col);
	this->initShape();
}

Particles::~Particles()
{
}

const Vector2f Particles::getPos() const
{
	return Vector2f(this->posX, this->posY);
}

void Particles::setPos(Vector2f pos)
{
	this->posX = pos.x;
	this->posY = pos.y;
}

const Vector2f Particles::getVel() const
{
	return Vector2f(this->vx, this->vy);
}

void Particles::setVel(Vector2f vel)
{
	this->vx = vel.x;
	this->vy = vel.y;
}

void Particles::update()
{
	this->shape.setPosition(Vector2f(this->posX, this->posY));
}

void Particles::render(RenderTarget* target)
{
	target->draw(this->shape);
}

void Particles::initVariables(float x, float y, Color col)
{
	this->posX = x;
	this->posY = y;
	this->color = col;
	this->vx = 0;
	this->vy = 0;
}

void Particles::initShape()
{
	this->shape.setFillColor(this->color);
	this->shape.setRadius(3.f);
	this->shape.setPosition(Vector2f(this->posX, this->posY));
}
