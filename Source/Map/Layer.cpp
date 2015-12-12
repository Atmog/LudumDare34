#include "Layer.hpp"

namespace map
{

Layer::Layer()
{
    setName("");
}

void Layer::setName(std::string const& name)
{
    mName = name;
}

std::string Layer::getName() const
{
    return mName;
}

sf::Vector2f Layer::getSizePx() const
{
    return sf::Vector2f(0.f,0.f);
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

} // namespace map
