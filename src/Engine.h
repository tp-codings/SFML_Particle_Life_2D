#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Particles.h"
#include "Slider.h"
#include <vector>
using namespace sf;

class Engine
{
public:
	Engine();
	virtual ~Engine();

	void run();

	const bool running();

private:

	//window
	RenderWindow* window;
	VideoMode videomode;
	Event ev;

	//GUI
	Font font;
	Text GUI;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	bool mouseheld = false;

	//Particles
	std::vector<Particles*> red;
	std::vector<Particles*> yellow;
	std::vector<Particles*> green;
	std::vector<Particles*> blue;
	std::vector<Particles*> white;
	std::vector<Particles*> particles;

	//Slider
	std::vector<Slider*> slider;

	//game logic
	float velocity;
	float distanceMax;

	int amount;

	void update();
	void updateGUI();
	void updateMousePosition();
	void updateInput();
	void updateParticles();
	void updateSlider();

	float force(float, float);

	void render();
	void renderGUI(RenderTarget* target);
	void renderParticles(RenderTarget* target);
	void renderSlider(RenderTarget* target);

	void initWindow();
	void initGUI();
	void initVariables();
	void initSlider();

	void pollEvent();

	std::vector<Particles*> create(int number, Color color);
	int random(int range, int start);

	void interaction(std::vector<Particles*> particle1, std::vector<Particles*> particle2, float attraction);
};



