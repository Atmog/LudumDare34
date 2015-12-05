#ifndef TILELAYER_HPP
#define TILELAYER_HPP

#include "Tile.hpp"
#include "../TileLayer.hpp"

class TileLayer : public map::TileLayer<Tile>
{
    public:
        TileLayer();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // TILELAYER_HPP
