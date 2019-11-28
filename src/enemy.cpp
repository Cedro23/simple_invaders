#include <iostream>
#include "..\include\enemy.h"

Enemy::Enemy(float x, float y) : Entity(x, y)
{
	entityType = Entity::EntityType::enemy;

	curX = startingX;
	curY = startingY;

	speed = 1.0f;

	scale = 0.1f;

	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setPosition(sf::Vector2f(startingX, startingY));


}

Enemy::Enemy(float x, float y, float newSpeed) : Entity(x, y)
{
	entityType = Entity::EntityType::enemy;

	curX = startingX;
	curY = startingY;

	speed = newSpeed;

	scale = 0.1f;

	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setPosition(sf::Vector2f(startingX, startingY));
}



void Enemy::Move(bool isMovingRight)
{
	if (isMovingRight)
	{
		curX += speed;
		sprite.move(sf::Vector2f(speed, 0));
	}
	else
	{
		curX -= speed;
		sprite.move(sf::Vector2f(-speed, 0));
	}
}

Bullet Enemy::Shoot(sf::Texture& texture)
{
	return Bullet(this->curX + 63.0f, this->startingY - 95, texture, 0.1f, EntityType::enemy);
}