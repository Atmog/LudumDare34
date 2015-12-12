#include "TileLayer.hpp"

TileLayer::TileLayer()
{
    setSize({5,5});
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            mTiles.at(i + 5 * j).mSprite.setPosition(i * 128.f, j * 128.f);
        }
    }
}

sf::Vector2f TileLayer::getSizePx() const
{
    return sf::Vector2f(5 * 128.f,5 * 128.f);
}

void TileLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for (std::size_t i = 0; i < mTiles.size(); i++)
    {
        target.draw(mTiles.at(i).mSprite,states);
    }
}
