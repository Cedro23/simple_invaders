#pragma once
#include "invaders.h"
#include "entity.h"
#include "bullet.h"

class Player : public Entity
{
public:
	float curX;

	Player();

	void MoveLeft();
	void MoveRight();
	Bullet Shoot(sf::Texture&);
private:
};