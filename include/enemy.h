#pragma once
#include "invaders.h"
#include "bullet.h"

class Enemy : public Entity
{
public:
	float curX;
	float curY;

	Enemy(float, float);

	void Move(bool);
	Bullet Shoot(sf::Texture&);
private:
};