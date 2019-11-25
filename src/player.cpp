#include <iostream>
#include "..\include\player.h"


using namespace std;



Player::Player()
{
	texture.loadFromFile("assets/img/zywoo_jul.png");
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(scale,scale));
	sprite.setPosition(sf::Vector2f(startingX, startingY));
}

Bullet *Player::Shoot()
{
	return new Bullet(curX, startingY);
}

void Player::MoveLeft()
{
	if (curX > 0 )
	{
		curX -= speed;
		sprite.move(-speed, 0);
	}
}

void Player::MoveRight()
{
	if (curX < 1050)
	{
		curX += speed;
		sprite.move(speed, 0);
	}
}

void Player::Die()
{
	cout << "U ded" << endl;
}



