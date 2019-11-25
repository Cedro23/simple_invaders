#pragma once
#include "invaders.h"

/*
** A drawable object
*/
class Graphic
{
private:
    std::tuple<int, int> _coords = {0, 0};

protected:
    sf::Sprite _sprite;

public:
    Graphic();
    Graphic(const sf::Texture &texture);
    virtual ~Graphic();
    sf::FloatRect getBox();
    void setTexture(const sf::Texture &texture);
    void setCoords(const int &x, const int &y);
    virtual void draw(sf::RenderWindow &window);
};
