#include "TileLayerComponent.hpp"
#include "../Entity.hpp"

namespace ses
{

TileLayerComponent::TileLayerComponent() : Component()
{
    mArray.setPrimitiveType(sf::Quads);
    mTexture = nullptr;
}

TileLayerComponent::TileLayerComponent(sf::Vector2u size, sf::Texture* texture) : Component()
{
    mArray.setPrimitiveType(sf::Quads);
    resize(size);
    mTexture = texture;
}

TileLayerComponent::~TileLayerComponent()
{
    mTexture = nullptr;
}

void TileLayerComponent::resize(sf::Vector2u size)
{
    mSize = size;
    mArray.resize(mSize.x * mSize.y * 4);
}

void TileLayerComponent::setTexture(sf::Texture* texture)
{
    mTexture = texture;
}

sf::Texture* TileLayerComponent::getTexture()
{
    return mTexture;
}

void TileLayerComponent::setTileRect(sf::Vector2u pos, sf::IntRect tRect)
{
    if (pos.x < mSize.x && pos.y < mSize.y)
    {
        sf::Vertex* quad = &mArray[(pos.x + pos.y * mSize.x) * 4];

        quad[0].position = sf::Vector2f(pos.x * tRect.width, pos.y * tRect.height);
        quad[1].position = sf::Vector2f((pos.x + 1) * tRect.width, pos.y * tRect.height);
        quad[2].position = sf::Vector2f((pos.x + 1) * tRect.width, (pos.y + 1) * tRect.height);
        quad[3].position = sf::Vector2f(pos.x * tRect.width, (pos.y + 1) * tRect.height);

        quad[0].texCoords = sf::Vector2f(tRect.left, tRect.top);
        quad[1].texCoords = sf::Vector2f(tRect.left + tRect.width, tRect.top);
        quad[2].texCoords = sf::Vector2f(tRect.left + tRect.width, tRect.top + tRect.height);
        quad[3].texCoords = sf::Vector2f(tRect.left, tRect.top + tRect.height);
    }
}

sf::IntRect TileLayerComponent::getTileRect(sf::Vector2u pos)
{
    sf::IntRect tRect;
    if (pos.x < mSize.x && pos.y < mSize.y)
    {
        sf::Vertex* quad = &mArray[(pos.x + pos.y * mSize.x) * 4];
        tRect.left = (int)quad[0].texCoords.x;
        tRect.top = (int)quad[0].texCoords.y;
        tRect.width = (int)quad[2].texCoords.x - tRect.left;
        tRect.height = (int)quad[2].texCoords.y - tRect.top;
    }
    return tRect;
}

sf::FloatRect TileLayerComponent::getBounds() const
{
    sf::Vector2f pos(0.f,0.f);
    if (mEntity != nullptr)
    {
        pos = mEntity->getPosition();
    }
    return sf::FloatRect(pos,sf::Vector2f(mSize.x * 32.f, mSize.y * 32.f));
}

void TileLayerComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mTexture != nullptr)
    {
        states.texture = mTexture;
        target.draw(mArray,states);
    }
}

} // namespace ses
