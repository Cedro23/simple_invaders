#pragma once
#include "invaders.h"
#include "player.h"

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

	Player player;

	
	//Event manager
	bool isLeftArrowPressed = false;
	bool isRightArrowPressed = false;
	bool isSpacebarPressed = false;
	void ProcessEvents();
	void HandleEvent(sf::Event, bool);

	//Score manager
	int currentScore = 0;
	void DisplayScore();
	void UpdateScore(int);

	//Timer manager
	sf::Time timer;
	void UpdateTimer(sf::Time);


	std::vector<Bullet*> bullets;

public:
    Game(void);
    ~Game();
    void run();

    static constexpr float WINDOW_WIDTH = 1200;
    static constexpr float WINDOW_HEIGHT = 900;
};