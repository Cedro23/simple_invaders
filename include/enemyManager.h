#pragma once
#include "invaders.h"
#include "enemy.h"

class EnemyManager
{
public:
	std::vector<Enemy> enemies;
	sf::RenderWindow* window;

	EnemyManager();
	//~EnemyManager();

	bool isMovingRight = true;
	bool isEnemyMoving = true;

	void SetRenderWindow(sf::RenderWindow&);
	void SpawnEnemies();
	void SpawnEnemies(float);
	void InitTextures(sf::Texture&);
	void RenderEnemy(Enemy);
	void UpdateEnemies();
	void ClearEnemies();
	void MoveDown();
	bool IsGameOver();

private:
	
};
