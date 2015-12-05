#ifndef SES_SPRITECOMPONENT_HPP
#define SES_SPRITECOMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "../Component.hpp"

namespace ses
{

class SpriteComponent : public Component, public sf::Sprite
{
    public:
        SpriteComponent();
        SpriteComponent(sf::Texture const& texture);
        SpriteComponent(sf::Texture const& texture, sf::IntRect const& textureRect);
        virtual ~SpriteComponent();

        sf::FloatRect getBounds() const;
};

} // namespace ses

#endif // SES_SPRITECOMPONENT_HPP
