#include "Tile.hpp"

namespace map
{

Tile::Tile()
{
    setCoords({0,0});
    setId(0);
}

std::size_t Tile::getId() const
{
    return mId;
}

void Tile::setId(std::size_t const& id)
{
    mId = id;
}

sf::Vector2i Tile::getCoords() const
{
    return mCoords;
}

void Tile::setCoords(sf::Vector2i const& coords)
{
    mCoords = coords;
}

} // namespace map
