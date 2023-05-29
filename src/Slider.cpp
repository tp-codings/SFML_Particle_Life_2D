#include "Slider.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace sf;

Slider::Slider(RenderWindow *win)
{
	this->initVariables(win);
	this->initGUI();
	this->initShape();
}

Slider::~Slider()
{
}

void Slider::update()
{
	this->updateMousePosition();
	this->updateSlider();
	this->updateShape();
	this->updateGUI();
	//std::cout << positionSlider.x << "\n";
}

void Slider::updateMousePosition()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Slider::updateGUI()
{
	std::stringstream ss1;
	std::stringstream ss2;

	ss1 << this->title;
	ss2 << this->round3Decimal(this->value);

	this->textRect.setString(ss1.str());
	this->textRect.setCharacterSize(this->sizeRect.y * 0.42);
	this->textRect.setPosition((Vector2f(this->positionRect.x + 10, this->positionRect.y)));

	this->textValue.setString(ss2.str());
	this->textValue.setCharacterSize(this->sizeRect.y * 0.42);
	this->textValue.setPosition((Vector2f(this->positionRect.x + this->sizeRect.x + 10, this->positionRect.y)));
}

void Slider::updateSlider()
{

	if (!Mouse::isButtonPressed(Mouse::Left))
	{
		this->mouseheld = false;
	}
	if (slider.getGlobalBounds().contains(this->mousePosView) || this->mouseheld)
	{

		if (Mouse::isButtonPressed(Mouse::Left))
		{

			if (this->mousePosView.x >= this->positionRect.x+this->sizeSlider.x*0.5 && this->mousePosView.x <= this->positionRect.x + this->sizeRect.x-this->sizeSlider.x*0.5)
			{
				this->positionSlider = Vector2f(this->mousePosView.x-this->sizeSlider.x*0.5, this->positionSlider.y);
				this->value = (abs(this->start)+abs(this->end))*(this->positionSlider.x / (this->sizeRect.x - this->sizeSlider.x) - this->positionRect.x / (this->sizeRect.x - this->sizeSlider.x))+(this->start);
			}
			else if (this->mousePosView.x <= this->positionRect.x + this->sizeSlider.x * 0.5)
			{
				this->positionSlider = Vector2f(this->positionRect.x, this->positionSlider.y);
				this->value = (abs(this->start) + abs(this->end)) * (this->positionSlider.x / (this->sizeRect.x - this->sizeSlider.x) - this->positionRect.x / (this->sizeRect.x - this->sizeSlider.x)) + (this->start);
			}
			else if (this->mousePosView.x > this->positionRect.x + this->sizeRect.x - this->sizeSlider.x * 0.5)
			{
				this->positionSlider = Vector2f(this->positionRect.x+this->sizeRect.x-this->sizeSlider.x, this->positionSlider.y);
				this->value = (abs(this->start) + abs(this->end)) * (this->positionSlider.x / (this->sizeRect.x - this->sizeSlider.x) - this->positionRect.x / (this->sizeRect.x - this->sizeSlider.x)) + (this->start);
			}
			this->mouseheld = true;
		}
	}
}

void Slider::updateShape()
{
	this->slider.setPosition(positionSlider);
	this->slider.setFillColor(colorSlider);
	this->slider.setSize(sizeSlider);

	this->rect.setPosition(positionRect);
	this->rect.setFillColor(colorRect);
	this->rect.setSize(sizeRect);

}

void Slider::render(RenderTarget* target)
{
	target->draw(this->rect);
	target->draw(this->slider);
	this->renderGUI(target);
}

const Vector2f Slider::getPosSlider() const
{
	return this->positionSlider;
}

const Vector2f Slider::getPosRect() const
{
	return this->positionRect;
}

const float Slider::getValue() const
{
	return this->value;
}

void Slider::setPos(Vector2f pos)
{
	this->positionRect = pos;
	this->positionSlider = Vector2f(this->positionRect.x + 0.5 * this->sizeRect.x - 0.5 * this->sizeSlider.x, this->positionRect.y);
}

void Slider::setFillColorSlider(Color col)
{
	this->colorSlider = col;
}

void Slider::setFillColorRect(Color col)
{
	this->colorRect = col;
}

void Slider::setSize(Vector2f size)
{
	this->sizeRect = size;
	this->sizeSlider = Vector2f(this->sizeRect.x * 0.075, this->sizeRect.y);
	this->updateShape();
}

void Slider::setTitle(std::string name)
{
	this->title = name;
}

void Slider::setCharakterSize(float size)
{
	this->textRect.setCharacterSize(size);
	this->textValue.setCharacterSize(size);
}

void Slider::setTextColorValue(Color col)
{
	this->textValue.setFillColor(col);
}

void Slider::setTextColorRect(Color col)
{
	this->textRect.setFillColor(col);
}

void Slider::setRange(Vector2f range)
{
	this->start = range.x;
	this->end = range.y;
}

void Slider::initVariables(RenderWindow *win)
{
	this->colorRect = Color::Green;
	this->colorSlider = Color::Black;
	this->positionRect = Vector2f(0, 0);
	this->sizeRect = Vector2f(400.f, 60.f);
	this->sizeSlider = Vector2f(30.f, 60.f);
	this->positionSlider = Vector2f(this->positionRect.x+0.5*this->sizeRect.x-0.5*this->sizeSlider.x, this->positionRect.y);
	this->value = 0.0;
	this->start = -1;
	this->end = 1;
	this->title = "... du stinkst";
	this->mouseheld = false;
	this->window = win;
}

void Slider::initGUI()
{
	if (!this->font.loadFromFile("Fonts/Silkscreen-Bold.ttf")) std::cout << "fuck it";
	this->textRect.setFont(this->font);
	this->textRect.setCharacterSize(20);
	this->textRect.setString("NONE");
	this->textRect.setFillColor(Color::Black);
	this->textRect.setPosition(Vector2f(this->positionRect.x + 10, this->positionRect.y));

	if (!this->font.loadFromFile("Fonts/Silkscreen-Bold.ttf")) std::cout << "fuck it";
	this->textValue.setFont(this->font);
	this->textValue.setCharacterSize(20);
	this->textValue.setString("NONE");
	this->textValue.setFillColor(Color::Black);
	this->textValue.setPosition(Vector2f(this->positionRect.x + this->sizeRect.x + 10, this->positionRect.y));
}


void Slider::initShape()
{
	this->rect.setFillColor(this->colorRect);
	this->rect.setSize(this->sizeRect);
	this->rect.setPosition(this->positionRect);

	this->slider.setFillColor(this->colorSlider);
	this->slider.setSize(this->sizeSlider);
	this->slider.setPosition(this->positionSlider);
}

void Slider::renderGUI(RenderTarget* target)
{
	target->draw(this->textRect);
	target->draw(this->textValue);
}

float Slider::round3Decimal(float val)
{
	int zw = int(val * 1000);
	return float(zw) / 1000;
}
