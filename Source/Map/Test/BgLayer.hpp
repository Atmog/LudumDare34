#ifndef BGLAYER_HPP
#define BGLAYER_HPP

#include "../Layer.hpp"

#include <SFML/Graphics/Sprite.hpp>

class BgLayer : public map::Layer
{
    public:
        BgLayer();

        sf::Vector2f getSizePx() const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite mSprite;
};

#endif // BGLAYER_HPP
