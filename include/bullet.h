#pragma once
#include "invaders.h"
#include "entity.h"

class Bullet : public Entity
{
public:
	float curY;

	EntityType shooterEntity;

	Bullet(float, float, sf::Texture&, float, EntityType);

	void MoveForward();

private:
};