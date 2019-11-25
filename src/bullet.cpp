#include <iostream>
#include "..\include\bullet.h"

using namespace std;

Bullet::Bullet(float x, float y) : startingX(x), startingY(y)
{
	_texture.loadFromFile("assets/img/chicken_bullet.png");
	_sprite.setTexture(_texture);
	_sprite.setScale(sf::Vector2f(scale, scale));
	_sprite.setPosition(sf::Vector2f(startingX + 50.0f, startingY - 30.0f));
}

void Bullet::MoveForward()
{
	_sprite.move(sf::Vector2f(0.0f, -speed));
	curY += speed;
}