#include <iostream>
#include "..\include\button.h"

using namespace std;

Button::Button()
{}

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineColor(sf::Color::White);
	this->shape.setOutlineThickness(4.0f);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setColor(sf::Color::White);
	this->text.setCharacterSize(50);
	this->text.setPosition(
		this->shape.getPosition().x - this->text.getGlobalBounds().width / 2.0f,
		this->shape.getPosition().y
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
}

Button::~Button()
{}

bool Button::Update(const sf::Vector2f mousePos)
{
	//Update booleans for hover and pressed

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->shape.setOutlineColor(hoverColor);
		this->shape.setOutlineThickness(6.0f);
		this->text.setColor(hoverColor);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->shape.setOutlineColor(activeColor);
			this->text.setColor(activeColor);

			return true;
		}
	}
	else
	{
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(4.0f);
		this->text.setColor(sf::Color::White);
	}

	return false;
}

void Button::Render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}