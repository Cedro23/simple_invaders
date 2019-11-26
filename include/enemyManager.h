#pragma once
#include "invaders.h"
#include "enemy.h"

class EnemyManager
{
public:
	std::vector<Enemy> enemies;

	EnemyManager();
	//~EnemyManager();

	bool isMovingRight = true;
	bool isEnemyMoving = true;

	void SpawnEnemies();
	void InitTextures(sf::Texture&);
	void UpdateEnemies(sf::RenderWindow&);
	void MoveDown();
	bool IsGameOver();

private:
	
};
