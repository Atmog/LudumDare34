#include "BgLayer.hpp"
#include "../../Application/Application.hpp"

BgLayer::BgLayer()
{
    mSprite.setTexture(ah::Application::getResources().getTexture("bg"));
    sf::Vector2u wSize = ah::Application::getWindow().getSize();
    sf::Vector2f scale = sf::Vector2f(wSize.x/800.f,wSize.y/600.f);
    mSprite.setScale(scale);
}

sf::Vector2f BgLayer::getSizePx() const
{
    return static_cast<sf::Vector2f>(ah::Application::getWindow().getSize());
}

void BgLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}
