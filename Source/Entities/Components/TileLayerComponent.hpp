#ifndef SES_TILELAYERCOMPONENT_HPP
#define SES_TILELAYERCOMPONENT_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "../Component.hpp"

namespace ses
{

class TileLayerComponent : public Component, public sf::Drawable
{
    public:
        TileLayerComponent();
        TileLayerComponent(sf::Vector2u size, sf::Texture* texture);
        virtual ~TileLayerComponent();

        void resize(sf::Vector2u size);

        void setTexture(sf::Texture* texture);
        sf::Texture* getTexture();

        void setTileRect(sf::Vector2u pos, sf::IntRect tRect);
        sf::IntRect getTileRect(sf::Vector2u pos);

        sf::FloatRect getBounds() const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        sf::VertexArray mArray;
        sf::Vector2u mSize;
        sf::Texture* mTexture;
};

} // namespace ses

#endif // SES_TILELAYERCOMPONENT_HPP
