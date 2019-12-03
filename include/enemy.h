#pragma once
#include "invaders.h"
#include "bullet.h"

class Enemy : public Entity
{
public:
	float curX;
	float curY;

	sf::Texture* bulletTexture;

	float shootingTimer;
	float currentTimer = 0.0f;

	Enemy(float, float, sf::Texture&);
	Enemy(float, float, float, float, sf::Texture&);

	float RandomFloat(float, float);
	void Move(bool);
	Bullet Shoot();
private:
};