#include "Map.hpp"

namespace map
{

Map::Map()
{
}

void Map::addLayer(Layer* layer)
{
    if (layer != nullptr)
    {
        mLayers.push_back(layer);
    }
}

Layer* Map::getLayer(std::string const& name)
{
    for (std::size_t i = 0; i < mLayers.size(); i++)
    {
        if (mLayers.at(i) != nullptr)
        {
            if (mLayers.at(i)->getName() == name)
            {
                return mLayers.at(i);
            }
        }
    }
    return nullptr;
}

Layer* Map::getLayer(std::size_t const& id)
{
    if (id >= 0 && id < mLayers.size())
    {
        return mLayers.at(id);
    }
    return nullptr;
}

void Map::render(std::string const& name, sf::RenderTarget& target)
{
    for (std::size_t i = 0; i < mLayers.size(); i++)
    {
        if (mLayers.at(i) != nullptr)
        {
            if (mLayers.at(i)->getName() == name)
            {
                target.draw(*mLayers.at(i));
            }
        }
    }
}

void Map::render(std::size_t const& id, sf::RenderTarget& target)
{
    if (id >= 0 && id < mLayers.size())
    {
        if (mLayers.at(id) != nullptr)
        {
            target.draw(*mLayers.at(id));
        }
    }
}

void Map::render(sf::RenderTarget& target)
{
    for (std::size_t i = 0; i < mLayers.size(); i++)
    {
        if (mLayers.at(i) != nullptr)
        {
            target.draw(*mLayers.at(i));
        }
    }
}

} // namespace map
