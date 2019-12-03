#pragma once
#include "invaders.h"
#include "player.h"
#include "enemyManager.h"
#include "button.h"

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
		menu,		// codé
		game,		// codé
		pause,		// à coder
		gameover,	// partiellement codé
		howtoplay,	// à coder
		highscore,	// à coder
		save		// à coder
	};
	GameState gameState = GameState::menu;
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
	float maxCooldown = 60.0f;

	//Levels
	float enemySpeed = 1.0f;

	//Buttons
	sf::Color activeColor = sf::Color(55.0f, 55.0f, 55.0f);
	sf::Color hoverColor = sf::Color(150.0f, 150.0f, 150.0f);

	Button btnPlay = Button(480.0f, 200.0f, WINDOW_WIDTH / 4, 80.0f, &font, "Play", sf::Color::Black, hoverColor, activeColor);
	Button btnHowToPlay = Button(480.0f, 400.0f, WINDOW_WIDTH / 4, 80.0f, &font, "How to play", sf::Color::Black, hoverColor, activeColor);
	Button btnQuit = Button(480.0f, 600.0f, WINDOW_WIDTH / 4, 80.0f, &font, "Quit", sf::Color::Black, hoverColor, activeColor);
	
public:
    Game(void);
    ~Game();
    void run();

    static constexpr float WINDOW_WIDTH = 1200;
    static constexpr float WINDOW_HEIGHT = 900;
};
