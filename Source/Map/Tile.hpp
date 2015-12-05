#ifndef MAP_TILE_HPP
#define MAP_TILE_HPP

#include <cstddef>
#include <SFML/System/Vector2.hpp>

namespace map
{

class Tile
{
    public:
        Tile();

        std::size_t getId() const;
        void setId(std::size_t const& id);

        sf::Vector2i getCoords() const;
        void setCoords(sf::Vector2i const& coords);

    protected:
        std::size_t mId;
        sf::Vector2i mCoords;
};

} // namespace map

#endif // MAP_TILE_HPP
