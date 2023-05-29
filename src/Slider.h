#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class Slider
{
public:
	Slider(RenderWindow *win);
	virtual ~Slider();

	void update();

	void render(RenderTarget *target);

	const Vector2f getPosSlider() const;
	const Vector2f getPosRect() const;
	const float getValue() const;

	//Update Shape
	void setPos(Vector2f pos);
	void setFillColorSlider(Color col);
	void setFillColorRect(Color col);
	void setSize(Vector2f size);

	//Update GUI
	void setTitle(std::string title);
	void setCharakterSize(float size);
	void setTextColorValue(Color col);
	void setTextColorRect(Color col);
	void setRange(Vector2f range);


private:

	Vector2f positionSlider;
	Vector2f positionRect;

	Vector2f sizeRect;
	Vector2f sizeSlider;

	Color colorSlider;
	Color colorRect;

	Text textRect;
	Text textValue;
	Font font;

	RectangleShape rect;
	RectangleShape slider;

	float value;
	float start;
	float end;

	std::string title;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	bool mouseheld = false;
	RenderWindow *window;


	void initVariables(RenderWindow *win);
	void initGUI();
	void initShape();

	void updateMousePosition();
	void updateGUI();
	void updateSlider();
	void updateShape();

	void renderGUI(RenderTarget* target);

	float round3Decimal(float val);
};

