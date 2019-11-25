#pragma once
#include "invaders.h"
#include "entity.h"

class Bullet : public Entity
{
public:
	float curY;

	Bullet(float, float, sf::Texture&, float);

	void MoveForward();
	void DeleteBullet();

private:
};