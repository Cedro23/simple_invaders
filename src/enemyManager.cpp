#include <iostream>
#include "..\include\enemyManager.h"

using namespace std;

EnemyManager::EnemyManager()
{

}

void EnemyManager::SetRenderWindow(sf::RenderWindow& gameWindow)
{
	window = &gameWindow;
}

void EnemyManager::SpawnEnemies(sf::Texture& bulletTexture)
{
	int x = 100;
	int y = 80;

	for (size_t i = 1; i <= 55; i++)
	{
		enemies.push_back(Enemy::Enemy(i % 11 * x + 20, y, bulletTexture));
		if (i % 11 == 0)
		{
			y += 100;
		}
	}
}

void EnemyManager::SpawnEnemies(float newSpeed, sf::Texture& bulletTexture)
{
	int x = 100;
	int y = 80;

	for (size_t i = 1; i <= 55; i++)
	{
		enemies.push_back(Enemy::Enemy(i % 11 * x + 20, y, newSpeed, bulletTexture));
		if (i % 11 == 0)
		{
			y += 100;
		}
	}
}

void EnemyManager::MoveDown()
{
	if (enemies[enemies.size() - 1].curY + 50 > 730)
	{
		isEnemyMoving = false;

	}
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (isEnemyMoving)
		{
			enemies[i].curY += 50;
			enemies[i].sprite.move(sf::Vector2f(0, 50));
		}
	}
	isMovingRight = !isMovingRight;
}

void EnemyManager::InitTextures(sf::Texture& texture)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].InitTexture(texture);
		RenderEnemy(enemies[i]);
	}
}

void EnemyManager::RenderEnemy(Enemy enemy)
{
	window->draw(enemy.sprite);
}

void EnemyManager::UpdateEnemies()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (isEnemyMoving)
		{
			RenderEnemy(enemies[i]);
			if ((enemies[i].curX > 1150 && isMovingRight) || (enemies[i].curX <= 0 && !isMovingRight))
			{
				MoveDown();
			}
			enemies[i].Move(isMovingRight);
		}
	}
}

void EnemyManager::ClearEnemies()
{
	enemies.clear();
}

bool EnemyManager::IsGameOver()
{
	return !isEnemyMoving;
}
