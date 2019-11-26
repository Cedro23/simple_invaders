#pragma once
#include "invaders.h"
#include "bullet.h"

class Enemy : public Entity
{
public:
	float curX;
	float curY;

	Enemy(float, float, sf::Texture&);

	void MoveLeft();
	void MoveRight();
	Bullet Shoot(sf::Texture&);
private:
};