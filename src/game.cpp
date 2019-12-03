#include "game.h"
#include <iostream>

using namespace std;

Game::Game()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simple invaders", sf::Style::Close | sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);
	load();
}

Game::~Game()
{
}

void Game::load()
{
	enemyManager.SetRenderWindow(window);
	playerTexture.loadFromFile("assets/img/zywoo_jul.png");
	enemyTexture.loadFromFile("assets/img/s1mple.png");
	playerBulletTexture.loadFromFile("assets/img/chicken_bullet.png");
	enemyBulletTexture.loadFromFile("assets/img/dosia_bullet.png");
	font.loadFromFile("assets/fonts/cs_regular.ttf");

	enemyManager.SpawnEnemies(enemyBulletTexture);
	InitTextures();
}

#pragma region Text

sf::Text Game::createText(const std::string& text, const sf::Color& color)
{
	sf::Text newText;
	newText.setFont(font);
	newText.setCharacterSize(30);
	newText.setString(text);
	newText.setFillColor(color);

	return newText;
}

void Game::displayText(sf::Text text, float originX, float originY, float posX, float posY)
{
	text.setOrigin(originX, originY);
	text.setPosition(posX, posY);
	window.draw(text);
}

#pragma endregion

#pragma region Game Loop

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while ((timeSinceLastUpdate > TimePerFrame))
		{
			this->window.clear(sf::Color::Black);

			timeSinceLastUpdate -= TimePerFrame;

			ProcessEvents();
			this->update(TimePerFrame);
		}
		//éxecuter tout le temps
		UpdateStatistics(elapsedTime);

		this->window.display();
	}
}

void Game::update(sf::Time elapsedTime)
{
	if (gameState == GameState::menu) //si dans le menu
	{
		//create menu
		btnPlay.Render(&window);
		btnHowToPlay.Render(&window);
		btnQuit.Render(&window);

		btnPlay.Update((sf::Vector2f)sf::Mouse::getPosition(window));
		btnHowToPlay.Update((sf::Vector2f)sf::Mouse::getPosition(window));
		btnQuit.Update((sf::Vector2f)sf::Mouse::getPosition(window));
	}
	else if (gameState == GameState::game) //si la partie est en cours
	{
		UpdateBullets();
		if (playerBullets.size() > 0 || enemiesBullets.size() > 0)
		{
			CheckForCollisions();
		}
		if (enemyManager.enemies.size() <= 0)
		{
			//center player ?
			playerBullets.clear();
			enemiesBullets.clear();
			enemySpeed *= 1.07f;
			maxCooldown *= 0.9f;
			isEnemyShooting = false;
			enemyShootCounter = 3;
			enemyManager.SpawnEnemies(enemySpeed, maxCooldown, enemyBulletTexture);
			enemyManager.InitTextures(enemyTexture);
		}
		enemyManager.UpdateEnemies();
		for (size_t i = 0; i < enemyManager.enemies.size(); i++)
		{
			if (enemyManager.enemies[i].currentTimer >= enemyManager.enemies[i].shootingTimer)
			{
				enemiesBullets.push_back(enemyManager.enemies[i].Shoot());
				enemyManager.enemies[i].currentTimer = 0.0f;
				enemyManager.enemies[i].shootingTimer = enemyManager.enemies[i].RandomFloat(0.5f, maxCooldown);
			}
			else
			{
				enemyManager.enemies[i].currentTimer += elapsedTime.asSeconds();
			}
		}
		UpdatePlayer();
		if (enemyManager.IsGameOver())
			UpdateGameState(GameState::gameover);
	}
	else if (gameState == GameState::pause)
	{
		DisplayScore();
		UpdateTimer(elapsedTime);
		sf::Text pauseText = createText("Pause", sf::Color::White);
		sf::FloatRect box = pauseText.getLocalBounds();
		pauseText.setCharacterSize(75);
		displayText(pauseText, box.width, box.height, WINDOW_WIDTH / 2 - box.width / 4, 200);
	}
	else if (gameState == GameState::gameover) //si la partie est finie
	{
		sf::Text gameOverText = createText("Game Over", sf::Color::White);
		sf::FloatRect box = gameOverText.getLocalBounds();
		gameOverText.setCharacterSize(75);
		displayText(gameOverText, box.width, box.height, WINDOW_WIDTH / 2 - box.width / 4, WINDOW_HEIGHT / 2);
	}
}

void Game::UpdateGameState(GameState updatedGameState)
{
	gameState = updatedGameState;
}

void Game::UpdateStatistics(sf::Time elapsedTime)
{
	if (gameState == GameState::game || gameState == GameState::gameover)
	{
		UpdateTimer(elapsedTime);
		DisplayScore();
	}
}

#pragma endregion

#pragma region Entities

void Game::InitTextures()
{
	player.InitTexture(playerTexture);
	enemyManager.InitTextures(enemyTexture);
}

void Game::UpdatePlayer()
{
	window.draw(player.sprite);

	if (isLeftArrowPressed)
	{
		player.MoveLeft();
	}
	if (isRightArrowPressed)
	{
		player.MoveRight();
	}
}


#pragma endregion

#pragma region Bullets

void Game::UpdateBullets()
{
	for (int i = 0; i < playerBullets.size(); i++)
	{
		window.draw(playerBullets[i].sprite);
		playerBullets[i].MoveForward();
		if (playerBullets[i].curY <= 0)
		{
			playerBullets.erase(playerBullets.begin() + i);
		}
	}

	for (int i = 0; i < enemiesBullets.size(); i++)
	{
		window.draw(enemiesBullets[i].sprite);
		enemiesBullets[i].MoveForward();

		if (enemiesBullets[i].curY >= 900)
		{
			enemiesBullets.erase(enemiesBullets.begin() + i);
		}
	}
}

void Game::CheckForCollisions()
{
	//Collisions for player bullets
	for (size_t i = 0; i < playerBullets.size(); i++)
	{
		sf::FloatRect pbBounds = playerBullets[i].sprite.getGlobalBounds();
		float x1 = pbBounds.left; //left x 
		float x2 = pbBounds.left + pbBounds.width; //right x 
		float y1 = pbBounds.top; //top y 
		float y2 = pbBounds.top + pbBounds.height; //bot y		

		for (size_t j = 0; j < enemyManager.enemies.size(); j++)
		{
			sf::FloatRect enemyBounds = enemyManager.enemies[j].sprite.getGlobalBounds();
			sf::Vector2f ennemyBotLeft(enemyBounds.left, enemyBounds.top + enemyBounds.height);
			sf::Vector2f ennemyTopRight(enemyBounds.left + enemyBounds.width, enemyBounds.top);

			if ((ennemyBotLeft.x <= x1 && x1 <= ennemyTopRight.x) || (ennemyBotLeft.x <= x2 && x2 <= ennemyTopRight.x))
			{
				if ((ennemyBotLeft.y >= y1 && y1 >= ennemyTopRight.y) || (ennemyBotLeft.y >= y2 && y2 >= ennemyTopRight.y))
				{
					enemyManager.enemies.erase(enemyManager.enemies.begin() + j);
					playerBullets.erase(playerBullets.begin() + i);
					UpdateScore(50);
					break;
				}
			}
		}
	}

	//Collisions for enemy bullets
	for (size_t i = 0; i < enemiesBullets.size(); i++)
	{
		sf::FloatRect bulletBounds = enemiesBullets[i].sprite.getGlobalBounds();
		float x1 = bulletBounds.left; //left x 
		float x2 = bulletBounds.left + bulletBounds.width; //right x 
		float y1 = bulletBounds.top; //top y 
		float y2 = bulletBounds.top + bulletBounds.height; //bot y

		sf::FloatRect playerBounds = player.sprite.getGlobalBounds();
		sf::Vector2f playerBotLeft(playerBounds.left, playerBounds.top + playerBounds.height);
		sf::Vector2f playerTopRight(playerBounds.left + playerBounds.width, playerBounds.top);


		if ((playerBotLeft.x <= x1 && x1 <= playerTopRight.x) || (playerBotLeft.x <= x2 && x2 <= playerTopRight.x))
		{

			if ((playerBotLeft.y >= y1 && y1 >= playerTopRight.y) || (playerBotLeft.y >= y2 && y2 >= playerTopRight.y))
			{
				enemiesBullets.erase(enemiesBullets.begin() + i);
				gameState = GameState::gameover;
				break;
			}
		}

	}
}

#pragma endregion

#pragma region Events

void Game::ProcessEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			HandleEvent(event, true);
			break;
		case sf::Event::KeyReleased:
			HandleEvent(event, false);
			break;
		case sf::Event::Closed:
			this->window.close();
			break;
		default:
			break;
		}
	}
}

void Game::HandleEvent(sf::Event event, bool isTrue)
{
	if (isTrue && gameState == GameState::game)
	{
		if (event.key.code == 57) //spacebar
		{
			if (!isSpacebarPressed)
			{
				playerBullets.push_back(player.Shoot(playerBulletTexture));
				isSpacebarPressed = true;
			}
		}
		else if (event.key.code == 71) //left arrow
		{
			isLeftArrowPressed = true;
		}
		else if (event.key.code == 72) //right arrow
		{
			isRightArrowPressed = true;
		}
		else if (event.key.code == 36) //echap
		{
			gameState = GameState::pause;
			isLeftArrowPressed = false;
			isRightArrowPressed = false;
		}

	}
	else if (!isTrue && gameState == GameState::game)
	{
		if (event.key.code == 57) //spacebar
		{
			isSpacebarPressed = false;
		}
		else if (event.key.code == 71) //left arrow
		{
			isLeftArrowPressed = false;
		}
		else if (event.key.code == 72) //right arrow
		{
			isRightArrowPressed = false;
		}
	}
	else if (isTrue && gameState == GameState::pause)
	{
		if (event.key.code == 36) //echap
		{
			gameState = GameState::game;
		}
	}
}

#pragma endregion

#pragma region Timer

void Game::UpdateTimer(sf::Time elapsedTime)
{
	static int curSeconds;
	static int curMinutes;
	sf::Text scoreText;
	if (gameState == GameState::game)
	{
		timer += elapsedTime;
		int seconds = timer.asSeconds();
		curSeconds = seconds;
	}

	if (curSeconds >= 60)
	{
		curMinutes++;
		timer = sf::Time::Zero;
	}
	if (curSeconds >= 10)
	{
		scoreText = createText(to_string(curMinutes) + ":" + to_string(curSeconds), sf::Color::White);
	}
	else
	{
		scoreText = createText(to_string(curMinutes) + ":0" + to_string(curSeconds), sf::Color::White);
	}

	sf::FloatRect box = scoreText.getLocalBounds();
	displayText(scoreText, box.width / 2, box.top, WINDOW_WIDTH / 2, 10.f);
}

#pragma endregion

#pragma region Score

void Game::DisplayScore()
{
	sf::Text scoreText = createText("Score : " + to_string(currentScore), sf::Color::White);
	sf::FloatRect box = scoreText.getLocalBounds();
	displayText(scoreText, box.left, box.top, 0, 10);
}

void Game::UpdateScore(int scoreToAdd)
{
	currentScore += scoreToAdd;
}

#pragma endregion

