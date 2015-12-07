#include "SpriteComponent.hpp"
#include "../Entity.hpp"

namespace ses
{

SpriteComponent::SpriteComponent()
: Component()
, sf::Sprite()
{
}

SpriteComponent::SpriteComponent(sf::Texture const& texture)
: Component()
, sf::Sprite(texture)
{
}

SpriteComponent::SpriteComponent(sf::Texture const& texture, sf::IntRect const& textureRect)
: Component()
, sf::Sprite(texture,textureRect)
{
}

SpriteComponent::~SpriteComponent()
{
}

sf::FloatRect SpriteComponent::getBounds() const
{
    sf::FloatRect b = getGlobalBounds();
    sf::Vector2f p(b.left,b.top);
    if (mEntity != nullptr)
    {
        p = mEntity->getPosition() - mEntity->getOrigin();
    }
    b.left = p.x;
    b.top = p.y;
    return b;
}

} // namespace ses
