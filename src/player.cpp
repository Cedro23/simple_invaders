#include <iostream>
#include "..\include\player.h"


Player::Player()
{
	entityType = Entity::EntityType::player;

	startingX = 525.0f;
	startingY = 761.0f;
	curX = startingX;

	speed = 10.0f;

	scale = 0.5f;

	texture.loadFromFile("assets/img/zywoo_jul.png");

	sprite.setTexture(texture);
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
	if (curX < 1050)
	{
		curX+= speed;
		sprite.move(sf::Vector2f(speed, 0));
	}
}

Bullet Player::Shoot(sf::Texture& texture)
{
	//Passer la référence de ma bullet
	return Bullet(this->curX, this->startingY + 35, texture, 0.1f);
}








