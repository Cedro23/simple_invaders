#pragma once
#include "invaders.h"

class Bullet
{
public:
	sf::Texture _texture;
	sf::Sprite _sprite;


	float startingX = 0.0f;
	float startingY = 0.0f;
	float curY = 0.0f;

	float scale = 0.10f;

	float speed = 10.0f;

	Bullet(float, float);

	void MoveForward();

private:
};