#ifndef TILE_HPP
#define TILE_HPP

#include "../Tile.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Tile : public map::Tile
{
    public:
        Tile();

        sf::Sprite mSprite;
};

#endif // TILE_HPP
