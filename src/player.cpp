#include <iostream>
#include "..\include\player.h"


Player::Player()
{
	entityType = Entity::EntityType::player;

	startingX = 525.0f;
	startingY = 811.0f;
	curX = startingX;

	speed = 10.0f;

	scale = 0.2f;

	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setPosition(sf::Vector2f(startingX, startingY));
}

void Player::MoveLeft()
{
	if (curX > 0)
	{
		curX -= speed;
		sprite.move(sf::Vector2f(-speed,0));
	}
}

void Player::MoveRight()
{
	if (curX < 1140)
	{
		curX+= speed;
		sprite.move(sf::Vector2f(speed, 0));
	}
}



Bullet Player::Shoot(sf::Texture& texture)
{
	return Bullet(this->curX + 10.0f, this->startingY - 20.0f, texture, 0.1f, EntityType::player);
}