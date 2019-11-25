#pragma once
#include "invaders.h"
#include "..\include\bullet.h"

class Player
{
public:
	sf::Texture texture;
	sf::Sprite sprite;

	float startingX = 525.0f;
	float startingY = 761.0f;
	float curX = startingX;

	float scale = 0.5f;

	float speed = 10.0f;

	

	Player();
	
	Bullet *Shoot();
	void MoveLeft();
	void MoveRight();
	void Die();

private:
};