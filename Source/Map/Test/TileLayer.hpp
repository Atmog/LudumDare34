#ifndef TILELAYER_HPP
#define TILELAYER_HPP

#include "Tile.hpp"
#include "../TileLayer.hpp"

class TileLayer : public map::TileLayer<Tile>
{
    public:
        TileLayer();

        sf::Vector2f getSizePx() const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // TILELAYER_HPP
