#include <iostream>
#include "..\include\bullet.h"

using namespace std;

Bullet::Bullet(float x, float y, sf::Texture& texture, float scale) : Entity(x,y)
{
	entityType = Entity::EntityType::bullet;

	curY = startingY;

	speed = 10.0f;

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setPosition(sf::Vector2f(startingX + 63.0f, startingY - 60.0f));
}

void Bullet::MoveForward()
{
	sprite.move(sf::Vector2f(0.0f, -speed));
	curY += speed;
}