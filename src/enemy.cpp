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

	shootingTimer = RandomFloat(0.5f, 60.0f);

	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setPosition(sf::Vector2f(startingX, startingY));
}

Enemy::Enemy(float x, float y, float newSpeed, float newMaxCD, sf::Texture& bulTexture) : Entity(x, y)
{
	entityType = Entity::EntityType::enemy;

	curX = startingX;
	curY = startingY;

	speed = newSpeed;

	scale = 0.1f;

	bulletTexture = &bulTexture;

	shootingTimer = RandomFloat(0.5f, newMaxCD);

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

float Enemy::RandomFloat(float min, float max)
{
	// this  function assumes max > min, you may want 
	// more robust error checking for a non-debug build
	assert(max > min);
	float random = ((float)rand()) / (float)RAND_MAX;

	// generate (in your case) a float between 0 and (4.5-.78)
	// then add .78, giving you a float between .78 and 4.5
	float range = max - min;
	return (random * range) + min;
}

