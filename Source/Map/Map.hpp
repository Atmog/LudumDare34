#ifndef MAP_MAP_HPP
#define MAP_MAP_HPP

#include "Layer.hpp"

namespace map
{

class Map
{
    public:
        Map();

        void addLayer(Layer* layer);
        Layer* getLayer(std::string const& name);
        Layer* getLayer(std::size_t const& id);

        void render(std::string const& name, sf::RenderTarget& target);
        void render(std::size_t const& id, sf::RenderTarget& target);
        void render(sf::RenderTarget& target);

    protected:
        std::vector<Layer*> mLayers;
};

} // namespace map

#endif // MAP_MAP_HPP
