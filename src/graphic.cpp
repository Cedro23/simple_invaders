#include "graphic.h"

Graphic::Graphic()
{
}

Graphic::Graphic(const sf::Texture &texture)
{
    this->setTexture(texture);
}

Graphic::~Graphic()
{
}

void Graphic::setTexture(const sf::Texture &texture)
{
    this->_sprite.setTexture(texture);
    sf::FloatRect box = this->_sprite.getLocalBounds();
    this->_sprite.setOrigin(box.left + box.width / 2.0f, box.top + box.height / 2.0f);
}

void Graphic::setCoords(const int &x, const int &y)
{
    this->_coords = std::make_tuple(x, y);
}

sf::FloatRect Graphic::getBox()
{
    return this->_sprite.getGlobalBounds();
}

void Graphic::draw(sf::RenderWindow &window)
{
    this->_sprite.setPosition(std::get<0>(this->_coords), std::get<1>(this->_coords));
    window.draw(this->_sprite);
};