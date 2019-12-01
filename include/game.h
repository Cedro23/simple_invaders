#pragma once
#include "invaders.h"
#include "player.h"
#include "enemyManager.h"

/*
** Game handling
*/
class Game
{
private:
    void update(sf::Time);
    void load();

	const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

	sf::Text createText(const std::string& text, const sf::Color& color);
	void displayText(sf::Text, float, float, float, float);
    sf::RenderWindow window;
    sf::Font font;

	//Gamestates
	enum class GameState {
		menu,
		game,
		gameover
	};
	GameState gameState = GameState::game;
	void UpdateGameState(GameState);

	//Entities manager
	Player player;
	EnemyManager enemyManager;
	void InitTextures();
	void UpdatePlayer();

	//Textures manager
	sf::Texture playerBulletTexture;
	sf::Texture playerTexture;
	sf::Texture enemyBulletTexture;
	sf::Texture enemyTexture;

	//Event manager
	bool isLeftArrowPressed = false;
	bool isRightArrowPressed = false;
	bool isSpacebarPressed = false;
	void ProcessEvents();
	void HandleEvent(sf::Event, bool);

	//Statistics
	void UpdateStatistics(sf::Time);

	//Score manager
	int currentScore = 0;
	void DisplayScore();
	void UpdateScore(int);

	//Timer manager
	sf::Time timer;
	void UpdateTimer(sf::Time);

	//Bullet manager
	std::vector<Bullet> playerBullets;
	std::vector<Bullet> enemiesBullets;
	void UpdateBullets();
	void CheckForCollisions();
	int enemyShootCounter = 3;
	bool isEnemyShooting = true;
	float cdTimer = 0.0f;
	float cooldown = 2.0f;

	//Levels
	float enemySpeed = 1.0f;
	
public:
    Game(void);
    ~Game();
    void run();

    static constexpr float WINDOW_WIDTH = 1200;
    static constexpr float WINDOW_HEIGHT = 900;
};
