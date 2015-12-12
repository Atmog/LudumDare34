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
        SpriteComponent(std::string const& textureId, sf::IntRect const& textureRect = sf::IntRect(0,0,0,0));
        SpriteComponent(sf::Texture const& texture, sf::IntRect const& textureRect = sf::IntRect(0,0,0,0));
        virtual ~SpriteComponent();

        sf::FloatRect getBounds() const;

        void load(pugi::xml_node& node);
        void save(pugi::xml_node& node);

    private:
        std::string mTextureId;
};

} // namespace ses

#endif // SES_SPRITECOMPONENT_HPP
