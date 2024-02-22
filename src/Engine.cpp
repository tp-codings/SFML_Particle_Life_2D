#include "Engine.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <vector>

Engine::Engine()
{
	this->initWindow();
	this->initGUI();
	this->initVariables();
	this->initSlider();
	this->yellow = this->create(this->amount, Color::Yellow);
	this->red = this->create(this->amount, Color::Red);
	this->green = this->create(this->amount, Color::Green);
	this->blue = this->create(this->amount, Color::Blue);
	this->white = this->create(this->amount, Color::White);
}

Engine::~Engine()
{
	delete this->window;
}

void Engine::run()
{
	while (this->running())
	{
		this->update();
		this->render();
	}
}

const bool Engine::running()
{
	return this->window->isOpen();
}

void Engine::update()
{
	this->updateGUI();
	this->updateMousePosition();
	this->updateInput();
	this->pollEvent();
	this->updateParticles();
	this->updateSlider();
	this->interaction(this->green, this->green, this->slider[5]->getValue() / 100);
	this->interaction(this->green, this->red, this->slider[8]->getValue() / 100);
	this->interaction(this->green, this->yellow, this->slider[7]->getValue() / 100);
	this->interaction(this->green, this->blue, this->slider[6]->getValue() / 100);
	this->interaction(this->green, this->white, this->slider[9]->getValue() / 100);

	this->interaction(this->red, this->red, this->slider[0]->getValue()/100);
	this->interaction(this->red, this->green, this->slider[3]->getValue() / 100);
	this->interaction(this->red, this->yellow, this->slider[2]->getValue() / 100);
	this->interaction(this->red, this->blue, this->slider[1]->getValue() / 100);
	this->interaction(this->red, this->white, this->slider[4]->getValue() / 100);

	this->interaction(this->yellow, this->yellow, this->slider[10]->getValue() / 100);
	this->interaction(this->yellow, this->green, this->slider[12]->getValue() / 100);
	this->interaction(this->yellow, this->red, this->slider[13]->getValue() / 100);
	this->interaction(this->yellow, this->blue, this->slider[11]->getValue() / 100);
	this->interaction(this->yellow, this->white, this->slider[14]->getValue() / 100);

	this->interaction(this->blue, this->blue, this->slider[15]->getValue() / 100);
	this->interaction(this->blue, this->red, this->slider[18]->getValue() / 100);
	this->interaction(this->blue, this->yellow, this->slider[17]->getValue() / 100);
	this->interaction(this->blue, this->green, this->slider[16]->getValue() / 100);
	this->interaction(this->blue, this->white, this->slider[19]->getValue() / 100);

	this->interaction(this->white, this->white, this->slider[20]->getValue() / 100);
	this->interaction(this->white, this->red, this->slider[23]->getValue() / 100);
	this->interaction(this->white, this->green, this->slider[24]->getValue() / 100);
	this->interaction(this->white, this->blue, this->slider[21]->getValue() / 100);
	this->interaction(this->white, this->yellow, this->slider[22]->getValue() / 100);

}

void Engine::updateGUI()
{
	std::stringstream ss;
	ss << "LIFESIMULATOR :)";
	this->GUI.setString(ss.str());
	this->GUI.setPosition(0.5 * this->window->getSize().x - 0.5 * this->GUI.getGlobalBounds().width, 0.24 * this->window->getSize().y);
}

void Engine::updateMousePosition()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Engine::updateInput()
{
	this->velocity = this->slider[25]->getValue()/100;
	this->distanceMax = this->slider[26]->getValue();
}

void Engine::updateParticles()
{
	for (auto* particle : this->particles)
	{
		particle->update();
	}
}

void Engine::updateSlider()
{
	for (auto* slides : slider)
	{
		slides->update();

	}
}

void Engine::render()
{
	this->window->clear();
	this->renderGUI(this->window);
	this->renderSlider(this->window);
	this->renderParticles(this->window);
	this->window->display();
}

void Engine::renderGUI(RenderTarget* target)
{
	target->draw(this->GUI);
}

void Engine::renderParticles(RenderTarget* target)
{
	for (auto* particle : this->particles)
	{
		particle->render(target);
	}

}

void Engine::renderSlider(RenderTarget* target)
{
	for (auto* slides : slider)
	{
		slides->render(target);
	}
}

void Engine::initWindow()
{
	this->videomode.height = 800;
	this->videomode.width = 1500;
	this->window = new RenderWindow(this->videomode, "Life", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(30);
	this->window->setVerticalSyncEnabled(false);
}

void Engine::initGUI()
{
	if (!this->font.loadFromFile("Fonts/Silkscreen-Bold.ttf")) std::cout << "fuck it";
	this->GUI.setFont(this->font);
	this->GUI.setCharacterSize(20);
	this->GUI.setString("NONE");
	this->GUI.setFillColor(Color::White);
	this->GUI.setPosition(0.5 * this->window->getSize().x - 0.5 * this->GUI.getGlobalBounds().width, 0.24 * this->window->getSize().y);
}

void Engine::initVariables()
{
	this->velocity = 0.f;
	this->distanceMax = 0.f;
	this->amount = 1200;
}

void Engine::initSlider()
{
	Vector2f range = Vector2f(-100, 100);
	Vector2f size = Vector2f(400, 25);

	for (int i = 0; i < 27; i++)
	{
		this->slider.push_back(new Slider(this->window));
		this->slider[i]->setSize(size);
		this->slider[i]->setPos(Vector2f(0, i * (size.y + 5)));
		this->slider[i]->setRange(range);
		this->slider[i]->setTextColorValue(Color::White);
		this->slider[i]->setFillColorRect(Color::White);
	}

	this->slider[0]->setTitle("Red -> Red");
	this->slider[1]->setTitle("Red -> Blue");
	this->slider[2]->setTitle("Red -> Yellow");
	this->slider[3]->setTitle("Red -> Green");
	this->slider[4]->setTitle("Red -> white");
		  
	this->slider[5]->setTitle("Green -> Green");
	this->slider[6]->setTitle("Green -> Blue");
	this->slider[7]->setTitle("Green -> Yellow");
	this->slider[8]->setTitle("Green -> Red");
	this->slider[9]->setTitle("Green -> white");

	this->slider[10]->setTitle("Yellow -> Yellow");
	this->slider[11]->setTitle("Yellow -> Blue");
	this->slider[12]->setTitle("Yellow -> Green");
	this->slider[13]->setTitle("Yellow -> Red");
	this->slider[14]->setTitle("Yellow -> white");

	this->slider[15]->setTitle("Blue -> Blue");
	this->slider[16]->setTitle("Blue -> Green");
	this->slider[17]->setTitle("Blue -> Yellow");
	this->slider[18]->setTitle("Blue -> Red");
	this->slider[19]->setTitle("Blue -> white");

	this->slider[20]->setTitle("White -> White");
	this->slider[21]->setTitle("White -> Blue");
	this->slider[22]->setTitle("White -> Yellow");
	this->slider[23]->setTitle("White -> Red");
	this->slider[24]->setTitle("White -> Green");

	this->slider[25]->setTitle("Velocity");
	this->slider[26]->setTitle("Distance");
	this->slider[25]->setRange(Vector2f(0,100));
	this->slider[26]->setRange(Vector2f(0,1000));
}

void Engine::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::F) this->window->close();
			break;
		}
	}
}

std::vector<Particles*> Engine::create(int number, Color color)
{
	std::vector<Particles*> group;
	for (int i = 0; i < number; i++)
	{
		group.push_back(new Particles(random(600, 700), random(600, 50), color));
		this->particles.push_back(group[i]);
	}
	return group;
}

int Engine::random(int range, int start)
{
	return rand() %range +start;
}

float Engine::force(float r, float a)
{
	const float beta = 0.3f;
	if (r < beta)
	{
		return r / beta - 1;
	}
	else if (beta < r && r < 1)
	{
		return a * (1 - abs(2 * r - 1 - beta) / (1 - beta));
	}
	else {
		return 0.0f;
	}
}
void Engine::interaction(std::vector<Particles*> particle1, std::vector<Particles*> particle2, float attraction)
{	
	for (int i = 0; i < particle1.size(); i++)
	{
		float fx = 0;
		float fy = 0;
		
		for (int j = 0; j < particle2.size(); j++)
		{
			float dx = particle2[j]->getPos().x - particle1[i]->getPos().x;
			float dy = particle2[j]->getPos().y - particle1[i]->getPos().y;
			float distance = sqrt(dx * dx + dy * dy);

			if (distance > 0 && distance < this->distanceMax)
			{
				const float f = this->force(distance / this->distanceMax, attraction);
				fx += dx / distance * f;
				fy += dy / distance * f;

			}
		}

		fx *= this->distanceMax;
		fy *= this->distanceMax;

		particle1[i]->vx = particle1[i]->vx * 0.3f + fx*this->velocity * 0.2f;
		particle1[i]->vy = particle1[i]->vy * 0.3f + fy*this->velocity * 0.2f;
		particle1[i]->posX += particle1[i]->vx * this->velocity * 0.2f;
		particle1[i]->posY += particle1[i]->vy * this->velocity * 0.2f;
		if (particle1[i]->posX <= 400)
		{
			particle1[i]->vx *= -1;
			particle1[i]->setPos(Vector2f(401, particle1[i]->posY));
		}
		if (particle1[i]->posX >= this->window->getSize().x)
		{
			particle1[i]->vx *= -1;
			particle1[i]->setPos(Vector2f(this->window->getSize().x-5, particle1[i]->posY));
		}
		if (particle1[i]->posY <= 0)
		{
			particle1[i]->vy *= -1;
			particle1[i]->setPos(Vector2f(particle1[i]->posX, 1));
		}
		if (particle1[i]->posY >= this->window->getSize().y)
		{
			particle1[i]->vy *= -1;
			particle1[i]->setPos(Vector2f(particle1[i]->posX, this->window->getSize().y-5));
		}
		
		//std::cout << a->getPos().x << " " << a->getPos().y << "\n";
		//std::cout << fx << " " << fy << "\n";
	}
}



/*float avx = a->getVel().x;
		float avy = a->getVel().y;
		a->setVel(Vector2f((avx + fx)*0.5, (avy + fy)*0.5));
		a->setPos(Vector2f(a->getPos().x + avx, a->getPos().y + avy));
		if (a->getPos().x <= 0 || a->getPos().x >= this->window->getSize().x)
		{
			a->setVel(Vector2f(-a->getVel().x, a->getVel().y));
		}

		if (a->getPos().y <= 0 || a->getPos().y >= this->window->getSize().y)
		{
			a->setVel(Vector2f(a->getVel().x, -a->getVel().y));
		}*/