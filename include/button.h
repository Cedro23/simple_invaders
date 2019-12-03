#pragma once
#include "invaders.h"

class Button
{
private:
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button();
	Button(float, float, float, float,
		sf::Font*, std::string,
		sf::Color, sf::Color, sf::Color);
	~Button();

	bool Update(const sf::Vector2f);
	void Render(sf::RenderTarget*);
};