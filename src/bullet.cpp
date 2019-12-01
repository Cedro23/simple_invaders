#include <iostream>
#include "..\include\bullet.h"

using namespace std;

Bullet::Bullet(float x, float y, sf::Texture& texture, float scale, EntityType shooterEntityType) : Entity(x, y)
{
	entityType = Entity::EntityType::bullet;
	shooterEntity = shooterEntityType;

	curY = startingY;

	if (shooterEntity == EntityType::player)
	{
		speed = 10.0f;
	}
	else if (shooterEntity == EntityType::enemy)
	{
		speed = 5.0f;
	}

	//sprite.setOrigin(startingX, startingY);
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setPosition(sf::Vector2f(startingX, startingY));
}

void Bullet::MoveForward()
{
	if (shooterEntity == EntityType::player)
	{
		sprite.move(sf::Vector2f(0.0f, -speed));
		curY -= speed;
	}
	if (shooterEntity == EntityType::enemy)
	{
		sprite.move(sf::Vector2f(0.0f, speed));
		curY += speed;
	}
}