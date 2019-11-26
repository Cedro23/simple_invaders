#include <iostream>
#include "..\include\entity.h"

using namespace std;

Entity::Entity(float x, float y) : startingX(x), startingY(y)
{

}

Entity::Entity()
{

}

void Entity::InitTexture(sf::Texture& texture)
{
	sprite.setTexture(texture);
}

//void Entity::Die()
//{
//	cout << "U ded" << endl;
//}
