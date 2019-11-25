#pragma once
#include "invaders.h"
#include "entity.h"

class Player : public Entity
{
public:
	float curX;

	Player();

	void MoveLeft();
	void MoveRight();
private:
};