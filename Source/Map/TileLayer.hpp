#ifndef MAP_TILELAYER_HPP
#define MAP_TILELAYER_HPP

#include "Layer.hpp"

namespace map
{

template <typename T>
class TileLayer : public Layer
{
    public:
        TileLayer();

        void setSize(sf::Vector2i const& size);
        sf::Vector2u getSize() const;

        void setTileId(sf::Vector2i const& coords, std::size_t const& id);
        std::size_t getTileId(sf::Vector2i const& coords) const;

    protected:
        sf::Vector2i mSize;
        std::vector<T> mTiles;
};

template <typename T>
TileLayer<T>::TileLayer()
{
}

template <typename T>
void TileLayer<T>::setSize(sf::Vector2i const& size)
{
    mSize = size;
    mTiles.resize(size.x * size.y);
}

template <typename T>
sf::Vector2u TileLayer<T>::getSize() const
{
    return mSize;
}

template <typename T>
void TileLayer<T>::setTileId(sf::Vector2i const& coords, std::size_t const& id)
{
    for (int i = 0; i < mTiles.size(); i++)
    {
        if (mTiles.at(i).getCoords() == coords)
        {
            mTiles.at(i).setId(id);
        }
    }
    return 0;
}

template <typename T>
std::size_t TileLayer<T>::getTileId(sf::Vector2i const& coords) const
{
    for (int i = 0; i < mTiles.size(); i++)
    {
        if (mTiles.at(i).getCoords() == coords)
        {
            return mTiles.at(i).getId();
        }
    }
}

} // namespace map

#endif // MAP_TILELAYER_HPP
