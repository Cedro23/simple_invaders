#include <iostream>
#include "..\include\enemy.h"

Enemy::Enemy(float x, float y, sf::Texture& texture) : Entity(x, y)
{
	entityType = Entity::EntityType::enemy;

	curX = startingX;
	curY = startingY;

	speed = 5.0f;

	scale = 0.5f;

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setPosition(sf::Vector2f(startingX, startingY));
}

