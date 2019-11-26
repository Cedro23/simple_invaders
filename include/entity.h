#pragma once
#include "invaders.h"

class Entity
{
public:
	enum class EntityType
	{
		enemy,
		player,
		bullet
	};

	EntityType entityType;

	sf::Texture texture;
	sf::Sprite sprite;

	float startingX;
	float startingY;

	float scale;

	float speed;

	Entity(float, float);
	Entity();
	void InitTexture(sf::Texture&);

private:
};


