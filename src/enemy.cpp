#include <iostream>
#include "..\include\enemy.h"

using namespace std;

Enemy::Enemy(float x, float y, sf::Texture& bulTexture) : Entity(x, y)
{
	entityType = Entity::EntityType::enemy;

	curX = startingX;
	curY = startingY;

	speed = 1.0f;

	scale = 0.1f;

	bulletTexture = &bulTexture;

	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setPosition(sf::Vector2f(startingX, startingY));
}

Enemy::Enemy(float x, float y, float newSpeed, sf::Texture& bulTexture) : Entity(x, y)
{
	entityType = Entity::EntityType::enemy;

	curX = startingX;
	curY = startingY;

	speed = newSpeed;

	scale = 0.1f;

	bulletTexture = &bulTexture;

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

Bullet Enemy::Shoot()
{
	return Bullet(this->curX, this->curY + 30, *bulletTexture, 0.1f, EntityType::enemy);
}