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
	playerTexture.loadFromFile("assets/img/zywoo_jul.png");
	enemyTexture.loadFromFile("assets/img/s1mple.png");
	playerBulletTexture.loadFromFile("assets/img/chicken_bullet.png");
	enemyBulletTexture.loadFromFile("assets/img/dosia_bullet.png");
	font.loadFromFile("assets/fonts/CosmicAlien.ttf");
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
		this->window.display();
	}
}

void Game::update(sf::Time elapsedTime)
{
	UpdateTimer(elapsedTime);
	DisplayScore();
	UpdateBullets();
	UpdatePlayer();
}

#pragma endregion

#pragma region Entities

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
		if (playerBullets[i].curY > 1550)
		{
			playerBullets.erase(playerBullets.begin() + i);
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
	if (isTrue)
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
			exit(0);
		}

	}
	else
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
}

#pragma endregion

#pragma region Timer

void Game::UpdateTimer(sf::Time elapsedTime)
{
	sf::Text scoreText;
	timer += elapsedTime;
	int seconds = timer.asSeconds();
	static int minutes = 0;

	if (seconds >= 60)
	{
		minutes++;
		timer = sf::Time::Zero;
	}

	if (seconds >= 10)
	{
		scoreText = createText(to_string(minutes) + ":" + to_string(seconds), sf::Color::White);
	}
	else
	{
		scoreText = createText(to_string(minutes) + ":0" + to_string(seconds), sf::Color::White);
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

