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

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

} // namespace map
