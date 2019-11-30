#pragma once
#include "invaders.h"
#include "bullet.h"

class Enemy : public Entity
{
public:
	float curX;
	float curY;

	sf::Texture* bulletTexture;

	Enemy(float, float, sf::Texture&);
	Enemy(float, float, float, sf::Texture&);

	void Move(bool);
	Bullet Shoot();
	void ShootManager();
private:
};